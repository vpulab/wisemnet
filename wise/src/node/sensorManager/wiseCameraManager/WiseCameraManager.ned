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

package node.sensorManager.wiseCameraManager;

simple WiseCameraManager like node.sensorManager.WiseBaseSensorManager {

parameters:
	bool collectTraceInfo = default (false);
	int numSensingDevices = default (1);
	string maxSampleRates = default ("");
	string type_src = default ("Target"); //"Video"
	
	string calib_filename = default("none");
	string calib_type = default("none");
	string calib_world2map_filename = default("none");
	
	string fov_type = default ("bounding_box");
	double fov_bb_width = default (16.0);
	double fov_bb_height = default (12.0);
		
	double fov_di_los = default (45.0);
	double fov_di_dov = default (10.0);
	double fov_di_aov = default (15.0);
	
	
	
gates:
	output toApplicationModule;
	output toNodeContainerModule[];
	input fromApplicationModule;
	input fromNodeContainerModule[];
	input fromResourceManager;
}

