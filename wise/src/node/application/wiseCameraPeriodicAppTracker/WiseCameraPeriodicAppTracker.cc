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
 * \file WiseCameraPeriodicAppTracker.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseCameraPeriodicAppTracker class
 * \version 1.4
 */
#include <wise/src/node/application/wiseCameraPeriodicAppTracker/WiseCameraPeriodicAppTracker.h>
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h>//packet format
#include <wise/src/utils/WiseUtils.h>
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

Define_Module(WiseCameraPeriodicAppTracker);

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraPeriodicAppTracker::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppTracker::startup()");

	// Access related-module parameters (read number of targets)
	//cModule *network = getParentModule()->getParentModule();

	//read flags and configuration params
	_target_id = par("target_id"); //get the ID of the target to track
	_waitForInitialization = par("waitForInitialization").boolValue(); //wait GUI when target is initializeds
}

/*!
 * Init resources for tracking. Declared in base class WiseCameraPeriodicApp.
 */
bool WiseCameraPeriodicAppTracker::at_init()
{
    WISE_DEBUG_32("WiseCamPerAppTracker::at_init()");

    //create GUI windows
    double cpuf = this->resMgr->getPROInfo().clockfreq;
    double senf = this->resMgr->getSENFrameRate();
    _win1 << "Camera" << self << ":tracking (sen=" << senf<<"fps cpu="<<cpuf/1e9<<" Ghz)"<<std::endl;

    cv::namedWindow(_win1.str().c_str());

    if (this->_pause_place_GUI)
    {
        cv::Mat temp = cv::Mat::zeros(480,640,CV_32F);
        std::cout << "Please place the GUI and press any key..." << std::endl;
        cv::imshow(_win1.str().c_str(),temp);
        cv::waitKey(0);
    }

    // Set up tracker.
    // Instead of MIL, you can also use
    // BOOSTING, KCF, TLD, MEDIANFLOW or GOTURN
    _tracker = cv::Tracker::create( "KCF" );
    _isInit = false; //tracker not initialized

    return true;
}

/*!
 * Destroy resources for tracking. Declared in base class WiseCameraPeriodicApp.
 */
void WiseCameraPeriodicAppTracker::at_finishSpecific()
{
    WISE_DEBUG_32("WiseCamPerAppTracker::at_finishSpecific()");

   //destroy GUI windows
   cv::destroyAllWindows();
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicApp.
 */
bool WiseCameraPeriodicAppTracker::at_sample()
{
    // Called when a new sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppTracker::at_sample()");
    _step_counter++;

    if (_buf.type != FRAMES)
        opp_error("\n[WISECAM]: error - not sensing frames\n ");
    cv::Mat frame = _buf.frame;

    if (_isInit == false && _gtreader != NULL)
    {
       //read ground-truth data
       std::map<int,std::vector<target_detection_t>> *alldets = _gtreader->getData();
       std::vector<target_detection_t> dets = (*alldets)[_buf.curFrame];

           //initialize tracker if detections available
           if((int)dets.size()>0)
           {
               for (int i=0;i<(int)dets.size();i++)
                {
                    target_detection_t d = dets[i];

                    if (d.target_id ==  _target_id)
                    {
                        // Define an initial bounding box
                        int width = abs(d.bb_x_tl-d.bb_x_br);
                        int height = abs(d.bb_y_tl-d.bb_y_br);
                        cv::Rect2d bbox = cv::Rect2d(d.bb_x_tl,d.bb_y_tl, width,height);

                        // Uncomment the line below if you
                        // want to choose the bounding box
                        // bbox = selectROI(frame, false);

                        // Initialize tracker with first frame and bounding box
                        _tracker->init(frame, bbox);

                        _tracker->update(frame, _bbox);
                        cv::rectangle(frame,_bbox, cv::Scalar( 255, 0, 0 ), 2, 1 );
                        cv::Mat newFrame;
                        cv::resize(frame,newFrame,cv::Size(frame.cols*_displayWinScale,frame.rows*_displayWinScale));
                        cv::imshow(_win1.str().c_str(),newFrame);
                        if (_waitForInitialization)
                            cv::waitKey(0);

                        _isInit = true;
                    }
                }
           }
    }
    else
    {
        _tracker->update(frame, _bbox);
        // Draw bounding box
        cv::rectangle(frame,_bbox, cv::Scalar( 255, 0, 0 ), 2, 1 );
    }

    //get the frame number and write it on the current frame
    stringstream ss;
    cv::rectangle(frame, cv::Point(10, 2), cv::Point(100,20), cv::Scalar(255,255,255), -1);
    ss << _buf.curFrame;
    cv::putText(frame,  ss.str().c_str(), cv::Point(15, 15),cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

    //show the current frame with tracking data
    cv::Mat newFrame;
    cv::resize(frame,newFrame,cv::Size(frame.cols*_displayWinScale,frame.rows*_displayWinScale));
    cv::imshow(_win1.str().c_str(),newFrame);
    cv::waitKey(1);

    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicApp".
 */
bool WiseCameraPeriodicAppTracker::at_end_sample()
{
	// Called when a new sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppTracker::at_end_sample()");

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraPeriodicAppTrackerMessage type)
 */
bool WiseCameraPeriodicAppTracker::process_network_message(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_32("WiseCamPerAppTracker::process_network_message()");

    std::cout << "received data node=" << self << std::endl;
    const WiseCameraPeriodicAppPacket *m = check_and_cast<const WiseCameraPeriodicAppPacket*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();

    std::ostringstream os;
    os << "CAM" << self << " Received data from cam " << ctl.source;
    //cv::imshow(os.str(), m->getFrame());
    //cv::waitKey(1);*/
    return true;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraPeriodicAppTracker::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppTracker::handleDirectApplicationMessage()");

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}
