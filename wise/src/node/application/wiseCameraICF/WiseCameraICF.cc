// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the ICF tracker for single targets described in:
//      Kamal et al, "Information Weighted Consensus Filters and Their Application
//      in Distributed Camera Networks", IEEE TAC 2013
//      http://ieeexplore.ieee.org/document/6576197/
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#include "WiseCameraICF.h"
#include "TMacControlMessage_m.h"
#include "WiseUtils.h"
#include <cmath>

Define_Module(WiseCameraICF);

//Structures/variables for logging
#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE trace() << "WISEICF: "

ofstream WiseCameraICF::logger; //mylog.txt
std::ofstream *writerICF=NULL;  //other logs

#define MULTILOG(str)        \
{                            \
    LOGGER << str << endl;   \
    BASE_TRACE << str;       \
}

/*! Class destructor */
WiseCameraICF::~WiseCameraICF()
{
    if (writerICF) {
        writerICF->close();
        delete writerICF;
        writerICF=NULL;
    }
}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraICF::at_startup()
{
    // Called upon simulation start-up
    MULTILOG("START-UP");

    readParameters();//Read parameters
    initStructures();//create internal structures

    if (writerICF == NULL)
        writerICF = new ofstream();

    //Create streams for logging results
    if(collectAccuracyStats) {
        std::ostringstream os;
        os << "res/ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".dat";

        if (!writerICF->is_open()){
            writerICF->open(os.str().c_str());
            *writerICF << "# procNoiseCov=" << procNoiseCov << " measNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << endl;
            *writerICF << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc,ResultsDelay" << endl;
            *writerICF << "#t_sim\tt_step\tNID\tTID\tZx\tZy\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc\tDelay" << endl;
        }
    }

    if(collectPowerStats) {
        std::ostringstream os1;
        os1 << "res/ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max
              << "_CPU" << std::setfill('0') << std::setw(3) << resMgr->getPROClk()/1e5 << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user()
              << ".res" << std::setfill('0') << std::setw(3) << self;
        resMgr->initLogger(os1.str().c_str(), self, self); //energy-consumption log
    }

    if(collectNetworkStats) {
        std::ostringstream os2;
        os2 << "res/ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".rad";
        radioModule->initLogger(os2.str().c_str());
    }

    if (!logger.is_open())
            logger.open("myLog.txt");

    LOGGER << "procNoiseCov=" << procNoiseCov << " measNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << " share=" << share << endl;
}

/*! Read parameters of MTT_ICF*/
void WiseCameraICF::readParameters()
{
    // Access related-module parameters (read number of targets)
    cModule *network = getParentModule()->getParentModule();
    n_targets = network->par("numPhysicalProcesses");

    //ICF Filter settings
    procNoiseCov = hasPar("procNoiseCov") ? par("procNoiseCov") : 0.1;
    measNoiseCov = hasPar("measNoiseCov") ? par("measNoiseCov") : 1e-1;

    // Consensus settings
    iter_max = hasPar("iter_max") ? par("iter_max") : 20;
    alpha = hasPar("alpha") ? par("alpha") : 0.1;
    share = hasPar("share")?par("share").stringValue() : "COM";

    collectNetworkStats = hasPar("collectNetworkStats")?par("collectNetworkStats").boolValue() : false;
    collectPowerStats = hasPar("collectPowerStats")?par("collectPowerStats").boolValue() : false;
    collectAccuracyStats = hasPar("collectAccuracyStats")?par("collectAccuracyStats").boolValue() : false;
}

