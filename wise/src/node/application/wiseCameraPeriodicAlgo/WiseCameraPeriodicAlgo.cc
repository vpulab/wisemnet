// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the template for a periodic algorithm that provides an interface
//  to develop algorithms such as WiseCameraICF, WiseCameraKCF,...
//
//  This template iteratively performs the following operations (modeled as a finite-state-machine):
//          1. First performs sensing
//          2. Second processes the sensed data
//          3. Third performs communication with other cameras, if needed
//
//  This template provides also a synchronization in the network initialization
//          1. Set the running parameters of each camera (see the *.ini files)
//          2. Discovery of neighbors (i.e. cameras that can exchange data) by:
//              - FOV spatial overlap
//              - Communication range
//          3. Iterative sensing, processing & comms until the simulation is finished
//
//  Moreover, this template also provides synchronous/asynchronous sensing
//  by means of the parameter 'sensing_mode':
//          - _sensing_mode = IDEAL; //frames captured each 'sampling_time', does not consider processing time
//          - _sensing_mode = REAL_PERIOD; //frames captured each 'sampling_time', considers processing time
//          - _sensing_mode = REAL_DEMAND; //frames captured after processing, considers processing time
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#include <fstream>
#include "TMacControlMessage_m.h"

#include "WiseCameraPeriodicAlgo.h"
#include "WiseCameraPeriodicAlgoPacket_m.h"
#include "WiseUtils.h"

#define perr_app(m) opp_error("\n[Application]:\n " m)

// For logging all the module information into baseline Castalia trace
#define BASE_TRACE trace() << "WISEALGO: "

/*! Initialization of WiseCameraPeriodicAlgo class and getting of user-defined variables in omnetpp.ini file*/
void WiseCameraPeriodicAlgo::startup()
{
    BASE_TRACE << "STARTUP";

    //initialize WiseCameraApplication class
	WiseCameraApplication::startup();

	//network is not ready until the comms&vision graphs are discovered
	_network_ready = false;

	//sensing parameters - capturing frequency
	_sampling_time = par("sampling_time"); // frequency to capture frames
	_sample_lifetime = par("sample_lifetime"); // duration of each frame
	if (_sample_lifetime < 0 || _sample_lifetime > _sampling_time)
		_sample_lifetime = _sampling_time;
	_sampling_end2start_time = _sampling_time - _sample_lifetime; // time to wait between capturing frames and their lifespan (usually zero)

	//sensing parameters - capturing mode
	std::string tmp = par("sensing_mode").stringValue();
	if (tmp.compare("IDEAL") == 0)       _sensing_mode = IDEAL; //frames captured each 'sampling_time', does not consider processing time
	if (tmp.compare("REAL_PERIOD") == 0) _sensing_mode = REAL_PERIOD; //frames captured each 'sampling_time', considers processing time
	if (tmp.compare("REAL_DEMAND") == 0) _sensing_mode = REAL_DEMAND; //frames captured after processing, considers processing time
	_lastSenTime = 0;

    //resource manager - set framerate and update "sampling_time" if above sensing capabilities
    resMgr->setSENFrameRate(1/_sampling_time); //frames per second

    if (_frameRate != 1/resMgr->getSENFrameRate()){ //check if "sampling_time" is above max sensing framerate
        _sampling_time = 1/resMgr->getSENFrameRate();
        if (_sample_lifetime < 0 || _sample_lifetime > _sampling_time)
            _sample_lifetime = _sampling_time;
        _sampling_end2start_time = _sampling_time - _sample_lifetime;
    }

    //initialize variables - data received from sensing module
    _frameRate = -1; _resizeSRC=-1,_curFrame = -1;
    _resize = par("resize"); // resize data to increase processing speed

    //initialize variables - counters for communication TX/RX data
    _bytesRX=0; _bytesTX=0;_bytesTXtot=0;_bytesTXtot=0;

    //initialize variables - display results
    _show_results = par("show_results");

    //initialize variables - strings to print the state & alarms of the application layer
   _state_str = create_ALGO_FSM_str();
   _alarm_str = create_ALGO_ALARM_str();

    //initialize superclass - the application layer
    at_startup();

    //initialize network connectivity - discover neighbors for being ready to process
    _fsm_state = FSM_UNDEFINED;
    setTimer(ALARM_WAIT_GRAPH, 0);

    //initialize sensing (equal for all sensing modes)
    _databuf_ready = false;
    setTimer(ALARM_SENSOR_SAMPLE, 0);

	BASE_TRACE << "sampling_time=" << _sampling_time << " sample_lifetime=" << _sample_lifetime << " sensing mode=" << _sensing_mode;
}

