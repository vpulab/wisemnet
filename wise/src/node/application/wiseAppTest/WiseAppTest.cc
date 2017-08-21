// *****************************************************************************
//  Copyright (C): Christian Nastasi, 2011                                    
//  Author(s): Christian Nastasi                                              
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa)           
//  - School of Elec Eng and Computer Science, Queen Mary University (London) 
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:          
//  - c.nastasi@sssup.it                                                      
//  - nastasichr@gmail.com                                                    
//  - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#include "WiseAppTest.h"
using namespace std;

Define_Module(WiseAppTest);

#define ALARM_SEND_PACKET 0
#define ALARM_SENSOR_SAMPLE 1
#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "

ofstream WiseAppTest::logger;

void WiseAppTest::startup()
{
	// This function is called upon simulation start-up
	if (!logger.is_open())
		logger.open("myLog.txt");
	LOGGER << "WiseAppTest::startup() called" << endl;

	// Set alarm to send a packet (0 delay -> NOW).
	setTimer(ALARM_SEND_PACKET, 0);
	// Set alarm to request a sample to the sensor manager (in 8 seconds)
	setTimer(ALARM_SENSOR_SAMPLE, 8);
}

void WiseAppTest::finishSpecific()
{
	// This function is called when simulation is finishing
	LOGGER << "WiseAppTest::finishSpecific() called" << endl;
}

void WiseAppTest::timerFiredCallback(int index)
{
	// Called when an alarm expires:
	LOGGER << "WiseAppTest::timerFiredCallback() called";
	switch (index) {
	case ALARM_SENSOR_SAMPLE:
	    LOGGER << "ALARM_SENSOR_SAMPLE" << endl;
		// alarm was for sensor reading:
		// query the sensor manager a new sample (image)
		requestSensorReading();
		break;
	case ALARM_SEND_PACKET:
	    LOGGER << "ALARM_SEND_PACKET" << endl;
		// alarm was a send packet: create a simple packet of 19200 
		// bytes, put some payload and broadcast it.
		WiseApplicationPacket * pkt;
		pkt = new WiseApplicationPacket("Wise Test Application Pkt",APPLICATION_PACKET);
		pkt->setPayloadArraySize(19200);
		for (unsigned char c = 0; c < 100; c++)
			pkt->setPayload(c, c);
		pkt->setSequenceNumber(1);
		pkt->setByteLength(19200);
		toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS);
		break;
	default:
		// unexpected alarm ID: generate and error
		opp_error("WiseAppTest::timerFiredCallback(): BAD index");
	}
}

void WiseAppTest::handleSensorReading(WiseSensorManagerMessage *m)
{
    // Function called when a new sample (from the sensor manager) is ready
    LOGGER << "WiseAppTest::handleSensorReading() called" << endl;
    // Check that the sample type is from EmptySensor
    WiseEmptySensorMessage *s = check_and_cast<WiseEmptySensorMessage*>(m);
    // Print the sensor reading (a random value)
    LOGGER << "\tEmpty Sensor (Random Value) = " << s->getRandomValue() << endl;
    // Set alarm to read a new sample after 10 seconds
    setTimer(ALARM_SENSOR_SAMPLE, 10);
}

void WiseAppTest::fromNetworkLayer(WiseApplicationPacket * rcvPacket, const char *src, double rssi, double lqi)
{
	// Function called when a packet is received from the network layer of the communication module
	LOGGER << "WiseAppTest::fromNetworkLayer() called" << endl; 

	// Print some packet info: sender ID, RSSI, LQI, payload(hex) 
	LOGGER << "\tRx from" << string(src) << " with rssi=" << rssi << " lqi=" << lqi << endl << "\tPayload[] = " << hex;
	for (unsigned c = 0; c < 100; c++)
		logger << (unsigned int) rcvPacket->getPayload(c) << " ";
	logger << dec << endl;
	// Calculate application-to-application communication delay and print it
	ApplicationInteractionControl_type ctl = rcvPacket->getApplicationInteractionControl();
	double l = 1000 * SIMTIME_DBL(simTime() - ctl.timestamp);
	LOGGER << "\t app2app delay = " << l << endl;
}

void WiseAppTest::handleDirectApplicationMessage(WiseApplicationPacket *) {}
