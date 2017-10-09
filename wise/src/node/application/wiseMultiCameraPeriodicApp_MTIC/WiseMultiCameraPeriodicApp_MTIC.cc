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
 * \file WiseMultiCameraPeriodicApp_MTIC.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the MTIC tracker
 * \version 1.4
 */
#include <wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC.h>
#include <wise/src/world/gui/opencv/WiseGuiWorldOpencv.h> //class to print data/targets in the ground-plane
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

//register module in simulator
Define_Module(WiseMultiCameraPeriodicApp_MTIC);

//additional log for tracking data
std::ofstream *writerICFMTIC=NULL;

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseMultiCameraPeriodicApp_MTIC::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppMTIC::at_startup() called");

    readParameters();//Read parameters
    initStructures();//create internal structures

    //Create streams for logging results
    if (writerICFMTIC == NULL)
        writerICFMTIC = new ofstream();

    //log enabled
    if(_collectAccuracyStats) {
        std::ostringstream os;
        os << base_out_path.c_str() << "MTIC" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << _n_targets << "_I" << std::setfill('0') << std::setw(2) << _iter_max << ".dat";

        if (!writerICFMTIC->is_open()){
            writerICFMTIC->open(os.str().c_str());
            *writerICFMTIC << "# processNoiseCov=" << _procNoiseCov << " measurementNoiseCov=" << _measNoiseCov << " _iter_max=" << _iter_max << " alpha=" << _alpha << endl;
            *writerICFMTIC << "#Simulation_time,tracking_step,NodeID,TargetID,MeasurementX,MeasurementY,EstimateX,EstimateY,GroundTruthX,GroundTruthY,Error,ErrorAcc,ResultsDelay" << endl;
            *writerICFMTIC << "#t_sim\tt_step\tNID\tTID\tnumZ\tnumC\tX_x\tX_y\tXx\tXy\tGTx\tGTy\tErr\tErrAcc\tDelay" << endl;
        }
    }

    if(_collectPowerStats) {
        std::ostringstream os;
        os << base_out_path.c_str() << "MTIC" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << _n_targets << "_I" << std::setfill('0') << std::setw(2) << _iter_max
          << "_CPU" << std::setfill('0') << std::setw(3) << resMgr->getPROClk()/1e5 << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user()
          << ".res" << std::setfill('0') << std::setw(3) << self;
        resMgr->initLogger(os.str().c_str(), self,_camID); //energy-consumption log
    }

    if (_collectNetworkStats) {
        std::ostringstream os;
        os << base_out_path.c_str() << "MTIC" << "_r" << std::setfill('0') << std::setw(4) << _currentRun << "_N" << std::setfill('0') << std::setw(2) << n_nodes << "_T" << std::setfill('0') << std::setw(2) << _n_targets << "_I" << std::setfill('0') << std::setw(2) << _iter_max << ".rad";
        radioModule->initLogger(os.str().c_str());
    }

    WISE_DEBUG_32("WiseCamPerAppMTIC::processNoiseCov=" << _procNoiseCov << " measurementNoiseCov=" << _measNoiseCov << " _iter_max=" << _iter_max << " alpha=" << _alpha << " lambda=" << _lambda);
}

/*! Read parameters of MTT_ICF*/
void WiseMultiCameraPeriodicApp_MTIC::readParameters()
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::readParameters() called");

    // Access related-module parameters (read number of targets)
   cModule *network = getParentModule()->getParentModule();
   _n_targets = network->par("numPhysicalProcesses");

   //MTIC Filter settings
   _procNoiseCov = hasPar("procNoiseCov") ? par("procNoiseCov") : 0.1;
   _measNoiseCov = hasPar("measNoiseCov") ? par("measNoiseCov") : 1e-1;

   // Consensus settings
   _iter_max = hasPar("iter_max") ? par("iter_max") : 20;
   _alpha = hasPar("alpha") ? par("alpha").doubleValue() : 0.1;
   _share = hasPar("share")?par("share").stringValue() : "COM";

    //Association parameters of NN algorithm
    _lambda = hasPar("lambda") ? par("lambda").doubleValue() : 0.0; //clutter level

    _displayStats = hasPar("displayStats") ? par("displayStats") : false;

    _collectNetworkStats = hasPar("collectNetworkStats")?par("collectNetworkStats").boolValue() : false;
    _collectPowerStats = hasPar("collectPowerStats")?par("collectPowerStats").boolValue() : false;
    _collectAccuracyStats = hasPar("collectAccuracyStats")?par("collectAccuracyStats").boolValue() : false;
}

