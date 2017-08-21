// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file is part of the implementation for the cost-aware coalition-based
//  tracking (CAWC) for single targets described in the paper:
//      Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
//      Tracker tracking", IEEE Sensors Journal, May 2015
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#include "WiseCameraCAWCTracker.h"
#include "WiseUtils.h"

Define_Module(WiseCameraCAWCTracker);

//Error handling
#define perr_app(m) error("\n[WISECAWC]:\n " m)

//LOG UTILS
#define LOGGER logger << "[" << std::setfill('0') << std::setprecision(5) << simTime() << "] @ " << self << " : "
static ofstream logger;
CAWC::coalition_log_t coaLog; //structure to save all coalition data

using namespace CAWC;

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraCAWCTracker::at_startup()
{
    //Reference to network
    //cModule *network = getParentModule()->getParentModule();

    //read parameters - current test
    _testName = par("testName").stringValue();

    // read parameters - tracker
    _tracker.selectTracker(static_cast<CAWC::tracker_type_t>(par("tracker_selected").doubleValue()));
    _tracker.setId(self);
    _tracker.setFramerate(resMgr->getSENFrameRate_user());
    double m = par("score_m").doubleValue();
    double v = par("score_v").doubleValue();
    double th = par("score_th").doubleValue();
    _tracker.setTrackerUtility(m,v,th);

    //get camera ID
    _camID = par("camID").doubleValue();

    // read initialization for target tracking
    _iniT.resize = _resize;
    _iniT.filenameGT = par("initFile_ip_gt").stringValue();
    FILE *fp=fopen(_iniT.filenameGT.c_str(),"r");
    fscanf(fp,"%d", &_iniT.id);//read the target ID
    while(!feof(fp)) {
        int n = fscanf(fp,"%d,%d,%d,%d,%d,%d", &_iniT.camID, &_iniT.frame, &_iniT.Xc, &_iniT.Yc, &_iniT.width, &_iniT.height);
        if (n>0 && _iniT.camID==_camID)
            break;
    }
    fclose(fp);

    //initialize variables - data buffer
    for (int i = 0; i < MAX_SIZE_BUFFER; i++)
        _nb_buf.push_back(CAWC::init_neigb_data(-1,-1,_step_counter,-1,-1,-1,-1));

    //initialize variables - coalition & canera data
    _coa_buf = CAWC::init_coalition_data(0,-1,0.01);
    _cam_buf = CAWC::init_camera_data(_camID);

    //initialize variables - log structure for coalition results
    coaLog.rxdata = cv::Mat::zeros(n_nodes, 1, CV_64F);
    coaLog.txdata = cv::Mat::zeros(n_nodes, 1, CV_64F);

    // initialize variables - log files for results
    std::string logfile = "logs/"+ _testName  + "_t" + to_string_(_iniT.id,2) +"_run" + to_string_(_currentRun,3) + "_Coalition.log"; //coalition log
    if (!logger.is_open())
            logger.open(logfile.c_str()); //application messages log

    _logCOAstr = "res/" + _testName + "_t" + to_string_(_iniT.id,2) + "_run" + to_string_(_currentRun,3) + "_Coalition.coa"; //coalition log

    std::ostringstream oscam;
    oscam << _testName << "_t" << to_string_(_iniT.id,2) << "_run" <<  std::setfill('0') << std::setw(4) << _currentRun << "_n" << std::setfill('0') << std::setw(3) << self << "_N" << n_nodes << "T" << _maxSimtime
             << "_CPU" << std::setfill('0') << std::setw(5) << resMgr->getPROClk()/1e5 << "_SEN" << std::setfill('0') << std::setw(5) << resMgr->getSENClk()/1e5
             << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user() << ".dat" << std::setfill('0') << std::setw(3) << self;
    _logCAMstr = "res/" + oscam.str(); //camera results log

    std::ostringstream os;

    os << "res/" << _testName << "_t" << to_string_(_iniT.id,2) << "_run" <<  std::setfill('0') << std::setw(4) << _currentRun << "_n" << std::setfill('0') << std::setw(3) << self << "_N" << n_nodes << "T" << _maxSimtime
            << "_CPU" << std::setfill('0') << std::setw(5) << resMgr->getPROClk()/1e5 << "_SEN" << std::setfill('0') << std::setw(5) << resMgr->getSENClk()/1e5
            << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user() << ".res" << std::setfill('0') << std::setw(3) << self;
    resMgr->initLogger(os.str().c_str(), self, _camID); //energy-consumption log

    //initialize variables - strings with camera IDs to show results
    _winName << _tracker.getTrackerName() << " results (CAM " << to_string(_camID) << " ,node id=" << to_string(self) << ")";

    //initialize variables - add string for additional alarms of the application layer
    _alarm_str.insert(std::make_pair(ALARM_WAIT_NEGOTIATION, "ALARM_WAIT_NEGOTIATION"));
}

