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
	#include "WiseApplicationPacket_m.h"	
}};

class WiseApplicationPacket;

packet WiseCameraMultiVideoPacket extends WiseApplicationPacket {

	unsigned long iterationStep;
	unsigned int TypeNeighbour; //already defined in WiseSimplePeriodicTrackerMessage
	
	//unsigned long trackingCount;  //already defined in WiseSimplePeriodicTrackerMessage	
	//unsigned int targetID; //already defined in WiseSimplePeriodicTrackerMessage
	//double positionX; //already defined in WiseSimplePeriodicTrackerMessage
	//double positionY; //already defined in WiseSimplePeriodicTrackerMessage
	
	//double Vx; 	// x-velocity of the target
	//double Vy;	// y-velocity of the target	
	//cv::Mat IF_u; // information vector of the target estimation by the node
	//cv::Mat frame; // information matrix of the target estimation by the node
}
