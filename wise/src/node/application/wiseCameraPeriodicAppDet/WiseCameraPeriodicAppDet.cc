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
 * \file WiseCameraPeriodicAppDet
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseCameraPeriodicAppDet class
 * \version 1.4
 */
#include <wise/src/node/application/wiseCameraPeriodicAppDet/WiseCameraPeriodicAppDet.h>
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h>//packet format
#include <wise/src/utils/WiseUtils.h>
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

Define_Module(WiseCameraPeriodicAppDet);

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraPeriodicAppDet::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppDet::startup()");

	// Access related-module parameters (read number of targets)
	//cModule *network = getParentModule()->getParentModule();
}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeriodicAppDet::at_init()
{
    WISE_DEBUG_32("WiseCamPerAppDet::at_init()");

    //create GUI windows
    _win1 << "Camera" << self << ":frame";
    cv::namedWindow(_win1.str().c_str());

    _win2 << "Camera" << self << ":mog2";
    cv::namedWindow(_win2.str().c_str());

    //create Background Subtractor objects
    _pMOG2 = cv::createBackgroundSubtractorMOG2(); //MOG2 approach

    return true;
}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
void WiseCameraPeriodicAppDet::at_finishSpecific()
{
    WISE_DEBUG_32("WiseCamPerAppDet::at_finishSpecific()");

   //destroy GUI windows
   cv::destroyAllWindows();
}


/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeriodicAppDet::at_sample()
{
    // Called when a new sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppDet::at_sample()");
    _step_counter++;

    if (_buf.type != FRAMES)
        opp_error("\n[WISECAM]: error - not sensing frames\n ");
    cv::Mat frame = _buf.frame;

    //PERFORM SOME BASIC PROCESSING USING OPENCV
    //update the background model
    cv::Mat fgmask;
    _pMOG2->apply(frame, fgmask);

    //get the frame number and write it on the current frame
    stringstream ss;
    rectangle(frame, cv::Point(10, 2), cv::Point(100,20), cv::Scalar(255,255,255), -1);
    ss << _buf.curFrame;
    cv::putText(frame,  ss.str().c_str(), cv::Point(15, 15),cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

    //show the current frame and the fg masks
    cv::imshow(_win1.str().c_str(), frame);
    cv::imshow(_win2.str().c_str(), fgmask);
    cv::waitKey(100);

    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicAlgo".
 */
bool WiseCameraPeriodicAppDet::at_end_sample()
{
	// Called when a new sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppDet::at_end_sample()");

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraPeriodicAppTestMessage type)
 */
bool WiseCameraPeriodicAppDet::process_network_message(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_32("WiseCamPerAppDet::process_network_message()");

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
void WiseCameraPeriodicAppDet::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppDet::handleDirectApplicationMessage()");

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}