void WiseCameraCAWCTracker::at_finishSpecific()
{
    logger.close();
    save_camera_data();
    if(_coa_buf.manID == self)
        save_coalition_data();
}

/*!
 * This function defines the behavior to specific alarms generated by the algorithm. To be implemented in superclasses of WiseCameraPeriodicAlgo.
 *
 * @param[in] index Code of the generated alarm.
 */
void WiseCameraCAWCTracker::at_timer_fired(int index)
{
    LOGGER << "ALARM: " << _alarm_str[index]<< endl;

    switch (index) {
      //check completion of negotiation
      case ALARM_WAIT_NEGOTIATION:
              fsm_algo(INVALID); //we go to the FSM when coalition is checked to be completed
          break;
      default:
          LOGGER << "WRONG ALARM!!: index=" << index << endl;
    }
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by KFs.
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseCameraCAWCTracker::make_measurements(const vector<WiseTargetDetection>&dt)
{

}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraCAWCTracker::at_init()
{
    return true;
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraCAWCTracker::at_sample()
{
    LOGGER << "PROCESSED frame=" << std::setfill('0') << std::setw(4) << _curFrame << std::endl;

    //tracker initialization
    if (!_tracker.getStarted() && _curFrame >= _iniT.frame) {

        _iniT.Xc = _scaleCols*_iniT.Xc;
        _iniT.Yc = _scaleRows*_iniT.Yc;
        _iniT.width = _scaleCols*_iniT.width;
        _iniT.height = _scaleRows*_iniT.height;
        _tracker.initialize(_frame,_iniT);

        //cv::putText(_frame, to_string(_curFrame).c_str(), cv::Point(10, 15), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 0, 255), 1, CV_AA);
        //cv::rectangle(_frame,_tracker.getTrackWindow(), cv::Scalar( 255, 0, 0 ), 2, 1 );
        //cv::imshow("TEST",_frame);
        //cv::waitKey(0);
    }

    //tracker update
    if(_tracker.getStarted())
        _tracker.update(_frame);

    //tracker visualization
    if (_show_results)
        cv::rectangle(_frame,_tracker.getTrackWindow(), cv::Scalar( 255, 0, 0 ), 2, 1 );

    //cv::putText(_frame, to_string(_step_counter).c_str(), cv::Point(10, 15), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 0, 255), 1, CV_AA);
    cv::putText(_frame, to_string(_curFrame).c_str(), cv::Point(10, 15), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 0, 255), 1, CV_AA);
    //cv::imshow("PRUEBA", _frame); cv::waitKey(0);

    //update own data in buffer
    _tracker.computeScore(_frame);
    std::string util = "u=" + to_string_(_tracker.getScore(),2);
    cv::putText(_frame, util.c_str(), cv::Point(45, 15), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 0, 255), 1, CV_AA);

    update_data_buffer(self,self,_camID,_tracker.getScore(),resMgr->getRemainingEnergy(),1,1, _step_counter);

    //start sharing data to create the coalition
    _coa_buf.state = UTILITY_SHARING; //update coalition status
    _time_pkt_processing = 0;//time to process the received packets
    WiseCameraCAWCTrackerPkt *pkt = CAWC::create_utility_pkt(self, _camID,_tracker.getScore(),resMgr->getRemainingEnergy(),1,1,_curFrame);
    send_message(pkt); //broadcast camera utility packet

    //save camera data
    _cam_buf.step_count.push_back(_step_counter);
    _cam_buf.frameID.push_back(_curFrame);
    _cam_buf.time.push_back(SIMTIME_DBL(simTime()));

    _cam_buf.u.push_back(_nb_buf[self].utility);
    _cam_buf.b.push_back(_nb_buf[self].battery_level);
    _cam_buf.l.push_back(_nb_buf[self].load_level);

    cv::Rect2d est = _tracker.getTrackWindow(); //estimation in the image plane
    double Xw0=-1,Yw0=-1;
    if (_tracker.getStarted()) {
        double x = 1/_scaleCols * (est.x+est.width/2);
        double y = 1/_scaleRows * (est.y+est.height);
        camMgr->imageToWorld(x,y,0, Xw0, Yw0); //conversion image->ground plane
    }

    _cam_buf.Xi.push_back(est.x);
    _cam_buf.Yi.push_back(est.y);
    _cam_buf.Wi.push_back(est.width);
    _cam_buf.Hi.push_back(est.height);
    _cam_buf.Xw.push_back(Xw0);
    _cam_buf.Yw.push_back(Yw0);

    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicAlgo".
 */
bool WiseCameraCAWCTracker::at_end_sample()
{
    LOGGER << "CHECKING COALITION COMPLETED =" << (_coa_buf.state == INACTIVE) << endl;

    //check if coalition is active
    if (_coa_buf.state != INACTIVE) {
        setTimer(ALARM_WAIT_NEGOTIATION,_sampling_time/10); //we check again after a certain time
        return false;
    }

    //save data in coalition log structure
    if (self == _coa_buf.manID) {
       coaLog.rx.push_back(coaLog.rxdata.clone());
       coaLog.tx.push_back(coaLog.txdata.clone());
    }

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraCAWCTrackerMessage type)
 */
bool WiseCameraCAWCTracker::process_network_message(WiseApplicationPacket *pkt)
{
    int prev_manager = -1;
    double e2=0,e1 = cv::getTickCount();

    const WiseCameraCAWCTrackerPkt *m = check_and_cast<const WiseCameraCAWCTrackerPkt*>(pkt);
    //LOGGER << "PROCESS NETWORK PKT FROM NODE=" << m->getNodeID() << " CAMID=" << m->getCamID() << << " TYPE=" << CAWCpkt_str[m->getPktType()] << endl;

    switch (m->getPktType()){

        // camera utility (sent by all cameras) - msg processed by all cameras
        case CAWC_UTILITY:

            if (m->getFrameID() != _curFrame)
                perr_app("error al recibir datos: Frame incorrecto");

            LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] << " (frID=" << m->getFrameID() << "curFrame=" << _curFrame << ")" << endl;
            _nb_buf[m->getNodeID()].rcv_data_utility = true;//update flag for received utility

            //update buffer with received data from neighbor
            update_data_buffer(m->getNodeID(),m->getNodeID(),m->getCamID(),m->getUtility(),m->getBattery_level(),
                               m->getLoad_level(),m->getPriority(),_step_counter);//save packet content

            //check if data has been received from all neighbors (cameras)
            if (check_databuffer_ready() == true)
                identify_and_announce_manager(); // broadcast "CAWC_NEWMANAGER" packet
            break;

        // new manager announced to the network (sent by one camera) - msg processed by all cameras
        case CAWC_NEWMANAGER:

            _coa_buf.state = MANAGER_SELECTION; //update coalition status
            prev_manager = _coa_buf.manID;//save old manager
            _coa_buf.manID = m->getNewManager();//update new manager
            _coa_buf.rcv_state_manager = false;//FLAG to exchange data between old and new managers

            if (_coa_buf.manID != self) {
                LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] << " (send ack to manager)" << endl;
                //if not the manager -> send ACK to manager
                WiseCameraCAWCTrackerPkt *p = CAWC::create_empty_pkt(CAWC_NEWMANAGER_ACK, CAWCpkt_str[CAWC_NEWMANAGER_ACK], self,_camID);
                send_message(p,to_string(_coa_buf.manID));//unicast "CAWC_NEWMANAGER_ACK" packet
                delete p;
            }
            else {

                if(prev_manager != _coa_buf.manID) {
                    LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (manager change -> request previous data)" << endl;
                  //request the old manager to send the target estimation
                  WiseCameraCAWCTrackerPkt *p = CAWC::create_empty_pkt(CAWC_NEWMANAGER_ACK_SEND, CAWCpkt_str[CAWC_NEWMANAGER_ACK_SEND], self,_camID);
                  send_message(p,to_string(prev_manager));//unicast "CAWC_NEWMANAGER_ACK_SEND" packet
                  delete p;
                }
                else {
                    LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (manager is the same -> copy previous data)" << endl;
                    //if old=new manager -> store previous target estimation
                    _coa_buf.rcv_state_manager = true;
                    m->getX().copyTo(_coa_buf.IF.x);
                    m->getP().copyTo(_coa_buf.IF.P);
                }
            }
            break;

        // ack to the new manager announcement (sent by all cameras) - processed by manager
        case CAWC_NEWMANAGER_ACK:

            if(_coa_buf.manID == self) {
                LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (manager receives ack)" << endl;
                _nb_buf[m->getNodeID()].rcv_ack_manager = true; //update flag of received ACK

                //check that all ACKs are received
                if (check_manager_ack() == true) {
                    _coa_buf.cams.clear();
                    _coa_buf.nego.clear();
                    negotiation_request_camera(); //unicast "CAWC_NEGOTIATION_JOIN" packet
                }
            }
            break;

        // ack to the new manager announcement (sent by the old manager) - processed by new manager
        case CAWC_NEWMANAGER_ACK_SEND: {

            LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (old manager sends data)" << endl;
            WiseCameraCAWCTrackerPkt *p = CAWC::create_empty_pkt(CAWC_NEWMANAGER_SEND, CAWCpkt_str[CAWC_NEWMANAGER_SEND], self,_camID);
            p->setX(_coa_buf.IF.x.clone());
            p->setP(_coa_buf.IF.P.clone());
            p->setInitialized(_coa_buf.initialized);
            send_message(p,to_string(_coa_buf.manID));//unicast "CAWC_NEWMANAGER_SEND" packet
            delete p;
            break;
        }

        // data sent by old manager - processed by new manager
        case CAWC_NEWMANAGER_SEND:

            if(self == _coa_buf.manID) {
                LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (received old manager data)" << endl;
                _nb_buf[m->getNodeID()].rcv_ack_manager = true; //update flag of received ACK
                _coa_buf.rcv_state_manager = true;
                _coa_buf.initialized = m->getInitialized();
                m->getX().copyTo(_coa_buf.IF.x);
                m->getP().copyTo(_coa_buf.IF.P);

                //check that all ACKs are received
                if (check_manager_ack() == true) {
                    _coa_buf.cams.clear();
                    _coa_buf.nego.clear();
                    negotiation_request_camera(); //unicast "CAWC_NEGOTIATION_JOIN" packet
                }
            }
            break;

        // proposal to join coalition - sent by manager - processed by cameras
        case CAWC_NEGOTIATION_JOIN:
            LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] << " (received negotiation)" << endl;
                negotiation_reply(); //unicast "CAWC_NEGOTIATION_REPLY" packet
            break;

        // accept/reject proposal to join coalition - sent by each requested camera - processed by manager
        case CAWC_NEGOTIATION_REPLY:

            if(_coa_buf.manID == self) {
                LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " cam=" << m->getNodeID() << ((m->getReply() == true)?" ADD TO COALITION":" REJECT COALITION") << endl;
                if (m->getReply() == true)
                    _coa_buf.cams.push_back(m->getNodeID()); //add camera to coalition

                if (negotiation_request_camera() == false) //look for next camera until 'false'
                    collaboration_request_data();//request measurements to cameras - unicast "CAWC_COLLABORATION_REQUEST" packet
            }
            else
                perr_app("ERROR (cameras should not reply instead the manager)");
            break;

        // ask for data to join coalition - sent by manager - processed by all cameras
        case CAWC_COLLABORATION_REQUEST:
            LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (sending data to manager)" << endl;
            collaboration_send_data(); //send data to manager - unicast "CAWC_COLLABORATION_DATA" packet
            break;

        // ask for data to collaborate - sent by coalition cameras - processed by manager
        case CAWC_COLLABORATION_DATA:

            //store received data
            _nb_buf[m->getNodeID()].rcv_state = true;
            _nb_buf[m->getNodeID()].z = m->getZ().clone();
            _nb_buf[m->getNodeID()].Rinv = m->getRinv().clone();
            _nb_buf[m->getNodeID()].Ht = m->getHt().clone();
            _nb_buf[m->getNodeID()].H = m->getH().clone();

            //check that all data is received
            if (check_manager_collaboration_data() == true) {
                LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (store received data and fusion)" << endl;
                collaboration_fuse(); //do data fusion
                collaboration_end(); //notify that collaboration is done - broadcast "CAWC_COLLABORATION_END" packet
            }
            else
                LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (store received data)" << endl;

            break;

        //signal to terminate the exchange of msgs to collaborate --> next frame can be analyzed
        case CAWC_COLLABORATION_END:

            LOGGER << "PROCESS PKT FROM node=" << m->getNodeID() << " TYPE=" << CAWCpkt_str[m->getPktType()] <<  " (reset collaboration data)" << endl;
            //reset all flags & data
            for (int i=0; i < n_nodes; i++) {
                _nb_buf[i].utility = -1;
                _nb_buf[i].battery_level = -1;
                _nb_buf[i].load_level = -1;
                _nb_buf[i].rcv_data_utility = false;
                _nb_buf[i].rcv_ack_manager = false;
                _nb_buf[i].rcv_state = false;
            }

            //save amount of data communicated
            coaLog.rxdata.at<double>(0,self) = _bytesRX;
            coaLog.txdata.at<double>(0,self) = _bytesTX;
            _coa_buf.state = INACTIVE;
            break;
    }

    e2 = cv::getTickCount();
    _time_pkt_processing += (e2 - e1)/ cv::getTickFrequency(); //CPU time for processing packets

    return true;
}