/*! Specific operations to perform when finishing the tracker*/
void WiseCameraPeriodicAlgo::finishSpecific()
{
    //destroy superclass - the application layer
    at_finishSpecific();

	WiseCameraApplication::finishSpecific();
}

/*!
 * Callback function for responding to alarms generated for sync the tracker operations
 * @param[in]  index  Type of alarm
 */
void WiseCameraPeriodicAlgo::timerFiredCallback(int index)
{
    switch (index)
    {
        BASE_TRACE << "ALARM: " << _alarm_str[index];

        //check comms graph completion
        case ALARM_WAIT_GRAPH:

            //BASE_TRACE << "ALARM_WAIT_GRAPH";
            if (check_graph_completion()) {
                BASE_TRACE << "BOTH_GRAPHS_COMPLETED (network_ready=true,  max_neigbourgFOV=" << max_NeighboursFOV << ") Sending reset to network...";

                // Send reset message to all network nodes for synchronization
                // NOTE: we cannot use "sendDirectApplicationMessage" since it is implemented in the superclass
                WiseCameraPeriodicAlgoPacket *pkt = new WiseCameraPeriodicAlgoPacket("CONTROL:reset", APPLICATION_PACKET);
                pkt->setType(WISE_NEIGHBOUR_RESET);
                toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);

                _fsm_state = FSM_INIT;
                fsm_algo(INVALID); //restart the FSM to start sensing+processing+comms
                }
            else
                setTimer(ALARM_WAIT_GRAPH, 0.25);//both graphs are not ready (wait 0.25sec and repeat checking)
            break;

        //request data from sensing module
        case ALARM_SENSOR_SAMPLE:
            requestSensorReading();
            if (_sensing_mode == REAL_PERIOD || _sensing_mode == IDEAL)
                setTimer(ALARM_SENSOR_SAMPLE,_sampling_time);
            break;

        //do processing of sensed data
        case ALARM_PROCESS_SAMPLE:
            fsm_algo(INVALID);
            break;
        default:
            at_timer_fired(index);
    }
}

/*!
 * Function in charge of managing the states of the fsm (updating and performing the desired operations)
 * @param[in]  t  Type of sample received by the tracker from the SensorManager (used depending on the current state)
 * @param[in]  restart  Boolean value to restart the tracker fsm and for going to the initial state = FSM_INIT.
 */
