// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the MTIC-consensus tracker for multiple targets:
//         Kamal et al, "Distributed Multi-Target Tracking and Data Association in Vision Networks",
//         IEEE TPAMI 2016.
//         http://ieeexplore.ieee.org/document/7286852/
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#include "WiseCameraMTIC.h"
#include "TMacControlMessage_m.h"
#include "WiseUtils.h"
#include <cmath>

Define_Module(WiseCameraMTIC);

//Structures/variables for logging
#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE trace() << "WISEMTIC: "

ofstream WiseCameraMTIC::logger; //mylog.txt
std::ofstream *writerICFMTIC=NULL;//other logs

using namespace mtic;//for using all structures in the namespace of WiseCameraMTIC_utils.h

/*! Class destructor */
WiseCameraMTIC::~WiseCameraMTIC()
{
    LOGGER << " Generated " << countClutters/n_targets << " clutters/target for " << this->tracking_step_counter << " samples"<< std::endl;
    if (writerICFMTIC) {
        writerICFMTIC->close();
        delete writerICFMTIC;
        writerICFMTIC=NULL;
    }
}

void WiseCameraMTIC::at_finishSpecific()
{
    declareOutput("Generated clutters/target");
    collectOutput("Generated clutters/target", "", countClutters/n_targets);
}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraMTIC::at_startup()
{
    // Called upon simulation start-up
    BASE_TRACE << "START-UP";

    readParameters();//Read parameters
    initStructures();//create internal structures

    //Create streams for logging results
    if (writerICFMTIC == NULL)
        writerICFMTIC = new ofstream();

    if(collectAccuracyStats) {
        std::ostringstream os;
        os << "res/MTIC" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".dat";

        if (!writerICFMTIC->is_open()){
            writerICFMTIC->open(os.str().c_str());
            *writerICFMTIC << "# processNoiseCov=" << procNoiseCov << " measurementNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << endl;
            *writerICFMTIC << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc,ResultsDelay" << endl;
            *writerICFMTIC << "#t_sim\tt_step\tNID\tTID\tZx\tZy\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc\tDelay" << endl;
        }
    }

    if(collectPowerStats) {
        std::ostringstream os1;
        os1 << "res/MTIC" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max
          << "_CPU" << std::setfill('0') << std::setw(3) << resMgr->getPROClk()/1e5 << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user()
          << ".res" << std::setfill('0') << std::setw(3) << self;
        resMgr->initLogger(os1.str().c_str(), self, self); //energy-consumption log
    }

    if (collectNetworkStats) {
        std::ostringstream os2;
        os2 << "res/MTIC" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << n_targets << "_I" << std::setfill('0') << std::setw(2) << iter_max << ".rad";
        radioModule->initLogger(os2.str().c_str());
    }

    if (!logger.is_open())
            logger.open("myLog.txt");

    LOGGER << "processNoiseCov=" << procNoiseCov << " measurementNoiseCov=" << measNoiseCov << " iter_max=" << iter_max << " alpha=" << alpha << " lambda=" << lambda << endl;
}

/*! Read parameters of MTT_ICF*/
void WiseCameraMTIC::readParameters()
{
    // Access related-module parameters (read number of targets)
   cModule *network = getParentModule()->getParentModule();
   n_targets = network->par("numPhysicalProcesses");

   //ICF Filter settings
   procNoiseCov = hasPar("procNoiseCov") ? par("procNoiseCov") : 0.1;
   measNoiseCov = hasPar("measNoiseCov") ? par("measNoiseCov") : 1e-1;

   // Consensus settings
   iter_max = hasPar("iter_max") ? par("iter_max") : 20;
   alpha = hasPar("alpha") ? par("alpha").doubleValue() : 0.1;
   share = hasPar("share")?par("share").stringValue() : "COM";

    //Association parameters of NN algorithm
    lambda = hasPar("lambda") ? par("lambda").doubleValue() : 0.0; //clutter level

    collectNetworkStats = hasPar("collectNetworkStats")?par("collectNetworkStats").boolValue() : false;
    collectPowerStats = hasPar("collectPowerStats")?par("collectPowerStats").boolValue() : false;
    collectAccuracyStats = hasPar("collectAccuracyStats")?par("collectAccuracyStats").boolValue() : false;
}