/*!
 * Called when data from a neighbor node is received and needs to be saved in the memory of the current node
 *
 * @param[in] pos Position of the databuffer. Currently, the nodeID (unique in the network) is used as position
 * @param[in] nodeID Identifier of the source node corresponding to the data received
 * @param[in] CAMID Identifier of the camera of the data received
 * @param[in] u Utility of the data received
 * @param[in] blevel Battery level of the data received
 * @param[in] load Load level of the data received
 * @param[in] priority Priority of the data received
 * @param[in] counter Processing step counter of the data received
 *
 * @return FLAG to indicate the correct data save
 */
bool WiseCameraCAWCTracker::update_data_buffer(int pos, int nodeID, int CAMID, double u, double blevel, double load, double priority, int counter)
{
    //check requested position outside buffer limit (MAX_SIZE_BUFFER)
    if (pos > (int)_nb_buf.size())
        return false;

    //store received data
    CAWC::neigbor_data_t &nbdata = _nb_buf[pos];
    nbdata.nodeID = nodeID;
    nbdata.camID = CAMID;
    nbdata.utility = u;
    nbdata.battery_level = blevel;
    nbdata.load_level = load;
    nbdata.priority = priority;
    nbdata.rcv_data_utility = true;
    nbdata.step_counter = counter;

    return true;
}

