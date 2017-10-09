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
 * \file WiseMultiCameraPeriodicApp_KCF.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseMultiCameraPeriodicApp_KCF.cc class
 * \version 1.4
 */
#include <wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCF.h>
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

Define_Module(WiseMultiCameraPeriodicApp_KCF);

std::ofstream *final_writer=NULL;

/*! Class destructor */
void WiseMultiCameraPeriodicApp_KCF::at_finishSpecific()
{
    WISE_DEBUG_32("WiseCamPerAppKCF::at_finishSpecific()");

    if (final_writer) {
        final_writer->close();
        delete final_writer;
        final_writer = NULL;
    }
}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseMultiCameraPeriodicApp_KCF::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppKCF::at_startup() called");

    readParameters();
    initStructures();

    // init logs

    //create message & copy data
    std::ostringstream os;
    os << base_out_path.c_str() << "KCF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".dat";

    if (final_writer == NULL)
           final_writer = new ofstream();

    if (!final_writer->is_open()){
        final_writer->open(os.str().c_str());
        *final_writer << "# procNoiseCov=" << procNoiseCov << " measNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << endl;
        *final_writer << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc,DelayForPackets" << endl;
        *final_writer << "#t_sim\tt_step\tNID\tTID\tZx\tZy\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc\tDelay" << endl;
    }

    std::ostringstream os1;
    os1 << base_out_path.c_str() << "KCF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max
        << "_CPU" << std::setfill('0') << std::setw(3) << resMgr->getPROClk()/1e5 << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user()
        << ".res" << std::setfill('0') << std::setw(3) << self;
    resMgr->initLogger(os1.str().c_str(), self, _camID); //energy-consumption log

    std::ostringstream os2;
    os2 << base_out_path.c_str() << "KCF"  << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".rad";
    radioModule->initLogger(os2.str().c_str());

    WISE_DEBUG_32("WiseCamPerAppKCF::procNoiseCov=" << procNoiseCov << " measNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha);
}

/*! Read parameters of MTT_ICF*/
void WiseMultiCameraPeriodicApp_KCF::readParameters()
{
    WISE_DEBUG_32("WiseCamPerAppKCF::readParameters() called");

    // Access related-module parameters (read number of targets)
        cModule *network = getParentModule()->getParentModule();
        n_targets = network->par("numPhysicalProcesses");

        // Kalman Filter settings
        procNoiseCov = hasPar("procNoiseCov") ? par("procNoiseCov") : 0.1;
        measNoiseCov = hasPar("measNoiseCov") ? par("measNoiseCov") : 1e-1;

        // Consensus settings
        iter_max = hasPar("iter_max") ? par("iter_max") : 10;
        alpha = hasPar("alpha") ? par("alpha") : 0.1;

        _share_msg = hasPar("_share_msg")?par("_share_msg").stringValue() : "COM";
}

/*! Initialization of structures for tracking targets*/
void WiseMultiCameraPeriodicApp_KCF::initStructures()
{
   WISE_DEBUG_32("WiseCamPerAppKCF::initStructures() called");

   xgt.resize(n_targets);
   z.resize(n_targets);

   states_init.clear();
   states_estimate.clear();
   states_final.clear();
   error.clear();
   errorAcc.clear();

   states_init.resize(n_targets);
   states_estimate.resize(n_targets);
   states_final.resize(n_targets);
   error.resize(n_targets);
   errorAcc.resize(n_targets);

   for (unsigned int i = 0; i < n_targets; i++)
   {
       node_ctrl_t ctrl = kcf::init_node_ctrl(n_nodes,MAX_SIZE_BUFFER);
       node_controls.push_back(ctrl);

       error[i] = 0;
       errorAcc[i] = 0;
   }
}


