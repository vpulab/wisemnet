// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#include "WiseCameraClusterICF.h"
#include "TMacControlMessage_m.h"
#include "WiseCameraClusterICFMsg_m.h"

Define_Module(WiseCameraClusterICF);

//Structures/variables for logging
#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE trace() << "WISEICF: "

ofstream WiseCameraClusterICF::logger;
std::ofstream *writerCICF=NULL;

using namespace icfcluster;//for using all structures in the namespace of WiseCameraST_ICF_utils.h

/*! Class destructor */
WiseCameraClusterICF::~WiseCameraClusterICF()
{
    if (writerCICF) {
        writerCICF->close();
        delete writerCICF;
    }
}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraClusterICF::at_startup()
{
    // Called upon simulation start-up
    BASE_TRACE << "START-UP";

    readParameters();//Read parameters
    initStructures();//create internal structures

    //Create streams for logging results
    if (!logger.is_open())
        logger.open("myLog.txt");

    if (writerCICF == NULL)
        writerCICF = new ofstream();

    std::ostringstream os;
    os << "res/icf_results_Nc" << std::setfill('0') << std::setw(3) << n_nodes << "_Nt" << std::setfill('0') << std::setw(2) << n_targets << "_iter" << std::setfill('0') << std::setw(2) << iter_max << ".res";

    if (!writerCICF->is_open()){
        writerCICF->open(os.str().c_str());
        *writerCICF << "# processNoiseCov=" << procNoiseCov << " measurementNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << endl;
        *writerCICF << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc" << endl;
        *writerCICF << "#t_sim\tt_step\tNID\tTID\tZx\tZy\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc" << endl;
    }

    LOGGER << "processNoiseCov=" << procNoiseCov << " measurementNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << endl;
}

/*! Read parameters of MTT_ICF*/
void WiseCameraClusterICF::readParameters()
{
    // Access related-module parameters (read number of targets)
    cModule *network = getParentModule()->getParentModule();
    n_targets = network->par("numPhysicalProcesses");

    //READ PARAMETERS
    //ICF Filter settings
    procNoiseCov = hasPar("procNoiseCov") ? par("procNoiseCov") : 0.1;
    measNoiseCov = hasPar("measNoiseCov") ? par("measNoiseCov") : 1e-1;

    // Consensus settings
    iter_max = hasPar("iter_max") ? par("iter_max") : 20;
    alpha = hasPar("alpha") ? par("alpha") : 0.1;
}