/*!
 * Called to check that the data (utility) from all neighbors have been received.
 *
 * @return FLAG to indicate if all neighbor data is stored (TRUE) or the node has to wait for new incoming data (FALSE)
 */
bool WiseCameraCAWCTracker::check_databuffer_ready()
{
    //check if buffer is ready for further processing
    int count = 0;
    for (int i=0; i < n_nodes; i++)
        if (_nb_buf[i].rcv_data_utility == true)
            count++;

    LOGGER << "UTILITY BUFFER " << count <<"/"<< n_nodes << endl;
    return count==n_nodes;
}

/*!
 * Called to check that all coalition cameras have sent the ACK message to the manager
 *
 * @return FLAG to indicate if all cameras have replied (TRUE) or the node has to wait for new incoming replies (FALSE)
 */
bool WiseCameraCAWCTracker::check_manager_ack()
{
    //check if buffer is ready for further processing
    int count = 0;
    for (int i=0; i < n_nodes; i++)
        if (_nb_buf[i].rcv_ack_manager == true)
            count++;

    LOGGER << "ACK-TO-MANAGER " << count <<"/"<< n_nodes-1 << endl;
    if (_coa_buf.rcv_state_manager == true)
        return count==n_nodes-1;
    else
        return false;
}

/*!
 * Called to identify the next manager for the coalition
 *
 * @return FLAG to indicate successful identification
 */
