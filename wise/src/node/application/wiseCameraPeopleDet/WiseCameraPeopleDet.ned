// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the people-detect-transmit demo:
//      J. SanMiguel & A. Cavallaro,
//      "Networked Computer Vision: the importance of a holistic simulator",
//      IEEE COMPUTER 2017, http://ieeexplore.ieee.org/document/XXXX/
//      Preprint available at http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

package node.application.wiseCameraPeopleDet;

simple WiseCameraPeopleDet like node.application.wiseCameraPeriodicAlgo.WiseCameraPeriodicAlgo {
parameters:
 	string applicationID = default ("WiseCameraPeopleDet");
	
	string testName = default("none");
	// Adding THIS-application-specific parameters
	double mode = default(3);//send descriptors - compression enabled
	bool isSink = default(false);	
	
	// --- Inherited parameters --- //
	string sensing_mode = default("periodic"); //"on_demand"
	double sampling_time = default (1);
	double sample_lifetime = default (-1);
	//bool show_results = default(false);

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
	
	bool extractGabor = default(false);
	
	bool show_results = default(false);
	
gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