/*! Initialization of structures for tracking targets*/
void WiseCameraICF::initStructures()
{
   dimS = DIM_STATE_T_4D;
   dimM = DIM_MEASUREMENT_T_2D;

   //status for each target
   camStatus.clear();
   camStatus.resize(n_targets);

   node_controls.clear();

   for (int tid = 0; tid < n_targets; tid++)
   {
       //create control data
       icf::node_ctrl_t ctrl(tid,n_nodes,icf::MAX_SIZE_BUFFER,dimS);

       //determine the neighbourgs to share (FOV or COM graphs)
       share.compare("FOV") == 0 ? ctrl.n_neighbourgs = neighborsFOV.size(): ctrl.n_neighbourgs = neighborsCOM.size();

       node_controls.push_back(ctrl);//store in list
   }
   LOGGER << "Created resources (" << node_controls.size() << " structs) for "<< n_targets << " targets, " << n_nodes << " nodes and " << icf::MAX_SIZE_BUFFER << " max iterations to buffer" << endl;
}

/*!
 * This function defines the behavior to specific alarms generated by the WiseCameraICF
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseCameraICF::at_timer_fired(int index)
{
    MULTILOG("ALARM: " << _alarm_str[index]);

    switch (index) {
      case ALARM_WAIT_NEGOTIATION:
          //go to the FSM to check completion of negotiation
          fsm_tracker(INVALID);
          break;
      default:
          LOGGER << "WRONG ALARM!!: index=" << index << endl;
    }
}

/*!
 * From the WiseBaseApplication class. This function allows to generate messages corresponding to TX packets
 *
 * @param[in] c Message received
 */