void WiseMultiCameraPeriodicApp_MTIC::at_finishSpecific()
{
    _rdata.clear();

    declareOutput("Generated clutters/target");
    collectOutput("Generated clutters/target", "", _countClutters/_n_targets);

    WISE_DEBUG_32("WiseCamPerAppMTIC:: Generated " << _countClutters/_n_targets << " clutters/target for " << _tracking_step_counter << " samples");
    if (writerICFMTIC) {
        writerICFMTIC->close();
        delete writerICFMTIC;
        writerICFMTIC=NULL;
    }
}

/*! Initialization of structures for tracking targets*/
void WiseMultiCameraPeriodicApp_MTIC::initStructures()
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::initStructures() called");

     _dimS = mtic::DIM_STATE_T_4D;
     _dimM = mtic::DIM_MEASUREMENT_T_2D;

     _countClutters = 0;

     //status for each target
     _camStatus.clear();
     _camStatus.resize(_n_targets);

     _node_controls.clear();

     for (int tid = 0; tid < _n_targets; tid++)
     {
         //create control data
         mtic::node_ctrl_mtic_t ctrl(tid,n_nodes,mtic::MAX_SIZE_BUFFER,_dimS);

         //determine the neighborhood to share (FOV or COM graphs)
         _share.compare("FOV") == 0 ? ctrl.n_neighbourgs = _neighborsFOVoverlap.size(): ctrl.n_neighbourgs = _neighborsCOM.size();

         _node_controls.push_back(ctrl);//store in list
     }
     WISE_DEBUG_32("WiseCamPerAppMTIC::Created resources (" << _node_controls.size() << " structs) for "<< _n_targets << " targets, " << n_nodes << " nodes and " << mtic::MAX_SIZE_BUFFER << " max iterations to buffer");
  }

