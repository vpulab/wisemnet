// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
#include "WiseCameraAppTest.h"
#include "WiseCameraDetectionsMessage_m.h"
#include "WiseCameraAppTestPacket_m.h"
#include "WiseDebug.h"

Define_Module(WiseCameraAppTest);

#define ALARM_SEND_PACKET 0
#define ALARM_SENSOR_SAMPLE 1
#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "

ofstream WiseCameraAppTest::logger;

void WiseCameraAppTest::startup()
{
	// This function is called upon simulation start-up
	if (!logger.is_open())
		logger.open("myLog.txt");

	WiseCameraApplication::startup();
	declareOutput("Number of detections");
	detection_counter = 0;
	setTimer(ALARM_SENSOR_SAMPLE, 8);
}

void WiseCameraAppTest::finishSpecific()
{
	// This function is called when simulation is finishing
	WiseCameraApplication::finishSpecific();
}

void WiseCameraAppTest::timerFiredCallback(int index)
{
	// Called when an alarm expires

	switch (index) {
	case ALARM_SENSOR_SAMPLE:
		// alarm was for sensor reading:
		// query the sensor manager for a new sample (image)
		requestSensorReading();
		break;
	case ALARM_SEND_PACKET:
		// alarm was a send packet: create a test packet and broadcast
		WiseCameraAppTestPacket * pkt;
		pkt = new WiseCameraAppTestPacket("Wise Camera App Test Pkt",APPLICATION_PACKET);
		// Add the local detection counter to the message
		pkt->setDetectionCounter(detection_counter); 
		// The packet length is 100 bytes 
		pkt->setByteLength(100); 
		toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);
		// Set the alarm to send a packet after 40 seconds.
		setTimer(ALARM_SEND_PACKET, 40);
		break;
	default:
		// unexpected alarm ID: generate and error
		opp_error("WiseCameraAppTest::timerFiredCallback(): BAD index");
	}
}

void WiseCameraAppTest::fromNetworkLayer(WiseApplicationPacket * rcvPacket, const char *src, double rssi, double lqi)
{
	// Function called when a packet is received from the network layer
	// of the communication module
	
	WiseCameraAppTestPacket *m;
	m = check_and_cast<WiseCameraAppTestPacket*>(rcvPacket);

	// Print some packet info: sender ID, RSSI, LQI
	ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();
	double l = 1000 * SIMTIME_DBL(simTime() - ctl.timestamp);
	LOGGER << "RX packet:" " from=" << string(src) << " rssi=" << rssi << " lqi=" << lqi << " e2e_delay_ms=" << l << endl;
	LOGGER << "Packet Content: local detection counter of node [" << ctl.source << "] = " << m->getDetectionCounter() << endl;
}

void WiseCameraAppTest::handleSensorReading(WiseCameraMessage *sample)
{
	// Function called when a new sample is ready (from the sensor manager)
    unsigned int old_count = detection_counter;

	string t = sample->getCameraSampleType();
	if (t != "WiseCameraDetections") {
		LOGGER << "Received invalid camera sample of unhandled type '" << t << "'" << endl;
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
			LOGGER << "Detection: BoundingBox: " << " X_tl=" << d.bb_x_tl << " Y_tl=" << d.bb_y_tl << " X_br=" << d.bb_x_br << " Y_br=" << d.bb_y_br << endl;
		}
	}

	if (old_count == detection_counter)
	    LOGGER << "Detection: none " << endl;

	// Set the alarm to have a new sample after 2 seconds.
	setTimer(ALARM_SENSOR_SAMPLE, 2);
}

void WiseCameraAppTest::handleDirectApplicationMessage(WiseApplicationPacket *)
{

}
