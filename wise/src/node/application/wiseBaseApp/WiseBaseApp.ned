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

// NED description for the interface/template wiseBaseApp of the Application layer
package node.application.wiseBaseApp;

moduleinterface WiseBaseApp extends node.application.iApplication {

parameters:
	bool synchronizedStartup;			//FLAG to enable synchronized start of all camera nodes
	bool neighborDiscoverCOM;			//FLAG to enable the discovery of nodes via broadcasting "discovery requests" packets
	bool fullConnectivityCOM;   		//FLAG to enable if all cameras are connected
	string manualConnectivityCOM;		//String to manually define the connectivity as 1 or 0 (e.g. 1 0 1, connected to camera 0 and 2)
	double latencyNeighborDiscoverCOM;	//Latency base value to start the broadcast of packets
	
	string base_out_path;				//Base path to write logs 
gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
}
