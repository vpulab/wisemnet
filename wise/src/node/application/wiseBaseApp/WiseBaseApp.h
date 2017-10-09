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
 * \file WiseBaseApp.cc
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header file for the WiseBaseApp class
 * \version 1.4
 */

#ifndef __WISEBASEAPP_H
#define __WISEBASEAPP_H
#include <omnetpp.h>

#include <castalia/src/helpStructures/TimerService.h>
#include <castalia/src/helpStructures/CastaliaModule.h>    //generic castalia module
#include <castalia/src/node/application/VirtualApplication.h>   //app model from castalia
#include <castalia/src/node/communication/radio/Radio.h>   //radio model from castalia
#include <castalia/src/node/mobilityManager/VirtualMobilityManager.h> //mobility manager from castalia

#include <wise/src/node/resourceManager/WiseResourceManager.h> //wise resource manager module
#include <wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h> //wise camera manager module
#include <wise/src/node/sensorManager/WiseSensorManagerMessage_m.h> //descriptor for sensor messages
#include <wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h> //packet descriptor

#define SELF_NETWORK_ADDRESS selfAddress.c_str()

/*! \class WiseBaseApp
 *  \brief This class implements the template for developing applications in WiSEMnet (network interface
 *
 *  The class contains basic functions to initialize resources, send/receive messages from/to network (or
 *  direct node-to-node communication) and handling of control messages. Prior to process packets, WiseBaseApp
 *  class discovers the communication graph for each node (ie, neigbours nodes using network communication).
 *
 *  Steps for developing a new application, \n
 *  1) Define a new application (new class extending WiseBaseApp)\n
 *  2) Create the structures to be used within your new application\n
 *  3) Implement the functions startup() and finishSpecific() for the new application requirements \n
 *  4) Implement the function handleSensorReading() to handle the data provided by the SensorManager \n
 *  5) Implement the functions fromNetworkLayer() and handleDirectApplicationMessage() to handle received
 *  packets from, respectively the network and direct node-to-node communication \n
 *  6) Functions handleNetworkControlMessage(), handleMacControlMessage() and handleRadioControlMessage() are optional
 *
 */
class WiseBaseApp: public CastaliaModule, public TimerService {
private:
	simtime_t initialize_time;   //!< First time of module initialization (in secs of the sim)
	bool first_initialize;       //!< FLAG to indicate initialization

protected:

	/*--- The .ned file's parameters ---*/
	string applicationID;        //!< Custom text (may not match ApplicationName which describes the selected application)
	int priority;
	bool synchronizedStartup;
	int maxAppPacketSize;
	int packetHeaderOverhead;
	int constantDataPayload;
	bool isSink;
	double latencyNeighborDiscoverCOM;
	double latencyMax;
	int latencyBuckets;

	/*--- Custom class parameters ---*/
	int self;			    //!< the node's ID
	int n_nodes;			//!< number of nodes
	string selfAddress;
	WiseResourceManager *resMgr;
	WiseBaseSensorManager *senMgr;
	WiseCameraManager *camMgr;
	VirtualMobilityManager *mobilityModule;	
	Radio *radioModule;
	int disabled;
	double cpuClockDrift;
	double last_packet_latency;

	/*--- Communication graph ---*/
	bool _fullConnectivityCOM;
	bool _neighborDiscoverCOM;              //!< FLAG to indicate that nodes are currently being discovered
	bool _neighborDiscoverCOMCompleted;     //!< FLAG to indicate that nodes have been discovered (COMs graph)
	string _manualConnectivityCOM;
	std::vector<std::string> _neighborsCOM; //!< List of neigbourg IDs
	std::map<std::string, bool> _connectivity_map_comms; //!< List of neigbourg IDs (as pairs <ID,status>)
    unsigned int _max_neighborsCOM; //!< Maximum number of neighbors (per camera node) in the network for COMM graph

	double txDistMax;
	bool _dummy_comms;

    int _currentRun;
    double _maxSimtime;