bool WiseCameraCAWCTracker::identify_and_announce_manager()
{
    _coa_buf.state = MANAGER_SELECTION; //update coalition status

    double minVal,maxVal,maxValb,maxVall;
    cv::Point minLoc,maxLoc;
    cv::Mat b = cv::Mat::zeros(1,n_nodes,CV_64F); //battery of all camera nodes
    cv::Mat l = cv::Mat::zeros(1,n_nodes,CV_64F); //load of all camera nodes

    //only the old coalition manager identifies next manager
    if (_coa_buf.manID == self){

        //get the battery & load of all received nodes
        for (int i=0; i < n_nodes; i++)  {
           b.at<double>(0,i) = _nb_buf[i].battery_level;
           l.at<double>(0,i) = _nb_buf[i].load_level;
        }

        //find mix/max values
        cv::minMaxLoc( b, &minVal, &maxValb, &minLoc, &maxLoc );
        cv::minMaxLoc( l, &minVal, &maxVall, &minLoc, &maxLoc );

       //compute the cost function
       cv::Mat hfun = b/maxValb * _coa_buf.beta + (1-l/maxVall) * (1-_coa_buf.beta);
       cv::minMaxLoc( hfun, &minVal, &maxVal, &minLoc, &maxLoc );

       //update new manager & announce to the network
       (_coa_buf.manID == maxLoc.x)?LOGGER<<"MANAGER node="<<_coa_buf.manID << endl:LOGGER<<"NEW MANAGER node="<< maxLoc.x << endl;
       _coa_buf.manID = maxLoc.x;
       _coa_buf.rcv_state_manager = false;
       //cout << "Battery b=" << print(b,5) << endl << "Load l=" << print(l,4) << endl << "hfun h=" << print(hfun,5) << endl;

       WiseCameraCAWCTrackerPkt *pkt = CAWC::create_newMan_pkt(self,_camID, _coa_buf.manID,_coa_buf.IF.x.clone(),_coa_buf.IF.P.clone());
       send_message(pkt); //Announce new manager to all cameras (Broadcast message)

       //Log coalition data
       coaLog.b.push_back(b.clone());
       coaLog.l.push_back(l.clone());
       coaLog.manager.push_back(_coa_buf.manID);
       coaLog.step_count.push_back(_step_counter);
       coaLog.frameID.push_back(this->_curFrame);
    }
    return true;
}

/*!
 * Called to select new cameras to be added to the coalition by exploring the marginal utilities & costs
 *
 * @return FLAG to indicate successful processing of the packet
 */