/*! Initialization of structures for tracking targets*/
void WiseCameraClusterICF::initStructures()
{
   //initialize structures for internal variables
   xgt.clear();
   z.clear();
   error.clear();
   errorAcc.clear();

   xgt.resize(n_targets);
   z.resize(n_targets);
   error.resize(n_targets);
   errorAcc.resize(n_targets);

   // Control structures & ICF filters for each target
   ICFs.clear();
   //ICFs.resize(n_targets);
   this->dimS = DIM_STATE_T_4D;
   this->dimM = DIM_MEASUREMENT_T_2D;

   // Create & initialize control structures for each target
   for (int tid = 0; tid < n_targets; tid++)
   {
       //generic structures
       error[tid]    = 0;
       errorAcc[tid] = 0;
       xgt[tid]      = cv::Mat::zeros(dimS, 1, CV_64F);
       z[tid]        = cv::Mat::zeros(dimM, 1, CV_64F);

       //CREATE ICF FILTER
       ICF_t icf;//create ICF filter
       icf.eyeS = cv::Mat::eye(dimS, dimS, CV_64F);
       icf.dimS = DIM_STATE_T_4D;
       icf.dimM = DIM_MEASUREMENT_T_2D;

       //prior, posterior and covariance of the state
       icf.x_ = cv::Mat::zeros(dimS, 1, CV_64F); //prior state
       icf.x  = cv::Mat::zeros(dimS, 1, CV_64F); //posterior state
       icf.P  = (cv::Mat_<double>(dimS, dimS) << 5,0,0,0, 0,5,0,0, 0,0,2,0, 0,0,0,2); //prior state covariance
       icf.Pinv  = cv::Mat::zeros(dimS, dimS, CV_64F);
       icf.Pinv  = icf.P.inv(cv::DECOMP_SVD); //prior state covariance

       //transition matrix
       icf.A  = (cv::Mat_<double>(dimS, dimS) << 1,0,1,0, 0,1,0,1, 0,0,1,0, 0,0,0,1);
       icf.At = cv::Mat::zeros(dimS, dimS, CV_64F);
       cv::transpose(icf.A, icf.At);

       //measurement matrix
       icf.H    = (cv::Mat_<double>(dimM, dimS) << 1,0,0,0, 0,1,0,0);
       icf.Ht = cv::Mat::zeros(dimS, dimM, CV_64F);
       cv::transpose(icf.H, icf.Ht);

       //measurement covariance
       icf.Rinv = measNoiseCov * cv::Mat::eye(dimM, dimM, CV_64F);
       icf.Rinv = 1.0 * icf.Rinv.inv(cv::DECOMP_SVD);

       //process covariance
       icf.Q  = procNoiseCov * (cv::Mat_<double>(dimS, dimS) << 1,0,0.1,0, 0,1,0,0.1, 0,0,0.1,0, 0,0,0,0.1);

       //information-based variables
       icf.J_ = cv::Mat::zeros(dimS, dimS, CV_64F); //prior information matrix
       icf.J_ = icf.eyeS/icf.P;
       icf.J  = cv::Mat::zeros(dimS, dimS, CV_64F); //posterior information matrix
       icf.v  = cv::Mat::zeros(dimS, 1, CV_64F); //??
       icf.V  = cv::Mat::zeros(dimS, dimS, CV_64F); //??

       LOGGER << "ICF CONFIG" << endl << "A=" << endl << icf.A << endl << "H=" << endl << icf.H
               << endl << "P=" << endl << icf.P << endl << "Pinv=" << endl << icf.Pinv << endl
               << endl << "Rinv=" << endl << icf.Rinv << endl << "Q=" << endl << icf.Q << endl;

       ICFs.push_back(icf);

       //CREATE ASSOCIATED CONTROL STRUCTURE
       node_ctrl_t ctrl;
       ctrl.initialized = false;
       ctrl.detection_miss = false;
       ctrl.iter_counter = 0; // iteration of the consensus
       ctrl.n_neighbourgs =  neighborsFOV.size();//we consider as neigbourghs the FOV graph

       //buffer for neighbor's data of MAX_SIZE_BUFFER iterations
       ctrl.nb_data_buffer.clear();
       ctrl.nb_data_buffer.resize(MAX_SIZE_BUFFER);

       for (int j=0; j<MAX_SIZE_BUFFER;j++){
           //create control for neighbor data
           ctrl.nb_data_buffer[j].nb_data.clear();
           ctrl.nb_data_buffer[j].nb_data.resize(n_nodes);
           ctrl.nb_data_buffer[j].iter_buffer=-1;

           //fill neighbor data with zeros
           for (int n=0; n<n_nodes; n++){
              neigbourg_data_t &nb_node = ctrl.nb_data_buffer[j].nb_data[n]; //associated neigbour's data
              nb_node.rcv_data = false;  // data not received yet
              nb_node.v = cv::Mat::zeros(dimS, 1, cv::DataType<double>::type);    //information vector of node
              nb_node.V = cv::Mat::zeros(dimS, dimS, cv::DataType<double>::type);    //information vector of node
           }
       }

      node_controls.push_back(ctrl);
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
void WiseCameraClusterICF::make_measurements(const vector<WiseTargetDetection>&dt)
{
    int tid=0;
    vector<const WiseTargetDetection*> ordered;
    ordered.resize(n_targets, NULL);

    // reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        ordered[d->target_id] = &(*d);

    // get data from ordered list of 'WiseTargetDetections' and copy data to 'state_t' and 'measurement_t' lists
    for (tid = 0; tid < n_targets && (unsigned int)tid < dt.size(); tid++)
    {
        LOGGER << "tid=" << tid << " -> MAKE MEASUREMENT" << endl;

        if (ordered[tid] == NULL) {
            node_controls[tid].detection_miss = true;
            continue;
        }
        const WiseTargetDetection &d = *(ordered[tid]);
        if (!d.valid) {
            node_controls[tid].detection_miss = true;
            continue;
        }

        //measurements + Gaussian noise
        z[tid].at<double>(0)  = (d.ext_bb_x_tl + d.ext_bb_x_br) / 2 + normal(0, sqrt(measNoiseCov), 0);
        z[tid].at<double>(1)  = (d.ext_bb_y_tl + d.ext_bb_y_br) / 2 + normal(0, sqrt(measNoiseCov), 0);
        node_controls[tid].detection_miss = false;

        LOGGER << " z=" << z[tid] << endl;
    }

    // Set remaining targets to detection_miss (ie, targets not processed due to non existing measurements)
    for (; tid < n_targets; tid++)
        node_controls[tid].detection_miss = true;

    //copy the real positions in the ground-truth lists
    for (tid = 0; tid < n_targets; tid++) {
        const WiseTargetDetection &d = *(ordered[tid]);
        xgt[tid].at<double>(0) = (d.true_bb_x_tl + d.true_bb_x_br) / 2;
        xgt[tid].at<double>(1) = (d.true_bb_y_tl + d.true_bb_y_br) / 2;
        LOGGER << "tid="<< tid << " xgt=" << xgt[tid] << endl;
    }
}

/*!
 * Init resources for ICF processing. Declared in base class WiseCameraSimplePeriodicTracker.
 */
void WiseCameraClusterICF::at_tracker_init()
{

}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraClusterICF::at_tracker_first_sample()
{
	// Called when the first sample (image) is ready
	BASE_TRACE << "FIRST SAMPLE";
	
	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	//at_tracker_sample(); // option 2

	//find the maximum neigb
	max_neigb_network = 0;
	for (int i = 0; i < n_nodes; i++) {

	    cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseCameraClusterICF *c = check_and_cast<WiseCameraClusterICF*>(m);

        if (c->neighborsFOV.size() > (unsigned int)max_neigb_network)
            max_neigb_network = c->neighborsFOV.size();
    }

	//initialize targets
	 for (int tid = 0; tid < n_targets; tid++){

	    ICF_t &icf = ICFs[tid];

        icf.x_.at<double>(0) = xgt[tid].at<double>(0) + normal(0,sqrt(icf.P.at<double>(0,0)));
        icf.x_.at<double>(1) = xgt[tid].at<double>(1) + normal(0,sqrt(icf.P.at<double>(1,1)));
        icf.x_.at<double>(2) = 0 + normal(0,sqrt(icf.P.at<double>(2,2)));
        icf.x_.at<double>(3) = 0 + normal(0,sqrt(icf.P.at<double>(3,3)));

        node_controls[tid].initialized = true;
        LOGGER << " tid=" << tid << " INIT x=" << icf.x_ << " xgt=" << xgt[tid] << endl;
    }

	//do processing
	return at_tracker_sample();
}

/*!
 * KF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraClusterICF::at_tracker_end_first_sample()
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
bool WiseCameraClusterICF::at_tracker_sample()
{
    // Called when a new sample (image) is ready
    tracking_step_counter++;

    // NOTE: Measurement has been made through the make_measurements() method and is available in the measurement vector
    for (int tid = 0; tid < n_targets; tid++)
    {
        LOGGER << "tid=" << tid << " -> PROCESS SAMPLE t=" <<  tracking_step_counter << endl;

        //get elements in the lists for the target ID
        node_ctrl_t &ctrl = node_controls[tid];

        //check if there is consensus under progress
        if (ctrl.iter_counter > 0){
            LOGGER << "Trying to start consensus without finishing the previous one> curr=" << ctrl.iter_counter << " max=" << iter_max << endl;
            return false;
        }

        prepData(tid); //compute internal information vector & matrix
        consensusStart(tid); //start consensus iterations
    }
    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseCameraClusterICF::at_tracker_end_sample()
{
	// Called when a new sample (image) is no longer valid
	LOGGER << "END NEW SAMPLE";
	return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it calls consensusProcess function to initiate a round of consensus when needed
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraICFMessage type)
 */
void WiseCameraClusterICF::process_network_message(WiseApplicationPacket *pkt)
{
    WiseCameraClusterICFMsg *m = check_and_cast<WiseCameraClusterICFMsg*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    LOGGER << "RX from " << ctl.source << ". Packet content: [ TID=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << ") ]" << endl;

    //source node and target IDs of recv packet
    int node = atoi(ctl.source.c_str());
    int tid = m->getTargetID();
    node_ctrl_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'

    // store recv data in buffer
    int index = findIndexInBuffer(tid, (int)m->getIterationStep()); // get the index of the buffer for the iteration of the received data
    storeDataInBuffer(tid, index, node, m); // store data in buffer

    //check matching of iteration number between node and recv data
    if (m->getIterationStep() != ctrl.iter_counter){
       LOGGER << "WRONG ITERATION!! (curr=" <<  ctrl.iter_counter << " rcv=" << m->getIterationStep() << ")" << endl;
       return;
    }

    // get data for current consensus iteration of the node
    index = findIndexInBuffer(tid, (int)ctrl.iter_counter); // Index of the buffer
    std::vector<neigbourg_data_t> &curr_nb_data= ctrl.nb_data_buffer[index].nb_data; // data of the buffer

    //count the number of received data from nodes (to start consensus if all data has been recv)
    int c = 0;
    for (int i=0; i < n_nodes; i++)
       if (curr_nb_data[i].rcv_data == true)
           c++;

    //compute the consensus if we have all neighbor's data
    if (c==ctrl.n_neighbourgs)
        consensusProcess(tid, (int)ctrl.iter_counter);
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraClusterICF::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
    // Called when a DirectApplication Message is received
    BASE_TRACE << "HANDLE DIRECT APPLICATION MESSAGE";

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}

