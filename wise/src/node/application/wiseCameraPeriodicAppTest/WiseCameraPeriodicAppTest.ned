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

//NED description for the wiseCameraPeriodicAppTest class
package node.application.wiseCameraPeriodicAppTest;

simple WiseCameraPeriodicAppTest like node.application.wiseCameraPeriodicApp.WiseCameraPeriodicApp {
parameters:
	
	// --- Inherited parameters --- //
	
	//parameters required by WiseCameraPeriodicApp interface	
	bool logResourceData=default(false); //!< FLAG to enable/disable the log for employed resources
	
	string sensing_mode = default("periodic"); //!< Defines the mode for sensing frames
	double sampling_time = default (1);//!< frequency to get new samples (in secs) from physical process (through SensorDeviceManager)
	double sample_lifetime = default (-1);//!< Lifetime in secs of the captured samples
	
	string filenameGT=default("");//!< Filename with the ground-truth data
	string formatGT=default("");//!< Format of the ground-truth data	
    bool show_gtruth=default(false);  //!< FLAG to enable/disable the display of ground-truth data
    
    bool pause_execution=default(false);//!< FLAG to pause the execution for each iteration
    bool pause_place_GUI=default(false); //!< FLAG to pause the execution only at the beginning
    double displayWinScale=default(1.0);//!< Scale factor of all display windows
    int pause_executionID=default(-1);//!< ID of the camera/node required to be paused during execution (used jointly with "_pause_execution"
    
	//parameters required by WiseCameraApp interface	
	bool neighborDiscoverFOVoverlap = default (false);  // FLAG to generate the VISION graph with overlapped FOVs (co-visibility)
	string camID = default("");  						// Camera Identifier
	
	//parameters required by WiseBaseApplication interface
	bool synchronizedStartup = default(true);		//FLAG to enable synchronized start of all camera nodes
	bool neighborDiscoverCOM = default(false);		//FLAG to enable the discovery of nodes via broadcasting "discovery requests" packets
	bool fullConnectivityCOM = default(false);		//FLAG to enable if all cameras are connected
	string manualConnectivityCOM = default("");		//String to manually define the connectivity as 1 or 0 (e.g. 1 0 1, connected to camera 0 and 2)
	double latencyNeighborDiscoverCOM = default(5); //Latency value to start the broadcast of packets
	string base_out_path = default("res/");			//Base path to write logs
	
	//parameters specific for iApplication
 	string applicationID = default("demo");	//Type of application running within each camera node
 	bool collectTraceInfo = default(true);			//FLAG to enable logging at application level
	int priority = default(1);
	int maxAppPacketSize = default(30);				// in bytes
	int packetHeaderOverhead = default(8);			// in bytes
	int constantDataPayload = default(2);			// in bytes
	
gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