/*!
 * This function defines the behavior to specific alarms generated by the algorithm. To be implemented in superclasses of WiseCameraPeriodicAlgo.
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseMultiCameraPeriodicApp_KCF::at_timer_fired(int index)
{
    WISE_DEBUG_32("WiseCamPerAppKCF::ALARM: " << _alarm_str[index]);

    switch (index) {
      //check completion of negotiation
      case ALARM_WAIT_NEGOTIATION:
          fsm_app(INVALID); //we go to the FSM when coalition is checked to be completed
          break;
      default:
          WISE_DEBUG_32("WiseCamPerAppKCF::WRONG ALARM!!: index=" << index);
    }
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by KFs.
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseMultiCameraPeriodicApp_KCF::make_measurements(const vector<WiseTargetDetection>&dt)
{
    // Called to properly read the sample: when a new sample is available a measurement has to be created from it
    unsigned int tid = 0;

    vector<const WiseTargetDetection*> ordered;
    ordered.resize(n_targets, NULL);

    // reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        ordered[d->target_id] = &(*d);

    // get data from ordered list of 'WiseTargetDetections' and copy data to 'state_t' and 'measurement_t' lists
    for (; tid < n_targets && tid < dt.size(); tid++)
    {
        if (ordered[tid] == NULL) {
            node_controls[tid].detection_miss = true;
            continue;
        }
        const WiseTargetDetection &d = *(ordered[tid]);
        if (!d.valid) {
            z[tid] = cv::Mat::zeros(dimM, 1, CV_64F);
            node_controls[tid].detection_miss = true;
            continue;
        }

        //get the measurements + Gaussian noise
        z[tid].at<double>(0)  = (d.ext_bb_x_tl + d.ext_bb_x_br) / 2 + normal(0, sqrt(measNoiseCov), 0);
        z[tid].at<double>(1)  = (d.ext_bb_y_tl + d.ext_bb_y_br) / 2 + normal(0, sqrt(measNoiseCov), 0);

        node_controls[tid].detection_miss = false;
        WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " -> MAKE MEASUREMENT" << " z=[" << z[tid].at<double>(0) << "," << z[tid].at<double>(0) << "]");
    }

    // Set the residuals to detection_miss (ie, targets not processed)
    for (; tid < n_targets; tid++)
        node_controls[tid].detection_miss = true;

    // copy the real positions in the ground-truth lists
    for (tid = 0; tid < n_targets; tid++) {
        const WiseTargetDetection &d = *(ordered[tid]);
        xgt[tid].at<double>(0) = (d.true_bb_x_tl + d.true_bb_x_br) / 2;
        xgt[tid].at<double>(1) = (d.true_bb_y_tl + d.true_bb_y_br) / 2;
        //WISE_DEBUG_32("WiseCamPerAppKCF::tid="<< tid << " xgt=[" << xgt[tid].at<double>(0) << "," << xgt[tid].at<double>(1) << "]" << endl;
    }
}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraSimplePeriodicTracker. Called upon tracker init
 */
bool WiseMultiCameraPeriodicApp_KCF::at_init()
{
	// Initialization of the Kalman Filters. Could also done in at_startup()
    KFs.clear();
    this->dimS = 4;
    this->dimM = 2;

    for (unsigned tid = 0; tid < n_targets; tid++)
    {
        xgt[tid]      = cv::Mat::zeros(dimS, 1, CV_64F);
        z[tid]        = cv::Mat::zeros(dimM, 1, CV_64F);

        KalmanFilter_t KF = kcf::init_KalmanFilter(dimS,dimM,procNoiseCov,measNoiseCov);
        KFs.push_back(KF);

        //reinitialize control data
        node_ctrl_t &ctrl = node_controls[tid];

        if (_share_msg.compare("FOV") == 0)
            ctrl.n_neighbourgs = _neighborsFOVoverlap.size();//neighbors in the FOV graph
        else
            ctrl.n_neighbourgs = _neighborsCOM.size();//neighbors in the COM graph


        for (int j=0; j<MAX_SIZE_BUFFER;j++)
            for (int n=0; n<n_nodes; n++)
            {
                neigbourg_data_t &nb_node = ctrl.nb_data_buffer[j].nb_data[n]; //associated neigbour's data
                nb_node.rcv_data = false;  // data not received yet
                nb_node.u = cv::Mat::zeros(dimS, 1, cv::DataType<double>::type);    //information vector of node
                nb_node.U = cv::Mat::zeros(dimS, dimS, cv::DataType<double>::type);    //information vector of node
                nb_node.end_collaboration =false;
            }
    }
    return true;
}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_KCF::at_first_sample()
{
	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	//at_tracker_sample(); // option 2

    //ground-truth initialization of filters (at 1st step, all with same initial data)
    for (unsigned tid = 0; tid < n_targets; tid++)
    {
       KalmanFilter_t &KF = KFs[tid];
       KF = kcf::initKFstate(KF,xgt[tid]);

       node_controls[tid].initialized = true;
       node_controls[tid].first_start_time = SIMTIME_DBL(simTime());
//TODO
      // WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " INIT x_=" << print(KF.x_,3) << " xgt=[" << xgt[tid].at<double>(0) << "," << xgt[tid].at<double>(1) << "]" << endl;
    }
    return at_sample();
}

