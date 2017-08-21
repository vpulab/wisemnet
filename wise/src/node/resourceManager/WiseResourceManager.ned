// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2016
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for consumption models of smart-cameras:
//         SanMiguel & Cavallaro, "Energy Consumption Models for Smart-Camera Networks",
//         IEEE TCSVT 2016, http://ieeexplore.ieee.org/document/7517353/
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

package node.resourceManager;

simple WiseResourceManager {
 parameters:
	bool collectTraceInfo = default (false);
	double ramSize = default (0.0);			//in kB
	double flashSize = default (0.0);		//in kB
	double flashWriteCost = default (0.0);	//per kB
	double flashReadCost = default (0.0);	//per kB
	double imageSize = default (0.0);		//the space that the OS (e.g. Contiki or TinyOS) occupies in the flash

	string cpuPowerSpeedLevelNames = default ("");
	string cpuPowerPerLevel = default ("");	//spent energy per time unit
	string cpuSpeedPerLevel = default ("");
	int cpuInitialPowerLevel = default (-1);	// index for the cpuPowerLevels array
	double sigmaCPUClockDrift = default (0.00003);	// the standard deviation of the Drift of the CPU

	double optimizationFactor = default (5);
	
	//double initialEnergy = default (18720);	
	// energy of the node in Joules, default value corresponds to two AA batteries
	// source http://www.allaboutbatteries.com/Energy-tables.html
	// double initialEnergy = default (1e12);
	double initialEnergy = default (1e12);

	double baselineNodePower = default (6);	// periodic energy consumption of node, in mWatts
	double periodicEnergyCalculationInterval = default (1000);	// interval for energy calculation, in msec     

	//Consumption models
    string CPUmodel = default ("../../../models/CPU/CPU_ARM-Cortex-A9.dat");    
    string SENmodel = default ("../../../models/SEN/SEN_B3.dat");
    string COMmodel = default ("../../../models/COM/CC2420.txt");      
    
    //Operating parameters
    double CPUfreq = default (-1); //in MHz (-1 indicates operation at (fmax-fmin)/2
    double SENfreq = default (-1); //in MHz (-1 indicates operation at (fmax-fmin)/2
    //double SENframerate = default (5);    
    double COMbitrate = default (-1); //maximum bitrate
    
 gates:
	output toSensorDevManager;
	output toApplication;
	output toNetwork;
	output toMac;
	output toRadio;
	input powerConsumption @ directIn;
}

