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
	#include <opencv.hpp>
}};

class WiseCameraMessage;
class noncobject cv::Mat;

message WiseCameraVideoMessage extends WiseCameraMessage {
	bool valid;	
	string fileName;
	double frameRateSRC;
	double resize;
	int curFrame; // index of frame in the videofile
	cv::Mat frame; // current frame returned		
}	