/*!
 * KF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_KCF::at_end_first_sample()
{
	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_KCF::at_sample()
{
    // Called when a new sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppKCF::at_sample() called");

    _tracking_step_counter++;
    _camStatus = kcf::COLLABORATION; //flag to indicate that the camera is busy
	
    if(_tracking_step_counter==1)
        at_first_sample();

    // NOTE: Measurement has been made through the make_measurements() method and is available in the measurement vector
    for (unsigned int tid = 0; tid < n_targets; tid++)
    {
        WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " -> PROCESS SAMPLE t=" <<  _tracking_step_counter);

        //get elements in the lists for the target ID
        node_ctrl_t &ctrl = node_controls[tid];
        KalmanFilter_t &KF = KFs[tid];

        //check if there is consensus under progress
        if (ctrl.iter_counter > 0){
            WISE_DEBUG_32("WiseCamPerAppKCF::Trying to start consensus without finishing the previous one> curr=" << ctrl.iter_counter << " max=" << iter_max);
            return false;
        }

        // Uncomment to initialize KF only when data is ready
        // Currently, initialization is done using ground-truth in the 1st iteration. See function at_tracker_first_sample()
        //if (ctrl.detection_miss == false && ctrl.initialized == false)
        //    initKF(tid);

        // compute information initial vector and matrix
        if (ctrl.detection_miss == true) {
           //generate empty information when target not in FOV (ie, no detection)
           KF.u = cv::Mat::zeros(dimS, 1, cv::DataType<double>::type);  //information vector of node
           KF.U = cv::Mat::zeros(dimS, dimS, cv::DataType<double>::type); //information matrix of node
        }
        else {
           //generate information when target is in FOV
           KF.u = KF.Ht * KF.Rinv * z[tid];
           KF.U = KF.Ht * KF.Rinv * KF.H;
        }
        //std::cout << " node=" << self << " tid=" << tid << " u=" << KF.u << " U=" << KF.U << endl;

        // Send information vector and matrix at each node (initial message for k=1)
        ctrl.iter_counter=1;
        if (ctrl.n_neighbourgs == 0 || iter_max == 0) //no neighbors
        {
            //use only local information
            KF.u.copyTo(KF.y);
            KF.U.copyTo(KF.S);

            estimateTarget(tid);
        }
        else
            sendKCFmessage(tid); // send estimation to neighbors
    }
    return true;
}


/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseMultiCameraPeriodicApp_KCF::at_end_sample()
{
    //check if the camera is still collaborating
    if (_camStatus != kcf::INACTIVE) {
        WISE_DEBUG_32("WiseCamPerAppKCF::node not ready (own)");
        setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time); //we check again after a certain time
        return false;
    }

    if (_dummy_comms==false) {
        //perform some additional checking at network level since 'real wireless' may desynchronize nodes
        // TODO: implement a protocol to sync the end of the consensus iteration
        for (int i = 0; i< n_nodes; i++)
        if (i!= self) {
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");
            WiseMultiCameraPeriodicApp_KCF*c = check_and_cast<WiseMultiCameraPeriodicApp_KCF*>(m);
            if (c->_camStatus != kcf::INACTIVE) {
                WISE_DEBUG_32("WiseCamPerAppKCF::node not ready (netcheck)");
                setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time); //we check again after a certain time
                return false;
            }
        }
    }

    //restart 'busy' state of other cameras
    for (unsigned int tid = 0; tid < n_targets; tid++) {
        node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
        //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration
        for (int i=0; i < n_nodes; i++)
            ctrl.nb_data_buffer[0].nb_data[i].end_collaboration = false;
    }

    WISE_DEBUG_32("WiseCamPerAppKCF::node ready");
    return true;

   /*
    //ALTERNATIVE METHOD - not tested
    unsigned int tid_c = 0, c = 0;

    for (unsigned int tid = 0; tid < n_targets; tid++) {
        node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
        //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration

        c=0;
        for (int i=0; i < n_nodes; i++)
            if (ctrl.nb_data_buffer[0].nb_data[i].end_collaboration == true){
                //WISE_DEBUG_32("WiseCamPerAppKCF::finished node=" << i << endl;
                c++;
            }
            else
                //WISE_DEBUG_32("WiseCamPerAppKCF::not finished node=" << i << endl;

        if (c==(unsigned int)ctrl.n_neighbourgs)
            tid_c++;
    }

    if (tid_c < n_targets || _camStatus != kcf::INACTIVE){
        WISE_DEBUG_32("WiseCamPerAppKCF::node not ready, tid=" << tid_c << " status=" << _camStatus << " c=" << c << " n=" << node_controls[0].n_neighbourgs << endl;
        setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
        return false;
    }
    else {

        WISE_DEBUG_32("WiseCamPerAppKCF::node ready" << endl;
        return true;
    }   */
}

