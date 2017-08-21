// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the MTIC-consensus tracker for multiple targets:
//         Kamal et al, "Distributed Multi-Target Tracking and Data Association in Vision Networks",
//         IEEE TPAMI 2016.
//         http://ieeexplore.ieee.org/document/7286852/
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************
package node.application.wiseCameraMTIC;

simple WiseCameraMTIC like node.application.wiseCameraSimplePeriodicTracker.WiseCameraSimplePeriodicTracker {
parameters:
 	string applicationID = default ("WiseCameraMTIC");

	// Adding THIS-application-specific parameters	
	double procNoiseCov = default(0.1);
	double measNoiseCov = default(1e-1);	
	int iter_max = default(10);
	double alpha = default(0.25);
	
	double lambda = default(0.0); //clutter per camera sensor
	 
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
