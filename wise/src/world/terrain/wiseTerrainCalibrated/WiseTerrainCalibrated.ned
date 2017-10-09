// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Juan C. SanMiguel
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  Developed at the:
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//	DESCRIPTION:
//  This file describes the NED file for the network visualizer (WiseCalibratedTerrain) with calibration data
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

package world.terrain.wiseTerrainCalibrated;

simple WiseTerrainCalibrated like world.terrain.WiseBaseTerrain {

parameters:
	bool collectTraceInfo = default (false);
	string gui = default ("opencv");
	bool gui_wait_start = default(false);
	bool gui_show = default(false);	
	string GPmap_path = default("path-to-groundplane_image");
	bool draw_trajectory = default(false);
	double scale_world = default(1); 	// to scale the size of the GUI-world so it can fit in small displays
gates:
	input update @ directIn; // WiseBaseTerrain Update
}
