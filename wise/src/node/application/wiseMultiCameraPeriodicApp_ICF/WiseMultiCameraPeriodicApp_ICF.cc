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
 * \file WiseMultiCameraPeriodicApp_ICF.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseMultiCameraPeriodicApp_ICF class
 * \version 1.4
 */
#include <wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF.h>
#include <wise/src/world/gui/opencv/WiseGuiWorldOpencv.h> //class to print data/targets in the ground-plane
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

Define_Module(WiseMultiCameraPeriodicApp_ICF);//register module in simulator

std::ofstream *writerICF=NULL;  //additional log for tracking data

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseMultiCameraPeriodicApp_ICF::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppICF::at_startup()");

    readParameters();//Read parameters
    initStructures();//create internal structures

    if (writerICF == NULL)
        writerICF = new ofstream();

    //Create streams for logging results
    if(_collectAccuracyStats) {
        std::ostringstream os;
        os << base_out_path.c_str() << "ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << _n_targets << "_I" << std::setfill('0') << std::setw(2) << _iter_max << ".dat";

        if (!writerICF->is_open()){
            writerICF->open(os.str().c_str());
            *writerICF << "# _procNoiseCov=" << _procNoiseCov << " _measNoiseCov=" << _measNoiseCov << " iter_max=" << _iter_max << " alpha=" << _alpha << endl;
            *writerICF << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc,ResultsDelay" << endl;
            *writerICF << "#t_sim\tt_step\tNID\tTID\tZx\tZy\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc\tDelay" << endl;
        }
    }

    if(_collectPowerStats) {
        std::ostringstream os1;
        os1 << base_out_path.c_str() << "ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << _n_targets << "_I" << std::setfill('0') << std::setw(2) << _iter_max
              << "_CPU" << std::setfill('0') << std::setw(3) << resMgr->getPROClk()/1e5 << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user()
              << ".res" << std::setfill('0') << std::setw(3) << self;
        resMgr->initLogger(os1.str().c_str(), self, _camID); //energy-consumption log
    }

    if(_collectNetworkStats) {
        std::ostringstream os2;
        os2 << base_out_path.c_str() << "ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << _n_targets << "_I" << std::setfill('0') << std::setw(2) << _iter_max << ".rad";
        radioModule->initLogger(os2.str().c_str());
    }

    WISE_DEBUG_32("WiseCamPerAppICF::\t procNoiseCov=" << _procNoiseCov << " measNoiseCov=" << _measNoiseCov << " iter_max=" << _iter_max << " alpha=" << _alpha << " share=" << _share);
}

/*! Read parameters of MTT_ICF*/
void WiseMultiCameraPeriodicApp_ICF::readParameters()
{
    WISE_DEBUG_32("WiseCamPerAppICF::readParameters()");

    // Access related-module parameters (read number of targets)
    cModule *network = getParentModule()->getParentModule();
    _n_targets = network->par("numPhysicalProcesses");

    //ICF Filter settings
    _procNoiseCov = hasPar("procNoiseCov") ? par("procNoiseCov") : 0.1;
    _measNoiseCov = hasPar("measNoiseCov") ? par("measNoiseCov") : 1e-1;

    // Consensus settings
    _iter_max = hasPar("iter_max") ? par("iter_max") : 20;
    _alpha = hasPar("alpha") ? par("alpha") : 0.1;
    _share = hasPar("share")?par("share").stringValue() : "COM";

    _collectNetworkStats = hasPar("collectNetworkStats")?par("collectNetworkStats").boolValue() : false;
    _collectPowerStats = hasPar("collectPowerStats")?par("collectPowerStats").boolValue() : false;
    _collectAccuracyStats = hasPar("collectAccuracyStats")?par("collectAccuracyStats").boolValue() : false;
    _displayStats =  hasPar("displayStats")?par("displayStats").boolValue() : false;
}

