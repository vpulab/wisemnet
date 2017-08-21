// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2013
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file describes a template to implement tracking algorithms. Currently only used by WiseCameraDPF
//  TODO: remove this template in future releases of WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#include <fstream>
#include "TMacControlMessage_m.h"
#include "WiseCameraSimplePeriodicTracker.h"
#include "WiseCameraSimplePeriodicTracker_m.h"

// For logging all the module information into baseline Castalia trace
#define BASE_TRACE trace() << "WISESPTRACKER: "

/*! Initialization of WiseCameraSimplePeriodicTracker class and getting of user-defined variables in omnetpp.ini file*/
void WiseCameraSimplePeriodicTracker::startup()
{
    BASE_TRACE << "STARTUP";

    //initialize WiseCameraApplication class
	WiseCameraApplication::startup();

	//read user-defined variables in omnetpp.ini
	network_ready = false;//network is not ready until the comms&vision graphs are discovered
	sampling_time = par("sampling_time");
	sample_lifetime = par("sample_lifetime");
	if (sample_lifetime < 0 || sample_lifetime > sampling_time)
		sample_lifetime = sampling_time;
	sampling_end2start_time = sampling_time - sample_lifetime;

	//set the initial status to check for network being ready
	fsm_state = FSM_WAIT_GRAPHS;
    setTimer(ALARM_WAIT_GRAPH, 0);

	//initialize superclass
	at_startup();

	BASE_TRACE << "sampling_time=" << sampling_time << " sample_lifetime=" << sample_lifetime << " sampling_end2start_time=" << sampling_end2start_time;

	_time_atsample = 0;
    _time_pkt_processing = 0;
	_bytesTX = 0;
    _bytesRX = 0;

    _state_str = create_ALGO_FSM_str();
    _alarm_str = create_ALGO_ALARM_str();
    tracking_step_counter = -1;
}

/*! Specific operations to perform when finishing the tracker*/
void WiseCameraSimplePeriodicTracker::finishSpecific()
{
    at_finishSpecific();

    WiseCameraApplication::finishSpecific();
}

/*!
 * Callback function for responding to alarms generated for sync the tracker operations
 * @param[in]  index  Type of alarm
 */
