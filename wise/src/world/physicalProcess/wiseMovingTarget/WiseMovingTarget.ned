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

package world.physicalProcess.wiseMovingTarget;

simple WiseMovingTarget like 
			world.physicalProcess.WiseBasePhysicalProcess {

parameters:
 	bool collectTraceInfo = default (false);
 	bool log_enabled = default (false);
 	bool random_init = default (false);
 	bool random_noise = default (false);
	string description = default ("Moving Target");
	double x_init = default(0);
	double y_init = default(0);
	double z_init = default(0);
	double bb_width = default(10);
	double bb_height = default(10);
	double bb_depth = default(10);
	double update_time = default(1.0);
        string move_type = default("");
        double noise_min = default(0);
        double noise_max = default(0);        
        double move_min_x = default(0);
        double move_max_x = default(0);
        double move_min_y = default(0);
        double move_max_y = default(0);
	double move_later = default(0);
	double noise = default(0.0);

	bool unique_color=default(false);
	
gates:
 	output toNode[];
	input fromNode[];

}
