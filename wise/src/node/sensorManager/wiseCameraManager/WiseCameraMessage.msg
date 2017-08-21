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
	#include "WiseSensorManagerMessage_m.h"
}};

class WiseSensorManagerMessage;

message WiseCameraMessage extends WiseSensorManagerMessage {
	string cameraSampleType;
}

//enum WiseCameraCommandType
//{
//	WISE_CAM_CMD_OVERLAPPING_FOV = 0;
//};
//
//message WiseCameraCommand extends WiseSensorManagerMessage {
//	unsigned int type;
//	string overlappingFovCams[];
//}