/*!
 * Implements posterior estimation step of the KF filter
 *
 * @param[in] tid Target ID of the associated KF structures
 */
void WiseMultiCameraPeriodicApp_KCF::estimateTarget(int tid)
{
    KFs[tid] = kcf::update(KFs[tid],false);  //update with measurements
    KFs[tid].x.copyTo(states_final[tid]);  //copy final posterior
    KFs[tid] = kcf::predict(KFs[tid]);//compute prior (predict of next step)

    //return to initial status & save result
    node_controls[tid].iter_counter=0;
    logResult(tid);
}

/*!
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseMultiCameraPeriodicApp_KCF::sendKCFmessage(int tid)
{
    std::ostringstream os;
    //double delay=0.001;

    //create message & copy data
    os << "KCF: node=" << self << " tid=" << tid << " t=" << _tracking_step_counter << " k=" << node_controls[tid].iter_counter;
    WiseMultiCameraPeriodicApp_KCFPacket *pkt = new WiseMultiCameraPeriodicApp_KCFPacket(os.str().c_str(), APPLICATION_PACKET);

    if (node_controls[tid].iter_counter == 1)
    {
        WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " -> SENDING MSG to nodes for k=" << node_controls[tid].iter_counter);
        //send this data only for k=1 (initial consensus iteration)
        pkt->setIF_u(KFs[tid].u); //information vector
        pkt->setIF_U(KFs[tid].U); //information matrix
        pkt->setByteLength(KCFpkt_size[KCF_COLLABORATION_DATA1]);
        pkt->setPktType(KCF_COLLABORATION_DATA1);
    }
    else
    {
        if (node_controls[tid].iter_counter > iter_max){
            WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " -> SENDING MSG to nodes to END consensus");
            pkt->setByteLength(KCFpkt_size[KCF_COLLABORATION_END]);
            pkt->setPktType(KCF_COLLABORATION_END);
            _camStatus = kcf::INACTIVE;//flag to indicate that the node has finished consensus
        }
        else {
            WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " -> SENDING MSG to nodes for k=" << node_controls[tid].iter_counter);
            //send this data only for k>1
            pkt->setPositionX(KFs[tid].x.at<double>(0));
            pkt->setPositionY(KFs[tid].x.at<double>(1));
            pkt->setByteLength(KCFpkt_size[KCF_COLLABORATION_DATA2]);
            pkt->setPktType(KCF_COLLABORATION_DATA2);
        }
    }

    pkt->setTrackingCount(_tracking_step_counter); //current step counter
    pkt->setIterationStep(node_controls[tid].iter_counter);
    pkt->setTargetID(tid); //target id
    pkt->setSubType(WISE_APP_NORMAL); //normal APP for the network

    if (_share_msg.compare("FOV") == 0) {
        // We can distribute the data among neighbors using the FOV graph
        pkt->setTypeNeighbour(WISE_NEIGHBOR_FOV); //type defined in "WiseCameraSimplePeriodicTracker.msg"
        send_messageNeighboursFOV(pkt);//unicast message
    }
    else{
        // We can distribute the data among neighbors using the COM graph
        pkt->setTypeNeighbour(WISE_NEIGHBOR_COM);
        // when real wireless channel exists, it is better to send unicast messages
        // so we are able to retransmit missing packets
        // Alternatively, "send_message(pkt)" could be used but some packets will be lost
        send_messageNeighboursCOM(pkt);//unicast message
    }

    //we assume a broadcast packet for FOVs/COMs in dummy channels so count packet TX only once
    if (_dummy_comms == true)
        _bytesTX = _bytesTX - (node_controls[tid].n_neighbourgs-1)*pkt->getByteLength();

    return 1;
}


/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neighbors, stores the pkt content and when all the data is available (from all neighbors),
 * it performs consensus and sends back the averaged result to the neighbors using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseMultiCameraPeriodicApp_KCFMessage type)
 */