/*! Initialization of structures for tracking targets*/
void WiseMultiCameraPeriodicApp_ICF::initStructures()
{
    WISE_DEBUG_32("WiseCamPerAppICF::initStructures()");

    _tracking_step_counter = 0;
    _time_atsample=0;
    _time_pkt_processing=0;
    _bytesTXround=0;
    _bytesRXround=0;
    _bytesTXprev=0;
    _bytesRXprev=0;

   _dimS = icf::DIM_STATE_T_4D;
   _dimM = icf::DIM_MEASUREMENT_T_2D;

   //status for each target
   _camStatus.clear();
   _camStatus.resize(_n_targets);

   _node_controls.clear();

   for (int tid = 0; tid < _n_targets; tid++)
   {
       //create control data
       icf::node_ctrl_t ctrl(tid,n_nodes,icf::MAX_SIZE_BUFFER,_dimS);

       //determine the neighbourgs to share (FOV or COM graphs)
       _share.compare("FOV") == 0 ? ctrl.n_neighbors = _neighborsFOVoverlap.size(): ctrl.n_neighbors = _neighborsCOM.size();

       _node_controls.push_back(ctrl);//store in list
   }
   WISE_DEBUG_32("WiseCamPerAppICF::\tNew resources (" << _node_controls.size() << " structs) for "<< _n_targets << " targets, " << n_nodes << " nodes and " << icf::MAX_SIZE_BUFFER << " max iterations to buffer)");
}



/*!
 * Destroy resources for tracking. Declared in base class WiseCameraPeriodicApp.
 */
void WiseMultiCameraPeriodicApp_ICF::at_finishSpecific()
{
    WISE_DEBUG_32("WiseCamPerAppICF::at_finishSpecific()");

    if (writerICF) {
       writerICF->close();
       delete writerICF;
       writerICF=NULL;
    }
}

