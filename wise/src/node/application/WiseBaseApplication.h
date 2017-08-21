// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011 (nastasichr@gmail.com)
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
//  This file describes a template to implement applications in WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WISEBASEAPPLICATION_H__
#define __WISEBASEAPPLICATION_H__

#include <sstream>
#include <vector>
#include <string>
#include <omnetpp.h>
#include "WiseApplicationPacket_m.h"
#include "WiseSensorManagerMessage_m.h"
//#include "ResourceManager.h"
#include "Radio.h"
#include "WiseResourceManager.h"
#include "WiseCameraManager.h"
#include "VirtualMobilityManager.h"
#include "CastaliaModule.h"
#include "TimerService.h"

#define SELF_NETWORK_ADDRESS selfAddress.c_str()

using namespace std;

/*! \class WiseBaseApplication
 *  \brief This class implements the template for developing applications in WiSE framework
 *
 *  The class contains basic functions to initialize resources, send/receive messages from/to network (or direct node-to-node
 *  communication) and handling of control messages. Prior to process packets, WiseBaseApplication class discovers the communication
 *  graph for each node (ie, neigbours nodes using network communication).
 *
 *  Steps for developing a new application, \n
 *  1) Define a new application (new class extending WiseBaseApplication)\n
 *  2) Create the structures to be used within your new application\n
 *  3) Implement the functions startup() and finishSpecific() for the new application requirements \n
 *  4) Implement the function handleSensorReading() to handle the data provided by the SensorManager \n
 *  5) Implement the functions fromNetworkLayer() and handleDirectApplicationMessage() to handle received
 *  packets from, respectively the network and direct node-to-node communication \n
 *  6) Functions handleNetworkControlMessage(), handleMacControlMessage() and handleRadioControlMessage() are optional
 *
 */
class WiseBaseApplication: public CastaliaModule, public TimerService {
private:
	simtime_t initialize_time;   //!< First time of module initialization (in secs of the sim)
	bool first_initialize;       //!< FLAG to indicate initialization

protected:
	/*--- The .ned file's parameters ---*/
	string applicationID;        //!< Type of application currently running in the node. Must be defined as a superclass of WiseBaseApplication
	int priority;
	bool synchronizedStartup;
	int maxAppPacketSize;
	int packetHeaderOverhead;
	int constantDataPayload;
	bool isSink;
	double latencyNeighbourDiscoverCOM;
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
	bool neighbourFullConnectivity;
	bool neighbourDiscoverCOM;              //!< FLAG to indicate that nodes are currently being discovered
	bool neighbourDiscoverCOMCompleted;     //!< FLAG to indicate that nodes have been discovered (COMs graph)
	string userDefinedConnectivity;
	std::vector<std::string> neighborsCOM; //!< List of neigbourg IDs
	std::map<std::string, bool> connectivity_map_comms; //!< List of neigbourg IDs (as pairs <ID,status>)

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

    static ofstream elogger; //!< Used to collect node print-out for energy consumption

protected:
	WiseBaseApplication() : first_initialize(true) {} ;
	virtual void initialize(); //!< Init resources of this (base) class
	virtual void finish(); //!< Destroy resources of this (base) class
	virtual void handleMessage(cMessage * msg); //!< Manages the received messages by redirection to specific function depending on the message type

	// Functions to be implemented in derived superclasses
	virtual void startup() = 0; //!< Specific code to initialize resources (to be implemented in superclasses of WiseBaseApplication)
    virtual void finishSpecific() = 0; //!< Specific code to destroy resources (to be implemented in superclasses of WiseBaseApplication)

	// Function to send packets to other modules (sensor, network, nodes)
	void requestSensorReading(int index = 0);  //!< Sends a request (packet) to SensorManager to sample data
	void toNetworkLayer(cMessage *); //!< Sends a message to the entire network without destination (should not APPLICATION_PACKET type as it needs destination)
	void toNetworkLayer(cPacket *, const char *, double delay=0); //!< Sends a packet to the network with a specific delay. This packet will be received by the CommunicationModule and delivered to all the nodes.
	void sendDirectApplicationMessage(WiseApplicationPacket*, const char*, unsigned type=WISE_APP_DIRECT_COMMUNICATION); //!< Sends a packet to the network using direct node-to-node links (not using the CommunicationModule)

	// Function to process received packets from other modules (sensor, network, nodes). To be implemented in derived superclasses
	virtual void fromNetworkLayer(WiseApplicationPacket *, const char *, double, double) = 0; //!< Process a received packet from the network, ie CommunicationModule (to be implemented in superclasses of WiseBaseApplication)
	virtual void handleSensorReading(WiseSensorManagerMessage *) = 0; //!< Process a received packet from the SensorManager, usually after a request (to be implemented in superclasses of WiseBaseApplication)
	virtual void handleDirectApplicationMessage(WiseApplicationPacket *) = 0; //!< Process a received packet from a direct node-to-node links (to be implemented in superclasses of WiseBaseApplication)
	virtual void handleNetworkControlMessage(cMessage *); //!< Process a network control message (to be implemented in superclasses of WiseBaseApplication, not mandatory?)
	virtual void handleMacControlMessage(cMessage *); //!< Process a MAC control message (to be implemented in superclasses of WiseBaseApplication, not mandatory?)
	virtual void handleRadioControlMessage(RadioControlMessage *); //!< Process a radio control message (to be implemented in superclasses of WiseBaseApplication, not mandatory?)

	inline bool lastNode() const { return self == (n_nodes - 1); } ; //!<
    inline bool firstNode() const { return self == 0; } ; //!<

private:
	void readParameter();                                 //!< Read parameters for running the node from opmnetpp.ini
	void processAppPacket(WiseApplicationPacket *pkt);   //!< Redirects the application packets according to their type
	void normalAppPacket(WiseApplicationPacket *pkt);    //!< Checks and redirects Application packets with type=WISE_APP_NORMAL and calls "fromNetworkLayer" for their processing
	void discoverNeighbours(double);                    //!< Initiates the process for discovering COMMs neigbourghs using broadcast protocol
	void procDiscoverNeighboursRequest(WiseApplicationPacket *pkt);  //!<
	void procDiscoverNeighboursReply(WiseApplicationPacket *pkt);     //!<
	void discoverNeighboursCompleted();  //!<
	void notifyNeighbourDiscoveredCOM();  //!<
};

#endif //__WISEBASEAPPLICATION_H__
