// *****************************************************************************************
// Copyright (C) 2011 Christian Nastasi, 2017 Juan C. SanMiguel and Andrea Cavallaro
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
 * \file WiseCameraAppTest.cc
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Source file for the WiseCameraAppTest class
 * \version 1.4
 */
#include <wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.h>
#include <wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.h> //to use "WiseCameraAppTestPacket" packets
#include <wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h> //to process "WiseCameraDetectionsMessage" packets
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
using namespace std;

/** @brief Code for the timer callback to send a packet to the network*/
#define ALARM_SEND_PACKET 0

/** @brief Code for the timer callback to perform a sensor reading*/
#define ALARM_SENSOR_SAMPLE 1

Define_Module(WiseCameraAppTest);

/*
 * \brief Method for specific resource initialization (variables and structures) after WiseBaseApp::initialize()
 */
void WiseCameraAppTest::startup()
{
    WISE_DEBUG_32("WiseCameraAppTest::startup() called");

	// This function is called upon simulation start-up
	WiseCameraApp::startup();
	declareOutput("Number of detections");
	detection_counter = 0;
	setTimer(ALARM_SENSOR_SAMPLE, 2);
	setTimer(ALARM_SEND_PACKET, 5);
}

/*
 * \brief Method for specific resource destroy (variables and structures) after WiseBaseApp::finish()
 */
void WiseCameraAppTest::finishSpecific()
{
    // This function is called when simulation is finishing
    WISE_DEBUG_32("WiseCameraAppTest::finishSpecific() called");
}

/*
 * \brief Method to handle the timers set in the application layer
 *
 * Method to handle the timers set in the application layer set via
 * the function "setTimer". When timers are triggered, this function
 * is executed.
 *
 * \param index Code of the triggered timer
 */
void WiseCameraAppTest::timerFiredCallback(int index)
{
	// Called when an alarm expires
    WISE_DEBUG_32("WiseCameraAppTest::timerFiredCallback() called");

	switch (index) {
	case ALARM_SENSOR_SAMPLE:
		// alarm was for sensor reading:
		// query the sensor manager for a new sample (image)
		requestSensorReading();
		break;
	case ALARM_SEND_PACKET:
		// alarm was a send packet: create a test packet and broadcast
		WiseCameraAppTestPacket* pkt;
		pkt = new WiseCameraAppTestPacket("WiseCamAppTest Pkt",APPLICATION_PACKET);
		// Add the local detection counter to the message
		pkt->setDetectionCounter(detection_counter); 
		// The packet length is 100 bytes 
		pkt->setByteLength(100); 
		pkt->setPayloadArraySize(100);
		toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);
		WISE_DEBUG_32("WiseCameraAppTest::\tTX detection packet");

		// Set the alarm to send a packet after 10 seconds.
		setTimer(ALARM_SEND_PACKET, 5);
		break;
	default:
		// unexpected alarm ID: generate and error
		opp_error("WiseCameraAppTest::timerFiredCallback(): BAD index");
	}
}


/*
 * \brief Method to handle data received from the sensor
 *
 * Method to handle data received from the sensor after a request
 * sensor reading. This function must extract the relevant data from
 * the received message and make it available for the application layer.
 * This method extends the "handleSensorReading" method of the WiseBaseApp class.
 *
 * \param m Message containing the sensed data
 */
void WiseCameraAppTest::handleSensorReading(WiseCameraMessage *sample)
{
    WISE_DEBUG_32("WiseCameraAppTest::handleSensorReading()");

    // Function called when a new sample is ready (from the sensor manager)
    unsigned int old_count = detection_counter;

    string t = sample->getCameraSampleType();
    if (t != "WiseCameraDetections") {
        WISE_DEBUG_32("WiseCameraAppTest::\tReceived invalid camera sample of unhandled type '" << t << "'");
        return;
    }
    // The sample type is expected to be a 'WiseCameraDetectionsMessage'.
    // Information about the valid detections (bounding boxes) are printed
    // to the log file (see the WiseTargetDetection for more details).
    WiseCameraDetectionsMessage *msg;
    msg = check_and_cast<WiseCameraDetectionsMessage*>(sample);
    unsigned len = msg->getDetectionsArraySize();
    for (unsigned i = 0; i < len; i++) {
        WiseTargetDetection d = msg->getDetections(i);
        if (d.valid) {
            // Add to detection counter in CastaliaResult File
            collectOutput("Number of detections");
            // Add to node detection counter
            detection_counter++;
            // Log some information
            WISE_DEBUG_32("WiseCameraAppTest::\tDetection: BoundingBox: " << " X_tl=" << d.bb_x_tl << " Y_tl=" << d.bb_y_tl << " X_br=" << d.bb_x_br << " Y_br=" << d.bb_y_br);
        }
    }

    if (old_count == detection_counter)
        WISE_DEBUG_32("WiseCameraAppTest::\tDetection: none " );

    // Set the alarm to have a new sample after 2 seconds.
    setTimer(ALARM_SENSOR_SAMPLE, 2);
}

/*
 * \brief Method to handle data received from the network
 *
 * Method to handle data received from the network for application-specific
 * processing. This method extends the "fromNetworkLayer" method of the WiseBaseApp class.
 *
 * \param rcvPacket Packet received with the data and metadata
 * \param src   Identifier of the source node
 * \param rssi  Received Signal Strength Indication
 * \param lqi   Link Quality Indicator
 *
 * \see https://en.wikipedia.org/wiki/Received_signal_strength_indication
 * \see https://en.wikipedia.org/wiki/Link_quality_analysis
 */
void WiseCameraAppTest::fromNetworkLayer(WiseBaseAppPacket * rcvPacket, const char *src, double rssi, double lqi)
{
	// Function called when a packet is received from the network layer of the communication module
    WISE_DEBUG_32("WiseCameraAppTest::fromNetworkLayer()");

	WiseCameraAppTestPacket *m;
	m = check_and_cast<WiseCameraAppTestPacket*>(rcvPacket);

	// Print some packet info: sender ID, RSSI, LQI
	ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
	double l = 1000 * SIMTIME_DBL(simTime() - ctl.timestamp);
	WISE_DEBUG_32("WiseCameraAppTest::\tRX packet:" " from=" << string(src) << " rssi=" << rssi << " lqi=" << lqi << " e2e_delay_ms=" << l);
	WISE_DEBUG_32("WiseCameraAppTest::\tPacket Content: local detection counter of node [" << ctl.source << "] = " << m->getDetectionCounter());
}