/*!
 * This function defines the behavior to specific alarms generated by the WiseMultiCameraPeriodicApp_ICF
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseMultiCameraPeriodicApp_ICF::at_timer_fired(int index)
{
    WISE_DEBUG_32("WiseCamPerAppICF::at_timer_fired() ALARM: " << _alarm_str[index]);

    switch (index) {
      case ALARM_WAIT_NEGOTIATION:
          //go to the FSM to check completion of negotiation
          fsm_app(INVALID);
          break;
      default:
          WISE_DEBUG_32("WiseCamPerAppICF::\tWRONG ALARM!!: index=" << index);
    }
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by ICFs.
 *
 *  Called to properly read the sample: when a new sample is available a measurement has to be created from it
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseMultiCameraPeriodicApp_ICF::make_measurements(const vector<WiseTargetDetection>&dt)
{
    WISE_DEBUG_32("WiseCamPerAppICF::make_measurements()");

    // reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
    vector<const WiseTargetDetection*> ordered;
    ordered.resize(_n_targets, NULL);

    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        ordered[d->target_id] = &(*d);

    // get data from ordered list of 'WiseTargetDetections' and copy data to 'state_t' and 'measurement_t' lists
    for (int tid = 0; tid < _n_targets && tid < (int)dt.size(); tid++)
    {
        if (ordered[tid] == NULL) {
            _node_controls[tid].detection_miss = true;
            continue;
        }
        const WiseTargetDetection &d = *(ordered[tid]);
        if (!d.valid) {
            _ICFs[tid].z = cv::Mat::zeros(_dimM, 1, CV_64F);
            _node_controls[tid].detection_miss = true;
            continue;
        }

        //measurements + Gaussian noise
        _ICFs[tid].z.at<double>(0)  = (d.ext_bb_x_tl + d.ext_bb_x_br) / 2 + normal(0, _measNoiseCov, 0);
        _ICFs[tid].z.at<double>(1)  = (d.ext_bb_y_tl + d.ext_bb_y_br) / 2 + normal(0, _measNoiseCov, 0);
        _node_controls[tid].detection_miss = false;
        WISE_DEBUG_32("WiseCamPerAppICF::\t tid=" << tid << " -> MAKE MEASUREMENT z=" << format(mat2vec(_ICFs[tid].z), cv::Formatter::FMT_DEFAULT));

    }

    //copy the real positions in the ground-truth lists
    for (int tid = 0; tid < _n_targets; tid++) {
        const WiseTargetDetection &d = *(ordered[tid]);
        _ICFs[tid].xgt.at<double>(0) = (d.true_bb_x_tl + d.true_bb_x_br) / 2;
        _ICFs[tid].xgt.at<double>(1) = (d.true_bb_y_tl + d.true_bb_y_br) / 2;
    }
}

/*!
 * Init resources for ICF processing. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_ICF::at_init()
{
    WISE_DEBUG_32("WiseCamPerAppICF::at_init()");

    _ICFs.clear();
    _tracking_step_counter= 0;

    // ICF filters for each target..
    for (int tid = 0; tid < _n_targets; tid++)
    {
       //create ICF filter
       icf::ICF_t icf(_dimS,_dimM,_procNoiseCov,_measNoiseCov,n_nodes);
       _ICFs.push_back(icf); //store in list

       //update the neighbourgs to share (FOV or COM graphs)
       icf::node_ctrl_t& ctrl = _node_controls[tid];
       _share.compare("FOV") == 0 ? ctrl.n_neighbors = _neighborsFOVoverlap.size(): ctrl.n_neighbors = _neighborsCOM.size();
    }
    WISE_DEBUG_32("WiseCamPerAppICF::Initialized " << _ICFs.size() << " ICF filters for "<< _n_targets << " targets, " << n_nodes << " nodes and " << icf::MAX_SIZE_BUFFER << " iterations");
    return true;
}

/*!
 * ICF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_ICF::at_first_sample()
{
    // Called when the first sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppICF::at_first_sample()");
	
	//find the maximum neighborg degree
	_max_neigb_network = 0;
	for (int i = 0; i < n_nodes; i++) {

	    cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseMultiCameraPeriodicApp_ICF *c = check_and_cast<WiseMultiCameraPeriodicApp_ICF*>(m);

        if (_share.compare("FOV") == 0){
            if (c->_neighborsFOVoverlap.size() > (unsigned int)_max_neigb_network)
                _max_neigb_network = c->_neighborsFOVoverlap.size();
        }
        else{
            if (_neighborsCOM.size() > (unsigned int)_max_neigb_network)
                _max_neigb_network = _neighborsCOM.size();
        }
    }

	//initialize structures to save data
	_rdata.clear();
    for (int tid = 0; tid < _n_targets; tid++){
        std::vector<icf::round_data_t> rdata;
        _rdata.push_back(rdata);
    }

	//initialize targets with ground-truth data
	 for (int tid = 0; tid < _n_targets; tid++){

	    icf::ICF_t &icf = _ICFs[tid];
	    icf.initICFstate(_ICFs[tid].xgt);

        _node_controls[tid].initialized = true;
        _node_controls[tid].first_start_time = SIMTIME_DBL(simTime());

        WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid << " -> INIT x_=" <<  mat2vec(icf.x_) << " xgt=" << mat2vec(_ICFs[tid].xgt));
    }

	//do processing
	//return at_sample();
	 return true;
}

/*!
 * ICF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_ICF::at_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppICF::at_end_first_sample()");

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, ICF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_ICF::at_sample()
{
    // Called when a new sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppICF::at_sample()");
    _tracking_step_counter++;

    if(_tracking_step_counter==1)
        at_first_sample();

    // NOTE: Measurement has been made through the make_measurements() method and is available in the measurement vector
    for (int tid = 0; tid < _n_targets; tid++)
    {
        _rdata[tid].clear();
        _camStatus[tid] = icf::COLLABORATION; //flag to indicate that the camera is busy doing consensus

        //check if there is consensus under progress
        if (_node_controls[tid].iter_counter > 0){
            WISE_DEBUG_32("WiseCamPerAppICF::\tStart consensus without ending previous iter > curr=" << _node_controls[tid].iter_counter << " max=" << _iter_max);
            return false;
        }
        else
            WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid << " -> PROCESS SAMPLE t=" << _tracking_step_counter);

        //record initial time for consensus
        _node_controls[tid].start_time = simTime().dbl();

        //compute internal information vector & matrix
        _ICFs[tid].prepData(_node_controls[tid].detection_miss);

        //start consensus iterations
        consensusStart(tid);
    }
    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseMultiCameraPeriodicApp_ICF::at_end_sample()
{
    // Called when a new sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppICF::at_end_sample()");

	 //check if the camera is doing consensus for any target
	int camStatusTotal=0;
	for (int tid = 0; tid < _n_targets; tid++)
	    if (_camStatus[tid] == icf::INACTIVE)
	        camStatusTotal++;

    if (camStatusTotal != _n_targets) {
        WISE_DEBUG_32("WiseCamPerAppICF::\tnode not ready (own," << camStatusTotal << "/" << _n_targets <<" targets done)");
        setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time); //we check again after a certain time
        return false;
    }
    else
        WISE_DEBUG_32("WiseCamPerAppICF::\tnode ready (own," << camStatusTotal << "/" << _n_targets <<" targets done)");

    /*for (int tid = 0; tid < n_targets; tid++) {
        icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
                //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration
        int c=0;
        for (int i=0; i < n_nodes; i++)
            if(ctrl.nb_data_buffer[0].nb_data[i].end_collaboration == true)
                c++;
        if (c!=ctrl.n_neighbors)
        {
            LOGGER << "node not ready (own, waiting for COLLABORATION END)" << c << "/"<< ctrl.n_neighbors << endl;
            setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
            return false;
        }
    }*/

    /*if (_dummy_comms==false) {
            //perform some additional checking at network level since 'real wireless' may desynchronize nodes
            // TODO: implement a protocol to sync the end of the consensus iteration
            for (int i = 0; i< n_nodes; i++)
            if (i!= self) {
                cModule *m = getParentModule()->getParentModule(); // m=SN
                m = m->getSubmodule("node", i)->getSubmodule("Application");
                WiseMultiCameraPeriodicApp_ICF*c = check_and_cast<WiseMultiCameraPeriodicApp_ICF*>(m);

                camStatusTotal=0;
                for (int tid = 0; tid < _n_targets; tid++)
                    if (c->_camStatus[tid] == icf::INACTIVE)
                        camStatusTotal++;

                if (camStatusTotal != _n_targets)  {
                    LOGGER << "node not ready (netcheck)" << camStatusTotal << "/" << _n_targets <<" targets done)" << std::endl;
                    setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time); //we check again after a certain time
                    return false;
                }
            }
        }
*/

        //restart 'busy' state of other cameras
        for (int tid = 0; tid < _n_targets; tid++) {
            icf::node_ctrl_t &ctrl = _node_controls[tid]; //get the control structure associated to target 'tid'
            //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration
            for (int i=0; i < n_nodes; i++)
                ctrl.nb_data_buffer[0].nb_data[i].end_collaboration = false;
        }/**/

    WISE_DEBUG_32("WiseCamPerAppICF::\tnode ready");

    if(_displayStats && _tracking_step_counter > 1)
        displayStats();

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neighbors, stores the pkt content and when all the data is available (from all neighbors),
 * it calls consensusProcess function to initiate a round of consensus when needed
 *
 * @param[in] pkt Received packet (should be casted to a WiseMultiCameraPeriodicApp_ICFMessage type)
 */
