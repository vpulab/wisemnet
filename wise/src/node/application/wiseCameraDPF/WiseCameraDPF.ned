// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
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
//  This file is part of the implementation for the DPF tracker for single targets described in:
//      - C. Nastasi, A. Cavallaro, "WiSE-MNet: an experimental environment for Wireless Multimedia Sensor Networks"
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//      - C. Nastasi, A. Cavallaro, "Distributed target tracking under realistic network conditions",
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
package node.application.wiseCameraDPF;

simple WiseCameraDPF like node.application.wiseCameraSimplePeriodicTracker.WiseCameraSimplePeriodicTracker {
parameters:
 	string applicationID = default ("WiseCameraDPF");

	int n_particles = default(100);
	double particle_spreading_factor = default(5);
	int n_gmm_components = default(-1);

	double sampling_time = default (1);
	double sample_lifetime = default (-1);
	
	bool collectNetworkStats = default(false);
	bool collectPowerStats = default(false);
	bool collectAccuracyStats = default(false);

	bool synchronizedStartup = default (true);
		
	bool showCamImage = default (false);
	
	bool neighbourDiscoverCOM = default (true); // for COMMS graph			
	bool neighbourDiscoverFOV = default (false); // for VISION graph
	bool neighbourFullConnectivity = default(false);
	string userDefinedConnectivity = default("");
	
	double latencyNeighbourDiscoverCOM = default(10);//delay to discover COMMS neighborgs

	bool trace_particles = default (false); // if collectTraceInfo == true
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