/*!
 * Initialization of ICF for consensus (and also the first initial target position from the first sample).
 *
 * @param[in] tid Target ID of the associated ICF structures
 */
void WiseCameraClusterICF::prepData(int tid)
{
    node_ctrl_t &ctrl = node_controls[tid];
    ICF_t &icf = ICFs[tid];

    //initialize ICF (if we have data and it is not already initialized)
   /*if (ctrl.detection_miss == false && ctrl.initialized == false) {
        icf.x_.at<double>(0) = xgt[tid].at<double>(0) + normal(0,sqrt(icf.P.at<double>(0,0)));
        icf.x_.at<double>(1) = xgt[tid].at<double>(1) + normal(0,sqrt(icf.P.at<double>(1,1)));
        icf.x_.at<double>(2) = xgt[tid].at<double>(2) + normal(0,sqrt(icf.P.at<double>(2,2)));
        icf.x_.at<double>(3) = xgt[tid].at<double>(3) + normal(0,sqrt(icf.P.at<double>(3,3)));

        ctrl.initialized = true;
        LOGGER << " tid=" << tid << " INIT x=" << icf.x_ << " xgt=" << xgt[tid] << endl;
      }*/

    cv::Mat u = cv::Mat::zeros(dimS, 1, CV_64F);    //information vector
    cv::Mat U = cv::Mat::zeros(dimS, dimS, CV_64F); //information matrix

    // compute u,U - empty if target not in FOV (ie, no detection)
    if (ctrl.detection_miss == false) {
        u = icf.Ht * icf.Rinv * z[tid];
        U = icf.Ht * icf.Rinv * icf.H;
    }

    //LOGGER << "Ht=" << icf.Ht << " H=" << icf.H << " Rinv=" << icf.Rinv << endl;
    //LOGGER << "u=" << u << " U=" << U << endl;

    icf.v = (1/(double)ctrl.n_neighbourgs * icf.J_ * icf.x_) + u;
    icf.V = (1/(double)ctrl.n_neighbourgs * icf.J_) + U;
    //LOGGER << "v=" << icf.v << " V=" << icf.V << endl;
}