void WiseCameraPeriodicAlgo::fsm_algo(sample_type_t t, bool restart)
{
    BASE_TRACE << "FSM STATE: " << _state_str[_fsm_state] << "(step = " << _step_counter << ")";

	if (restart)
		_fsm_state = FSM_INIT;

	switch(_fsm_state)
	{
	    case FSM_UNDEFINED:
	        setTimer(ALARM_PROCESS_SAMPLE,_sample_lifetime);
            break;

        case FSM_INIT:
            _step_counter = 0;
            at_init();
            _fsm_state = FSM_WAIT_SAMPLE;
            if (isSink == false)
                setTimer(ALARM_PROCESS_SAMPLE, 0);
            break;

        case FSM_WAIT_SAMPLE:
            //check for new data to process
            if (_databuf_ready == true){
                _fsm_state = FSM_PROCESS_SAMPLE;
                setTimer(ALARM_PROCESS_SAMPLE, 0);//process data
            }
            else
                setTimer(ALARM_PROCESS_SAMPLE,_sample_lifetime/10); //wait and check again for new data
            break;

        case FSM_PROCESS_SAMPLE:
        {
            double e1;//time;
            _databuf_ready = false; //data is being processed
            _step_counter++;

            //measure execution time
            e1 = cv::getTickCount();
            at_sample();
            _time_atsample = (cv::getTickCount() - e1)/ cv::getTickFrequency();

            //show current image
            if(_show_results) {
                cv::imshow(_winName.str().c_str(), _frame);
                cv::waitKey(10);
            }

            _fsm_state = FSM_PROCESS_END_SAMPLE;
            fsm_algo(INVALID);
            break;
        }
        case FSM_PROCESS_END_SAMPLE:
            if (at_end_sample() == true) {

                //compute energy consumption
                resMgr->computeEnergyPRO(_curFrame,_time_atsample,_time_pkt_processing);

                //compute the delay due to time spent in processing
                double delay = resMgr->getSpentTime();
                if (delay < 0 || _sensing_mode == IDEAL)
                   delay=0;
                setTimer(ALARM_PROCESS_SAMPLE,delay);

                //request new data (frame) if we are operating in the "ON_DEMAND" sensing mode
                //"REAL_PERIOD" and "IDEAL" capturing modes are handled in 'timerFiredCallback' function
                if (_sensing_mode == REAL_DEMAND)
                    setTimer(ALARM_SENSOR_SAMPLE,0);

                _fsm_state = FSM_WAIT_SAMPLE;
                resMgr->computeEnergyCOM(_curFrame,_bytesTX,_bytesRX);
                resMgr->logCurrentData();

                _bytesTX = 0;
                _bytesRX = 0;
            }
            break;
	}
}

/*!
 * Function to check the completion of the discovery process for the communications and vision graph for all nodes
 */
bool WiseCameraPeriodicAlgo::check_graph_completion()
{
    //check for all the network nodes if they are completed
    for (int i = 0; i < n_nodes; i++) {
        cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseCameraPeriodicAlgo *c = check_and_cast<WiseCameraPeriodicAlgo*>(m);

        if (c->neighbourDiscoverCOMCompleted == false || c->neighbourDiscoverFOVCompleted == false)
            return false;
    }

    _network_ready = true;//both graphs ready, indicate network is ready

    //compute the maximum number of neighbors in the network
    max_NeighboursFOV = 0;
    for (int i = 0; i < n_nodes; i++) {
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");
            WiseCameraPeriodicAlgo *c = check_and_cast<WiseCameraPeriodicAlgo*>(m);

            if (c->neighborsFOV.size() > max_NeighboursFOV);
                max_NeighboursFOV = c->neighborsFOV.size();
    }

    //we arrive here when graph discovery is completed
    return true;
}

/*!
 * Function to process packets coming from the network
 * @param[in]  p  Packet
 * @param[in]  src string defining the source node
 * @param[in]  rssi ???
 * @param[in]  lqi ???
 */
void WiseCameraPeriodicAlgo::fromNetworkLayer(WiseApplicationPacket *pkt, const char *src, double rssi, double lqi)
{
    //avoid further data processing if node is not ready
    if (!_network_ready){
       BASE_TRACE << "Received pkt and node is not ready";
       return;
    }

    //Reinitialization request
    if (pkt->getTypeNeighbour() == WISE_NEIGHBOUR_RESET){

        //reinitialize only if we have not initialized yet in the same step
        if (_step_counter != 0){
            _fsm_state = FSM_INIT;
            fsm_algo(INVALID);
            BASE_TRACE << "Received init request from=" << string(src) << " -> Ready (YES)";
        }
        else
            BASE_TRACE << "Received init request from=" << string(src) << " -> Already initiated (NO)";

        return;
    }

    //Received data
    _bytesRX = _bytesRX + pkt->getByteLength();

    //process packet from network
    ApplicationInteractionControl_type ctl = pkt->getApplicationInteractionControl();
    double l = SIMTIME_DBL(simTime() - ctl.timestamp);
    BASE_TRACE << "RX packet:" " from=" << string(src) << " rssi=" << rssi << " lqi=" << lqi << " app2app_delay=" << l;
    process_network_message(pkt);//to be defined in the superclass
}

