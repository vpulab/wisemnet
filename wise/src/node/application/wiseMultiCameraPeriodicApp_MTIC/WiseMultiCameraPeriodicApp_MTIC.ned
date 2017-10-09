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

 package node.application.wiseMultiCameraPeriodicApp_MTIC;

simple WiseMultiCameraPeriodicApp_MTIC like node.application.wiseCameraPeriodicApp.WiseCameraPeriodicApp {
parameters:
    
	// Adding THIS-application-specific parameters	
	double procNoiseCov = default(0.1);
	double measNoiseCov = default(1e-1);	
	int iter_max = default(10);
	double alpha = default(0.25);	
	double lambda = default(0.0); //clutter per camera sensor

	string share = default ("FOV");
	
	bool displayStats = default(false);	
	bool collectNetworkStats = default(false);
	bool collectPowerStats = default(false);
	bool collectAccuracyStats = default(false);
	
	// --- Inherited parameters --- //
	
    //parameters required by WiseCameraAppPeriodic interface	
    bool logResourceData=default(false);
    
	double sampling_time = default (1);
	double sample_lifetime = default (-1);
	string sensing_mode = default("none"); //"periodic" or "on-demand"	
	
	//ground-truth settings
	string filenameGT= default("");
	bool show_gtruth= false;
	string formatGT= default("");
	
	bool pause_execution=default(false);
    bool pause_place_GUI=default(false);
    int pause_executionID=default(-1);
    double displayWinScale=default(1.0);
    
    //parameters required by WiseCameraApp interface	
	bool neighborDiscoverFOVoverlap = default (false);  // for VISION graph
	string camID = default("");

	//parameters required by WiseBaseApp interface
	bool synchronizedStartup = default(true);
	bool neighborDiscoverCOM = default(false);	
	bool fullConnectivityCOM = default(false);
	string manualConnectivityCOM = default("");
	double latencyNeighborDiscoverCOM = default(5); //delay to discover COMMS neighborgs
	string base_out_path = default("res/");			//Base path to write logs
		
	//parameters specific for iApplication
 	string applicationID = default("WiseMultiCameraPeriodicApp_MTIC");	
 	bool collectTraceInfo = default(true);
	int priority = default(1);
	int maxAppPacketSize = default(30);	// in bytes
	int packetHeaderOverhead = default(8);	// in bytes
	int constantDataPayload = default(2);	// in bytes
	 
gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
