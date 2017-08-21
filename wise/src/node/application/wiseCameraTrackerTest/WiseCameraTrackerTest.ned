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
//  This file describes a template to test cameratracker applications
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

package node.application.wiseCameraTrackerTest;

simple WiseCameraTrackerTest like node.application.wiseCameraSimplePeriodicTracker.WiseCameraSimplePeriodicTracker {
parameters:
 	string applicationID = default ("WiseCameraTrackerTest");

	// Adding THIS-application-specific parameters
	int some_parameter = default(10);

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
