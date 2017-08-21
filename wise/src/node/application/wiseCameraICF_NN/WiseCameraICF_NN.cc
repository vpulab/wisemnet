// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2013
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#include "WiseCameraICF_NN.h"
#include "TMacControlMessage_m.h"
#include "hungarian.h"


Define_Module(WiseCameraICF_NN);

//Structures/variables for logging
#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE trace() << "WISEICF_NN: "

ofstream WiseCameraICF_NN::logger;
std::ofstream *writerICFNN=NULL;

using namespace icf;//for using all structures in the namespace of WiseCameraICF_NN_utils.h

/*! Class destructor */
WiseCameraICF_NN::~WiseCameraICF_NN()
{
    LOGGER << " Generated " << countClutters/n_targets << " clutters/target for " << this->tracking_step_counter << " samples"<< std::endl;
    if (writerICFNN) {
        writerICFNN->close();
        delete writerICFNN;
        writerICFNN=NULL;
    }
}

void WiseCameraICF_NN::at_finishSpecific()
{
    declareOutput("Generated clutters/target");
    collectOutput("Generated clutters/target", "", countClutters/n_targets);
}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraICF_NN::at_startup()
{
    // Called upon simulation start-up
    BASE_TRACE << "START-UP";

    readParameters();//Read parameters
    initStructures();//create internal structures

    //Create streams for logging results
    if (!logger.is_open())
        logger.open("myLog.txt");

    if (writerICFNN == NULL)
           writerICFNN = new ofstream();

    if(collectAccuracyStats) {
        std::ostringstream os;
        os << "res/ICF" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".dat";

        if (!writerICFNN->is_open()){
            writerICFNN->open(os.str().c_str());
            *writerICFNN << "# processNoiseCov=" << procNoiseCov << " measurementNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << endl;
            *writerICFNN << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc,ResultsDelay" << endl;
            *writerICFNN << "#t_sim\tt_step\tNID\tTID\tZx\tZy\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc\tDelay" << endl;
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

    LOGGER << "processNoiseCov=" << procNoiseCov << " measurementNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << " lambda=" << lambda << endl;
}

/*! Read parameters of MTT_ICF*/
void WiseCameraICF_NN::readParameters()
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

    //Association parameters of NN algorithm
    lambda = hasPar("lambda") ? par("lambda") : 1.0; //clutter level

    collectNetworkStats = hasPar("collectNetworkStats")?par("collectNetworkStats").boolValue() : false;
    collectPowerStats = hasPar("collectPowerStats")?par("collectPowerStats").boolValue() : false;
    collectAccuracyStats = hasPar("collectAccuracyStats")?par("collectAccuracyStats").boolValue() : false;
}

/*! Initialization of structures for tracking targets*/
void WiseCameraICF_NN::initStructures()
{
     this->dimS = DIM_STATE_T_4D;
     this->dimM = DIM_MEASUREMENT_T_2D;

     this->countClutters = 0;

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
 * This function defines the behavior to specific alarms generated by the algorithm. To be implemented in superclasses of WiseCameraPeriodicAlgo.
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseCameraICF_NN::at_timer_fired(int index)
{
    LOGGER << "ALARM: " << _alarm_str[index]<< endl;

    switch (index) {
      //check completion of negotiation
      case ALARM_WAIT_NEGOTIATION:
          fsm_tracker(INVALID); //we go to the FSM when coalition is checked to be completed
          break;
      default:
          LOGGER << "WRONG ALARM!!: index=" << index << endl;
    }
}

/*!
 * From the WiseBaseApplication class.
 *
 * @param[in] c Message received
 */
void WiseCameraICF_NN::handleMacControlMessage(cMessage *c)
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

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by ICFs.
 *
 *  Called to properly read the sample: when a new sample is available a measurement has to be created from it
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseCameraICF_NN::make_measurements(const vector<WiseTargetDetection>&dt)
{

    // reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
    vector<const WiseTargetDetection*> ordered;
    ordered.resize(n_targets, NULL);

    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        ordered[d->target_id] = &(*d);

    //copy the real positions in the ground-truth lists
    for (int tid = 0; tid < n_targets; tid++) {
        const WiseTargetDetection &d = *(ordered[tid]);
        ICFs[tid].xgt.at<double>(0) = (d.true_bb_x_tl + d.true_bb_x_br) / 2;
        ICFs[tid].xgt.at<double>(1) = (d.true_bb_y_tl + d.true_bb_y_br) / 2;
    }

    zlist.clear();

    // generate measurements (in world coordinates, assuming known camera calibration)
    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        if ((*d).valid == true) {
            cv::Mat z_ = cv::Mat::zeros(dimM, 1, CV_64F);
            z_.at<double>(0)  = ((*d).ext_bb_x_tl + (*d).ext_bb_x_br) / 2 + normal(0, sqrt(measNoiseCov), 0);
            z_.at<double>(1)  = ((*d).ext_bb_y_tl + (*d).ext_bb_y_br) / 2 + normal(0, sqrt(measNoiseCov), 0);
            zlist.push_back(z_);
            LOGGER << " -> MAKE MEASUREMENT" << " z=[" << z_.at<double>(0) << "," << z_.at<double>(1) << "]" << endl;
        }

    // generate clutter measurements
    generateClutterMeasurements(&zlist);
}

void WiseCameraICF_NN::generateClutterMeasurements (std::vector<cv::Mat> *zlist)
{
    srand(cv::getTickCount()); // Seed the time
    int numClutters = poisson(lambda); //TODO: change seed for each simulation
    LOGGER << " Creating " << numClutters << " clutter measurements" << endl;
    for (int c = 1; c <= numClutters;c++){

        cv::Mat clut = cv::Mat::zeros(dimM, 1, CV_64F);
        switch (camera_info.get_fov_type())
        {
            case WiseCameraInfo::DIRECTIONAL:
            {
               WiseCameraInfo::fov_di_t fov;
               camera_info.get_fov_di(fov);

               //check if target is inside camera's FOV
               vector<cv::Point> points;
               points.clear();
               points.push_back(cvPoint(fov.c_px,fov.c_py));
               points.push_back(cvPoint(fov.c_cx,fov.c_cy));
               points.push_back(cvPoint(fov.c_bx,fov.c_by));
               points.push_back(cvPoint(fov.c_px,fov.c_py));

               double dist=-1;
               int x_init,y_init=0;

               //the point lies outside the FOV (dist == 0, on the edge; dist == 1, inside)
               while(dist < 0)
               {
                   srand(cv::getTickCount()); // Seed the time
                   x_init = fmod(rand(),(fov.max_x-fov.min_x + 1)) + fov.min_x;
                   y_init = fmod(rand(),(fov.max_y-fov.min_y + 1)) + fov.min_y;

                   dist = cv::pointPolygonTest(points, cvPoint(x_init, y_init), false);
               }
               clut = (cv::Mat_<double>(2, 1) << x_init, y_init);
               break;
            }
            case WiseCameraInfo::BOUNDING_BOX:
            {
                WiseCameraInfo::fov_bb_t fov;
                camera_info.get_fov_bb(fov);
                cv::Mat camPos = (cv::Mat_<double>(2, 1) << fov.c_x, fov.c_y); //x-y position of camera
                cv::Mat camSiz = (cv::Mat_<double>(2, 1) << fov.width, fov.height); //W-H size of camera
                clut = camPos + camSiz*uniform(0, 1);
                break;
            }
            default:
                break;
        }
        zlist->push_back(clut);
        countClutters++;
        LOGGER << "-> MAKE CLUTTER" << " zc=[" << clut.at<double>(0) << "," << clut.at<double>(1) << "]" << endl;
    }
}

/*!
 * Init resources for ICF processing. Declared in base class WiseCameraSimplePeriodicTracker.
 */
void WiseCameraICF_NN::at_tracker_init()
{
    // ICF filters for each target
     ICFs.clear();

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
bool WiseCameraICF_NN::at_tracker_first_sample()
{
    // Called when the first sample (image) is ready
        BASE_TRACE << "FIRST SAMPLE";

        //find the maximum neighborg degree
        max_neigb_network = 0;
        for (int i = 0; i < n_nodes; i++) {

            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");
            WiseCameraICF_NN *c = check_and_cast<WiseCameraICF_NN*>(m);

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
 * KF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraICF_NN::at_tracker_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
	BASE_TRACE << "END FIRST SAMPLE";

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_tracker_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraICF_NN::at_tracker_sample()
{
    // Called when a new sample (image) is ready
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

      //associate measurements to targets
      dataAssociation();

      //compute internal information vector & matrix
      ICFs[tid].prepData(node_controls[tid].detection_miss);

      //start consensus iterations
      consensusStart(tid);
    }
    return true;
}

void WiseCameraICF_NN::dataAssociation()
{
    // compute the association (matching between target positions and measurements)
    cv::Mat matching = compute_association_NN (zlist);

    //Copy assignment to measurement variable 'z' associated to each target
    for (int tid = 0; tid < n_targets; tid++){
        ICFs[tid].z = cv::Mat::zeros(dimM, 1, CV_64F); //empty measurement
        node_controls[tid].detection_miss = true; //miss detection 'by default'

        //association using NN algorithm
        for (unsigned int m = 0; m < zlist.size(); m++)
            if (matching.at<double>(tid,m) == 1) {
                zlist[m].copyTo(ICFs[tid].z);
                node_controls[tid].detection_miss = false;
                LOGGER << " tid=" << tid << " pos=" << mat2vec(ICFs[tid].x_) <<" -> associated to z=[" << mat2vec(ICFs[tid].z) << endl;
            }
    }
}


cv::Mat WiseCameraICF_NN::compute_association_NN (std::vector<cv::Mat> zlist)
{
    cv::Mat dist = cv::Mat::zeros(n_targets, zlist.size(), CV_64F); //variable for target-measurement distance
    cv::Mat asoc = cv::Mat::zeros(n_targets, zlist.size(), CV_64F);
    cv::Mat cost = cv::Mat::zeros(n_targets, zlist.size(), CV_64F);

    // distance between "target estimations" and "measurements" (euclidean - L2 norm)

    for (int tid = 0; tid < n_targets; tid++)
        for (int m = 0; (unsigned int)m < zlist.size(); m++){
            cv::Mat pos = (cv::Mat_<double>(dimM, 1) << ICFs[tid].x_.at<double>(0), ICFs[tid].x_.at<double>(1)); //x-y position of target
            dist.at<double>(tid,m) = cv::norm(pos, zlist[m],cv::NORM_L2);
            //LOGGER << " pos=" << pos <<  " z=" << ztemp[m] << " dist=" << dist.at<double>(tid,m) << endl;
        }

    //COMPUTE assignment using Hungarian algorithm to find best matching

    hungarian(dist, &asoc, &cost);
    //TODO
    //std::cout << "dist=" << print(dist,3) << endl;
    //std::cout << "matches=" << print(asoc,3) << endl;
    //std::cout << "cost=" << print(cost,3) << endl;
    LOGGER << "dist=" << dist << " matches=" << asoc << " cost=" << cost << endl;

    return asoc;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseCameraICF_NN::at_tracker_end_sample()
{
    // Called when a new sample (image) is no longer valid
        LOGGER << "END NEW SAMPLE" << endl;

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


        //for (int tid = 0; tid < n_targets; tid++) {
        //    icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
        //            //int index = findIndexInBuffer(tid, iter_max); // Index of the buffer for the last iteration
        //    int c=0;
        //    for (int i=0; i < n_nodes; i++)
        //        if(ctrl.nb_data_buffer[0].nb_data[i].end_collaboration == true)
        //            c++;
        //    if (c!=ctrl.n_neighbourgs)
        //    {
        //        LOGGER << "node not ready (own, waiting for COLLABORATION END)" << c << "/"<< ctrl.n_neighbourgs << endl;
        //       setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
        //        return false;
        //    }
        //}/**/

        if (_dummy_comms==false) {
                //perform some additional checking at network level since 'real wireless' may desynchronize nodes
                // TODO: implement a protocol to sync the end of the consensus iteration
                for (int i = 0; i< n_nodes; i++)
                if (i!= self) {
                    cModule *m = getParentModule()->getParentModule(); // m=SN
                    m = m->getSubmodule("node", i)->getSubmodule("Application");
                    WiseCameraICF_NN*c = check_and_cast<WiseCameraICF_NN*>(m);

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
 * receives data from its neighbors, stores the pkt content and when all the data is available (from all neighbors),
 * it calls consensusProcess function to initiate a round of consensus when needed
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraICFMessage type)
 */
void WiseCameraICF_NN::process_network_message(WiseApplicationPacket *pkt)
{
    double e2=0,e1 = cv::getTickCount();
    int i=0,c=0, index=-1;

    WiseCameraICFMsg *m = check_and_cast<WiseCameraICFMsg*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    LOGGER << "RX from " << ctl.source << ". Packet content: [ TID=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << ") ]" << endl;

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
                    consensusProcess(tid, (int)ctrl.iter_counter);
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
void WiseCameraICF_NN::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
    // Called when a DirectApplication Message is received
    BASE_TRACE << "HANDLE DIRECT APPLICATION MESSAGE";

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
void WiseCameraICF_NN::consensusStart(int tid)
{
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
 * from all neighbors.
 *
 * @param[in] tid Target ID of the associated ICF structures
 * @param[in] k Number of the current iteration
 */
void WiseCameraICF_NN::consensusProcess(int tid, int k)
{
    LOGGER << " CONSENSUS for k=" <<  k << endl;

       icf::node_ctrl_t &ctrl = node_controls[tid];

       int index = ctrl.findIndexInBuffer(k); // Index of the buffer
       ctrl.nb_data_buffer[index].iter_buffer = -1; //free the buffer position for further usage

       //combine estimations of neighbors
       ICFs[tid].update_state_neighbors(ctrl.nb_data_buffer[index].nb_data,alpha,ctrl.n_neighbourgs,max_neigb_network);

      //restart status of received data
      for (int i=0; i < n_nodes; i++)
          ctrl.nb_data_buffer[index].nb_data[i].rcv_data = false;

      //continue consensus if not exceed the max iterations
      ctrl.iter_counter = ++k;

      //send message to neighbors (posterior state OR collaboration end)
      sendICFmessage(tid);

      //check if data for next consensus round is already buffer
      checkNextConsensusRound(tid,ctrl.iter_counter);

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


void WiseCameraICF_NN::checkNextConsensusRound(int tid, int k)
{
    icf::node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'

    // get data for current consensus iteration of the node
    int index = ctrl.findIndexInBuffer(k); // Index of the buffer

    int c=0;
    for (int i=0; i < n_nodes; i++)
        if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true){
            c++;
        }
    //compute the consensus if we have all neighbor's data
    if (c==ctrl.n_neighbourgs){
        LOGGER << "tid=" << tid << " -> DATA for k=" << node_controls[tid].iter_counter << " already available" << endl;
        consensusProcess(tid, k);
    }
}


/*!
 * Function for finding a minimum edge weight matching given a MxN Edge weight
 * matrix WEIGHTS using the Hungarian Algorithm.
 *
 * An edge weight of Inf indicates that the pair of vertices given by its
 * position have no adjacent edge.
 *
 * @param[in] weights distance between each target and measurement
 * @param[out] outMatches a MxN matrix with ones in the place of the matchings and zeros elsewhere
 * @param[out] outCost the cost of the minimum matching
 */
void WiseCameraICF_NN::hungarian(cv::Mat weights, cv::Mat* outMatches, cv::Mat* outCost)
{
    int rows = weights.rows;
    int cols = weights.cols;
    hungarian_problem_t p;
    int** m = mat_to_matrix(weights,rows,cols);

    hungarian_init(&p, m, rows, cols, HUNGARIAN_MODE_MINIMIZE_COST) ;

    // solve the assignment problem
    hungarian_solve(&p);

    // get the results
    *outMatches = matrix_to_mat(p.assignment, rows, cols);
    *outCost = matrix_to_mat(p.cost, rows, cols);

    // free used memory
    hungarian_free(&p);
    free(m);
}

/*!
 * Function to convert cv::Mat variables to int** variable in order
 * to apply the hungarian problem. To speedup the process, values of
 * source matrix are converted to integer values.
 *
 * @param[in] src Matrix data
 * @param[in] rows Number of rows of the matrix
 * @param[in] cols Number of cols of the matrix
 * @param[out] Matrix as a double pointer (**) of integer values
 */
int** WiseCameraICF_NN::mat_to_matrix(cv::Mat src, int rows, int cols)
{
    int i,j;
    int** r;
    r = (int**)calloc(rows,sizeof(int*));
    for(i=0;i<rows;i++){
        r[i] = (int*)calloc(cols,sizeof(int));
        for(j=0;j<cols;j++)
          r[i][j] = (int)src.at<double>(i,j);
    }
    return r;
}
/*!
 * Function to convert int** into cv::Mat variables
 *
 * @param[in] src Matrix data
 * @param[in] rows Number of rows of the matrix
 * @param[in] cols Number of cols of the matrix
 * @param[out] cv::Mat matrix
 *
*/
cv::Mat WiseCameraICF_NN::matrix_to_mat(int**src, int rows, int cols)
{
    int i,j;
    cv::Mat r = cv::Mat::zeros(rows, cols, CV_64F);
    for(i=0;i<rows;i++)
        for(j=0;j<cols;j++)
          r.at<double>(i,j) = (double)src[i][j];

    return r;
}

/*!
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseCameraICF_NN::sendICFmessage(int tid)
{
    //create message & copy data
       std::ostringstream os;
       os << "ICF: node=" << self << " tid=" << tid << " t=" << tracking_step_counter << " k=" << node_controls[tid].iter_counter;

       WiseCameraICFMsg *pkt = new WiseCameraICFMsg(os.str().c_str(), APPLICATION_PACKET);
       pkt->setTrackingCount(tracking_step_counter); //current step counter
       pkt->setIterationStep(node_controls[tid].iter_counter); //set the current consensus iteration k=1
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

/*!
 * Write results in txt files
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraICF_NN::logResult(int tid)
{
    double delay = simTime().dbl()-node_controls[tid].start_time;
      double err = ICFs[tid].compute_error();
      ICFs[tid].errAcc += err;

      LOGGER << "tid=" << tid <<" t="<< tracking_step_counter << " FINAL -> x=" << mat2vec(ICFs[tid].x) << " J=" << cv::trace(ICFs[tid].J).val[0]
            << " x_=" <<  mat2vec(ICFs[tid].x_) << "," << "] J_=" << cv::trace(ICFs[tid].J_).val[0]
            << " z=" << mat2vec(ICFs[tid].z) << " gt=" << mat2vec(ICFs[tid].xgt)<< endl;

      *writerICFNN << std::setprecision(6) << simTime().dbl() << "\t" << tracking_step_counter << "\t" << self << "\t" << tid  << "\t" <<
              setprecision(4) << ICFs[tid].z.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].z.at<double>(1) << "\t" <<
              setprecision(4) << ICFs[tid].x_.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].x_.at<double>(1) << "\t" <<
              setprecision(4) << ICFs[tid].x.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].x.at<double>(1) << "\t" <<
              setprecision(4) << ICFs[tid].xgt.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].xgt.at<double>(1) << "\t" <<
              setprecision(4) << err << "\t" << setprecision(4) <<  ICFs[tid].errAcc << "\t" << delay << endl;
}
