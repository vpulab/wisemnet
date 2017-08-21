// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011 (nastasichr@gmail.com)
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//	DESCRIPTION:
//  This file describes the NED file for the network visualizer (WiseBaseTerrain)
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
package world.terrain;

moduleinterface WiseBaseTerrain {

parameters:
	bool collectTraceInfo;	//FLAG to active the collection of debug information
	string gui;				//type of GUI used for visualizing the network
    bool gui_wait_start;	//FLAG to wait for a key-pressed event before starting the application
    bool gui_show;			//FLAG to show the GUI
    double scale_factor;	//FLAG to scale the size of the GUI so it can fit in small displays
    bool draw_trajectory;	//FLAG to disable repainting for each target and being able to visualize its trajectory
    string GPmap_path;		//Location/path for the image describing the ground-plane map.
    						//The GUI will paint cameras & targets on this ground-plane map 
    						//It is only loaded if "SN.use_calibration" is enabled.
    
gates:
	//output toSensorDevManager;
	//output toApplication;
	//output toNetwork;
	//output toMac;
	//output toRadio;
	input update @ directIn; // WiseBaseTerrain Update
}
