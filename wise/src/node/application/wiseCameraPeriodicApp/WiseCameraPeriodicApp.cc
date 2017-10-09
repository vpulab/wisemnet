// *****************************************************************************************
// Copyright (C) 2017 Juan C. SanMiguel and Andrea Cavallaro
// You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
// license (see the attached LICENSE_WISE file).
//
// This file is part of the WiseMnet simulator
//
// Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// Please cite the following reference when publishing results obtained with WiseMnet:
//   J. SanMiguel & A. Cavallaro,
//   "Networked Computer Vision: the importance of a holistic simulator",
//   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
// *****************************************************************************************

/**
 * \file WiseCameraPeriodicApp.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseCameraPeriodicApp.cc class
 * \version 1.4
 */

#include <fstream>
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h>
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h>//packet format
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h> // constants & types
#include <wise/src/utils/WiseUtils.h>
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

#define perr_app(m) error("\n[WiseCamPerApp]:\n " m) // Error messages from the application layer
#define perr(m) error(m)                             // Error messages from the node itself

static map<int,std::string> create_FSM_APP_str();//mapping <integer,string> for easy printing of messages in console
static map<int,std::string> create_ALARM_APP_str();//mapping <integer,string> for easy printing of messages in console
static map<int,cv::Scalar> create_color_list(); //mapping <integer,color> for easy printing of targets

/*! Initialization of WiseCameraPeriodicApp class and getting of user-defined variables in omnetpp.ini file*/
void WiseCameraPeriodicApp::startup()
{
    WISE_DEBUG_31("WiseCamPerApp::startup()");

    //variable initialization
   _network_ready = false; //wait to discovery the comms&vision graphs
   _fsm_state = FSM_UNDEFINED;

   //read display settings
   _displayWinScale = par("displayWinScale");   //factor to scale all displayed windows
   _pause_execution = par("pause_execution");   //flag to stop each execution for visualization
   _pause_executionID = par("pause_executionID");   //flag to stop each execution for visualization
   _pause_place_GUI = par("pause_place_GUI");   //flag to pause the program initialization to place GUIs

   //read other parameters/flags
   _logResourceData = par("logResourceData"); //flag to enable the logger for resources employed

	WiseCameraApp::startup();   //WiseCameraApp class
	startup_sensing();          //settings for sensing
	startup_gtruth();           //settings for ground-truth
	startup_logs();             //settings for loggers (resources,...)
	at_startup();               //initialize the application layer of derived classes

   //set timers
   setTimer(ALARM_WAIT_GRAPH, 0); //check immediately the completion of neighbor discovery
   setTimer(ALARM_SENSOR_SAMPLE, 0); //request immediately sensing of data

   //initialize strings to print the state & alarms of the application layer
   _state_str = create_FSM_APP_str();
   _alarm_str = create_ALARM_APP_str();
   _colorList = create_color_list();
}

/*! Specific operations to initialize the sensing mode and associated resources*/
void WiseCameraPeriodicApp::startup_sensing()
{
    //sensing parameters - capturing frequency
    _sampling_time = par("sampling_time");      // frequency for sensing (ie capture frames)
    _sample_lifetime = par("sample_lifetime");  // duration of each sampled data (ie frames)

    resMgr->setSENFrameRate(1/_sampling_time); //set framerate in resource manager (capped if above max capabilities)
    _sampling_time = 1/resMgr->getSENFrameRate(); //get updated framerate from resource manager

    if (_sample_lifetime < 0 || _sample_lifetime > _sampling_time)
        _sample_lifetime = _sampling_time;
    _sampling_end2start_time = _sampling_time - _sample_lifetime; // time to wait between capturing frames and their lifespan (usually zero)

    //sensing parameters - capturing mode
    std::string tmp = par("sensing_mode").stringValue();
    if (tmp.compare("IDEAL") == 0)       _sensing_mode = SEN_IDEAL; //frames captured each 'sampling_time', does not consider processing time
    if (tmp.compare("REAL_PERIOD") == 0) _sensing_mode = SEN_REAL_PERIOD; //frames captured each 'sampling_time', considers processing time (effect: frames captured and not processed)
    if (tmp.compare("REAL_DEMAND") == 0) _sensing_mode = SEN_REAL_DEMAND; //frames captured after processing, considers processing time (effect: skipped frames without being captured)
    _lastSenTime = 0;

    //initialize variables - data received from sensing module
    _buf.frameRate = -1;
    _buf.curFrame = -1;
    _buf.detections.clear();

    _databuf_ready = false;

    WISE_DEBUG_31("WiseCamPerApp::startup_sensing()" << " sampling_time=" << _sampling_time << " sample_lifetime=" << _sample_lifetime << " sensing mode=" << _sensing_mode);
}