bool WiseCameraCAWCTracker::negotiation_request_camera()
{
    _coa_buf.state = NEGOTIATION; //update coalition status

    double minVal,maxVal,Ucoa=0,mu,mc;
    cv::Point minLoc,maxLoc;
    cv::Mat Ucoa_new = cv::Mat::zeros(1, n_nodes, CV_64F); //utility of coalition after adding each camera
    int selCam = -1;

    //get camera utility if coalition is empty
    if (_coa_buf.cams.size() == 0) {
           for (int i=0; i < n_nodes; i++)
               Ucoa_new.at<double>(0,i) = _nb_buf[i].utility/MAX_UTILITY;
           coaLog.u.push_back(Ucoa_new.clone());
           //TODO
           //LOGGER << "NEGOTIATION: step =" << _step_counter << " (" << _curFrame << ") u="  << print(Ucoa_new,2) << endl;
    }
    else
    {
        //compute current coalition utility
        double tmp = 1;
        for (unsigned int i=0; i < _coa_buf.cams.size(); i++) {
            int id = _coa_buf.cams[i];
            tmp = tmp * ( 1 - _nb_buf[id].utility/MAX_UTILITY * _nb_buf[id].priority );
        }
        Ucoa = 1 - tmp;

        //compute coalition utility by adding cameras
        for (int i=0; i < n_nodes; i++) {
           std::vector<int>::iterator it1 = find(_coa_buf.cams.begin(), _coa_buf.cams.end(),i);
           std::vector<int>::iterator it2 = find(_coa_buf.nego.begin(), _coa_buf.nego.end(),i);

           // if camera is not in the coalition, compute the new utility by adding it
           if (it1 == _coa_buf.cams.end() && it2 == _coa_buf.nego.end())
               Ucoa_new.at<double>(0,i) = 1 - ((1-Ucoa) * (1 - _nb_buf[i].utility/MAX_UTILITY * _nb_buf[i].priority ));
       }
    }

    //find best camera
    cv::minMaxLoc( Ucoa_new, &minVal, &maxVal, &minLoc, &maxLoc );
    selCam = maxLoc.x;

    //get its marginal utility (mu) and cost (mc)
    _coa_buf.cams.size()>0 ? mu=Ucoa_new.at<double>(0,selCam)-Ucoa : mu=Ucoa_new.at<double>(0,selCam);
    _coa_buf.cams.size()>0 ? mc=_coa_buf.mcost : mc=0;

    //LOGGER << "  Ucoa=" << setprecision(2) << Ucoa << " Ucoa+cam = " << print(Ucoa_new,2) << ", selCam="<< selCam << ", bestMU=" << mu  << endl;

    //check if marginal utility is greater than marginal cost
    if (mu > mc && _nb_buf[selCam].utility/MAX_UTILITY > 0)
    {
        LOGGER << "NEGOTIATION man=" << _coa_buf.manID << " cam=" << selCam <<endl;
        _coa_buf.nego.push_back(selCam);

        WiseCameraCAWCTrackerPkt *pkt = CAWC::create_empty_pkt(CAWC_NEGOTIATION_JOIN, CAWCpkt_str[CAWC_NEGOTIATION_JOIN], self,_camID);
        send_message(pkt,to_string(selCam));//unicast packet
        delete pkt;
    }
    else{
        LOGGER << "  MU<MC -> END NEGOTIATION C=" << _coa_buf.cams << endl;

        coaLog.ucoa.push_back(1-Ucoa);
        coaLog.nego.push_back(_coa_buf.nego);
        coaLog.cams.push_back(_coa_buf.cams);

        //stop operation if there is no coalition to create
        if (_coa_buf.cams.size() == 0) {
            coaLog.x.push_back(_coa_buf.IF.x.clone());
            coaLog.P.push_back(_coa_buf.IF.P.clone());
            collaboration_end();
            _coa_buf.state = INACTIVE; //coalition ready to collaborate
        }
        else
            _coa_buf.state = COLLABORATION; //coalition ready to collaborate
        return false;
    }
    return true;
}

/*!
 * Called when replying the coalition manager to a request for joining the coalition
 *
 * @return FLAG to indicate successful processing of the packet
 */
bool WiseCameraCAWCTracker::negotiation_reply()
{
    _coa_buf.state = NEGOTIATION; //update coalition status

    WiseCameraCAWCTrackerPkt *pkt = CAWC::create_empty_pkt(CAWC_NEGOTIATION_REPLY, CAWCpkt_str[CAWC_NEGOTIATION_REPLY], self,_camID);
    (resMgr->getRemainingEnergy() > _coa_buf.est_energy2operate) ? pkt->setReply(true):pkt->setReply(false);
    if (resMgr->getRemainingEnergy() < _coa_buf.est_energy2operate)
        std::cout <<resMgr->getRemainingEnergy() << " e=" << _coa_buf.est_energy2operate <<endl;
    send_message(pkt,to_string(_coa_buf.manID));//unicast packet
    delete pkt;

    return true;
}

/*!
 * Called to check that all coalition cameras have sent the collaboration data to the manager
 *
 * @return FLAG to indicate if all cameras have replied (TRUE) or the node has to wait for new incoming data (FALSE)
 */
bool WiseCameraCAWCTracker::check_manager_collaboration_data()
{
    //check if buffer is ready for further processing
    int count = 0;
    for (int i=0; i < n_nodes; i++)
        if (_nb_buf[i].rcv_state == true)
            count++;

    LOGGER << "DATA-TO-MANAGER " << count <<"/"<< _coa_buf.cams.size() << endl;
    return (unsigned int)count>=_coa_buf.cams.size();
}

/*!
 * Called to request data to coalition cameras by the manager
 *
 * @return FLAG to indicate correct operation
 */