bool WiseMultiCameraPeriodicApp_ICF::process_network_message(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_32("WiseCamPerAppICF::process_network_message()");

    double e2=0,e1 = cv::getTickCount();
    int i=0,c=0, index=-1;

    WiseMultiCameraPeriodicApp_ICFPacket *m = check_and_cast<WiseMultiCameraPeriodicApp_ICFPacket*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    WISE_DEBUG_32("WiseCamPerAppICF::\tRX from " << ctl.source << ". Packet content: [ tid=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << " ]");

    //source node and target IDs of recv packet
    int node = atoi(ctl.source.c_str());
    int tid = m->getTargetID();
    icf::node_ctrl_t &ctrl = _node_controls[tid]; //get the control structure associated to target 'tid'

    switch (m->getPktTypeICF()){
        case ICF_COLLABORATION_DATA1:
        {
            WISE_DEBUG_32("WiseCamPerAppICF::\tCollaboration...");

            // store recv data in buffer
            if(ctrl.storeDataInBuffer((int)m->getIterationStep(), node, m) == -1)
                WISE_DEBUG_32("WiseCamPerAppICF::\tERROR BUFFER!!");

            //check matching of iteration number between node and recv data
            if (m->getIterationStep() != ctrl.iter_counter)
                WISE_DEBUG_32("WiseCamPerAppICF::\tWRONG ITERATION!! (curr=" <<  ctrl.iter_counter << " rcv=" << m->getIterationStep() << ")" << " tid="<<tid);

            // get data for current consensus iteration of the node
            index = ctrl.findIndexInBuffer((int)ctrl.iter_counter); // Index of the buffer

            //count the number of received data from nodes (to start consensus if all data has been recv)
            std::vector<int> missing;
            for (i=0; i < n_nodes; i++)
                if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true){
                    c++;
                }
                else{

                    map<string, bool>::const_iterator n;
                    for (n = _connectivity_map_comms.begin(); n != _connectivity_map_comms.end(); ++n)
                        if ((*n).second == true)
                            if (atoi((*n).first.c_str()) != this->self)
                            if (atoi((*n).first.c_str()) == i)
                                  missing.push_back(i);
                }

            //compute the consensus if we have all neighbor's data
            if (c==ctrl.n_neighbors)
                consensusProcess(tid);
            else
                WISE_DEBUG_32("WiseCamPerAppICF::\tWaiting for " << ctrl.n_neighbors-c << "/" << ctrl.n_neighbors << print_vector(missing) << "for consensus k=" << ctrl.iter_counter << " tid="<<tid);
          break;
        }

        case ICF_COLLABORATION_END:
            if ((int)m->getTrackingCount() == _tracking_step_counter)
            {
                ctrl.nb_data_buffer[0].nb_data[node].end_collaboration=true;
                WISE_DEBUG_32("WiseCamPerAppICF::\tCOLLABORATION END RECEIVED from node=" << node << " tid="<<tid);
            }
            else
                WISE_DEBUG_32("WiseCamPerAppICF::\tLate??? COLLABORATION END RECEIVED from node=" << node << " tid="<<tid << " t_curr=" << _tracking_step_counter << " t_rcv="<<(int)m->getTrackingCount());
            break;

        default:
            WISE_DEBUG_32("WiseCamPerAppICF::\t UNKNOWN PACKET!!");
            break;
    }

    e2 = cv::getTickCount();
   _time_pkt_processing += (e2 - e1)/ cv::getTickFrequency(); //CPU time for processing packets

   return true;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseMultiCameraPeriodicApp_ICF::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppICF::handleDirectApplicationMessage()");

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
void WiseMultiCameraPeriodicApp_ICF::consensusStart(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppICF::consensusStart()");
    _node_controls[tid].iter_counter=1;

    if (_node_controls[tid].n_neighbors > 0 && _iter_max > 0)
        sendICFmessage(tid); // send estimation to neighbors
    else
    {
        //perform final state estimation if there are no neighbors or maximum iterations reached
        _ICFs[tid].estimate_and_predict_state();
        logResult(tid);//save data
    }
}