void WiseCameraSimplePeriodicTracker::timerFiredCallback(int index)
{
    BASE_TRACE << "ALARM: " << _alarm_str[index]<< endl;

    switch (index)
    {
        case ALARM_WAIT_GRAPH:
            BASE_TRACE << "ALARM_WAIT_GRAPH";
            fsm_tracker(INVALID);
            break;
        case ALARM_SENSOR_SAMPLE:
            BASE_TRACE << "ALARM_SENSOR_SAMPLE";
            requestSensorReading();
            break;
        case ALARM_END_SAMPLE_PERIOD:
            BASE_TRACE << "ALARM_END_SAMPLE_PERIOD";
            fsm_tracker(INVALID);
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
void WiseCameraSimplePeriodicTracker::fsm_tracker(sample_type_t t, bool restart)
{
    double e1=0;

	if (restart){
	    BASE_TRACE << "FSM : RESTART";
		fsm_state = FSM_INIT;
	}

	switch(fsm_state)
	{
	    //wait for graph completion
	case FSM_WAIT_GRAPHS:
            BASE_TRACE << "FSM : FSM_WAIT_GRAPHS";

            if (check_graph_completion()) {
                BASE_TRACE << "BOTH_GRAPHS_COMPLETED (net ready,  maxFOV=" << max_NeighboursFOV << ") Send reset to net...";
                fsm_state = FSM_INIT;

                //send reset message to all network nodes (ie sync of sampling instants)
                WiseSimplePeriodicTrackerMessage *pkt = new WiseSimplePeriodicTrackerMessage("CONTROL:reset", APPLICATION_PACKET);
                pkt->setType(WISE_NEIGHBOUR_RESET);
                toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);
                //sendDirectApplicationMessage(pkt, BROADCAST_NETWORK_ADDRESS); //No direct as management of DirectApplicationMessage is in the superclass
                fsm_tracker(INVALID); //restart the FSM
            }
            else
                setTimer(ALARM_WAIT_GRAPH, 2);//both graphs are not ready (wait 1sec and repeat checking)
	        break;
	case FSM_INIT:
            BASE_TRACE << "FSM : INIT";
            //std::cout <<  "node=" << self << " FSM : INIT";;
            tracking_step_counter = 0;
            at_tracker_init();
            detections.clear();
            BASE_TRACE << "SETTING ALARM TO START IN " << ceil(simTime().dbl())-simTime().dbl() << "secs";
            setTimer(ALARM_SENSOR_SAMPLE, ceil(simTime().dbl())-simTime().dbl()); //we wait to get the first sample as there may be pending msgs in the net
            fsm_state = FSM_WAIT_FIRST_SAMPLE;
            break;
        case FSM_WAIT_FIRST_SAMPLE:
            BASE_TRACE << "FSM : WAIT_FIRST_SAMPLE";

            if (t == DETECTIONS)
                make_measurements(detections);
 	    
	        //measure execution time
            e1 = cv::getTickCount();
            at_tracker_first_sample();
            _time_atsample = (cv::getTickCount() - e1)/ cv::getTickFrequency();

            setTimer(ALARM_END_SAMPLE_PERIOD, sample_lifetime);
            fsm_state = FSM_WAIT_END_FIRST_SAMPLE;
            break;

        case FSM_WAIT_END_FIRST_SAMPLE:
            BASE_TRACE << "FSM : WAIT_END_FIRST_SAMPLE";
            //std::cout <<  "FSM : WAIT_END_FIRST_SAMPLE" << endl;
            if (at_tracker_end_first_sample() == true) {

            detections.clear();

            //compute energy consumption
            resMgr->computeEnergyPRO(tracking_step_counter,_time_atsample,_time_pkt_processing);
            resMgr->computeEnergyCOM(tracking_step_counter,_bytesTX,_bytesRX);
            resMgr->logCurrentData();

            _time_atsample = 0;
            _time_pkt_processing = 0;
            _bytesTX = 0;
            _bytesRX = 0;

            setTimer(ALARM_SENSOR_SAMPLE, sampling_end2start_time);
            fsm_state = FSM_WAIT_SAMPLE;
            }
            break;
        case FSM_WAIT_SAMPLE:
            BASE_TRACE << "FSM : WAIT_SAMPLE (step = " << tracking_step_counter << ")";
            //std::cout <<  "FSM : WAIT__SAMPLE" << endl;

            if (t == DETECTIONS)
                make_measurements(detections);
	
            //measure execution time
            e1 = cv::getTickCount();
            at_tracker_sample();
            _time_atsample = (cv::getTickCount() - e1)/ cv::getTickFrequency();

            setTimer(ALARM_END_SAMPLE_PERIOD, sample_lifetime);
            fsm_state = FSM_WAIT_END_SAMPLE;
            break;
        case FSM_WAIT_END_SAMPLE:
            BASE_TRACE << "FSM : WAIT_END_SAMPLE (step = " << tracking_step_counter << ")";

            if (at_tracker_end_sample() == true) {
                detections.clear();
	    
                //compute energy consumption
                resMgr->computeEnergyPRO(tracking_step_counter,_time_atsample,_time_pkt_processing);
                resMgr->computeEnergyCOM(tracking_step_counter,_bytesTX,_bytesRX);
                resMgr->logCurrentData();

                _time_atsample = 0;
                _time_pkt_processing = 0;
                _bytesTX = 0;
                _bytesRX = 0;

                setTimer(ALARM_SENSOR_SAMPLE, sampling_end2start_time);
                fsm_state = FSM_WAIT_SAMPLE;
            }
            break;
	}
}

/*!
 * Function to check the completion of the discovery process for the communications and vision graph for all nodes
 */
bool WiseCameraSimplePeriodicTracker::check_graph_completion()
{
    //check for all the network nodes if they are completed
    for (int i = 0; i < n_nodes; i++) {
        cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseCameraSimplePeriodicTracker *c = check_and_cast<WiseCameraSimplePeriodicTracker*>(m);

        if (c->neighbourDiscoverCOMCompleted == false || c->neighbourDiscoverFOVCompleted == false)
            return false;
    }

    network_ready = true;//both graphs ready, indicate network is ready

    //compute the maximum number of neighbors in the network
    max_NeighboursFOV = 0;
    for (int i = 0; i < n_nodes; i++) {
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");
            WiseCameraSimplePeriodicTracker *c = check_and_cast<WiseCameraSimplePeriodicTracker*>(m);

            if (c->neighborsFOV.size() > max_NeighboursFOV);
                max_NeighboursFOV = c->neighborsFOV.size();
    }

    //if we arrive here, it is because all graph discovery stages are completed
    return true;
}

/*!
 * Function to process packets coming from the network
 * @param[in]  p  Packet
 * @param[in]  src string defining the source node
 * @param[in]  rssi ???
 * @param[in]  lqi ???
 */
void WiseCameraSimplePeriodicTracker::fromNetworkLayer(WiseApplicationPacket *pkt, const char *src, double rssi, double lqi)
{
    //avoid further data processing if node is not ready
    if (!network_ready){
       BASE_TRACE << "Received pkt and node is not ready";
       return;
    }

    //Reinitialization request
    if (pkt->getTypeNeighbour() == WISE_NEIGHBOUR_RESET){

        //reinitialize only if we have not initialized yet in the same step
        if (tracking_step_counter == -1){
            fsm_state = FSM_INIT;
            fsm_tracker(INVALID);
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
void WiseCameraSimplePeriodicTracker::handleSensorReading(WiseCameraMessage *m)
{
    string type = m->getCameraSampleType();
    sample_type_t t;
    if (type == "WiseCameraDetections") {
        t = DETECTIONS;
        const WiseCameraDetectionsMessage *s = check_and_cast<const WiseCameraDetectionsMessage*>(m);

        unsigned len = s->getDetectionsArraySize();
        for (unsigned i = 0; i < len; i++) {
            WiseTargetDetection d = s->getDetections(i);
            detections.push_back(d);
            if (!d.valid)
                continue;
            BASE_TRACE << "Detection: BB(" << d.bb_x_tl << " " << d.bb_y_tl << " " << d.bb_x_br << " " << d.bb_y_br << ") extBB(" << d.ext_bb_x_tl << " " << d.ext_bb_y_tl << " " << d.ext_bb_x_br << " " << d.ext_bb_y_br << ") trueBB(" << d.true_bb_x_tl << " " << d.true_bb_y_tl << " " << d.true_bb_x_br << " " << d.true_bb_y_br << ")";/**/;
        }
    } else {
        opp_error("\n[WiseCameraSimplePeriodicTracker]: WiseCameraMessage is of invalid type");
    }
    //compute energy for sensing
    resMgr->computeEnergySEN(tracking_step_counter);
    fsm_tracker(t);
}

/*!
 * Function to send a message to a specific neighbors using the communication graph.
 *
 * @param[in] m Message to be sent
 * @param[in] dst String indicating the ID of the neighbor
 */
void WiseCameraSimplePeriodicTracker::send_message(WiseApplicationPacket *m, const std::string &dst)
{
    map<string, bool>::const_iterator n = connectivity_map_comms.find(dst);
    if (n == connectivity_map_comms.end())
        return; // overlapping fov but NOT a neighbour
    // This messages will trigger the event (simulation) AFTER other messages pending at the SAME sim_time
    // with prio < 10 (the default prio=0)
    m->setSchedulingPriority(10);
    toNetworkLayer(m, dst.c_str()); // Unicast send

    //update counter
    _bytesTX = _bytesTX + m->getByteLength();
}

/*!
 * Function to send a broadcast message to all neighbors so communication graph is used (ie, maximum coverage of radio signal).
 *
 * @param[in] m Message to be sent
 */
void WiseCameraSimplePeriodicTracker::send_message(WiseApplicationPacket *m)
{
    send_message(m, 0);
}

void WiseCameraSimplePeriodicTracker::send_message(WiseApplicationPacket *m, double delay)
{
    // This messages will trigger the event (simulation) AFTER other pending messages that at the SAME
    // sim_time have prio < 10 (the default prio=0)
    //m->setSchedulingPriority(10);

    // Broadcast send
    toNetworkLayer(m->dup(), "-1",delay);
    delete m;

   //update counter
    _bytesTX = _bytesTX + m->getByteLength();
}

/*!
 * Function to send a message to neighbors in the communication graph.
 *
 * @param[in] m Message to be sent
 */
int WiseCameraSimplePeriodicTracker::send_messageNeighboursCOM(WiseApplicationPacket *m, double base_delay)
{
    int nNodes = 0;
    double delay = self * base_delay;

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
               toNetworkLayer(m->dup(), (*n).first.c_str(), delay);
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
int WiseCameraSimplePeriodicTracker::send_messageNeighboursFOV(WiseApplicationPacket *m, double base_delay, double step_delay)
{
    int nNodes = 0;
    //double delay = self * base_delay;
    double delay = base_delay;

    if (neighborsFOV.size() == 0)
        return -1;//no neighbors

    m->setTypeNeighbour(WISE_NEIGHBOUR_FOV);

    map<string, bool>::const_iterator n;
    for (n = connectivity_map_fov.begin(); n != connectivity_map_fov.end(); ++n)
        if ((*n).second == true)
           if (atoi((*n).first.c_str()) != this->self)
           {
               nNodes++;
               BASE_TRACE << "SEND PKT to neigbFOV node=" << (*n).first.c_str();
               if (base_delay==0)
                   delay = 0;
               else
                   delay +=step_delay;

               toNetworkLayer(m->dup(), (*n).first.c_str(),delay);
           }

    //update counter
    _bytesTX = _bytesTX + nNodes*m->getByteLength();

    delete m;
    return 1;
}

/*!
 * From the WiseBaseApplication class.
 *
 * @param[in] c Message received
 */
void WiseCameraSimplePeriodicTracker::handleMacControlMessage(cMessage *c)
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