bool WiseCameraCAWCTracker::collaboration_request_data()
{
    LOGGER << "REQUEST DATA BY MANAGER " << endl;

    if(_coa_buf.cams.size() == 0)
        return false;

    //NOTE: in terms of energy consumption, broadcast is more efficient than (many) unicast
    WiseCameraCAWCTrackerPkt *pkt = CAWC::create_empty_pkt(CAWC_COLLABORATION_REQUEST, CAWCpkt_str[CAWC_COLLABORATION_REQUEST], self,_camID);
    for (unsigned int i=0; i < _coa_buf.cams.size();i++)
        send_message(pkt, to_string(_coa_buf.cams[i]));//unicast "CAWC_COLLABORATION_REQUEST" packet
    delete pkt;

    return true;
}

/*!
 * Called to send data from coalition cameras to the manager
 *
 * @return FLAG to indicate correct operation
 */
bool WiseCameraCAWCTracker::collaboration_send_data()
{
    LOGGER << "SEND REQUESTED DATA TO MANAGER " << endl;

    //get measurement (z)
    cv::Rect2d est = _tracker.getTrackWindow(); //estimation in the image plane
    double Xw0=0,Yw0=0; //estimation in the ground-plane
    double x = 1/_scaleCols * (est.x+est.width/2);
    double y = 1/_scaleRows * (est.y+est.height);
    camMgr->imageToWorld(x,y,0, Xw0, Yw0); //conversion image->ground plane
    cv::Mat z = (cv::Mat_<double>(1, 2) << Xw0, Yw0);

    //send the packet
    WiseCameraCAWCTrackerPkt *pkt = CAWC::create_meas_pkt(self,_camID, z,_coa_buf.IF.H,_coa_buf.IF.Ht,_coa_buf.IF.Rinv);
    send_message(pkt,to_string(_coa_buf.manID));//unicast "CAWC_COLLABORATION_DATA" packet
    delete pkt;

    return true;
}

/*!
 * Called to fuse the data received from coalition cameras by the manager
 *
 * @return FLAG to indicate correct operation
 */
bool WiseCameraCAWCTracker::collaboration_fuse()
{
    double Xw0,Yw0;
    LOGGER << "MANAGER FUSING DATA C=" << _coa_buf.cams << endl;

    if (_coa_buf.initialized == false)
    {
        if (_nb_buf[self].utility > 0){
            camMgr->imageToWorld(_iniT.Xc + _iniT.width/2,_iniT.Yc + _iniT.height,0, Xw0, Yw0); //conversion image->ground plane
            _coa_buf.IF.x.at<double>(0) = Xw0;
            _coa_buf.IF.x.at<double>(1) = Yw0;
            _coa_buf.IF.x.at<double>(2) = 0 + normal(0,sqrt(_coa_buf.IF.P.at<double>(2,2)));
            _coa_buf.IF.x.at<double>(3) = 0 + normal(0,sqrt(_coa_buf.IF.P.at<double>(3,3)));

        }
        else{
            //if 'manager' is not initialized, take the first received data
            _coa_buf.IF.x.at<double>(0) = _nb_buf[_coa_buf.cams[0]].z.at<double>(0);
            _coa_buf.IF.x.at<double>(1) = _nb_buf[_coa_buf.cams[0]].z.at<double>(1);
            _coa_buf.IF.x.at<double>(2) = 0 + normal(0,sqrt(_coa_buf.IF.P.at<double>(2,2)));
            _coa_buf.IF.x.at<double>(3) = 0 + normal(0,sqrt(_coa_buf.IF.P.at<double>(3,3)));
        }
        _coa_buf.initialized = true;
        //TODO
        //LOGGER << "Cam " << _camID << ": tracker and coalition data initialized x=" << print(_coa_buf.IF.x,4) << endl;
    }

    //prediction of the target state estimation
    cv::Mat x0 = _coa_buf.IF.x.clone();
    cv::Mat x_ = _coa_buf.IF.A * _coa_buf.IF.x;
    cv::Mat P_ = _coa_buf.IF.A * _coa_buf.IF.P * _coa_buf.IF.At + _coa_buf.IF.Q;

    //update of the target state estimation - fusion of coalition cameras
    cv::Mat V  = P_.inv(cv::DECOMP_SVD); //initiate information vector
    cv::Mat v  = V * x_; //initiate information matrix

    double u_total=0;
    for (unsigned int i=0; i<_coa_buf.cams.size();i++) {
        u_total= u_total+_nb_buf[_coa_buf.cams[i]].utility;
    }

    cv::Mat zt, H, Ht, Rinv;
    for (unsigned int i=0; i<_coa_buf.cams.size();i++) {
        H    = _nb_buf[_coa_buf.cams[i]].H.clone();
        Ht   = _nb_buf[_coa_buf.cams[i]].Ht.clone();
        Rinv = _nb_buf[_coa_buf.cams[i]].Rinv.clone();

        cv::transpose(_nb_buf[_coa_buf.cams[i]].z, zt);
        v = v + Ht*Rinv*zt;
        V = V + Ht*Rinv*H;
        //LOGGER <<  "H="<< H << endl << "Ht="<< Ht << endl << "Rinv="<< Rinv << endl;
        //LOGGER <<  "Ht*Rinv*zt="<<Ht*Rinv*zt << endl << "Ht*Rinv*H=" << Ht*Rinv*H << endl;
        //LOGGER << "  cam=" <<_coa_buf.cams[i] << " z=" << print(_nb_buf[_coa_buf.cams[i]].z, 4) << endl;
    }
    //LOGGER <<  "v="<<print(v, 4) << endl << "V="<<print(V, 4) << endl;

    //information filter data --> (x,P) representation
    _coa_buf.IF.P = V.inv(cv::DECOMP_SVD);
    _coa_buf.IF.x = _coa_buf.IF.P*v;

    //Log coalition data
    coaLog.x.push_back(_coa_buf.IF.x.clone());
    coaLog.P.push_back(_coa_buf.IF.P.clone());

    /*LOGGER << "  x0=" << print(x0, 4) << endl;
    LOGGER << "  x_=" << print(x_, 4) << endl;
    LOGGER << "  x =" << print(_coa_buf.IF.x, 4) << endl;
    LOGGER << "  P_ =" << print(P_, 2) << endl;
    LOGGER << "  P =" << print(_coa_buf.IF.P, 2) << endl;/**/
    return true;
}