/*!
 * This function defines the behavior to specific alarms generated by the algorithm. To be implemented in superclasses of WiseCameraPeriodicAlgo.
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseMultiCameraPeriodicApp_MTIC::at_timer_fired(int index)
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::ALARM: " << _alarm_str[index]);

    switch (index) {
      //check completion of negotiation
      case ALARM_WAIT_NEGOTIATION:
          fsm_app(INVALID); //we go to the FSM when coalition is checked to be completed
          break;
      default:
          WISE_DEBUG_32("WRONG ALARM!!: index=" << index);
    }
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by _ICFs.
 *
 *  Called to properly read the sample: when a new sample is available a measurement has to be created from it
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseMultiCameraPeriodicApp_MTIC::make_measurements(const vector<WiseTargetDetection>&dt)
{
    //reorder target detections so we directly associate lists of measurements and targets. Uses ID of targets (ie, ground-truth)
    vector<const WiseTargetDetection*> ordered;
    ordered.resize(_n_targets, NULL);

    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        ordered[d->target_id] = &(*d);

    //copy the real positions in the ground-truth lists
    for (int tid = 0; tid < _n_targets; tid++) {
        const WiseTargetDetection &d = *(ordered[tid]);
        _ICFs[tid].xgt.at<double>(0) = (d.true_bb_x_tl + d.true_bb_x_br) / 2;
        _ICFs[tid].xgt.at<double>(1) = (d.true_bb_y_tl + d.true_bb_y_br) / 2;
    }

    //clear list of measurements (possibly with data from the previous iteration)
    _zlist.clear();

    // generate measurements from ground-truth data in world coordinates (assuming known external calibration)
    for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d)
        if ((*d).valid == true) {
            cv::Mat z = cv::Mat::zeros(_dimM, 1, CV_64F);
            z.at<double>(0)  = ((*d).ext_bb_x_tl + (*d).ext_bb_x_br) / 2 + normal(0, _measNoiseCov, 0);
            z.at<double>(1)  = ((*d).ext_bb_y_tl + (*d).ext_bb_y_br) / 2 + normal(0, _measNoiseCov, 0);
            _zlist.push_back(z);
            WISE_DEBUG_32("WiseCamPerAppMTIC:: -> MAKE MEASUREMENT" << " z=[" << z.at<double>(0) << "," << z.at<double>(1) << "]");
        }
    WISE_DEBUG_32("z size=" << _zlist.size());

    //generate clutter measurements
    generateClutterMeasurements();
}

void WiseMultiCameraPeriodicApp_MTIC::generateClutterMeasurements ()
{
    _zclut.clear();//clear the list of clutters

    srand(cv::getTickCount()); // Seed the time
    int numClutters = poisson(_lambda); //TODO: change seed for each simulation
    WISE_DEBUG_32("WiseCamPerAppMTIC::generateClutterMeasurements() called. Creating " << numClutters << " meas");

    for (int c = 1; c <= numClutters;c++){

        cv::Mat clut = cv::Mat::zeros(_dimM, 1, CV_64F);//temporal variable to store one clutter measurement

        switch (_cam_info.get_fov_type())
        {
            // Generate clutter measurements for directional FOVs
            case WiseCameraInfo::DIRECTIONAL:
            {
               //check if target is inside camera's FOV
               double dist=-1;
               int x_init,y_init=0;

               //get the points/vertex describing the camera FOV
               WiseCameraInfo::fov_di_t fov;
               _cam_info.get_fov_di(fov);
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
                _cam_info.get_fov_bb(fov);
                cv::Mat camPos = (cv::Mat_<double>(2, 1) << fov.c_x, fov.c_y); //x-y position of camera
                cv::Mat camSiz = (cv::Mat_<double>(2, 1) << fov.width, fov.height); //W-H size of camera
                clut = camPos + camSiz*uniform(0, 1);
                break;
            }
            default:
                break;
        }
        _zlist.push_back(clut);
        _zclut.push_back(clut);
        _countClutters++;
        WISE_DEBUG_32("WiseCamPerAppMTIC::-> MAKE CLUTTER" << " zc=[" << clut.at<double>(0) << "," << clut.at<double>(1) << "]");
    }

    //_ICFs[tid].z.at<double>(0) -> number of measurements corresponding to clutter
    //_ICFs[tid].z.at<double>(1) -> number of measurements corresponding to targets
    for (int tid = 0; tid < _n_targets; tid++)
        _ICFs[tid].numClutters = numClutters;
}

/*!
 * Init resources for ICF processing. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_MTIC::at_init()
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::at_init() called");

     _ICFs.clear();

     // ICF filters for each target
     for (int tid = 0; tid < _n_targets; tid++)
     {
        //create ICF filter
        mtic::MTIC_t icf(_dimS,_dimM,_procNoiseCov,_measNoiseCov,_lambda,n_nodes);
        _ICFs.push_back(icf); //store in list

        //update the neighbourgs to share (FOV or COM graphs)
        mtic::node_ctrl_mtic_t& ctrl = _node_controls[tid];
        _share.compare("FOV") == 0 ? ctrl.n_neighbourgs = _neighborsFOVoverlap.size(): ctrl.n_neighbourgs = _neighborsCOM.size();
     }
     WISE_DEBUG_32("WiseCamPerAppMTIC::Created resources (" << _ICFs.size() << " ICF filters) for "<< _n_targets << " targets, " << n_nodes << " nodes and " << mtic::MAX_SIZE_BUFFER << " iterations");

     return true;
}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_MTIC::at_first_sample()
{
    // Called when the first sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppMTIC::at_first_sample() called");

    //find the maximum neighbor degree
    _max_neigb_network = 0;
    for (int i = 0; i < n_nodes; i++) {

        cModule *m = getParentModule()->getParentModule(); // m=SN
        m = m->getSubmodule("node", i)->getSubmodule("Application");
        WiseMultiCameraPeriodicApp_MTIC *c = check_and_cast<WiseMultiCameraPeriodicApp_MTIC*>(m);

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
        std::vector<mtic::round_data_t> rdata;
        _rdata.push_back(rdata);
    }

    //initialize targets with ground-truth data
     for (int tid = 0; tid < _n_targets; tid++){

        mtic::MTIC_t &icf = _ICFs[tid];
        icf.initICFstate(_ICFs[tid].xgt);

        _node_controls[tid].initialized = true;
        _node_controls[tid].first_start_time = SIMTIME_DBL(simTime());

        WISE_DEBUG_32("WiseCamPerAppMTIC::tid=" << tid << " -> INIT x_=" <<  mat2vec(icf.x_) << " xgt=" << mat2vec(_ICFs[tid].xgt));
    }

     //do processing
     //return at_sample();
     return true;
}

/*!
 * KF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_MTIC::at_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppMTIC::at_end_first_sample() called");

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraSimplePeriodicTracker.
 */
bool WiseMultiCameraPeriodicApp_MTIC::at_sample()
{
     //Called when a new sample (image) is ready
     WISE_DEBUG_32("WiseCamPerAppMTIC::at_sample() called");
     _tracking_step_counter++;

     if(_tracking_step_counter==1)
         at_first_sample();

    //associate measurements to targets
    dataAssociation();

    // NOTE: Measurements are computed in the make_measurements() method
    //       "_zlist" variable has the list of measurements for the current time step
    for (int tid = 0; tid < _n_targets; tid++)
    {
        _rdata[tid].clear();
      _camStatus[tid] = mtic::COLLABORATION; //flag to indicate that the camera is busy doing consensus

      //check if there is consensus under progress
      if (_node_controls[tid].iter_counter > 0){
          WISE_DEBUG_32("WiseCamPerAppMTIC::Start consensus without ending previous iter > curr=" << _node_controls[tid].iter_counter << " max=" << _iter_max);
          return false;
      }
      else
          WISE_DEBUG_32("WiseCamPerAppMTIC::tid=" << tid << " -> PROCESS SAMPLE t=" <<  _tracking_step_counter);

      //record initial time for consensus
      _node_controls[tid].start_time = simTime().dbl();

      //compute internal information vector & matrix
      _ICFs[tid].prepData(_node_controls[tid].detection_miss);

      //start consensus iterations
      consensusStart(tid);
    }
    return true;
}