void WiseCameraICF::handleMacControlMessage(cMessage *c)
{
    TMacControlMessage *m;
    try {
        m = check_and_cast<TMacControlMessage*>(c);
    } catch (exception& e) {
        // Ignore the control message if it is not from TMac
        return;
    }
    if (m->getType() == TMAC_TX_SUCCESS)
    {
        MULTILOG("packet SENT with T-MAC: retries = " << m->getTxRetries() << "  (max " << m->getMaxTxRetries() << ")");
    }
    else
        if (m->getType() == TMAC_TX_FAILURE)
            MULTILOG("packet NOT SENT with T-MAC: max retries reached (" << m->getMaxTxRetries() << ")");
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by ICFs.
 *
 *  Called to properly read the sample: when a new sample is available a measurement has to be created from it
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseCameraICF::make_measurements(const vector<WiseTargetDetection>&dt)
{
    // reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
    vector<const WiseTargetDetection*> ordered;
    ordered.resize(n_targets, NULL);

    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        ordered[d->target_id] = &(*d);

    // get data from ordered list of 'WiseTargetDetections' and copy data to 'state_t' and 'measurement_t' lists
    for (int tid = 0; tid < n_targets && tid < (int)dt.size(); tid++)
    {
        if (ordered[tid] == NULL) {
            node_controls[tid].detection_miss = true;
            continue;
        }
        const WiseTargetDetection &d = *(ordered[tid]);
        if (!d.valid) {
            ICFs[tid].z = cv::Mat::zeros(dimM, 1, CV_64F);
            node_controls[tid].detection_miss = true;
            continue;
        }

        //measurements + Gaussian noise
        ICFs[tid].z.at<double>(0)  = (d.ext_bb_x_tl + d.ext_bb_x_br) / 2 + normal(0, measNoiseCov, 0);
        ICFs[tid].z.at<double>(1)  = (d.ext_bb_y_tl + d.ext_bb_y_br) / 2 + normal(0, measNoiseCov, 0);
        node_controls[tid].detection_miss = false;
        LOGGER << "tid=" << tid << " -> MAKE MEASUREMENT z=" << format(mat2vec(ICFs[tid].z), cv::Formatter::FMT_DEFAULT) << endl;
    }

    //copy the real positions in the ground-truth lists
    for (int tid = 0; tid < n_targets; tid++) {
        const WiseTargetDetection &d = *(ordered[tid]);
        ICFs[tid].xgt.at<double>(0) = (d.true_bb_x_tl + d.true_bb_x_br) / 2;
        ICFs[tid].xgt.at<double>(1) = (d.true_bb_y_tl + d.true_bb_y_br) / 2;
    }
}

/*!
 * Init resources for ICF processing. Declared in base class WiseCameraSimplePeriodicTracker.
 */
void WiseCameraICF::at_tracker_init()
{
    ICFs.clear();

    // ICF filters for each target..
    for (int tid = 0; tid < n_targets; tid++)
    {
       //create ICF filter
       icf::ICF_t icf(dimS,dimM,procNoiseCov,measNoiseCov,n_nodes);
       ICFs.push_back(icf); //store in list

       //update the neighbourgs to share (FOV or COM graphs)
       icf::node_ctrl_t& ctrl = node_controls[tid];
       share.compare("FOV") == 0 ? ctrl.n_neighbourgs = neighborsFOV.size(): ctrl.n_neighbourgs = neighborsCOM.size();
    }
    LOGGER << "Created resources (" << ICFs.size() << " ICF filters) for "<< n_targets << " targets, " << n_nodes << " nodes and " << icf::MAX_SIZE_BUFFER << " iterations" << endl;

}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraICF::at_tracker_first_sample()
{
	// Called when the first sample (image) is ready
	MULTILOG("FIRST SAMPLE");
	
	//find the maximum neighborg degree
	max_neigb_network = 0;
	for (int i = 0; i < n_nodes; i++) {

	    cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseCameraICF *c = check_and_cast<WiseCameraICF*>(m);

        if (share.compare("FOV") == 0){
            if (c->neighborsFOV.size() > (unsigned int)max_neigb_network)
                max_neigb_network = c->neighborsFOV.size();
        }
        else{
            if (neighborsCOM.size() > (unsigned int)max_neigb_network)
                max_neigb_network = neighborsCOM.size();
        }
    }

	//initialize targets with ground-truth data
	 for (int tid = 0; tid < n_targets; tid++){

	    icf::ICF_t &icf = ICFs[tid];
	    icf.initICFstate(ICFs[tid].xgt);

        node_controls[tid].initialized = true;
        node_controls[tid].first_start_time = SIMTIME_DBL(simTime());

        LOGGER << "tid=" << tid << " -> INIT x_=" <<  mat2vec(icf.x_) << " xgt=" << mat2vec(ICFs[tid].xgt) << endl;
    }

	//do processing
	return at_tracker_sample();
}

/*!
 * ICF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraICF::at_tracker_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
	MULTILOG("END FIRST SAMPLE");

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_tracker_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, ICF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraICF::at_tracker_sample()
{
    // Called when a new sample (image) is ready
    MULTILOG("AT TRACKER SAMPLE");
    tracking_step_counter++;

    // NOTE: Measurement has been made through the make_measurements() method and is available in the measurement vector
    for (int tid = 0; tid < n_targets; tid++)
    {
        camStatus[tid] = icf::COLLABORATION; //flag to indicate that the camera is busy doing consensus

        //check if there is consensus under progress
        if (node_controls[tid].iter_counter > 0){
            LOGGER << "Start consensus without ending previous iter > curr=" << node_controls[tid].iter_counter << " max=" << iter_max << endl;
            return false;
        }
        else
            LOGGER << "tid=" << tid << " -> PROCESS SAMPLE t=" <<  tracking_step_counter << endl;

        //record initial time for consensus
        node_controls[tid].start_time = simTime().dbl();

        //compute internal information vector & matrix
        ICFs[tid].prepData(node_controls[tid].detection_miss);

        //start consensus iterations
        consensusStart(tid);
    }
    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseCameraICF::at_tracker_end_sample()
{
	// Called when a new sample (image) is no longer valid
    MULTILOG("END NEW SAMPLE");

	 //check if the camera is doing consensus for any target
	int camStatusTotal=0;
	for (int tid = 0; tid < n_targets; tid++)
	    if (camStatus[tid] == icf::INACTIVE)
	        camStatusTotal++;

    if (camStatusTotal != n_targets) {
        LOGGER << "node not ready (own," << camStatusTotal << "/" << n_targets <<" targets done)" << endl;
        setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
        return false;
    }
    else
        LOGGER << "node ready (own," << camStatusTotal << "/" << n_targets <<" targets done)" << endl;


    /*for (int tid = 0; tid < n_targets; tid++) {
        icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
                //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration
        int c=0;
        for (int i=0; i < n_nodes; i++)
            if(ctrl.nb_data_buffer[0].nb_data[i].end_collaboration == true)
                c++;
        if (c!=ctrl.n_neighbourgs)
        {
            LOGGER << "node not ready (own, waiting for COLLABORATION END)" << c << "/"<< ctrl.n_neighbourgs << endl;
            setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
            return false;
        }
    }*/

    if (_dummy_comms==false) {
            //perform some additional checking at network level since 'real wireless' may desynchronize nodes
            // TODO: implement a protocol to sync the end of the consensus iteration
            for (int i = 0; i< n_nodes; i++)
            if (i!= self) {
                cModule *m = getParentModule()->getParentModule(); // m=SN
                m = m->getSubmodule("node", i)->getSubmodule("Application");
                WiseCameraICF*c = check_and_cast<WiseCameraICF*>(m);

                camStatusTotal=0;
                for (int tid = 0; tid < n_targets; tid++)
                    if (c->camStatus[tid] == icf::INACTIVE)
                        camStatusTotal++;

                if (camStatusTotal != n_targets)  {
                    LOGGER << "node not ready (netcheck)" << camStatusTotal << "/" << n_targets <<" targets done)" << endl;
                    setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
                    return false;
                }
            }
        }


        //restart 'busy' state of other cameras
        for (int tid = 0; tid < n_targets; tid++) {
            icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
            //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration
            for (int i=0; i < n_nodes; i++)
                ctrl.nb_data_buffer[0].nb_data[i].end_collaboration = false;
        }/**/

    LOGGER << "node ready" << endl;
    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it calls consensusProcess function to initiate a round of consensus when needed
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraICFMessage type)
 */
