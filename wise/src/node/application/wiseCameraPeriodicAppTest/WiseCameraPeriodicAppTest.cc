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
 * \file WiseCameraPeriodicAppTest.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseCameraPeriodicAppTest class
 * \version 1.4
 */
#include <wise/src/node/application/wiseCameraPeriodicAppTest/WiseCameraPeriodicAppTest.h>
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h>//packet format
#include <wise/src/utils/WiseUtils.h>
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

Define_Module(WiseCameraPeriodicAppTest);

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraPeriodicAppTest::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppTest::startup()");

	// Access related-module parameters (read number of targets)
	//cModule *network = getParentModule()->getParentModule();
}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeriodicAppTest::at_init()
{
    WISE_DEBUG_32("WiseCamPerAppTest::at_init()");

    //create GUI windows
    _win1 << "Camera" << self << ":frame";
    cv::namedWindow(_win1.str().c_str());

    return true;
}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
void WiseCameraPeriodicAppTest::at_finishSpecific()
{
    WISE_DEBUG_32("WiseCamPerAppTest::at_finishSpecific()");

   //destroy GUI windows
   cv::destroyAllWindows();
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeriodicAppTest::at_sample()
{
    // Called when a new sample (image) is ready
    WISE_DEBUG_32("WiseCamPerAppTest::at_sample()");
    _step_counter++;

    if (_buf.type != FRAMES)
        opp_error("\n[WISECAM]: error - not sensing frames\n ");
    cv::Mat frame = _buf.frame;

    //get the frame number and write it on the current frame
    stringstream ss;
    rectangle(frame, cv::Point(10, 2), cv::Point(100,20), cv::Scalar(255,255,255), -1);
    ss << _buf.curFrame;
    cv::putText(frame,  ss.str().c_str(), cv::Point(15, 15),cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

    //show the current frame
    cv::imshow(_win1.str().c_str(), frame);
    cv::waitKey(100);

    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicAlgo".
 */
bool WiseCameraPeriodicAppTest::at_end_sample()
{
	// Called when a new sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppTest::at_end_sample()");

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraPeriodicAppTestMessage type)
 */
bool WiseCameraPeriodicAppTest::process_network_message(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_32("WiseCamPerAppTest::process_network_message()");

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
void WiseCameraPeriodicAppTest::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppTest::handleDirectApplicationMessage()");

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}
