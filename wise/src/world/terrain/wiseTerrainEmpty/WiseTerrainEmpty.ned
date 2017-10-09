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
//  This file describes the NED file for the network visualizer (WiseEmptyTerrain) without calibration data
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

package world.terrain.wiseTerrainEmpty;

simple WiseTerrainEmpty like world.terrain.WiseBaseTerrain {

parameters:
	bool collectTraceInfo = default (false);
	string gui = default ("opencv");
	bool gui_wait_start = default(false);
	bool gui_show = default(false);
	string GPmap_path = default("");
	bool draw_trajectory = default(false);
	double scale_world = default(1); 	// to scale the size of the GUI-world so it can fit in small displays
	
gates:
	input update @ directIn; // WiseBaseTerrain Update
}