/*! Specific operations to initialize the support of ground-truth data*/
void WiseCameraPeriodicApp::startup_gtruth()
{
    WISE_DEBUG_31("WiseCamPerApp::startup_gtruth()");

    // filename with ground-truth data
    _filenameGT = par("filenameGT").stringValue();
    cModule *parent = getParentModule();
    const char *physicalProcessName= parent->getParentModule()->par("physicalProcessName");

    //load other ground-truth settings if applicable
    if (_filenameGT.size()==0)
    {
        WISE_DEBUG_31("WiseCamPerApp::\t Cam "<<_camID<<": ground-truth file not defined (type "<< physicalProcessName<<")");
       _gtreader = NULL;
       _show_gtruth = false;
    }
    else
    {
        WISE_DEBUG_31("WiseCamPerApp::\t Cam "<<_camID<<": ground-truth file defined: " << _filenameGT << " (type "<< physicalProcessName<<")");
        _formatGT= par("formatGT").stringValue();
        _show_gtruth = par("show_gtruth").boolValue();
        _gtreader = new WiseGTreader();
        _gtreader->parsefile(_filenameGT.c_str(),_formatGT.c_str());
    }
    if(_show_gtruth)
    {
        _winGT << "Cam "<<_camID<<": Ground-truth Detections"<< std::endl;
        cv::namedWindow(_winGT.str().c_str());
        cv::Mat temp = cv::Mat::zeros(480,640,CV_32F);
        std::cout << "Please place the GUI and press any key..." << std::endl;
        cv::imshow(_winGT.str().c_str(),temp);
        cv::waitKey(0);
    }
}

/*! Initialization of logs for submodules*/
void WiseCameraPeriodicApp::startup_logs()
{
    WISE_DEBUG_31("WiseCamPerApp::startup_logs()");

    char subdir[]="res"; //relative directory to save generated files (relative to the location of the *.ini file)
    char prefix[]="Node";//Prefix for the filenames
    std::ostringstream os;

    if(_logResourceData)
    {
        //initialize log file
       os << subdir <<"/"<<prefix << self << "_" << applicationID << "_n" << std::setfill('0') << std::setw(3) << self;
       os << "_CPU" << std::setfill('0') << std::setw(5) << resMgr->getPROClk()/1e5;
       os << "_SEN" << std::setfill('0') << std::setw(5) << resMgr->getSENClk()/1e5;
       //os << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate(); //real framerate achieved by the sensing module
       os << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user(); //user-defined framerate

       os << "_";
       resMgr->initLogger(get_time_filename(os.str().c_str(), ".res").c_str(), self, _camID);
    }
    else
        resMgr->initIDs(self,_camID);
}
/*! Specific operations to perform when finishing the tracker*/
void WiseCameraPeriodicApp::finishSpecific()
{
    WISE_DEBUG_31("WiseCamPerApp::finishSpecific()");

    //clear buffer
    _buf.detections.clear();
    _buf.frame.release();

    cv::destroyAllWindows();

    at_finishSpecific();
}