/*!
 * Function to process a consensus iteration after receiving data
 * from all neighborgs.
 *
 * @param[in] tid Target ID of the associated ICF structures
 * @param[in] k Number of the current iteration
 */
void WiseMultiCameraPeriodicApp_ICF::consensusProcess(int tid)
{
    icf::node_ctrl_t &ctrl = _node_controls[tid];
    WISE_DEBUG_32("WiseCamPerAppICF::consensusProcess()for k=" <<  ctrl.iter_counter);

    //accumulate round data to display stats
    icf::round_data_t rdata;
    rdata.round = ctrl.iter_counter; //consensus round
    rdata.terr = _ICFs[tid].compute_error();
    rdata.delay = simTime().dbl()-_node_controls[tid].start_time;
    _rdata[tid].push_back(rdata);

    int index = ctrl.findIndexInBuffer(ctrl.iter_counter); // Index of the buffer

    //combine estimations of neighbors
    _ICFs[tid].update_state_neighbors(ctrl.nb_data_buffer[index].nb_data,_alpha,ctrl.n_neighbors,_max_neigb_network);

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

   if (ctrl.iter_counter >  _iter_max) {
       _ICFs[tid].estimate_and_predict_state(); //perform final state estimation when maximum iterations reached
       logResult(tid);//save data
       ctrl.iter_counter=0;//return to initial status
   }
   else{
       _ICFs[tid].estimate_state();
       WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid << " -> PAR RESULT x_=" <<  mat2vec(_ICFs[tid].x_) <<" x=" <<  mat2vec(_ICFs[tid].x) <<" err=" <<  setprecision(3) << _ICFs[tid].compute_error());
   }
}



