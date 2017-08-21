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
        #include "WisePhysicalProcessMessage_m.h"
}};

class WisePhysicalProcessMessage;

struct WiseTargetBoundingBox {
	double x_tl;
	double y_tl;
	double z_tl;
	double x_br;
	double y_br;
	double z_br;
};

message WiseMovingTargetMessage extends WisePhysicalProcessMessage {
	WiseTargetBoundingBox boundingBox;
	unsigned int targetID;
	bool visible = true;
}
