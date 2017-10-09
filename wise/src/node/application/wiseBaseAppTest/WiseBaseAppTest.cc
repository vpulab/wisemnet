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
 * \file WiseBaseAppTest.cc
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Source file for the WiseBaseAppTest class
 * \version 1.4
 */
#include <wise/src/node/application/wiseBaseAppTest/WiseBaseAppTest.h>
#include <wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h> //to use "WiseEmptySensorMessage" packets
#include <wise/src/utils/WiseDebug.h> //for logs/debug
using namespace std;

/** @brief Code for the timer callback to send a packet to the network*/
#define ALARM_SEND_PACKET 0

/** @brief Code for the timer callback to perform a sensor reading*/
#define ALARM_SENSOR_SAMPLE 1

Define_Module(WiseBaseAppTest);

/*
 * \brief Method for specific resource initialization (variables and structures) after WiseBaseApp::initialize()
 */
void WiseBaseAppTest::startup()
{
    WISE_DEBUG_32("WiseBaseAppTest::startup() called");

	// Set alarm to send a packet (0 delay -> NOW).
	setTimer(ALARM_SEND_PACKET, 0);
	// Set alarm to request a sample to the sensor manager (in 8 seconds)
	setTimer(ALARM_SENSOR_SAMPLE, 8);
}

/*
 * \brief Method for specific resource destroy (variables and structures) after WiseBaseApp::finish()
 */
void WiseBaseAppTest::finishSpecific()
{
	// This function is called when simulation is finishing
    WISE_DEBUG_32("WiseBaseAppTest::finishSpecific() called");
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
void WiseBaseAppTest::timerFiredCallback(int index)
{
	// Called when an alarm expires:
    WISE_DEBUG_32("WiseBaseAppTest::timerFiredCallback() called");

	switch (index) {
	case ALARM_SENSOR_SAMPLE:
	    WISE_DEBUG_32("WiseBaseAppTest::\tALARM_SENSOR_SAMPLE");
		// alarm was for sensor reading:
		// query the sensor manager a new sample (image)
		requestSensorReading();
		break;
	case ALARM_SEND_PACKET:
	{
	    WISE_DEBUG_32("WiseBaseAppTest::\tALARM_SEND_PACKET");
		// alarm was a send packet: create a simple packet of 19200 
		// bytes, put some payload and broadcast it.
	    WiseBaseAppPacket* pkt = new WiseBaseAppPacket("WiseBaseAppTest Pkt",APPLICATION_PACKET);
		pkt->setPayloadArraySize(19200);
		for (unsigned char c = 0; c < 100; c++)
			pkt->setPayload(c, c);
		pkt->setSequenceNumber(1);
		pkt->setByteLength(19200);
		toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);
		break;
	}
	default:
		// unexpected alarm ID: generate and error
		opp_error("WiseBaseAppTest::timerFiredCallback(): BAD index");
		break;
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
void WiseBaseAppTest::handleSensorReading(WiseSensorManagerMessage *m)
{
    // Function called when a new sample (from the sensor manager) is ready
    WISE_DEBUG_32("WiseBaseAppTest::handleSensorReading() called");

    // Check that the sample type is from EmptySensor and print it
    WiseEmptySensorMessage *s = check_and_cast<WiseEmptySensorMessage*>(m);
    WISE_DEBUG_32("WiseBaseAppTest::\tEmpty Sensor (Random Value) = " << s->getRandomValue());

    // Set alarm to read a new sample after 10 seconds
    setTimer(ALARM_SENSOR_SAMPLE, 10);
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
void WiseBaseAppTest::fromNetworkLayer(WiseBaseAppPacket* rcvPacket, const char *src, double rssi, double lqi)
{
	// Function called when a packet is received from the network layer of the communication module
    WISE_DEBUG_32("WiseBaseAppTest::fromNetworkLayer() called");

    //Payload
    std::ostringstream os;
	for (unsigned c = 0; c < 100; c++)
		os << (unsigned int) rcvPacket->getPayload(c) << " ";
	os << dec << endl;

	// Calculate application-to-application communication delay and print it
	ApplicationInteractionControl_type ctl = rcvPacket->getApplicationInteractionControl();
	double l = 1000 * SIMTIME_DBL(simTime() - ctl.timestamp);

	// Print some packet info: sender ID, RSSI, LQI, payload(hex)
	WISE_DEBUG_32("WiseBaseAppTest:\tRx from " << string(src) << " with rssi=" << rssi << " lqi=" << lqi << " app2app delay = " << l << " bytes=" << rcvPacket->getByteLength());
	//WISE_DEBUG_32("WiseBaseAppTest: Payload[] = " << os.str());
}