void WiseCameraICF::process_network_message(WiseApplicationPacket *pkt)
{
    double e2=0,e1 = cv::getTickCount();
    int i=0,c=0, index=-1;

    WiseCameraICFMsg *m = check_and_cast<WiseCameraICFMsg*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    MULTILOG("RX from " << ctl.source << ". Packet content: [ tid=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << " ]");

    //source node and target IDs of recv packet
    int node = atoi(ctl.source.c_str());
    int tid = m->getTargetID();
    icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'

    switch (m->getPktType()){
        case ICF_COLLABORATION_DATA1:
        {
            LOGGER << "Collaboration..." << endl;

            // store recv data in buffer
            if(ctrl.storeDataInBuffer((int)m->getIterationStep(), node, m) == -1)
                LOGGER << "ERROR BUFFER!!" << endl;

            //check matching of iteration number between node and recv data
            if (m->getIterationStep() != ctrl.iter_counter)
                LOGGER << "WRONG ITERATION!! (curr=" <<  ctrl.iter_counter << " rcv=" << m->getIterationStep() << ")" << " tid="<<tid << endl;

            // get data for current consensus iteration of the node
            index = ctrl.findIndexInBuffer((int)ctrl.iter_counter); // Index of the buffer

            //count the number of received data from nodes (to start consensus if all data has been recv)
            std::vector <int> missing;
            for (i=0; i < n_nodes; i++)
                if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true){
                    c++;
                }
                else{

                    map<string, bool>::const_iterator n;
                    for (n = connectivity_map_comms.begin(); n != connectivity_map_comms.end(); ++n)
                        if ((*n).second == true)
                            if (atoi((*n).first.c_str()) != this->self)
                            if (atoi((*n).first.c_str()) == i)
                                  missing.push_back(i);
                }

            //compute the consensus if we have all neighbor's data
            if (c==ctrl.n_neighbourgs)
                consensusProcess(tid);
            else
                LOGGER << "Waiting for " << ctrl.n_neighbourgs-c << "/" << ctrl.n_neighbourgs << print_vector(missing) << "for consensus k=" << ctrl.iter_counter << " tid="<<tid << endl;
          break;
        }

        case ICF_COLLABORATION_END:
            if ((int)m->getTrackingCount() == tracking_step_counter)
            {
                ctrl.nb_data_buffer[0].nb_data[node].end_collaboration=true;
                LOGGER << " COLLABORATION END RECEIVED from node=" << node << " tid="<<tid<< endl;
            }
            else
                LOGGER << " Late??? COLLABORATION END RECEIVED from node=" << node << " tid="<<tid << " t_curr=" << tracking_step_counter << " t_rcv="<<(int)m->getTrackingCount()<< endl;
            break;

        default:
            LOGGER << " UNKNOWN PACKET!!"<< endl;
            break;
    }

    e2 = cv::getTickCount();
   _time_pkt_processing += (e2 - e1)/ cv::getTickFrequency(); //CPU time for processing packets
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraICF::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
    // Called when a DirectApplication Message is received
    MULTILOG("HANDLE DIRECT APPLICATION MESSAGE");

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}