void WiseMultiCameraPeriodicApp_MTIC::dataAssociation()
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::dataAssociation() called");

    double b=0;
    cv::Mat y, Ptilde;

    for (int tid = 0; tid < _n_targets; tid++){

        //_ICFs[tid].z = cv::Mat::zeros(dimM, 1, CV_64F); //empty measurement
        _node_controls[tid].detection_miss = true; //miss detection 'by default'

        //compute S
        cv::Mat S = _ICFs[tid].R + _ICFs[tid].H *_ICFs[tid].J_.inv(cv::DECOMP_SVD) * _ICFs[tid].H.t();

        //compute Pd
        WiseCameraInfo::fov_di_t fov;
        _cam_info.get_fov_di(fov);
        double Pd = findPd(_ICFs[tid].H*_ICFs[tid].x_, S, fov);

        //NOTE: the 'lamdaf' parameter should have values, otherwise anything close to the target may be integrated!!
        //compute b
        b=2*M_PI*_ICFs[tid].lamdaf*sqrt(cv::determinant(S)) * (1.0-Pd*_ICFs[tid].Pg)/Pd;
        WISE_DEBUG_32("WiseCamPerAppMTIC::tid="<< tid << " lamdaf="<<_ICFs[tid].lamdaf<<" S="<<mat2vec(S)<< " Pd="<< Pd << " b="<<b);


        if (std::isinf(b))
        {
            perror("INF 'b' value detected. Probably a missed detection");
            WISE_DEBUG_32("WiseCamPerAppMTIC::INF 'b' value detected. Probably a missed detection");
        }


        //initialize stuff
        y = cv::Mat::zeros(_dimM, 1, CV_64F);
        Ptilde = cv::Mat::zeros(_dimM,_dimM, CV_64F);

        if (_zlist.size() > 0)
        {
            // WISE_DEBUG_32("WiseCamPerAppMTIC::tid="<< tid << " S="<<S <<"\n Doing association: "<< _zlist.size() << " measurements");
            WISE_DEBUG_32("WiseCamPerAppMTIC::tid="<< tid <<"\n Doing association: "<< _zlist.size() << " measurements");

            //compute s
            double sum_s=0;
            cv::Mat s = cv::Mat::zeros(_zlist.size(), 1, CV_64F);
            for (unsigned int n = 0; n < _zlist.size(); n++) {

                cv::Mat ztilde = _zlist[n] -_ICFs[tid].H * _ICFs[tid].x_;
                //LOGGER << "ztilde="<< mat2vec(ztilde)<<std::endl;
                cv::Mat res = -ztilde.t()*S.inv(cv::DECOMP_SVD) * ztilde/2;
                s.at<double>(n) = exp(res.at<double>(0));

                if (s.at<double>(n) < 0.0001)
                    s.at<double>(n) = 0;
                sum_s += s.at<double>(n);
            }

            //compute beta and the weighted measurement "y"
            cv::Mat beta=cv::Mat::zeros(_zlist.size(), 1, CV_64F);
            WISE_DEBUG_32("WiseCamPerAppMTIC::\tdata:" << mat2vec(_ICFs[tid].x_));
            for (unsigned int n = 0; n < _zlist.size(); n++) {
                beta.at<double>(n) = s.at<double>(n) /(b+sum_s);

                if(std::isnan(beta.at<double>(n)))
                    beta.at<double>(n) = 0; //avoid nan values

                y = y + beta.at<double>(n)*_zlist[n];
                cv::Mat ztilde = _zlist[n] -_ICFs[tid].H * _ICFs[tid].x_;
                Ptilde = Ptilde + beta.at<double>(n)*ztilde*ztilde.t();
                WISE_DEBUG_32("WiseCamPerAppMTIC::\tcontribution for z=" << mat2vec(_zlist[n])<< " --> "<< beta.at<double>(n));
            }

            _ICFs[tid].beta0 = b/(b+sum_s);
            cv::Mat tmp = (1-_ICFs[tid].beta0) * _ICFs[tid].H * _ICFs[tid].x_;
            Ptilde = Ptilde - (y-tmp)*(y-tmp).t();

            if(_ICFs[tid].beta0<1)
            {
                //we have measurements so there is no "detecction_miss"
                _node_controls[tid].detection_miss = false;

                //compute u U
                _ICFs[tid].u = _ICFs[tid].Ht * _ICFs[tid].Rinv * y;
                _ICFs[tid].U = _ICFs[tid].Ht * _ICFs[tid].Rinv * _ICFs[tid].H;

                //compute G
                cv::Mat K = _ICFs[tid].J_.inv(cv::DECOMP_SVD) * _ICFs[tid].Ht * S.inv(cv::DECOMP_SVD);
                cv::Mat C = Ptilde - (1-_ICFs[tid].beta0)*S;
                _ICFs[tid].G =-_ICFs[tid].J_ * K * (C.inv(cv::DECOMP_SVD) + K.t()*_ICFs[tid].J_*K).inv(cv::DECOMP_SVD) * K.t()*_ICFs[tid].J_;
            }
            else
            {
                //we have measurements but no association with current target so "detecction_miss"
                _node_controls[tid].detection_miss = true; //miss detection 'by default'
                _ICFs[tid].u = cv::Mat::zeros(_dimS, 1, CV_64F);    //information vector
                _ICFs[tid].U = cv::Mat::zeros(_dimS, _dimS, CV_64F); //information matrix
                _ICFs[tid].G = cv::Mat::zeros(_dimS, _dimS, CV_64F); //information matrix
            }

            if (std::isnan(_ICFs[tid].beta0))
            {
                WISE_DEBUG_32("WiseCamPerAppMTIC::NaN Beta value detected. Probably a missed detection");
                perror("NaN Beta value detected. Probably a missed detection");
            }
        }
        else
        {
            //we do not have measurements so "detecction_miss"
            _node_controls[tid].detection_miss = true; //miss detection 'by default'
            _ICFs[tid].u = cv::Mat::zeros(_dimS, 1, CV_64F);    //information vector
            _ICFs[tid].U = cv::Mat::zeros(_dimS, _dimS, CV_64F); //information matrix
            _ICFs[tid].G = cv::Mat::zeros(_dimS, _dimS, CV_64F); //information matrix
        }


    }

}
double WiseMultiCameraPeriodicApp_MTIC::findPd(cv::Mat pos, cv::Mat S, WiseCameraInfo::fov_di_t &fov)
{
    //TODO: improve the computation of "Probability of Detection (Pd)" for triangular FOVs considering uncertainty
    //      For more info, see JC.SanMiguel & A. CAvallaro, "Efficient estimation of target detection quality", IEEE ICIP 2017
    double Pd=0;

    //FOV shape defined by a set of points
    std::vector<cv::Point> points;
    points.clear();
    points.push_back(cvPoint(fov.c_px,fov.c_py));
    points.push_back(cvPoint(fov.c_cx,fov.c_cy));
    points.push_back(cvPoint(fov.c_bx,fov.c_by));
    points.push_back(cvPoint(fov.c_px,fov.c_py));

    //compute the distance of the target (variable "pos") to the FOV shape.
    double dist = cv::pointPolygonTest(points, cvPoint(pos.at<double>(0), pos.at<double>(1)), true);

    //point is inside the FOV shape
    if (dist <= 0)
        Pd = 0.001;
    else
    //point is inside the FOV shape
    {
        Pd = 0.95;//default value (high confidence detector)
        //Pd = 0.80;//default value (medium confidence detector)
        //Pd = 0.70;//default value (low confidence detector)
    }
    return Pd;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraSimplePeriodicTracker".
 */
bool WiseMultiCameraPeriodicApp_MTIC::at_end_sample()
{
    // Called when a new sample (image) is no longer valid
        WISE_DEBUG_32("WiseCamPerAppMTIC::at_end_sample() called");

         //check if the camera is doing consensus for any target
        int camStatusTotal=0;
        for (int tid = 0; tid < _n_targets; tid++)
            if (_camStatus[tid] == mtic::INACTIVE)
                camStatusTotal++;

        if (camStatusTotal != _n_targets) {
            WISE_DEBUG_32("WiseCamPerAppMTIC::node not ready (own," << camStatusTotal << "/" << _n_targets <<" targets done)");
            setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time); //we check again after a certain time
            return false;
        }
        else
            WISE_DEBUG_32("WiseCamPerAppMTIC::node ready (own," << camStatusTotal << "/" << _n_targets <<" targets done)");


        //for (int tid = 0; tid < _n_targets; tid++) {
        //    mtic::node_ctrl_mtic_t &ctrl = _node_controls[tid]; //get the control structure associated to target 'tid'
        //            //int index = findIndexInBuffer(tid, _iter_max); // Index of the buffer for the last iteration
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
                    WiseMultiCameraPeriodicApp_MTIC*c = check_and_cast<WiseMultiCameraPeriodicApp_MTIC*>(m);

                    camStatusTotal=0;
                    for (int tid = 0; tid < _n_targets; tid++)
                        if (c->_camStatus[tid] == mtic::INACTIVE)
                            camStatusTotal++;

                    if (camStatusTotal != _n_targets)  {
                        WISE_DEBUG_32("WiseCamPerAppMTIC::node not ready (netcheck)" << camStatusTotal << "/" << _n_targets <<" targets done)");
                        setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time); //we check again after a certain time
                        return false;
                    }
                }
            }


            //restart 'busy' state of other cameras
            for (int tid = 0; tid < _n_targets; tid++) {
                mtic::node_ctrl_mtic_t &ctrl = _node_controls[tid]; //get the control structure associated to target 'tid'
                //int index = findIndexInBuffer(tid, _iter_max); // Index of the buffer for the last iteration
                for (int i=0; i < n_nodes; i++)
                    ctrl.nb_data_buffer[0].nb_data[i].end_collaboration = false;
            }/**/

    WISE_DEBUG_32("WiseCamPerAppMTIC::node ready");

    if(_displayStats && _tracking_step_counter>1)
        displayStats();

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neighbors, stores the pkt content and when all the data is available (from all neighbors),
 * it calls consensusProcess function to initiate a round of consensus when needed
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraICFMessage type)
 */