/*!
 * Function to start the consensus iterations. It sends data to neighbors
 * (if any). If there are not, then it estimates target position.
 *
 * @param[in] tid Target ID of the associated ICF structures
 */
void WiseCameraClusterICF::consensusStart(int tid)
{
    node_ctrl_t &ctrl = node_controls[tid];

    ctrl.iter_counter=1;
    if (neighborsFOV.size() > 0 && iter_max > 0) //no neighbors
        sendICFmessage(tid); // send estimation to neighbors/**/
    else
        estimate(tid); //perform final state estimation
}

/*!
 * Function to process a consensus iteration after receiving data
 * from all neigborgs.
 *
 * @param[in] tid Target ID of the associated ICF structures
 * @param[in] k Number of the current iteration
 */
void WiseCameraClusterICF::consensusProcess(int tid, int k)
{
    LOGGER << " CONSENSUS for k=" <<  k << endl;

    node_ctrl_t &ctrl = node_controls[tid];
    ICF_t &icf = ICFs[tid];

    int index = findIndexInBuffer(tid, k); // Index of the buffer
    std::vector<neigbourg_data_t> &curr_nb_data= ctrl.nb_data_buffer[index].nb_data; // data of the buffer
    ctrl.nb_data_buffer[index].iter_buffer = -1; //free the buffer position for further usage

    cv::Mat vtemp = cv::Mat::zeros(dimS, 1, cv::DataType<double>::type);    //information vector of node
    cv::Mat Vtemp = cv::Mat::zeros(dimS, dimS, cv::DataType<double>::type);    //information vector of node

    vector<neigbourg_data_t>::const_iterator n;
    for (n = curr_nb_data.begin(); n != curr_nb_data.end(); ++n)
       if (n->rcv_data == true)
       {
           vtemp = vtemp + n->v;
           Vtemp = Vtemp + n->V;
           //std::cout << "vrec=" << cv::sum(n->v).val[0] << " Vrec=" << cv::sum(n->V).val[0] << endl;
       }

    ///std::cout << "vtemp=" << cv::sum(icf.vtemp).val[0] << " Vtemp=" << cv::sum(icf.Vtemp).val[0] << endl;

    double Delta = (double)ctrl.n_neighbourgs;
    double eps = alpha/(double)max_neigb_network;

    //LOGGER << "v=" << cv::sum(icf.v).val[0] << " V=" << cv::sum(icf.V).val[0] << endl;
    //LOGGER << "vtemp=" << cv::sum(icf.vtemp).val[0] << " Vtemp=" << cv::sum(icf.Vtemp).val[0] << endl;
    //add((1-Delta*eps)*icf.v, eps*icf.vtemp ,icf.v);
    //add((1-Delta*eps)*icf.V, eps*icf.Vtemp ,icf.V);
    icf.v = (1-Delta*eps)*icf.v + eps*vtemp;
    icf.V = (1-Delta*eps)*icf.V + eps*Vtemp;
    //LOGGER << "v=" << cv::sum(icf.v).val[0] << " V=" << cv::sum(icf.V).val[0] << endl;
    //LOGGER << "vtemp=" << cv::sum(icf.vtemp).val[0] << " Vtemp=" << cv::sum(icf.Vtemp).val[0] << endl;

   //restart status of received data
   for (int i=0; i < n_nodes; i++)
       curr_nb_data[i].rcv_data = false;

   //continue consensus if not exceed the max iterations
   ctrl.iter_counter = ++k;
   if (ctrl.iter_counter <=  iter_max)
       sendICFmessage(tid); //send posterior state to neighbors
   else
       estimate(tid); //perform final state estimation
}