/*!
 * Function to start the consensus iterations. It sends data to neighbors
 * (if any). If there are not, then it estimates target position.
 *
 * @param[in] tid Target ID of the associated ICF structures
 */
void WiseCameraICF::consensusStart(int tid)
{
    MULTILOG("CONSENSUS START");
    node_controls[tid].iter_counter=1;

    if (node_controls[tid].n_neighbourgs > 0 && iter_max > 0)
        sendICFmessage(tid); // send estimation to neighbors
    else
    {
        //perform final state estimation if there are no neighbors or maximum iterations reached
        ICFs[tid].estimate_and_predict_state();
        logResult(tid);//save data
    }
}

/*!
 * Function to process a consensus iteration after receiving data
 * from all neigborgs.
 *
 * @param[in] tid Target ID of the associated ICF structures
 * @param[in] k Number of the current iteration
 */
void WiseCameraICF::consensusProcess(int tid)
{
    icf::node_ctrl_t &ctrl = node_controls[tid];
    MULTILOG(" CONSENSUS for k=" <<  ctrl.iter_counter);

    int index = ctrl.findIndexInBuffer(ctrl.iter_counter); // Index of the buffer

    //combine estimations of neighbors
    ICFs[tid].update_state_neighbors(ctrl.nb_data_buffer[index].nb_data,alpha,ctrl.n_neighbourgs,max_neigb_network);

   //restart status of received data
   for (int i=0; i < n_nodes; i++)
       ctrl.nb_data_buffer[index].nb_data[i].rcv_data = false;

   //free the buffer position for further usage
   ctrl.nb_data_buffer[index].iter_buffer = -1;

   //continue consensus if not exceed the max iterations
   ctrl.iter_counter++;

   //send message to neighbors (posterior state OR collaboration end)
   sendICFmessage(tid);

   //check if data for next consensus round is already buffer
   checkNextConsensusRound(tid);

   if (ctrl.iter_counter >  iter_max) {
       ICFs[tid].estimate_and_predict_state(); //perform final state estimation when maximum iterations reached
       logResult(tid);//save data
       ctrl.iter_counter=0;//return to initial status
   }
   else{
       ICFs[tid].estimate_state();
       LOGGER << "tid=" << tid << " -> PAR RESULT x_=" <<  mat2vec(ICFs[tid].x_) <<" x=" <<  mat2vec(ICFs[tid].x) <<" err=" <<  setprecision(3) << ICFs[tid].compute_error() << endl;
   }
}



