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

package world.physicalProcess.wiseVideoFile;

simple WiseVideoFile like world.physicalProcess.WiseBasePhysicalProcess {
parameters:
 	bool collectTraceInfo = default (false);
 	bool log_enabled = default (false);
	string description = default ("Video File");

	bool allow_multiple_camera = default(true);
	string file_name = default ("");
	double frame_rate = default(25);
	double resize = default(-1);
	double move_later = default(0);
	
	double iniFrame = default(-1);
	double endFrame = default(-1);	
	double waitFrames = default(0);	
	
	bool show_video =  default(false);

gates:
 	output toNode[];
	input fromNode[];
}