/*!
 * Function to estimate the final result after completing the consensus iterations
 *
 * @param[in] tid Target ID of the associated ICF structures
 */
void WiseCameraClusterICF::estimate(int tid)
{
   node_ctrl_t &ctrl = node_controls[tid];
   ICF_t &icf = ICFs[tid];

    //estimation
   icf.x = icf.V.inv(cv::DECOMP_SVD)*icf.v;
   icf.J = ctrl.n_neighbourgs * icf.V;

   //prediction for next timestep
   icf.x_ = icf.A * icf.x;
   icf.J_ = icf.eyeS/(icf.J*icf.At+icf.Q);

   //return to initial status
   ctrl.iter_counter=0;

   //std::cout << "node=" << self << " tid=" << tid << " consensus k=" <<  ctrl.iter_counter << " x=" << icf.x << endl;

   //save data
   logResult(tid);
}

/*!
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseCameraClusterICF::sendICFmessage(int tid)
{
    std::ostringstream os;
    node_ctrl_t &ctrl = node_controls[tid];
    LOGGER << "tid=" << tid << " -> SENDING MSG to FOVs for k=" << ctrl.iter_counter << " (cid=" << cv::sum(ICFs[tid].V).val[0]+cv::sum(ICFs[tid].v).val[0] << ")"<< endl;

    //create message & copy data
    os << "ICF: node=" << self << " tid=" << tid << " t=" << tracking_step_counter << " k=" << ctrl.iter_counter;
    WiseCameraClusterICFMsg *pkt = new WiseCameraClusterICFMsg(os.str().c_str(), APPLICATION_PACKET);

    pkt->setICFv(ICFs[tid].v); //information vector
    pkt->setICFV(ICFs[tid].V); //information vector

    pkt->setTrackingCount(tracking_step_counter); //current step counter
    pkt->setIterationStep(ctrl.iter_counter); //set the current consensus iteration k=1
    pkt->setTargetID(tid); //target id
    pkt->setType(WISE_APP_NORMAL); //normal APP for the network

    // We can distribute the data among neighbourgs using the:
    // 1- COM graph
    //pkt->setTypeNeighbour(WISE_NEIGHBOUR_COM);
    //return send_messageNeighboursCOM(pkt);//option1
    // 2- FOV graph
    pkt->setTypeNeighbour(WISE_NEIGHBOUR_FOV); //type defined in "WiseCameraSimplePeriodicTracker.msg"
    return send_messageNeighboursFOV(pkt);//option2/**/
}