/*! Initialization of structures for tracking targets*/
void WiseCameraMTIC::initStructures()
{
     dimS = DIM_STATE_T_4D;
     dimM = DIM_MEASUREMENT_T_2D;

     countClutters = 0;

     //status for each target
     camStatus.clear();
     camStatus.resize(n_targets);

     node_controls.clear();

     for (int tid = 0; tid < n_targets; tid++)
     {
         //create control data
         mtic::node_ctrl_mtic_t ctrl(tid,n_nodes,mtic::MAX_SIZE_BUFFER,dimS);

         //determine the neighborhood to share (FOV or COM graphs)
         share.compare("FOV") == 0 ? ctrl.n_neighbourgs = neighborsFOV.size(): ctrl.n_neighbourgs = neighborsCOM.size();

         node_controls.push_back(ctrl);//store in list
     }
     LOGGER << "Created resources (" << node_controls.size() << " structs) for "<< n_targets << " targets, " << n_nodes << " nodes and " << mtic::MAX_SIZE_BUFFER << " max iterations to buffer" << endl;
  }

/*!
 * This function defines the behavior to specific alarms generated by the algorithm. To be implemented in superclasses of WiseCameraPeriodicAlgo.
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseCameraMTIC::at_timer_fired(int index)
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
void WiseCameraMTIC::handleMacControlMessage(cMessage *c)
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
void WiseCameraMTIC::make_measurements(const vector<WiseTargetDetection>&dt)
{
    //reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
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

    //clear list of measurements (possibly with data from the previous iteration)
    zlist.clear();


    // generate measurements from ground-truth data in world coordinates (assuming known external calibration)
    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        if ((*d).valid == true) {
            cv::Mat z_ = cv::Mat::zeros(dimM, 1, CV_64F);
            z_.at<double>(0)  = ((*d).ext_bb_x_tl + (*d).ext_bb_x_br) / 2 + normal(0, measNoiseCov, 0);
            z_.at<double>(1)  = ((*d).ext_bb_y_tl + (*d).ext_bb_y_br) / 2 + normal(0, measNoiseCov, 0);
            zlist.push_back(z_);
            LOGGER << " -> MAKE MEASUREMENT" << " z=[" << z_.at<double>(0) << "," << z_.at<double>(1) << "]" << endl;
        }

    //generate clutter measurements
    generateClutterMeasurements();
}

void WiseCameraMTIC::generateClutterMeasurements ()
{
    srand(cv::getTickCount()); // Seed the time
    int numClutters = poisson(lambda); //TODO: change seed for each simulation
    LOGGER << " Creating " << numClutters << " clutter measurements" << endl;
    for (int c = 1; c <= numClutters;c++){

        cv::Mat clut = cv::Mat::zeros(dimM, 1, CV_64F);//temporal variable to store one clutter measurement

        switch (camera_info.get_fov_type())
        {
            // Generate clutter measurements for directional FOVs
            case WiseCameraInfo::DIRECTIONAL:
            {
               //check if target is inside camera's FOV
               double dist=-1;
               int x_init,y_init=0;

               //get the points/vertex describing the camera FOV
               WiseCameraInfo::fov_di_t fov;
               camera_info.get_fov_di(fov);
               std::vector<cv::Point> points;
               points.clear();
               points.push_back(cvPoint(fov.c_px,fov.c_py));
               points.push_back(cvPoint(fov.c_cx,fov.c_cy));
               points.push_back(cvPoint(fov.c_bx,fov.c_by));
               points.push_back(cvPoint(fov.c_px,fov.c_py));

               //the point lies outside the FOV (dist == 0, on the edge; dist == 1, inside)
               while(dist < 0)
               {
                   srand(cv::getTickCount()); // Seed the time
                   x_init = fmod(rand(),(fov.max_x-fov.min_x + 1)) + fov.min_x; //get random "x" position
                   y_init = fmod(rand(),(fov.max_y-fov.min_y + 1)) + fov.min_y; //get random "y" position
                   dist = cv::pointPolygonTest(points, cvPoint(x_init, y_init), false); //check if inside FOV
               }
               clut = (cv::Mat_<double>(2, 1) << x_init, y_init);
               break;
            }

            // Generate clutter measurements for homogeneous FOVs (bounding box)
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
        zlist.push_back(clut);
        countClutters++;
        LOGGER << "-> MAKE CLUTTER" << " zc=[" << clut.at<double>(0) << "," << clut.at<double>(1) << "]" << endl;
    }

    //ICFs[tid].z.at<double>(0) -> number of measurements corresponding to clutter
    //ICFs[tid].z.at<double>(1) -> number of measurements corresponding to targets
    for (int tid = 0; tid < n_targets; tid++)
        ICFs[tid].z.at<double>(0) = numClutters;
}

/*!
 * Init resources for ICF processing. Declared in base class WiseCameraSimplePeriodicTracker.
 */
