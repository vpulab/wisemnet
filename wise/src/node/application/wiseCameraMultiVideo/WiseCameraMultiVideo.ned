// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************


package node.application.wiseCameraMultiVideo;

simple WiseCameraMultiVideo like node.application.wiseCameraPeriodicAlgo.WiseCameraPeriodicAlgo {
parameters:
 	string applicationID = default ("WiseCameraMultiVideo");

	// Adding THIS-application-specific parameters
	double mode = default(1); //=1 send frame, =2 send foreground mask
	bool isSink = default(false);	
	
	// --- Inherited parameters --- //

	// SimplePeriodicTracker
	double sampling_time = default (1);
	double sample_lifetime = default (-1);
	string sensing_mode = default("periodic"); 
	bool show_results = default(false);
	
	// CameraApplication
	bool synchronizedStartup = default (true);	
	bool showCamImage = default (false);
	
	double resize = default(-1);
	
	bool neighbourDiscoverCOM = default (true); // for COMMS graph			
	bool neighbourDiscoverFOV = default (false); // for VISION graph
	bool neighbourFullConnectivity = default(false);
	string userDefinedConnectivity = default("");
	
	
	double latencyNeighbourDiscoverCOM = default(10);//delay to discover COMMS neighborgs

	bool collectTraceInfo = default (true);

	int priority = default (1);
	int maxAppPacketSize = default (0);	// in bytes
	int packetHeaderOverhead = default (0);	// in bytes
	int constantDataPayload = default (0);	// in bytes
	
	double energyPerCapture = default(0.0);
	double energyPerProcessing = default(0.0);
gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