bool WiseMultiCameraPeriodicApp_MTIC::process_network_message(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::process_network_message() called");

    double e2=0,e1 = cv::getTickCount();
    int i=0,c=0, index=-1;

    WiseMultiCameraPeriodicApp_MTICPacket *m = check_and_cast<WiseMultiCameraPeriodicApp_MTICPacket*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
    WISE_DEBUG_32("WiseCamPerAppMTIC::RX from " << ctl.source << ". Packet content: [ TID=" << m->getTargetID() << " t=" << m->getTrackingCount()  << " k="<< m->getIterationStep() << ") ]");

    //source node and target IDs of recv packet
    int node = atoi(ctl.source.c_str());
    int tid = m->getTargetID();
    mtic::node_ctrl_mtic_t &ctrl = _node_controls[tid]; //get the control structure associated to target 'tid'

    switch (m->getPktType()){
        case MTIC_COLLABORATION_DATA1:
            {
                WISE_DEBUG_32("WiseCamPerAppMTIC::Collaboration...");

                // store recv data in buffer
                if(ctrl.storeDataInBuffer((int)m->getIterationStep(), node, m) == -1)
                    WISE_DEBUG_32("WiseCamPerAppMTIC::ERROR BUFFER!!");

                //check matching of iteration number between node and recv data
                if (m->getIterationStep() != ctrl.iter_counter)
                    WISE_DEBUG_32("WiseCamPerAppMTIC::WRONG ITERATION!! (curr=" <<  ctrl.iter_counter << " rcv=" << m->getIterationStep() << ")" << " tid="<<tid);

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
                        for (n = _connectivity_map_comms.begin(); n != _connectivity_map_comms.end(); ++n)
                            if ((*n).second == true)
                                if (atoi((*n).first.c_str()) != this->self)
                                if (atoi((*n).first.c_str()) == i)
                                      missing.push_back(i);
                    }

                //compute the consensus if we have all neighbor's data
                if (c==ctrl.n_neighbourgs)
                    consensusProcess(tid, (int)ctrl.iter_counter);
                else
                    WISE_DEBUG_32("WiseCamPerAppMTIC::Waiting for " << ctrl.n_neighbourgs-c << "/" << ctrl.n_neighbourgs << print_vector(missing) << "for consensus k=" << ctrl.iter_counter << " tid="<<tid);
              break;
            }

            case MTIC_COLLABORATION_END:
                if ((int)m->getTrackingCount() == _tracking_step_counter)
                {
                    ctrl.nb_data_buffer[0].nb_data[node].end_collaboration=true;
                    WISE_DEBUG_32("WiseCamPerAppMTIC:: COLLABORATION END RECEIVED from node=" << node << " tid="<<tid);
                }
                else
                    WISE_DEBUG_32("WiseCamPerAppMTIC:: Late??? COLLABORATION END RECEIVED from node=" << node << " tid="<<tid << " t_curr=" << _tracking_step_counter << " t_rcv="<<(int)m->getTrackingCount());
                break;

            default:
                WISE_DEBUG_32("WiseCamPerAppMTIC:: UNKNOWN PACKET!!");
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
void WiseMultiCameraPeriodicApp_MTIC::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppMTIC::handleDirectApplicationMessage() called");

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
void WiseMultiCameraPeriodicApp_MTIC::consensusStart(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::consensusStart() called");

    _node_controls[tid].iter_counter=1;

    if (_node_controls[tid].n_neighbourgs > 0 && _iter_max > 0)
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
 * from all neighbors.
 *
 * @param[in] tid Target ID of the associated ICF structures
 * @param[in] k Number of the current iteration
 */
void WiseMultiCameraPeriodicApp_MTIC::consensusProcess(int tid, int k)
{
    mtic::node_ctrl_mtic_t &ctrl = _node_controls[tid];
    WISE_DEBUG_32("WiseCamPerAppMTIC::consensusProcess() called for k=" <<  ctrl.iter_counter);

    //accumulate round data to display stats
    mtic::round_data_t rdata;
    rdata.round = ctrl.iter_counter; //consensus round
    _ICFs[tid].x = _ICFs[tid].V.inv(cv::DECOMP_SVD)*_ICFs[tid].v;
    rdata.terr = _ICFs[tid].compute_error();
    rdata.delay = simTime().dbl()-_node_controls[tid].start_time;
    _rdata[tid].push_back(rdata);

    WISE_DEBUG_32("WiseCamPerAppMTIC::tid=" << tid << " -> PAR RESULT x_=" <<  mat2vec(_ICFs[tid].x_) <<" x=" <<  mat2vec(_ICFs[tid].x) <<" err=" <<  setprecision(3) << _ICFs[tid].compute_error());

    int index = ctrl.findIndexInBuffer(k); // Index of the buffer
    ctrl.nb_data_buffer[index].iter_buffer = -1; //free the buffer position for further usage

    //combine estimations of neighbors
    _ICFs[tid].update_state_neighbors(ctrl.nb_data_buffer[index].nb_data,_alpha,ctrl.n_neighbourgs,_max_neigb_network);

    //restart status of received data
    for (int i=0; i < n_nodes; i++)
      ctrl.nb_data_buffer[index].nb_data[i].rcv_data = false;

    //continue consensus if not exceed the max iterations
    ctrl.iter_counter = ++k;

    //send message to neighbors (posterior state OR collaboration end)
    sendICFmessage(tid);

    //check if data for next consensus round is already buffer
    checkNextConsensusRound(tid,ctrl.iter_counter);

    if (ctrl.iter_counter >  _iter_max) {
      _ICFs[tid].estimate_and_predict_state(); //perform final state estimation when maximum iterations reached
      logResult(tid);//save data
      ctrl.iter_counter=0;//return to initial status
    }
    else{
      _ICFs[tid].x = _ICFs[tid].V.inv(cv::DECOMP_SVD)*_ICFs[tid].v;
      WISE_DEBUG_32("WiseCamPerAppMTIC::tid=" << tid << " -> PAR RESULT x_=" <<  mat2vec(_ICFs[tid].x_) <<" x=" <<  mat2vec(_ICFs[tid].x) <<" err=" <<  setprecision(3) << _ICFs[tid].compute_error());
    }
}


void WiseMultiCameraPeriodicApp_MTIC::checkNextConsensusRound(int tid, int k)
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::checkNextConsensusRound() called");

    //get the control structure associated to target 'tid'
    mtic::node_ctrl_mtic_t &ctrl = _node_controls[tid];

    // get data for current consensus iteration of the node
    int index = ctrl.findIndexInBuffer(k); // Index of the buffer

    int c=0;
    for (int i=0; i < n_nodes; i++)
        if (ctrl.nb_data_buffer[index].nb_data[i].rcv_data == true){
            c++;
        }
    //compute the consensus if we have all neighbor's data
    if (c==ctrl.n_neighbourgs){
        WISE_DEBUG_32("WiseCamPerAppMTIC::tid=" << tid << " -> DATA for k=" << _node_controls[tid].iter_counter << " already available");
        consensusProcess(tid, k);
    }
}

/*!
 * Send a message to all neighbors in the VISION (FOV) graph. The message contains the current estimation
 * of the node:  <x,y> position and <u,U> information vector&matrix.
 *
 * @param[in] tid Target ID of the associated KF structures
 */
int WiseMultiCameraPeriodicApp_MTIC::sendICFmessage(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::sendICFmessage() called");

    //create message & copy data
       std::ostringstream os;
       os << "ICF: node=" << self << " tid=" << tid << " t=" << _tracking_step_counter << " k=" << _node_controls[tid].iter_counter;

       WiseMultiCameraPeriodicApp_MTICPacket*pkt = new WiseMultiCameraPeriodicApp_MTICPacket(os.str().c_str(), APPLICATION_PACKET);
       pkt->setTrackingCount(_tracking_step_counter); //current step counter
       pkt->setIterationStep(_node_controls[tid].iter_counter); //set the current consensus iteration k=1
       pkt->setTargetID(tid); //target id
       pkt->setSubType(WISE_APP_NORMAL); //normal APP for the network

       //send message containing the posterior state estimation OR collaboration end
       if (_node_controls[tid].iter_counter > _iter_max){
           WISE_DEBUG_32("tid=" << tid << " -> SENDING MSG to FOVs to END consensus");
           pkt->setByteLength(mtic::ICFpkt_size_mtic[MTIC_COLLABORATION_END]);
           pkt->setPktType(MTIC_COLLABORATION_END);
           _camStatus[tid] = mtic::INACTIVE;//flag to indicate that the node has finished consensus
       }
       else {
           WISE_DEBUG_32("tid=" << tid << " -> SENDING MSG to FOVs for k=" << _node_controls[tid].iter_counter);
           pkt->setICFv(_ICFs[tid].v); //information vector
           pkt->setICFV(_ICFs[tid].V); //information matrix
           pkt->setICFW(_ICFs[tid].W); //information matrix
           pkt->setByteLength(mtic::ICFpkt_size_mtic[MTIC_COLLABORATION_DATA1]);
           pkt->setPktType(MTIC_COLLABORATION_DATA1);
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
           _bytesTX = _bytesTX - (_node_controls[tid].n_neighbourgs-1)*pkt->getByteLength();
       return 1;
}

/*!
 * Write results in txt files
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseMultiCameraPeriodicApp_MTIC::logResult(int tid)
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::logResult() called");

    double delay = simTime().dbl()-_node_controls[tid].start_time;
      double err = _ICFs[tid].compute_error();
      _ICFs[tid].errAcc += err;

      WISE_DEBUG_32("WiseCamPerAppMTIC::tid=" << tid <<" t="<< _tracking_step_counter << " FINAL -> x=" << mat2vec(_ICFs[tid].x) << " J=" << cv::trace(_ICFs[tid].J).val[0]
            << " x_=" <<  mat2vec(_ICFs[tid].x_) << "," << "] J_=" << cv::trace(_ICFs[tid].J_).val[0]
            << " z=" << mat2vec(_ICFs[tid].z) << " gt=" << mat2vec(_ICFs[tid].xgt));

      *writerICFMTIC << std::setprecision(6) << simTime().dbl() << "\t" << _tracking_step_counter << "\t" << self << "\t" << tid  << "\t" <<
              //setprecision(4) << _ICFs[tid].z.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].z.at<double>(1) << "\t" <<
              setprecision(4) << _zlist.size() << "\t" << setprecision(4) << _ICFs[tid].numClutters << "\t" <<
              setprecision(4) << _ICFs[tid].x_.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].x_.at<double>(1) << "\t" <<
              setprecision(4) << _ICFs[tid].x.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].x.at<double>(1) << "\t" <<
              setprecision(4) << _ICFs[tid].xgt.at<double>(0) << "\t" << setprecision(4) << _ICFs[tid].xgt.at<double>(1) << "\t" <<
              setprecision(4) << err << "\t" << setprecision(4) <<  _ICFs[tid].errAcc << "\t" << delay << endl;
}


bool WiseMultiCameraPeriodicApp_MTIC::displayStats()
{
    WISE_DEBUG_32("WiseCamPerAppMTIC::displayStats() called");

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
        std::cout << "cam "<<_camID << ": display stats for step="<< _tracking_step_counter << " (SimTime="<<simTime().dbl()<<"s)"<< std::endl;
        cv::imshow(winStats.str().c_str(), img);
        if (_n_targets < 6)
        {
            WiseTargetInfo t;

            t.id=self;
            t.pos_x=_ICFs[tid].x.at<double>(0);
            t.pos_y=_ICFs[tid].x.at<double>(1);
            t.unique_color=false;
            //gui->draw_target(t);
            terrain->place_target(t);
        }/**/
    }

    //plot clutter of all cameras
    bool first = true;
    for (int i = 0; i< n_nodes; i++)
        if (i!= self)
        {
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");
            WiseMultiCameraPeriodicApp_MTIC*c = check_and_cast<WiseMultiCameraPeriodicApp_MTIC*>(m);


            for (int tid = 0; tid < _n_targets; tid++)
            {
              int numC = c->_ICFs[tid].numClutters;
              for(int nc=0; nc<numC;nc++)
                  {

                      WiseTargetInfo t;

                      if (first == true)
                      {
                          first = false;
                          t.id = -100;
                      }
                      else
                          t.id=self;
                      t.pos_x= c->_zclut[nc].at<double>(0);
                      t.pos_y= c->_zclut[nc].at<double>(1);
                      t.unique_color=true;
                     //gui->draw_target(t);
                     terrain->place_noise(t);
                  }
            }
        }

    return true;
}
