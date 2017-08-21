// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@qmul.ac.uk
//  - a.cavallaro@qmul.ac.uk                                        
// *****************************************************************************

cplusplus {{
	#include "WiseApplicationPacket_m.h"
	#include "WiseDefinitionsTracking.h"
	#include <opencv.hpp>
}};

class WiseApplicationPacket;
class noncobject cv::Mat;

packet WiseCameraClusterICFMsg extends WiseApplicationPacket {

	unsigned long trackingCount;  //already defined in WiseSimplePeriodicTrackerMessage
	unsigned long iterationStep;
	unsigned int targetID; //already defined in WiseSimplePeriodicTrackerMessage
	unsigned int TypeNeighbour; //already defined in WiseSimplePeriodicTrackerMessage
		
	cv::Mat ICFv; // information vector of the target estimation by the node
	cv::Mat ICFV; // information matrix of the target estimation by the node
	//cv::Mat W; // information matrix of the target estimation by the node
}