bool WiseMultiCameraPeriodicApp_KCF::process_network_message(WiseBaseAppPacket *pkt)
{
    double e2=0,e1 = cv::getTickCount();
    int c = 0, tid = -1 , node = -1, i = 0, index = 0;

    WiseMultiCameraPeriodicApp_KCFPacket *m = check_and_cast<WiseMultiCameraPeriodicApp_KCFPacket*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    node = atoi(ctl.source.c_str());
    tid = m->getTargetID();
    node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
    WISE_DEBUG_32("WiseCamPerAppKCF::RX from " << ctl.source << ". Packet content: [TID=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << " Pos=(" << m->getPositionX() << "," << m->getPositionY() << ")]");

    switch (m->getPktType()){
        case KCF_COLLABORATION_DATA1:
        case KCF_COLLABORATION_DATA2:

            // store recv data in buffer
            index = findIndexInBuffer(tid, (int)m->getIterationStep()); // get the index of the buffer for the iteration of the received data
            storeDataInBuffer(tid, index, node, m); // store data in buffer

            //check if current iteration of consensus corresponds to recv data
            if (m->getIterationStep() !=ctrl.iter_counter){
                WISE_DEBUG_32("WiseCamPerAppKCF::WRONG ITERATION!! (curr=" <<  ctrl.iter_counter << " rcv=" << m->getIterationStep() << ")");
                return false;
             }

            // get data for current consensus iteration of the node
            index = findIndexInBuffer(tid, (int)ctrl.iter_counter); // Index of the buffer

            //count the number of nodes for which there is received data (to start consensus if all data has been recv)
            for (i=0; i < n_nodes; i++)
                if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true)
                    c++;

            //compute consensus if we have all neighbor's data
              if (c==ctrl.n_neighbourgs)
              {
                  WISE_DEBUG_32("WiseCamPerAppKCF:: CONSENSUS for k=" <<  ctrl.iter_counter);

                  //do consensus
                  if (ctrl.iter_counter == 1)
                      consensusMesurements(tid);
                  else
                      consensusState(tid);

                  //free positions of buffer
                  ctrl.nb_data_buffer[index].iter_buffer = -1; //free the used buffer position for future data
                  for (i=0; i < n_nodes; i++)
                      ctrl.nb_data_buffer[index].nb_data[i].rcv_data = false;

                  //send posterior state or END round to neighbors
                  ctrl.iter_counter++;
                  sendKCFmessage(tid);

                  //continue consensus if not exceed the max iterations
                  if (ctrl.iter_counter >  iter_max){
                     ctrl.iter_counter = 0;//restart the counter
                     KFs[tid].x.copyTo(states_final[tid]);//copy final posterior to node's data
                     KFs[tid] = kcf::predict(KFs[tid]);//predict next target state
                     logResult(tid);//save data
                 }
              }
              else
                  WISE_DEBUG_32("WiseCamPerAppKCF:: Waiting for " << node_controls[tid].n_neighbourgs-c << "/" << node_controls[tid].n_neighbourgs << "  nodes");

        break;
    case KCF_COLLABORATION_END:
        ctrl.nb_data_buffer[0].nb_data[node].end_collaboration=true;
        WISE_DEBUG_32("WiseCamPerAppKCF:: COLLABORATION END RECEIVED from node=" << node);
        break;
    }

    e2 = cv::getTickCount();
   _time_pkt_processing += (e2 - e1)/ cv::getTickFrequency(); //CPU time for processing packets
   return true;
}