/*!
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseMultiCameraPeriodicApp_ICF::sendICFmessage(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppICF::sendICFmessage()");

    //create message & copy data
    std::ostringstream os;
    os << "ICF: node=" << self << " tid=" << tid << " t=" << _tracking_step_counter << " k=" << _node_controls[tid].iter_counter;

    WiseMultiCameraPeriodicApp_ICFPacket *pkt = new WiseMultiCameraPeriodicApp_ICFPacket(os.str().c_str(), APPLICATION_PACKET);
    pkt->setTrackingCount(_tracking_step_counter); //current step counter
    pkt->setIterationStep(_node_controls[tid].iter_counter); //data for new iteration
    pkt->setTargetID(tid); //target id
    pkt->setSubType(WISE_APP_NORMAL); //normal APP for the network

    //send message containing the posterior state estimation OR collaboration end
    if (_node_controls[tid].iter_counter > _iter_max){
        WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid << " -> SENDING MSG to FOVs to END consensus");
        pkt->setByteLength(icf::ICFpkt_size[ICF_COLLABORATION_END]);
        pkt->setPktTypeICF(ICF_COLLABORATION_END);
        _camStatus[tid] = icf::INACTIVE;//flag to indicate that the node has finished consensus
    }
    else {
        WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid << " -> SENDING MSG to FOVs for k=" << _node_controls[tid].iter_counter);
        pkt->setICFv(_ICFs[tid].v); //information vector
        pkt->setICFV(_ICFs[tid].V); //information matrix
        pkt->setByteLength(icf::ICFpkt_size[ICF_COLLABORATION_DATA1]);
        pkt->setPktTypeICF(ICF_COLLABORATION_DATA1);
    }

    // Distribute the data among neighbors using the FOV or COM graphs.
    //  NOTE: For real wireless channels, it is better to send unicast messages so we can keep control of missing TX packets
    //        If "send_message(pkt)" is used, some packets may be lost without being noticed.
    if (_share.compare("FOV") == 0) {
        pkt->setSubTypeNeighbor(WISE_NEIGHBOR_FOV); //type defined in "WiseCameraSimplePeriodicTracker.msg"
        send_messageNeighboursFOV(pkt);//unicast message
    }
    else{
        pkt->setSubTypeNeighbor(WISE_NEIGHBOR_COM);
        send_messageNeighboursCOM(pkt);//unicast message
    }

    // We assume a broadcast packet for FOVs/COMs in dummy channels so count TX packets only once
    if (_dummy_comms == true)
        _bytesTX = _bytesTX - (_node_controls[tid].n_neighbors-1)*pkt->getByteLength();
    return 1;
}

void WiseMultiCameraPeriodicApp_ICF::checkNextConsensusRound(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppICF::checkNextConsensusRound()");
    icf::node_ctrl_t &ctrl = _node_controls[tid]; //get the control structure associated to target 'tid'

    // get data for current consensus iteration of the node
    int index = ctrl.findIndexInBuffer(ctrl.iter_counter); // Index of the buffer

    int c=0;
    for (int i=0; i < n_nodes; i++)
        if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true){
            c++;
        }
    //compute the consensus if we have all neighbor's data
    if (c==ctrl.n_neighbors){
        WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid << " -> DATA for k=" << _node_controls[tid].iter_counter << " already available");
        consensusProcess(tid);
    }
}
/*!
 * Write results in txt files
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseMultiCameraPeriodicApp_ICF::logResult(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppICF::logResult()");
    double delay = simTime().dbl()-_node_controls[tid].start_time;
    double err = _ICFs[tid].compute_error();
    _ICFs[tid].errAcc += err;

    WISE_DEBUG_32("WiseCamPerAppICF::\ttid=" << tid <<" t="<< _tracking_step_counter << " FINAL -> x=" << mat2vec(_ICFs[tid].x) << " J=" << cv::trace(_ICFs[tid].J).val[0]
              << " x_=" <<  mat2vec(_ICFs[tid].x_) << "," << "] J_=" << cv::trace(_ICFs[tid].J_).val[0]
              << " z=" << mat2vec(_ICFs[tid].z) << " gt=" << mat2vec(_ICFs[tid].xgt));

    *writerICF << std::setprecision(6) << simTime().dbl() << "\t" << _tracking_step_counter << "\t" << self << "\t" << tid  << "\t" <<
            setprecision(4) << _ICFs[tid].z.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].z.at<double>(1) << "\t" <<
            setprecision(4) << _ICFs[tid].x_.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].x_.at<double>(1) << "\t" <<
            setprecision(4) << _ICFs[tid].x.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].x.at<double>(1) << "\t" <<
            setprecision(4) << _ICFs[tid].xgt.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].xgt.at<double>(1) << "\t" <<
            setprecision(4) << err << "\t" << setprecision(4) <<  _ICFs[tid].errAcc << "\t" << delay << endl;
}

/*!
 * Display visual statistics during execution
 *
 */
