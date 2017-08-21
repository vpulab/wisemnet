// *****************************************************************************
//  Copyright (C): Christian Nastasi, 2011                                    
//  Author(s): Christian Nastasi                                              
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa)           
//  - School of Elec Eng and Computer Science, Queen Mary University (London) 
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:          
//  - c.nastasi@sssup.it                                                      
//  - nastasichr@gmail.com                                                    
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

package node.application.wiseAppTest;

simple WiseAppTest like node.application.WiseBaseApplication {

parameters:
	bool synchronizedStartup = default (true);
	
	bool neighbourDiscoverCOM = default (true);
	bool neighbourDiscoverFOV = default (true);
	bool neighbourFullConnectivity = default(false);
	string userDefinedConnectivity = default("");
	
	//delay to discover COMMS neighborgs	
	double latencyNeighbourDiscoverCOM = default(10);
	
 	string applicationID = default ("WiseAppTest");
	bool collectTraceInfo = default (true);
	int priority = default (1);
	int maxAppPacketSize = default (30);	// in bytes
	int packetHeaderOverhead = default (8);	// in bytes
	int constantDataPayload = default (2);	// in bytes

gates:
	output toApplicationDirect[];
	input fromApplicationDirect[];
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