/*!
 * Function to process the readings/detections obtained by the SensorManager. Currently it copies the list of detections provided
 *  into the local list of the tracker.
 *
 * @param[in] m Message received with all the detections
 */
void WiseCameraPeriodicAlgo::handleSensorReading(WiseCameraMessage *m)
{
    string type = m->getCameraSampleType();
    double currSenTime=SIMTIME_DBL(simTime());

    if (type == "WiseCameraDetections") {
       //t = DETECTIONS;
       const WiseCameraDetectionsMessage *s = check_and_cast<const WiseCameraDetectionsMessage*>(m);

       unsigned len = s->getDetectionsArraySize();
       for (unsigned i = 0; i < len; i++) {
           WiseTargetDetection d = s->getDetections(i);
           detections.push_back(d);
           if (!d.valid)
               continue;
           BASE_TRACE << "Detection: BB(" << d.bb_x_tl << " " << d.bb_y_tl << " " << d.bb_x_br << " " << d.bb_y_br << ") extBB(" << d.ext_bb_x_tl << " " << d.ext_bb_y_tl << " " << d.ext_bb_x_br << " " << d.ext_bb_y_br << ") trueBB(" << d.true_bb_x_tl << " " << d.true_bb_y_tl << " " << d.true_bb_x_br << " " << d.true_bb_y_br << ")";
       }
    }

    if (type == "WiseCameraVideo") {
            //t = FRAMES;
            const WiseCameraVideoMessage *s = check_and_cast<const WiseCameraVideoMessage*>(m);

            //we check if the sensed data is new
            if (_curFrame != s->getCurFrame())
            {
                _curFrame = s->getCurFrame();

                /*if (_resize != -1)
                    cv::resize(s->getFrame(),_frame,cv::Size(),_resize,_resize);
                else
                    _frame = s->getFrame();*/

                sen_info_t::sen_model_s newSz = resMgr->getSENInfo().model;
                if (s->getFrame().rows*s->getFrame().cols != newSz.rows*newSz.cols)
                {
                    _scaleRows = (double)newSz.rows/(double)s->getFrame().rows;
                    _scaleCols = (double)newSz.cols/(double)s->getFrame().cols;
                    cv::resize(s->getFrame(),_frame, cv::Size(newSz.cols,newSz.rows));
                }
                else
                    _frame = s->getFrame();

                _frameRateSRC = s->getFrameRateSRC();
                //_resizeSRC = s->getResize();
                //resMgr->setSENFrameSize(_frame.rows,_frame.cols,_frame.channels(),_resize);

                //energy consumption
                switch (_sensing_mode){
                    case REAL_PERIOD:
                    case IDEAL:
                        resMgr->computeEnergySEN(_curFrame);
                        break;
                    case REAL_DEMAND: {
                        double tidl = (currSenTime - _lastSenTime) - resMgr->getSENInfo().Tact[0];
                        if (tidl < 0)
                            tidl = 0;
                        resMgr->computeEnergySEN(_curFrame,tidl);
                        break;
                    }
                    default:
                        resMgr->computeEnergySEN(_curFrame);
                        break;
                }
                _databuf_ready = true;
                BASE_TRACE << "Read Frame " << _curFrame << " (Source@" << _frameRateSRC << "fps)";
            }
    }
    if (type != "WiseCameraVideo" && type != "WiseCameraDetections")
        opp_error("\n[WiseCameraPeriodicAlgo]: WiseCameraMessage is of invalid type");

    _lastSenTime = SIMTIME_DBL(simTime());
}

/*!
 * Function to send a message to a specific neighbors using the communication graph.
 *
 * @param[in] m Message to be sent
 * @param[in] dst String indicating the ID of the neighbor
 */
