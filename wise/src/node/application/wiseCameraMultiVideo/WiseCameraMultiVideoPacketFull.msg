// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

cplusplus {{
	#include "WiseCameraMultiVideoPacket_m.h"	
	#include <opencv.hpp>
}};

class WiseCameraMultiVideoPacket;
class noncobject cv::Mat;

packet WiseCameraMultiVideoPacketFull extends WiseCameraMultiVideoPacket {

	cv::Mat frame; // information matrix of the target estimation by the node
}