/*!
 * Implements the first round of KCF consensus where each node gathers the measurements of their neighborhood,
 * fuses the data and performs consensus over the prior state estimation.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
void WiseMultiCameraPeriodicApp_KCF::consensusMesurements(int tid)
{
    cv::Mat diff = cv::Mat::zeros(dimS, 1, cv::DataType<double>::type);
    KalmanFilter_t &KF = KFs[tid];//get KF

    node_controls[tid].start_time = simTime().dbl();

    // get data for current consensus iteration of the node
    int index = findIndexInBuffer(tid, (int)node_controls[tid].iter_counter); // Index of the buffer
    std::vector<neigbourg_data_t> &curr_nb_data= node_controls[tid].nb_data_buffer[index].nb_data; // data of the buffer

    KF.u.copyTo(KF.y); //initial information vector (own)
    KF.U.copyTo(KF.S); //initial information matrix (own)

    //data gathering from neighbors
    for (vector<neigbourg_data_t>::const_iterator n = curr_nb_data.begin(); n != curr_nb_data.end(); ++n)
        if (n->rcv_data == true){

         cv::Mat nb_data_ = (cv::Mat_<double>(dimS, 1) << n->rcv_state.x, n->rcv_state.y, n->rcv_state.Vx, n->rcv_state.Vy);

         //vector&matrix and difference between states only for k=1
         KF.y = KF.y + n->u;
         KF.S = KF.S + n->U;
         //std::cout << "node=" << self << " rcv_u=" << print(n->u,2) << " rcv_U=" << cv::sum(n->U).val[0] << endl;
      }
    //compute posterior estimation using measurements (only for k=1)
    //std::cout << "node="<<self<<" tid=" << tid << " k=1 x_=" << print(KF.x_,2) << " x =" << print(KF.x,2);/**/
    //std::cout << " o=" << print(KF.M*(KF.y - KF.S*KF.x_),2)  << " y=" << print(KF.y,2) << " S=" << cv::sum(KF.S).val[0]  << endl;
    KF = kcf::update(KF, false);
}