void WiseCameraPeriodicAlgo::send_message(WiseApplicationPacket *m, const std::string &dst)
{
    if (dst.compare (to_string(self)) == 0) {
            BASE_TRACE << "INTERNAL MESSAGE node=" << self << endl;
            process_network_message(m); // internal message - no network
    }
    else {
        map<string, bool>::const_iterator n = connectivity_map_comms.find(dst);
        if (n == connectivity_map_comms.end())
            return; // overlapping fov but NOT a neighbour
        // This msg triggers the event (simulation) AFTER other msgs pending at the SAME sim_time with prio < 10 (default prio=0)
        m->setSchedulingPriority(10);
        toNetworkLayer(m->dup(), dst.c_str()); // Unicast send

        //update counter
        _bytesTX = _bytesTX + m->getByteLength();
    }
}

/*!
 * Function to send a broadcast message to all neighbors so communication graph is used (ie, maximum coverage of radio signal).
 *
 * @param[in] m Message to be sent
 */
void WiseCameraPeriodicAlgo::send_message(WiseApplicationPacket *m)
{
    //JCS:originally not commented
    //map<string, bool>::const_iterator n = connectivity_map_comms.begin();

    // This msg triggers the event (simulation) AFTER other msgs pending at the SAME sim_time with prio < 10 (default prio=0)
    m->setSchedulingPriority(10);
    toNetworkLayer(m->dup(), "-1");// Broadcast send

    //internal message
    BASE_TRACE << "INTERNAL MESSAGE node=" << self << endl;
    process_network_message(m);

    //update counter
    _bytesTX = _bytesTX + m->getByteLength();

    delete m;
}

/*!
 * Function to send a message to neighbors in the communication graph.
 *
 * @param[in] m Message to be sent
 */
int WiseCameraPeriodicAlgo::send_messageNeighboursCOM(WiseApplicationPacket *m)
{
    int nNodes = 0;
    if (neighborsCOM.size() == 0)
           return -1;//no neighbors

    m->setTypeNeighbour(WISE_NEIGHBOUR_COM);

    map<string, bool>::const_iterator n;
    for (n = connectivity_map_comms.begin(); n != connectivity_map_comms.end(); ++n)
        if ((*n).second == true)
           if (atoi((*n).first.c_str()) != this->self)
           {
               nNodes++;
               BASE_TRACE << " SEND PKT to COM neighbor node=" << (*n).first.c_str();
               toNetworkLayer(m->dup(), (*n).first.c_str());
           }

    //update counter
    _bytesTX = _bytesTX + nNodes*m->getByteLength();

    delete m;
    return 1;
}

/*!
 * Function to send a message to neighbors in the vision graph.
 *
 * @param[in] m Message to be sent
 */
int WiseCameraPeriodicAlgo::send_messageNeighboursFOV(WiseApplicationPacket *m)
{
    if (neighborsFOV.size() == 0)
        return -1;//no neighbors

    m->setTypeNeighbour(WISE_NEIGHBOUR_FOV);

    map<string, bool>::const_iterator n;
    for (n = connectivity_map_fov.begin(); n != connectivity_map_fov.end(); ++n)
        if ((*n).second == true)
           if (atoi((*n).first.c_str()) != this->self)
           {
               BASE_TRACE << "SEND PKT to neigbFOV node=" << (*n).first.c_str();
               toNetworkLayer(m->dup(), (*n).first.c_str());
           }

    //update counter
    //_bytesTX = _bytesTX + nNodes*m->getByteLength();//unicast messages
    _bytesTX = _bytesTX + m->getByteLength();//broadcast messages

    delete m;
    return 1;
}

/*!
 * From the WiseBaseApplication class.
 *
 * @param[in] c Message received
 */
void WiseCameraPeriodicAlgo::handleMacControlMessage(cMessage *c)
{
    TMacControlMessage *m;
    try {
        m = check_and_cast<TMacControlMessage*>(c);
    } catch (exception& e) {
        // Ignore the control message if it is not from TMac
        return;
    }
    if (m->getType() == TMAC_TX_SUCCESS)
        BASE_TRACE << "packet SENT with T-MAC: retries = " << m->getTxRetries() << "  (max " << m->getMaxTxRetries() << ")";
    else
        if (m->getType() == TMAC_TX_FAILURE)
            BASE_TRACE << "packet NOT SENT with T-MAC: max retries reached (" << m->getMaxTxRetries() << ")";
}