bool WiseMultiCameraPeriodicApp_ICF::displayStats()
{
    WISE_DEBUG_32("WiseCamPerAppICF::displayStats()");

    double scale = 0.8;

    double enePRO = resMgr->getCurSpentEnergy(WISE_ENERGY_PRO_TOT);
    double eneCOM = resMgr->getCurSpentEnergy(WISE_ENERGY_COM_TOT);

    double tiRound = _sampling_time;

    double TXrate = 1/tiRound * resMgr->getCOMBytesTXdone(); //rateTX_achieve (bps)
    double RXrate = 1/tiRound * resMgr->getCOMBytesRXdone(); //rateRX_achieve (bps)

    //get the color list
    cModule *node = getParentModule();
    node = node->getParentModule()->getSubmodule("wiseTerrain");
    WiseBaseTerrain *terrain = check_and_cast<WiseBaseTerrain*>(node);
    WiseGuiWorldOpencv *gui=check_and_cast<WiseGuiWorldOpencv*>(terrain->get_GUI());
    std::map<int,cv::Scalar> clist = gui->getColorList();
    cv::Scalar colorCam = clist[(int)self];

    for (int tid = 0; tid < _n_targets; tid++) {

        std::ostringstream winStats;
        winStats << "Stats for Cam id="<< _camID << " TargetID=" << tid<< std::endl;
        cv::namedWindow(winStats.str().c_str());
        cv::Mat img = cv::Mat::zeros((_iter_max+1)*50, 850, CV_8UC3);

        std::ostringstream ss0,ss1,ss2,ss3;
        ss0 << "SUMMARY for Cam id=" << _camID << " TargetID=" << tid << " K=" << _tracking_step_counter  << " (Time="<<simTime().dbl()<<"s)";
        cv::putText(img, ss0.str().c_str(), cv::Point(50,50), cv::FONT_HERSHEY_SIMPLEX, scale, colorCam, 2, CV_AA);
        ss1 << "Time at-sample="<<_time_atsample*1e3 << "ms Processing="<<_time_pkt_processing*1e3 << "ms";
        cv::putText(img, ss1.str().c_str(), cv::Point(50,100), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale,colorCam, 2, CV_AA);
        ss2 << "Bandwidth: TXrate=" << TXrate/1e3 << "KBps RXrate=" << RXrate/1e3 << "KBps (MAX " << resMgr->getCOMInfo().bitrateTX/8 *1/1e3<< "KBps)";
        cv::putText(img, ss2.str().c_str(), cv::Point(50,150), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale,colorCam, 2, CV_AA);
        ss3 << "Consumption: EnergyPRO=" << enePRO*1e3<<"mJ EnergyCOM=" << eneCOM*1e3<<"mJ";
        cv::putText(img, ss3.str().c_str(), cv::Point(50,200), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale,colorCam, 2, CV_AA);

        for (int i=0;i<(int)_rdata[tid].size();i++)
        {
            int round = _rdata[tid][i].round;
            double rerr=_rdata[tid][i].terr;
            double delay=_rdata[tid][i].delay;
            std::ostringstream ss;
            ss<<"r="<< setprecision(2)<<round <<" error="<< setprecision(4)<<rerr<<" m Delay="<<delay*1e3<<" ms";
            cv::putText(img, ss.str().c_str(), cv::Point(50,200+30*(i+1)), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale,colorCam, 2, CV_AA);
        }
        cv::imshow(winStats.str().c_str(), img);
        std::cout << "cam "<<_camID << ": display stats for step="<< _tracking_step_counter << " (SimTime="<<simTime().dbl()<<"s)"<< std::endl;

        if (_n_targets < 6)
        {
            WiseTargetInfo t;

            t.id=self;
            t.pos_x=_ICFs[tid].x.at<double>(0);
            t.pos_y=_ICFs[tid].x.at<double>(1);
            t.unique_color=false;
            //gui->draw_target(t);
            terrain->place_target(t);
        }
    }
    return true;
}