/*!
 * Callback function for responding to alarms generated for sync the tracker operations
 * @param[in]  index  Type of alarm
 */
void WiseCameraPeriodicApp::timerFiredCallback(int index)
{
    WISE_DEBUG_31("WiseCamPerApp::timerFiredCallback() ALARM: " << _alarm_str[index]);

    switch (index)
    {
        //check comms graph completion
        case ALARM_WAIT_GRAPH:
            if (check_graph_completion()) {
                WISE_DEBUG_31("WiseCamPerApp::\tBOTH_GRAPHS_COMPLETED (network_ready=true,  max_neigbourgFOV=" << _max_neighborsFOV << " max_neigbourgCOM=" << _max_neighborsCOM << ") Sending reset to network...");

                // Send reset message to all network nodes for synchronization
                // NOTE: we cannot use "sendDirectApplicationMessage" since it is implemented in the superclass
                WiseCameraPeriodicAppPacket*pkt = new WiseCameraPeriodicAppPacket("CONTROL:reset", APPLICATION_PACKET);
                pkt->setSubTypeNeighbor(WISE_NEIGHBOR_RESET);
                toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);

                _fsm_state = FSM_INIT;
                fsm_app(INVALID); //restart the FSM to start sensing+processing+comms
                }
            else
            {
                WISE_DEBUG_31("WiseCamPerApp::\tWaiting to discover neighbors");
                setTimer(ALARM_WAIT_GRAPH, 0.1);//both graphs are not ready (wait 0.1sec and repeat checking)
            }
            break;

        //request data from sensing module
        case ALARM_SENSOR_SAMPLE:
            requestSensorReading(); //request the reading of the default sensor with index=0
            if (_sensing_mode == SEN_REAL_PERIOD || _sensing_mode == SEN_IDEAL)
                setTimer(ALARM_SENSOR_SAMPLE,_sampling_time);
            break;

        //do processing of sensed data
        case ALARM_PROCESS_SAMPLE:
            fsm_app(_buf.type);
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
void WiseCameraPeriodicApp::fsm_app(sample_type_t t, bool restart)
{
    WISE_DEBUG_31("WiseCamPerApp::fsm_app() FSM STATE: " << _state_str[_fsm_state] << "(step = " << _step_counter << ")");

	if (restart)
		_fsm_state = FSM_INIT;

	switch(_fsm_state)
	{
	    case FSM_UNDEFINED:
	        setTimer(ALARM_PROCESS_SAMPLE,_sample_lifetime);
            break;

        //state for initialization
        case FSM_INIT:
            _step_counter = 0;
            at_init();
            _fsm_state = FSM_WAIT_SAMPLE;//next FSM state
            setTimer(ALARM_PROCESS_SAMPLE, 0);//timer to process data
            break;

        //state to wait for a new sample (sensed data)
        case FSM_WAIT_SAMPLE:
            //check for new data to process
            if (_databuf_ready == true){

                //make measurements if we deal with "moving points"
                if (t == DETECTIONS)
                    make_measurements(_buf.detections);

                _fsm_state = FSM_PROCESS_SAMPLE;//next FSM state
                setTimer(ALARM_PROCESS_SAMPLE, 0);//timer to process data
            }
            else
                setTimer(ALARM_PROCESS_SAMPLE,_sample_lifetime/10); //wait and check again for new data
            break;

        //state to process data
        case FSM_PROCESS_SAMPLE:
        {
            this->_time_pkt_processing = 0;
            this->_time_atsample = 0;
            _databuf_ready = false; //data is being processed
            _step_counter++;

            //show ground-truth
            if (_show_gtruth)
                display_gtruth();

            //measure execution time
            double e1 = cv::getTickCount(); //initial time
            at_sample();
            _time_atsample = (cv::getTickCount() - e1)/ cv::getTickFrequency();

            if (_pause_execution)
                if(_pause_executionID == self || _pause_executionID == -1)
                    cv::waitKey(0);

            _fsm_state = FSM_PROCESS_END_SAMPLE;//next FSM state
            fsm_app(INVALID);//execute the new state of the FSM
            break;
        }
        case FSM_PROCESS_END_SAMPLE:
            if (at_end_sample() == true) {

                _bytesTXround = _bytesTX - _bytesTXprev;//TX bytes in the last iteration/round
                _bytesRXround = _bytesRX - _bytesRXprev;//RX bytes in the last iteration/round
                _bytesTXprev = _bytesTX;
                _bytesRXprev = _bytesRX;

                //compute energy consumption (processing)
                resMgr->computeEnergyPRO(_buf.curFrame,_time_atsample,_time_pkt_processing);

                //compute energy consumption (comms)
                resMgr->computeEnergyCOM(_buf.curFrame,_bytesTXround,_bytesRXround);
                resMgr->logCurrentData();

                if (!isSink)
                    resMgr->displayCurrentData();

                //compute the delay due to time spent in processing
                double delay = resMgr->getSpentTime();
                if (delay < 0 || _sensing_mode == SEN_IDEAL)
                   delay=0;
                setTimer(ALARM_PROCESS_SAMPLE,delay);

                //request new data (frame) if we are operating in the "ON_DEMAND" sensing mode
                //"REAL_PERIOD" and "IDEAL" capturing modes are handled in 'timerFiredCallback' function
                if (_sensing_mode == SEN_REAL_DEMAND)
                    setTimer(ALARM_SENSOR_SAMPLE,0);

                _fsm_state = FSM_WAIT_SAMPLE;//next FSM state
            }
            break;
	}
}

/*! Function to check the completion of the discovery process for the communications and vision graph for all nodes */
bool WiseCameraPeriodicApp::check_graph_completion()
{
    WISE_DEBUG_31("WiseCamPerApp::check_graph_completion() called");

    //check for all the network nodes if they are completed
    for (int i = 0; i < n_nodes; i++) {
        cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseCameraPeriodicApp *c = check_and_cast<WiseCameraPeriodicApp*>(m);

        if (c->_neighborDiscoverCOMCompleted == false || c->_neighborDiscoverFOVCompleted == false)
            return false;
    }

    _network_ready = true;//both graphs ready, indicate network is ready

    //compute the maximum number of neighbors in the network
    this->_max_neighborsFOV = 0;
    this->_max_neighborsCOM = 0;

    for (int i = 0; i < n_nodes; i++) {
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");
            WiseCameraPeriodicApp *c = check_and_cast<WiseCameraPeriodicApp*>(m);

            if (c->_neighborsFOVoverlap.size() > _max_neighborsFOV)
                _max_neighborsFOV = c->_neighborsFOVoverlap.size();

            if (c->_neighborsCOM.size() > _max_neighborsCOM)
                _max_neighborsCOM = c->_neighborsCOM.size();
    }

    //we arrive here when graph discovery is completed
    return true;
}

/*
 * \brief Method to handle data received from the network
 *
 * Method to handle data received from the network for application-specific
 * processing. This method extends the "fromNetworkLayer" method of the WiseBaseApp class.
 *
 * \param rcvPacket Packet received with the data and metadata
 * \param src   Identifier of the source node
 * \param rssi  Received Signal Strength Indication
 * \param lqi   Link Quality Indicator
 *
 * \see https://en.wikipedia.org/wiki/Received_signal_strength_indication
 * \see https://en.wikipedia.org/wiki/Link_quality_analysis
 */
void WiseCameraPeriodicApp::fromNetworkLayer(WiseBaseAppPacket *pkt, const char *src, double rssi, double lqi)
{
    WISE_DEBUG_31("WiseCamPerApp::fromNetworkLayer() called");

    //avoid further data processing if node is not ready
    if (!_network_ready){
       WISE_DEBUG_31("WiseCamPerApp::\tReceived packet and node is not ready yet");
       return;
    }

    //Reinitialization request
    if (pkt->getSubTypeNeighbor() == WISE_NEIGHBOR_RESET){

        //reinitialize only if we have not initialized yet in the same step
        if (_step_counter != 0){
            _fsm_state = FSM_INIT;
            fsm_app(INVALID);
            WISE_DEBUG_31("WiseCamPerApp::\tReceived init request from=" << string(src) << " -> Ready (YES)");
        }
        else
            WISE_DEBUG_31("WiseCamPerApp::\tReceived init request from=" << string(src) << " -> Already initiated (NO)");

        return;
    }

    //process packet from network
    double l = SIMTIME_DBL(simTime() - pkt->getApplicationInteractionControl().timestamp);
    WISE_DEBUG_31("WiseCamPerApp::\tRX packet:" " from=" << string(src) << " rssi=" << rssi << " lqi=" << lqi << " app2app_delay=" << l);
    process_network_message(pkt);//to be defined in the superclass
}

/*!
 * Function to handle messages coming from the SensorManager. It emulates the copying of sensed data (ie frames, detections)
 * in buffers making it usable for the application layer.
 * Currently two types of data can be sensed: detections (eg RFID tags) and frames (video streams)
 *
 * @param[in] m Message received with all the detections
 */
void WiseCameraPeriodicApp::handleSensorReading(WiseCameraMessage *m)
{
    WISE_DEBUG_31("WiseCamPerApp::handleSensorReading() called");

    string type = m->getCameraSampleType();
    double currSenTime=SIMTIME_DBL(simTime());

    //detections are stored in a variable named "detections"
    if (type == "WiseCameraDetections") {
       _buf.type = DETECTIONS;
       _buf.detections.clear();//we clear the buffer before placing new data

       const WiseCameraDetectionsMessage *s = check_and_cast<const WiseCameraDetectionsMessage*>(m);

       unsigned len = s->getDetectionsArraySize();
       for (unsigned i = 0; i < len; i++) {
           WiseTargetDetection d = s->getDetections(i);
           _buf.detections.push_back(d);
           if (!d.valid)
               continue;
           WISE_DEBUG_31("WiseCamPerApp::\tDetection: BB(" << d.bb_x_tl << " " << d.bb_y_tl << " " << d.bb_x_br << " " << d.bb_y_br << ") extBB(" << d.ext_bb_x_tl << " " << d.ext_bb_y_tl << " " << d.ext_bb_x_br << " " << d.ext_bb_y_br << ") trueBB(" << d.true_bb_x_tl << " " << d.true_bb_y_tl << " " << d.true_bb_x_br << " " << d.true_bb_y_br << ")");
       }
       _databuf_ready = true;
    }

    if (type == "WiseCameraVideo") {
        _buf.type = FRAMES;
        const WiseCameraVideoMessage *s = check_and_cast<const WiseCameraVideoMessage*>(m);

        //we check if the sensed data is new
        if (_buf.curFrame != s->getCurFrame())
        {
            _buf.curFrame = s->getCurFrame();//id of new frame
            _buf.frame = s->getFrame(); //new frame
            _buf.frameRateSRC = s->getFrameRateSRC(); //framerate of video file

            //energy consumption
            switch (_sensing_mode){
                case SEN_REAL_PERIOD:
                case SEN_IDEAL:
                    resMgr->computeEnergySEN(_buf.curFrame);
                    break;
                case SEN_REAL_DEMAND: {
                    double tidl = (currSenTime - _lastSenTime) - resMgr->getSENInfo().Tact[0];
                    if (tidl < 0)
                        tidl = 0;
                    resMgr->computeEnergySEN(_buf.curFrame,tidl);
                    break;
                }
                default:
                    resMgr->computeEnergySEN(_buf.curFrame);
                    break;
            }
            _databuf_ready = true;//already copied data
            WISE_DEBUG_31("WiseCamPerApp::\tRead Frame " << _buf.curFrame << " (Source@" << _buf.frameRateSRC << "fps)");
        }
    }
    if (type != "WiseCameraVideo" && type != "WiseCameraDetections")
        perr_app("\n[WiseCameraPeriodicApp]: WiseCameraMessage is of invalid type");

    _lastSenTime = SIMTIME_DBL(simTime());
}

/*
 * \brief Method to display ground-truth data using OpenCV HighGui
 */
void WiseCameraPeriodicApp::display_gtruth()
{
   WISE_DEBUG_31("WiseCamPerApp::display_gtruth() called");

   if (_buf.type != FRAMES)
       opp_error("\n[WISECAM]: error - not sensing frames\n ");
   cv::Mat frame;
   _buf.frame.copyTo(frame);

   //get the frame number and write it on the current frame
   stringstream ss;
   rectangle(frame, cv::Point(10, 2), cv::Point(100,20), cv::Scalar(255,255,255), -1);
   ss << _buf.curFrame;
   cv::putText(frame,  ss.str().c_str(), cv::Point(15, 15),cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

   //READ & DISPLAY DETECTIONS FROM GROUND-TRUTH
   std::map<int,std::vector<target_detection_t>> *alldets = _gtreader->getData();
   std::vector<target_detection_t> dets = (*alldets)[_buf.curFrame];

   for (int i=0;i<(int)dets.size();i++)
   {
       target_detection_t d = dets[i];
       cv::rectangle(frame, cv::Point(d.bb_x_tl,d.bb_y_tl),cv::Point(d.bb_x_br,d.bb_y_br), _colorList[d.target_id],2);

       stringstream str;
       str<<d.target_id;
       cv::putText(frame,str.str().c_str(),cv::Point(d.bb_x_tl, d.bb_y_tl-5),cv::FONT_HERSHEY_SIMPLEX, 0.5 , _colorList[d.target_id]);
       //cv::imshow(_winGT.str().c_str(),frame);
   }

   cv::Mat newFrame;
   cv::resize(frame,newFrame,cv::Size(frame.cols*_displayWinScale,frame.rows*_displayWinScale));
   cv::imshow(_winGT.str().c_str(),newFrame);
   cv::waitKey(1);
}

/*!
 * Function to send a message to a specific neighbors using the communication graph.
 *
 * @param[in] m Message to be sent
 * @param[in] dst String indicating the ID of the neighbor
 */
void WiseCameraPeriodicApp::send_message(WiseBaseAppPacket *m, const std::string &dst)
{
    WISE_DEBUG_31("WiseCamPerApp::send_message(m,dst) called");

    if (dst.compare (to_string(self)) == 0) {
        WISE_DEBUG_31("WiseCamPerApp::\tINTERNAL MESSAGE node=" << self);
        process_network_message(m); // internal message - no network
    }
    else {
        map<string, bool>::const_iterator n = _connectivity_map_comms.find(dst);
        if (n == _connectivity_map_comms.end())
            return; // overlapping fov but NOT a neighbour
        // This msg triggers the event (simulation) AFTER other msgs pending at the SAME sim_time with prio < 10 (default prio=0)
        m->setSchedulingPriority(10);
        toNetworkLayer(m->dup(), dst.c_str()); // Unicast send
    }
}

/*!
 * Function to send a broadcast message to all neighbors so communication graph is used (ie, maximum coverage of radio signal).
 *
 * @param[in] m Message to be sent
 */
void WiseCameraPeriodicApp::send_message(WiseBaseAppPacket *m)
{
    WISE_DEBUG_31("WiseCamPerApp::send_message(m) called");
    //JCS:originally not commented
    //map<string, bool>::const_iterator n = connectivity_map_comms.begin();

    // This msg triggers the event (simulation) AFTER other msgs pending at the SAME sim_time with prio < 10 (default prio=0)
    m->setSchedulingPriority(10);
    toNetworkLayer(m->dup(), "-1");// Broadcast send

    //internal message
    WISE_DEBUG_31("WiseCamPerApp::\tINTERNAL MESSAGE node=" << self);
    process_network_message(m);

    delete m;
}

/*!
 * Function to send a message to neighbors in the communication graph.
 *
 * @param[in] m Message to be sent
 */
int WiseCameraPeriodicApp::send_messageNeighboursCOM(WiseBaseAppPacket *m)
{
    WISE_DEBUG_31("WiseCamPerApp::send_messageNeighboursCOM(m) called");

    int nNodes = 0;
    if (_neighborsCOM.size() == 0)
           return -1;//no neighbors

    m->setSubTypeNeighbor(WISE_NEIGHBOR_COM);

    map<string, bool>::const_iterator n;
    for (n = _connectivity_map_comms.begin(); n != _connectivity_map_comms.end(); ++n)
        if ((*n).second == true)
           if (atoi((*n).first.c_str()) != this->self)
           {
               nNodes++;
               WISE_DEBUG_31("WiseCamPerApp::\tSEND PKT to COM neighbor node=" << (*n).first.c_str());
               toNetworkLayer(m->dup(), (*n).first.c_str());
           }

    delete m;
    return 1;
}

/*!
 * Function to send a message to neighbors in the vision graph.
 *
 * @param[in] m Message to be sent
 */
int WiseCameraPeriodicApp::send_messageNeighboursFOV(WiseBaseAppPacket *m)
{
    WISE_DEBUG_31("WiseCamPerApp::send_messageNeighboursFOV(m) called");

    if (_neighborsFOVoverlap.size() == 0)
        return -1;//no neighbors

    m->setSubTypeNeighbor(WISE_NEIGHBOR_FOV);

    map<string, bool>::const_iterator n;
    for (n = _connectivity_map_fov.begin(); n != _connectivity_map_fov.end(); ++n)
        if ((*n).second == true)
           if (atoi((*n).first.c_str()) != this->self)
           {
               WISE_DEBUG_31("WiseCamPerApp::\tSEND PKT to FOV neighbor node=" << (*n).first.c_str())
               toNetworkLayer(m->dup(), (*n).first.c_str());
           }

    delete m;
    return 1;
}

//mapping <integer,string> for easy printing of messages in console
static map<int,std::string> create_FSM_APP_str() {

   std::map<int,std::string> m;
   m.insert(std::make_pair(FSM_UNDEFINED, "FSM_UNDEFINED"));
   m.insert(std::make_pair(FSM_INIT, "FSM_INIT"));
   m.insert(std::make_pair(FSM_WAIT_SAMPLE, "FSM_WAIT_SAMPLE"));
   m.insert(std::make_pair(FSM_PROCESS_SAMPLE, "FSM_PROCESS_SAMPLE"));
   m.insert(std::make_pair(FSM_PROCESS_END_SAMPLE, "FSM_PROCESS_END_SAMPLE"));
   return m;
}

//mapping <integer,string> for easy printing of messages in console
static map<int,std::string> create_ALARM_APP_str() {

   std::map<int,std::string> m;
   m.insert(std::make_pair(ALARM_WAIT_GRAPH, "ALARM_WAIT_GRAPH"));
   m.insert(std::make_pair(ALARM_SENSOR_SAMPLE, "ALARM_SENSOR_SAMPLE"));
   m.insert(std::make_pair(ALARM_PROCESS_SAMPLE, "ALARM_PROCESS_SAMPLE"));
   return m;
}

//mapping <integer,color> for easy printing of targets
static map<int,cv::Scalar> create_color_list() {

   std::map<int,cv::Scalar> m;
   int Nmax = 50;//maximum number of colors
   cv::RNG rng(12345);//random number generator
   for (int i = 0; i < Nmax; i++)
       m.insert(std::make_pair(i, cv::Scalar(rng.uniform(0,255),rng.uniform(0, 255),rng.uniform(0, 255))));

   return m;
}