	/*--- Energy parameters ---*/
    double maxBatteryLevel;         //in .ini file, in mJ
    double EnergyPerCapture;        //in .ini file, in mJ
    double EnergyPerProcessing;     //in .ini file, in mJ
    double baseLineConsumedEnergy; //in Joules
    double captureConsumedEnergy;        //in Joules
    double processingConsumedEnergy;     //in Joules
    double radioConsumedEnergy;//in Joules
    double nodeConsumedEnergy;//in Joules (total, indicated in ResourceManager module)

    int _bytesRX, _bytesTX; //statistics for received/sent data

    /*--- log parameters ---*/
    static ofstream elogger; //!< Used to collect node print-out for energy consumption
    string base_out_path; //!< baseline path to write logs of application layer

protected:
	WiseBaseApp() : first_initialize(true) {} ;
	virtual void initialize(); //!< Initialize resources of this (base) class
	virtual void finish(); //!< Destroy resources of this (base) class
	virtual void handleMessage(cMessage * msg); //!< Manages the received messages by redirection to specific function depending on the message type

	// Functions to be implemented in derived superclasses
	virtual void startup() = 0; //!< Specific code to initialize resources (to be implemented in superclasses of WiseBaseApp)
    virtual void finishSpecific() = 0; //!< Specific code to destroy resources (to be implemented in superclasses of WiseBaseApp)

	// Function to send packets to other modules (sensor, network, nodes)
	void requestSensorReading(int index = 0);  //!< Sends a request (packet) to SensorManager to sample data
	void toNetworkLayer(cMessage *); //!< Sends a message to the entire network without destination (should not APPLICATION_PACKET type as it needs destination)
	void toNetworkLayer(cPacket *, const char *, double delay=0); //!< Sends a packet to the network with a specific delay. This packet will be received by the CommunicationModule and delivered to all the nodes.
	void sendDirectApplicationMessage(WiseBaseAppPacket*, const char*, unsigned type=WISE_APP_DIRECT_COMMUNICATION); //!< Sends a packet to the network using direct node-to-node links (not using the CommunicationModule)

	// Function to process received packets from other modules (sensor, network, nodes). To be implemented in derived superclasses
	virtual void fromNetworkLayer(WiseBaseAppPacket *, const char *, double, double) = 0; //!< Process a received packet from the network, ie CommunicationModule (to be implemented in superclasses of WiseBaseApp)
	virtual void handleSensorReading(WiseSensorManagerMessage *) = 0; //!< Process a received packet from the SensorManager, usually after a request (to be implemented in superclasses of WiseBaseApp)
	virtual void handleDirectApplicationMessage(WiseBaseAppPacket *) = 0; //!< Process a received packet from a direct node-to-node links (to be implemented in superclasses of WiseBaseApp)
	virtual void handleMacControlMessage(cMessage *); //!< Process a MAC control message (to be implemented in superclasses of WiseBaseApp, not mandatory?)
	virtual void handleNetworkControlMessage(cMessage *){}; //!< Process a network control message (to be implemented in superclasses of WiseBaseApp, not mandatory?)
	virtual void handleRadioControlMessage(RadioControlMessage *){}; //!< Process a radio control message (to be implemented in superclasses of WiseBaseApp, not mandatory?)

	inline bool lastNode() const { return self == (n_nodes - 1); } ; //!<
    inline bool firstNode() const { return self == 0; } ; //!<

private:
	void readParameter();                                 //!< Read parameters for running the node from opmnetpp.ini
	void processAppPacket(WiseBaseAppPacket *pkt);   //!< Redirects the application packets according to their type
	void normalAppPacket(WiseBaseAppPacket *pkt);    //!< Checks and redirects Application packets with type=WISE_APP_NORMAL and calls "fromNetworkLayer" for their processing
	void discoverNeighbors(double);                    //!< Initiates the process for discovering COMMs neigbourghs using broadcast protocol
	void procDiscoverNeighborsRequest(WiseBaseAppPacket *pkt);  //!<
	void procDiscoverNeighborsReply(WiseBaseAppPacket *pkt);     //!<
	void discoverNeighborsCompleted();  //!<
	void notifyNeighborDiscoveredCOM();  //!<
};

#endif //__WISEBASEAPP_H
