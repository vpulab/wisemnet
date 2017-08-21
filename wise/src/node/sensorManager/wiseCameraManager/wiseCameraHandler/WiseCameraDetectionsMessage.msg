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

cplusplus {{
	#include "WiseCameraMessage_m.h"
}};

class WiseCameraMessage;

struct WiseTargetDetection {
	unsigned int target_id;
	bool valid;
	// Image coordinate
	unsigned int bb_x_tl;
	unsigned int bb_y_tl;
	unsigned int bb_x_br;
	unsigned int bb_y_br;
	// World coordinate (might be cropped by FOV)
	double ext_bb_x_tl;
	double ext_bb_y_tl;
	double ext_bb_x_br;
	double ext_bb_y_br;
	// World TRUE coordinate
	double true_bb_x_tl;
	double true_bb_y_tl;
	double true_bb_x_br;
	double true_bb_y_br;
};

message WiseCameraDetectionsMessage extends WiseCameraMessage {
	WiseTargetDetection detections[];
}