/*!
 * Write results in txt files
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraClusterICF::logResult(int tid)
{
    ICF_t &icf = ICFs[tid];

    double xe = icf.x.at<double>(0) - xgt[tid].at<double>(0); //x-error
    double ye = icf.x.at<double>(1) - xgt[tid].at<double>(1); //y-error

    error[tid] = sqrt(xe*xe + ye*ye); //euclidean distance (l1 norm)
    errorAcc[tid] = errorAcc[tid] + error[tid];

    LOGGER << "tid=" << tid << " -> est:" << icf.x << " Z:" << z[tid] << " gt:" << xgt[tid] << " for t="<< tracking_step_counter << endl;

    *writerCICF << simTime() << "\t" << tracking_step_counter << "\t" << self << "\t" << tid  << "\t" <<
            setprecision(4) << z[tid].at<double>(0) << "\t" << setprecision(4) << z[tid].at<double>(1) << "\t" <<
            setprecision(4) << icf.x_.at<double>(0) << "\t" << setprecision(4) << icf.x_.at<double>(1) << "\t" <<
            setprecision(4) << icf.x.at<double>(0) << "\t" << setprecision(4) << icf.x.at<double>(1) << "\t" <<
            setprecision(4) << xgt[tid].at<double>(0) << "\t" << setprecision(4) << xgt[tid].at<double>(1) << "\t" <<
            setprecision(4) << error[tid] << "\t" << setprecision(4) <<  errorAcc[tid] << endl;
}

/*!
 * This function searches in the buffer for the index corresponding to a given target ID and iteration index.
 *
 * @param[in] tid Target ID
 * @param[in] iter_index Index of the consensus iteration
 * @return The index of the buffer with the data or the next available position to store data.
 *         Returns -1 if there are no available positions and there are no data related with the "iteration"
 */
int WiseCameraClusterICF::findIndexInBuffer(int tid, int iter_index)
{
    node_ctrl_t &ctrl = node_controls[tid]; //control for target
    int index=-1;

    //look for the index where the data of the iteration is stored in the buffer
    for (int i=0;i<MAX_SIZE_BUFFER;i++)
       if (ctrl.nb_data_buffer[i].iter_buffer == iter_index) {
           index = i;
           break;
       }

    //If data is not found, look for the next available position in buffer
    if (index == -1)
        for (int i=0;i<MAX_SIZE_BUFFER;i++)
            if (ctrl.nb_data_buffer[i].iter_buffer==-1) {
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
void WiseCameraClusterICF::storeDataInBuffer(int tid, int indBuf, int nodeID, WiseCameraClusterICFMsg *m)
{
    node_ctrl_t &ctrl = node_controls[tid]; //control for target

    if (indBuf == -1)
        LOGGER << endl << "WRONG INDEX!!!" << endl;

    //store data in the buffer
    ctrl.nb_data_buffer[indBuf].iter_buffer = m->getIterationStep();
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].rcv_data = true;
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].tid = tid;
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].v = m->getICFv();
    ctrl.nb_data_buffer[indBuf].nb_data[nodeID].V = m->getICFV();
}