void WiseCameraMTIC::at_tracker_init()
{
     ICFs.clear();

     // ICF filters for each target
     for (int tid = 0; tid < n_targets; tid++)
     {
        //create ICF filter
        mtic::MTIC_t icf(dimS,dimM,procNoiseCov,measNoiseCov,lambda,n_nodes);
        ICFs.push_back(icf); //store in list

        //update the neighbourgs to share (FOV or COM graphs)
        mtic::node_ctrl_mtic_t& ctrl = node_controls[tid];
        share.compare("FOV") == 0 ? ctrl.n_neighbourgs = neighborsFOV.size(): ctrl.n_neighbourgs = neighborsCOM.size();
     }
     LOGGER << "Created resources (" << ICFs.size() << " ICF filters) for "<< n_targets << " targets, " << n_nodes << " nodes and " << mtic::MAX_SIZE_BUFFER << " iterations" << endl;
}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseCameraMTIC::at_tracker_first_sample()
{
    // Called when the first sample (image) is ready
    BASE_TRACE << "FIRST SAMPLE";

    //find the maximum neighbor degree
    max_neigb_network = 0;
    for (int i = 0; i < n_nodes; i++) {

        cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseCameraMTIC *c = check_and_cast<WiseCameraMTIC*>(m);

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

        mtic::MTIC_t &icf = ICFs[tid];
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
bool WiseCameraMTIC::at_tracker_end_first_sample()
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
bool WiseCameraMTIC::at_tracker_sample()
{
    // Called when a new sample (image) is ready
    tracking_step_counter++;

    //associate measurements to targets
    dataAssociation();

    // NOTE: Measurements are computed in the make_measurements() method
    //       "zlist" variable has the list of measurements for the current time step
    for (int tid = 0; tid < n_targets; tid++)
    {
      camStatus[tid] = mtic::COLLABORATION; //flag to indicate that the camera is busy doing consensus

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

void WiseCameraMTIC::dataAssociation()
{
    double b=0;
    cv::Mat y, Ptilde;

    for (int tid = 0; tid < n_targets; tid++){

        //ICFs[tid].z = cv::Mat::zeros(dimM, 1, CV_64F); //empty measurement
        node_controls[tid].detection_miss = true; //miss detection 'by default'

        //compute S
        cv::Mat S = ICFs[tid].R + ICFs[tid].H *ICFs[tid].J_.inv(cv::DECOMP_SVD) * ICFs[tid].H.t();

        //compute Pd
        WiseCameraInfo::fov_di_t fov;
        camera_info.get_fov_di(fov);
        double Pd = findPd(ICFs[tid].H*ICFs[tid].x_, S, fov);

        //NOTE: the 'lamdaf' parameter should have values, otherwise anything close to the target may be integrated!!
        //compute b
        b=2*M_PI*ICFs[tid].lamdaf*sqrt(cv::determinant(S)) * (1.0-Pd*ICFs[tid].Pg)/Pd;
        //LOGGER << "tid="<< tid << "lamdaf="<<ICFs[tid].lamdaf<<" S="<<mat2vec(S)<< " Pd="<< Pd << " b="<<b << std::endl;

        //initialize stuff
        y = cv::Mat::zeros(dimM, 1, CV_64F);
        Ptilde = cv::Mat::zeros(dimM,dimM, CV_64F);

        if (zlist.size() > 0)
        {
            LOGGER << "tid="<< tid << " S="<<S <<"\n Doing association: "<< zlist.size() << " measurements"<<std::endl;
            //compute s
            double sum_s=0;
            cv::Mat s = cv::Mat::zeros(zlist.size(), 1, CV_64F);
            for (unsigned int n = 0; n < zlist.size(); n++) {

                cv::Mat ztilde = zlist[n] -ICFs[tid].H * ICFs[tid].x_;
                //LOGGER << "ztilde="<< mat2vec(ztilde)<<std::endl;
                cv::Mat res = -ztilde.t()*S.inv(cv::DECOMP_SVD) * ztilde/2;
                s.at<double>(n) = exp(res.at<double>(0));

                if (s.at<double>(n) < 0.0001)
                    s.at<double>(n) = 0;
                sum_s += s.at<double>(n);
            }

            //compute beta and the weighted measurement "y"
            cv::Mat beta=cv::Mat::zeros(zlist.size(), 1, CV_64F);
            LOGGER << "\tdata:" << mat2vec(ICFs[tid].x_) << std::endl;
            for (unsigned int n = 0; n < zlist.size(); n++) {
                beta.at<double>(n) = s.at<double>(n) /(b+sum_s);

                if(std::isnan(beta.at<double>(n)))
                    beta.at<double>(n) = 0; //avoid nan values

                y = y + beta.at<double>(n)*zlist[n];
                cv::Mat ztilde = zlist[n] -ICFs[tid].H * ICFs[tid].x_;
                Ptilde = Ptilde + beta.at<double>(n)*ztilde*ztilde.t();
                LOGGER << "\tcontribution for z=" << mat2vec(zlist[n])<< " --> "<< beta.at<double>(n)<< std::endl;
            }

            ICFs[tid].beta0 = b/(b+sum_s);
            cv::Mat tmp = (1-ICFs[tid].beta0) * ICFs[tid].H * ICFs[tid].x_;
            Ptilde = Ptilde - (y-tmp)*(y-tmp).t();

            if(ICFs[tid].beta0<1)
            {
                //we have measurements so there is no "detecction_miss"
                node_controls[tid].detection_miss = false;

                //compute u U
                ICFs[tid].u = ICFs[tid].Ht * ICFs[tid].Rinv * y;
                ICFs[tid].U = ICFs[tid].Ht * ICFs[tid].Rinv * ICFs[tid].H;

                //compute G
                cv::Mat K = ICFs[tid].J_.inv(cv::DECOMP_SVD) * ICFs[tid].Ht * S.inv(cv::DECOMP_SVD);
                cv::Mat C = Ptilde - (1-ICFs[tid].beta0)*S;
                ICFs[tid].G =-ICFs[tid].J_ * K * (C.inv(cv::DECOMP_SVD) + K.t()*ICFs[tid].J_*K).inv(cv::DECOMP_SVD) * K.t()*ICFs[tid].J_;
            }
            else
            {
                //we have measurements but no association with current target so "detecction_miss"
                node_controls[tid].detection_miss = true; //miss detection 'by default'
                ICFs[tid].u = cv::Mat::zeros(dimS, 1, CV_64F);    //information vector
                ICFs[tid].U = cv::Mat::zeros(dimS, dimS, CV_64F); //information matrix
                ICFs[tid].G = cv::Mat::zeros(dimS, dimS, CV_64F); //information matrix
            }
        }
        else
        {
            //we do not have measurements so "detecction_miss"

            node_controls[tid].detection_miss = true; //miss detection 'by default'
            ICFs[tid].u = cv::Mat::zeros(dimS, 1, CV_64F);    //information vector
            ICFs[tid].U = cv::Mat::zeros(dimS, dimS, CV_64F); //information matrix
            ICFs[tid].G = cv::Mat::zeros(dimS, dimS, CV_64F); //information matrix
        }
    }
}

double WiseCameraMTIC::findPd(cv::Mat pos, cv::Mat S, WiseCameraInfo::fov_di_t &fov)
{
    std::vector<cv::Point> points;
    double Pd=0;

//TODO: reprogram this Matlab code to compute the integral of the normal pdf in a square
//  Pd = mvncdf([lims(3);lims(4)],z,R) -  mvncdf([lims(1);lims(4)],z,R) -  mvncdf([lims(3);lims(2)],z,R) + mvncdf([lims(1);lims(2)],z,R);
//  if (Pd>1)
//      Pd = 1.0;
//  end
//  if(Pd<0.00001)
//     Pd = 0.001;
//  end

   // double error;
   // double upper[2] = {1.0,1.0};
   // double corr[1] = {0.0};

    // P( X < {val[0],val[1]} )
    // where X ~ MVN({0,0}, {1, corr[1];corr[1] 1})
    // Implementation from libMvtnorm from https://github.com/zhanxw/libMvtnorm
    //double Pd1 = pmvnorm_P(2,upper,corr,&error);

// cdf of points
// double mu=0, sigma=0;
// mu = fov[0].x;
// sigma = ICFs[0].R.at<double>(0,0);
//double p1x = cdf(fov[0].x,pos.at<double>(0),sqrt(sigma));
//double p1y = cdf(fov[0].y,pos.at<double>(1),sqrt(sigma));
//double p2x = cdf(fov[1].x,pos.at<double>(0),sqrt(sigma));
//double p2y = cdf(fov[1].y,pos.at<double>(1),sqrt(sigma));
//double p3x = cdf(fov[2].x,pos.at<double>(0),sqrt(sigma));
//double p3y = cdf(fov[2].y,pos.at<double>(1),sqrt(sigma));
//double p1 = p1x*p1y;
//double p2 = p2x*p2y;
//double p3 = p3x*p3y;

   points.clear();
   points.push_back(cvPoint(fov.c_px,fov.c_py));
   points.push_back(cvPoint(fov.c_cx,fov.c_cy));
   points.push_back(cvPoint(fov.c_bx,fov.c_by));
   points.push_back(cvPoint(fov.c_px,fov.c_py));

    double dist = cv::pointPolygonTest(points, cvPoint(pos.at<double>(0), pos.at<double>(1)), true);

    if (dist < 0)
        Pd = 0.001;
    else
    {
        Pd = 1;
        Pd=dist/80;
        //std::cout << " Pd=" << Pd << " dist="<< dist << std::endl;
    }
    return Pd;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseCameraMTIC::at_tracker_end_sample()
{
    // Called when a new sample (image) is no longer valid
        LOGGER << "END NEW SAMPLE" << endl;

         //check if the camera is doing consensus for any target
        int camStatusTotal=0;
        for (int tid = 0; tid < n_targets; tid++)
            if (camStatus[tid] == mtic::INACTIVE)
                camStatusTotal++;

        if (camStatusTotal != n_targets) {
            LOGGER << "node not ready (own," << camStatusTotal << "/" << n_targets <<" targets done)" << endl;
            setTimer(ALARM_WAIT_NEGOTIATION,sampling_time); //we check again after a certain time
            return false;
        }
        else
            LOGGER << "node ready (own," << camStatusTotal << "/" << n_targets <<" targets done)" << endl;


        //for (int tid = 0; tid < n_targets; tid++) {
        //    mtic::node_ctrl_mtic_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
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
                    WiseCameraMTIC*c = check_and_cast<WiseCameraMTIC*>(m);

                    camStatusTotal=0;
                    for (int tid = 0; tid < n_targets; tid++)
                        if (c->camStatus[tid] == mtic::INACTIVE)
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
                mtic::node_ctrl_mtic_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'
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
void WiseCameraMTIC::process_network_message(WiseApplicationPacket *pkt)
{
    double e2=0,e1 = cv::getTickCount();
    int i=0,c=0, index=-1;

    WiseCameraMTIC_Msg *m = check_and_cast<WiseCameraMTIC_Msg*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    LOGGER << "RX from " << ctl.source << ". Packet content: [ TID=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << ") ]" << endl;

    //source node and target IDs of recv packet
    int node = atoi(ctl.source.c_str());
    int tid = m->getTargetID();
    mtic::node_ctrl_mtic_t &ctrl = node_controls[tid]; //get the control structure associated to target 'tid'

    switch (m->getPktType()){
        case MTIC_COLLABORATION_DATA1:
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

            case MTIC_COLLABORATION_END:
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
void WiseCameraMTIC::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
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
void WiseCameraMTIC::consensusStart(int tid)
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
void WiseCameraMTIC::consensusProcess(int tid, int k)
{
    LOGGER << " CONSENSUS for k=" <<  k << endl;
    mtic::node_ctrl_mtic_t &ctrl = node_controls[tid];

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
      ICFs[tid].x = ICFs[tid].V.inv(cv::DECOMP_SVD)*ICFs[tid].v;
      LOGGER << "tid=" << tid << " -> PAR RESULT x_=" <<  mat2vec(ICFs[tid].x_) <<" x=" <<  mat2vec(ICFs[tid].x) <<" err=" <<  setprecision(3) << ICFs[tid].compute_error() << endl;
    }
}


void WiseCameraMTIC::checkNextConsensusRound(int tid, int k)
{
    //get the control structure associated to target 'tid'
    mtic::node_ctrl_mtic_t &ctrl = node_controls[tid];

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
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseCameraMTIC::sendICFmessage(int tid)
{
    //create message & copy data
       std::ostringstream os;
       os << "ICF: node=" << self << " tid=" << tid << " t=" << tracking_step_counter << " k=" << node_controls[tid].iter_counter;

       WiseCameraMTIC_Msg *pkt = new WiseCameraMTIC_Msg(os.str().c_str(), APPLICATION_PACKET);
       pkt->setTrackingCount(tracking_step_counter); //current step counter
       pkt->setIterationStep(node_controls[tid].iter_counter); //set the current consensus iteration k=1
       pkt->setTargetID(tid); //target id
       pkt->setType(WISE_APP_NORMAL); //normal APP for the network

       //send message containing the posterior state estimation OR collaboration end
       if (node_controls[tid].iter_counter > iter_max){
           LOGGER << "tid=" << tid << " -> SENDING MSG to FOVs to END consensus" << endl;
           pkt->setByteLength(mtic::ICFpkt_size_mtic[MTIC_COLLABORATION_END]);
           pkt->setPktType(MTIC_COLLABORATION_END);
           camStatus[tid] = mtic::INACTIVE;//flag to indicate that the node has finished consensus
       }
       else {
           LOGGER << "tid=" << tid << " -> SENDING MSG to FOVs for k=" << node_controls[tid].iter_counter << endl;
           pkt->setICFv(ICFs[tid].v); //information vector
           pkt->setICFV(ICFs[tid].V); //information matrix
           pkt->setICFW(ICFs[tid].W); //information matrix
           pkt->setByteLength(mtic::ICFpkt_size_mtic[MTIC_COLLABORATION_DATA1]);
           pkt->setPktType(MTIC_COLLABORATION_DATA1);
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
void WiseCameraMTIC::logResult(int tid)
{
    double delay = simTime().dbl()-node_controls[tid].start_time;
      double err = ICFs[tid].compute_error();
      ICFs[tid].errAcc += err;

      LOGGER << "tid=" << tid <<" t="<< tracking_step_counter << " FINAL -> x=" << mat2vec(ICFs[tid].x) << " J=" << cv::trace(ICFs[tid].J).val[0]
            << " x_=" <<  mat2vec(ICFs[tid].x_) << "," << "] J_=" << cv::trace(ICFs[tid].J_).val[0]
            << " z=" << mat2vec(ICFs[tid].z) << " gt=" << mat2vec(ICFs[tid].xgt)<< endl;

      *writerICFMTIC << std::setprecision(6) << simTime().dbl() << "\t" << tracking_step_counter << "\t" << self << "\t" << tid  << "\t" <<
              setprecision(4) << ICFs[tid].z.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].z.at<double>(1) << "\t" <<
              setprecision(4) << ICFs[tid].x_.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].x_.at<double>(1) << "\t" <<
              setprecision(4) << ICFs[tid].x.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].x.at<double>(1) << "\t" <<
              setprecision(4) << ICFs[tid].xgt.at<double>(0) << "\t" << setprecision(4) << ICFs[tid].xgt.at<double>(1) << "\t" <<
              setprecision(4) << err << "\t" << setprecision(4) <<  ICFs[tid].errAcc << "\t" << delay << endl;
}
