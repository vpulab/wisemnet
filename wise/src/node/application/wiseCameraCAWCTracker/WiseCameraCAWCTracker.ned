// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file is part of the implementation for the cost-aware coalition-based
//  tracking (CAWC) for single targets described in the paper:
//      Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
//      Tracker tracking", IEEE Sensors Journal, May 2015
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

package node.application.wiseCameraCAWCTracker;

simple WiseCameraCAWCTracker like node.application.wiseCameraPeriodicAlgo.WiseCameraPeriodicAlgo {
parameters:
 	string applicationID = default ("WiseCameraCAWCTracker");
	string testName = default("none");
	int camID = default(-1);
	
	bool debug = default(false);
	
	// Adding THIS-application-specific parameters
	//...
	
	// --- Inherited parameters --- //
	string sensing_mode = default("nowait"); //"on_demand", "periodic"
	double sampling_time = default (1);
	double sample_lifetime = default (-1);
	bool show_results = default(false);

	// CameraApplication
	bool synchronizedStartup = default (true);	
	bool showCamImage = default (false);
	
	double resize = default(-1);	
	
	bool neighbourDiscoverCOM = default (true); // for COMMS graph			
	bool neighbourDiscoverFOV = default (false); // for VISION graph
	bool neighbourFullConnectivity = default(false);
	string userDefinedConnectivity = default("");
	
	
	double latencyNeighbourDiscoverCOM = default(1);//delay to discover COMMS neighborgs

	bool collectTraceInfo = default (true);

	int priority = default (1);
	int maxAppPacketSize = default (0);	// in bytes
	int packetHeaderOverhead = default (0);	// in bytes
	int constantDataPayload = default (0);	// in bytes
		
	string initFile_ip_gt = default("none");
	
	int tracker_selected = default(0); //STRUCK tracker by default
	
	double score_m = default(-1);
	double score_v = default(-1);
	double score_th = default(0.5);
	
gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