/*!
 * Implements the >1st rounds of KCF consensus using the posterior state estimation
 * of each node.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
void WiseMultiCameraPeriodicApp_KCF::consensusState(int tid)
{
    cv::Mat diff = cv::Mat::zeros(dimS, 1, CV_64F);
    KalmanFilter_t &KF = KFs[tid];//get KF

    // get data for current consensus iteration of the node
    node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
    int index = findIndexInBuffer(tid, (int)ctrl.iter_counter); // Index of the buffer
    std::vector<neigbourg_data_t> &curr_nb_data= ctrl.nb_data_buffer[index].nb_data; // data of the buffer

   //data gathering from all neighbors
   for (vector<neigbourg_data_t>::const_iterator n = curr_nb_data.begin(); n != curr_nb_data.end(); ++n)
       if (n->rcv_data == true)
       {
           //conversion to cv::Mat + fuse information from other nodes
           cv::Mat nb_data_ = (cv::Mat_<double>(dimS, 1) << n->rcv_state.x, n->rcv_state.y, n->rcv_state.Vx, n->rcv_state.Vy);
           diff = diff + (nb_data_-KF.x); //only difference between states for k>1
           //std::cout << "node=" << self << " state_rcv=" << print(nb_data_,3) << endl;
       }
   diff=diff/ctrl.n_neighbourgs; //average difference with neighbors
   //std::cout << "node=" << self << " tid=" << tid << " k=" <<  ctrl.iter_counter << " x=" << print(KF.x,4);
   //std::cout << " diff=" << print(diff,4);

   KF.x = KF.x + alpha*diff;
   //std::cout << " x_updated=" << print(KF.x,4) << endl;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseMultiCameraPeriodicApp_KCF::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppKCF::handleDirectApplicationMessage() called");

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}

/*!
 * Write results in txt files
 *
 * @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseMultiCameraPeriodicApp_KCF::logResult(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppKCF::logResult() called");

    double delay = simTime().dbl()-node_controls[tid].start_time;

    double difX = states_final[tid].at<double>(0) - xgt[tid].at<double>(0);
    double difY = states_final[tid].at<double>(1) - xgt[tid].at<double>(1);
    error[tid] = sqrt(difX*difX + difY*difY);
    errorAcc[tid] = errorAcc[tid] + error[tid]; //accumulated

   //TODO
    //WISE_DEBUG_32("WiseCamPerAppKCF::tid=" << tid << " -> est:" << print(states_final[tid],2) << " Z:" << print(z[tid],2) << " gt:" << print(xgt[tid],2) << " for t="<< _tracking_step_counter << endl;
    //*final_writer << std::setfill('0') << std::setw(5)  << simTime().dbl() << "\t" << _tracking_step_counter << "\t" << self << "\t" << tid  << "\t"
    *final_writer << std::setw(5)  << simTime().dbl() << "\t" << _tracking_step_counter << "\t" << self << "\t" << tid  << "\t"
            << std::setprecision(4) << z[tid].at<double>(0) << "\t" << std::setprecision(4) << z[tid].at<double>(1) << "\t"
            << std::setprecision(4) << KFs[tid].x_.at<double>(0) << "\t" << std::setprecision(4) << KFs[tid].x_.at<double>(1) << "\t"
            << std::setprecision(4) << states_final[tid].at<double>(0) << "\t" << std::setprecision(4) << states_final[tid].at<double>(1) << "\t"
            << std::setprecision(4) << xgt[tid].at<double>(0) <<"\t" << std::setprecision(4) << xgt[tid].at<double>(1) << "\t"
            << std::setprecision(4) << error[tid] << "\t" << std::setprecision(4) <<  errorAcc[tid] << "\t" << delay << endl;
}

/*!
 * This function searches in the buffer for the index corresponding to a given target ID and iteration index.
 *
 * @param[in] tid Target ID
 * @param[in] iter_index Index of the consensus iteration
 * @return The index of the buffer with the data or the next available position to store data.
 *         Returns -1 if there are no available positions and there are no data related with the "iteration"
 */
int WiseMultiCameraPeriodicApp_KCF::findIndexInBuffer(int tid, int iter_index)
{
    node_ctrl_t &ctrl = node_controls[tid]; //control for target
    int index=-1;

    //look for the index where the data of the iteration is stored in the buffer
    for (int i=0;i<MAX_SIZE_BUFFER;i++)
       if (ctrl.nb_data_buffer[i].iter_buffer == iter_index)
       {
           index = i;
           break;
       }

    //If data is not found, look for the next available position in buffer
    if (index == -1)
        for (int i=0;i<MAX_SIZE_BUFFER;i++)
            if (ctrl.nb_data_buffer[i].iter_buffer==-1){
                index = i;
                break;
            }

    return index;
}

/*!
 * This function stores in the buffer the data for a given target ID, iteration index and neighbour node.
 *
 * @param[in] tid Target ID
 * @param[in] indBuf Index of the consensus iteration
 * @param[in] nodeID ID of the neighbour node
 *
 */
void WiseMultiCameraPeriodicApp_KCF::storeDataInBuffer(int tid, int indBuf, int nodeID, WiseMultiCameraPeriodicApp_KCFPacket *m)
{
    node_ctrl_t &ctrl = node_controls[tid]; //control for target

    if (indBuf == -1)
        WISE_DEBUG_32("WiseCamPerAppKCF::storeDataInBuffer WRONG INDEX!!!");

    //store data in the buffer
    ctrl.nb_data_buffer[indBuf].iter_buffer = m->getIterationStep();
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_data = true;
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_state.tid = tid;
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_state.x = m->getPositionX();
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_state.y = m->getPositionY();
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_state.Vx = m->getVx();
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_state.Vy = m->getVy();

    //copy information vector & matrix for k=1
    if (m->getIterationStep() == 1) {
        ctrl.nb_data_buffer[indBuf].nb_data[nodeID].u = m->getIF_u();
        ctrl.nb_data_buffer[indBuf].nb_data[nodeID].U = m->getIF_U();
    }
}
