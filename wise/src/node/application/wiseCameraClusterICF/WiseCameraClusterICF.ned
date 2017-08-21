// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2013
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@qmul.ac.uk
//  - juancarlos.sanmiguel@gmail.com
//  - a.cavallaro@qmul.ac.uk                                        
// *****************************************************************************


package node.application.wiseCameraClusterICF;

simple WiseCameraClusterICF like node.application.wiseCameraSimplePeriodicTracker.WiseCameraSimplePeriodicTracker {
parameters:
 	string applicationID = default ("WiseCameraClusterICF");

	// Adding THIS-application-specific parameters	
	double procNoiseCov = default(0.1);
	double measNoiseCov = default(1e-1);	
	int iter_max = default(10);
	double alpha = default(0.25);
	
	// --- Inherited parameters --- //

	// SimplePeriodicTracker
	double sampling_time = default (1);
	double sample_lifetime = default (-1);

	bool collectNetworkStats = default(false);
	bool collectPowerStats = default(false);
	bool collectAccuracyStats = default(false);
	
	// CameraApplication
	bool synchronizedStartup = default (true);	
	bool showCamImage = default (false);
	
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