/*!
 * Called when the tasks of the coalition are completed
 *
 * @return FLAG to indicate correct operation
 */
bool WiseCameraCAWCTracker::collaboration_end()
{
    LOGGER << "Send COALITION END " << endl;

    //announce the end of coalition processing
    WiseCameraCAWCTrackerPkt *pkt = CAWC::create_empty_pkt(CAWC_COLLABORATION_END, CAWCpkt_str[CAWC_COLLABORATION_END], self,_camID);
    send_message(pkt);

    return true;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraCAWCTracker::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
    // Called when a DirectApplication Message is received
    LOGGER << "HANDLE DIRECT APPLICATION MESSAGE" << endl;

    // In this case we treat the message received through DirectApplication as a normal network message
    process_network_message(pkt);
}

/*!
 * Called when the simulation is finished so coalition log can be written
 */
void WiseCameraCAWCTracker::save_coalition_data()
{
   ofstream logCOA;
   logCOA.open(_logCOAstr.c_str());

   logCOA << "run=" << _currentRun << endl;
   for (int i=0;(unsigned int)i<coaLog.step_count.size()-1;i++) {
       logCOA << "frameID=" << coaLog.frameID[i] << endl << "manager=" << coaLog.manager[i] << endl;
       logCOA << "nego=" << coaLog.nego[i] << endl << "cam=" << coaLog.cams[i] << endl;
      /* logCOA << "u=" << print(coaLog.u[i],4)<< endl << "ucoa=" << coaLog.ucoa[i]<< endl;
       logCOA << "b=" << print(coaLog.b[i],5)<< endl << "l=" << print(coaLog.l[i],4)<< endl;
       logCOA << "tx="<< print(coaLog.tx[i],4)<< endl << "rx="<< print(coaLog.rx[i],4)<< endl;
       logCOA << "x=" << print(coaLog.x[i],4)<< endl << "P=" << print(coaLog.P[i],4)<< endl;/**/
   }
   logCOA.close();
}

/*!
 * Called when the simulation is finished so coalition log can be written
 */
void WiseCameraCAWCTracker::save_camera_data()
{
 ofstream logCAM;
 logCAM.open(_logCAMstr.c_str());

 logCAM << "#" << "run=" << _currentRun << endl;
 logCAM << "#" << "nodeID=" << self << endl;
 logCAM << "#" << "camID=" << _cam_buf.camid << endl;
 logCAM << "#" << "targetID=" << _iniT.id << endl;
 logCAM << "#" << "scaleFactorRows=" << _scaleRows << endl;
 logCAM << "#" << "scaleFactorCols=" << _scaleCols << endl;
 logCAM << "#" << "t_sim\tfrID\tu\tl\tb\tXi\tYi\tWi\tHi\tX0i\tY0i\tX0w\tY0w" << endl;

 for (int i=0;(unsigned int)i<_cam_buf.step_count.size()-1;i++) {
     logCAM << std::setprecision(3) << _cam_buf.time[i] << "\t" << _cam_buf.frameID[i] << "\t";
     logCAM << std::setprecision(3) << _cam_buf.u[i] << "\t" << std::setprecision(3) << _cam_buf.l[i] << "\t" << _cam_buf.b[i] << "\t";
     logCAM << _cam_buf.Xi[i] << "\t" << _cam_buf.Yi[i] << "\t" << _cam_buf.Wi[i] << "\t" << _cam_buf.Hi[i] << "\t";
     logCAM << _cam_buf.Xi[i]+_cam_buf.Wi[i]/2 << "\t" << _cam_buf.Yi[i]+_cam_buf.Hi[i] << "\t";
     logCAM << std::setprecision(10) << _cam_buf.Xw[i] << "\t" << std::setprecision(10) << _cam_buf.Yw[i] << endl;
 }
 logCAM.close();
}