/*!
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseCameraICF::sendICFmessage(int tid)
{
    //create message & copy data
    std::ostringstream os;
    os << "ICF: node=" << self << " tid=" << tid << " t=" << tracking_step_counter << " k=" << node_controls[tid].iter_counter;

    WiseCameraICFMsg *pkt = new WiseCameraICFMsg(os.str().c_str(), APPLICATION_PACKET);
    pkt->setTrackingCount(tracking_step_counter); //current step counter
    pkt->setIterationStep(node_controls[tid].iter_counter); //data for new iteration
    pkt->setTargetID(tid); //target id
    pkt->setType(WISE_APP_NORMAL); //normal APP for the network

    //send message containing the posterior state estimation OR collaboration end
    if (node_controls[tid].iter_counter > iter_max){
        LOGGER << "tid=" << tid << " -> SENDING MSG to FOVs to END consensus" << endl;
        pkt->setByteLength(icf::ICFpkt_size[ICF_COLLABORATION_END]);
        pkt->setPktType(ICF_COLLABORATION_END);
        camStatus[tid] = icf::INACTIVE;//flag to indicate that the node has finished consensus
    }
    else {
        LOGGER << "tid=" << tid << " -> SENDING MSG to FOVs for k=" << node_controls[tid].iter_counter << endl;
        pkt->setICFv(ICFs[tid].v); //information vector
        pkt->setICFV(ICFs[tid].V); //information matrix
        pkt->setByteLength(icf::ICFpkt_size[ICF_COLLABORATION_DATA1]);
        pkt->setPktType(ICF_COLLABORATION_DATA1);
    }

    // Distribute the data among neighbors using the FOV or COM graphs.
    //  NOTE: For real wireless channels, it is better to send unicast messages so we can keep control of missing TX packets
    //        If "send_message(pkt)" is used, some packets may be lost without being noticed.
    if (share.compare("FOV") == 0) {
        pkt->setTypeNeighbour(WISE_NEIGHBOUR_FOV); //type defined in "WiseCameraSimplePeriodicTracker.msg"
        send_messageNeighboursFOV(pkt);//unicast message
    }
    else{
        pkt->setTypeNeighbour(WISE_NEIGHBOUR_COM);
        send_messageNeighboursCOM(pkt);//unicast message
    }

    // We assume a broadcast packet for FOVs/COMs in dummy channels so count TX packets only once
    if (_dummy_comms == true)
        _bytesTX = _bytesTX - (node_controls[tid].n_neighbourgs-1)*pkt->getByteLength();
    return 1;
}

void WiseCameraICF::checkNextConsensusRound(int tid)
{
    icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'

    // get data for current consensus iteration of the node
    int index = ctrl.findIndexInBuffer(ctrl.iter_counter); // Index of the buffer

    int c=0;
    for (int i=0; i < n_nodes; i++)
        if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true){
            c++;
        }
    //compute the consensus if we have all neighbor's data
    if (c==ctrl.n_neighbourgs){
        LOGGER << "tid=" << tid << " -> DATA for k=" << node_controls[tid].iter_counter << " already available" << endl;
        consensusProcess(tid);
    }
}
/*!
 * Write results in txt files
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraICF::logResult(int tid)
{
    double delay = simTime().dbl()-node_controls[tid].start_time;
    double err = ICFs[tid].compute_error();
    ICFs[tid].errAcc += err;

    MULTILOG("tid=" << tid <<" t="<< tracking_step_counter << " FINAL -> x=" << mat2vec(ICFs[tid].x) << " J=" << cv::trace(ICFs[tid].J).val[0]
              << " x_=" <<  mat2vec(ICFs[tid].x_) << "," << "] J_=" << cv::trace(ICFs[tid].J_).val[0]
              << " z=" << mat2vec(ICFs[tid].z) << " gt=" << mat2vec(ICFs[tid].xgt));

    *writerICF << std::setprecision(6) << simTime().dbl() << "\t" << tracking_step_counter << "\t" << self << "\t" << tid  << "\t" <<
            setprecision(4) << ICFs[tid].z.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].z.at<double>(1) << "\t" <<
            setprecision(4) << ICFs[tid].x_.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].x_.at<double>(1) << "\t" <<
            setprecision(4) << ICFs[tid].x.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].x.at<double>(1) << "\t" <<
            setprecision(4) << ICFs[tid].xgt.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].xgt.at<double>(1) << "\t" <<
            setprecision(4) << err << "\t" << setprecision(4) <<  ICFs[tid].errAcc << "\t" << delay << endl;
}
