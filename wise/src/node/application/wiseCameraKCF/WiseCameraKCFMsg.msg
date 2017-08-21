// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the Kalman-consensus tracker for single targets:
//         R. Olfati-Saber, "Kalman-consensus filter: Optimality stability and performance",
//         Proc. IEEE Conf. Decision and Control, pp. 7036-7042, 2009-Dec.
//         http://ieeexplore.ieee.org/document/4118472
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

cplusplus {{
	#include "WiseApplicationPacket_m.h"
	#include "WiseDefinitionsTracking.h"
	#include <opencv.hpp>
}};

class WiseApplicationPacket;
class noncobject cv::Mat;

enum WiseKCFCPacketType {   
    KCF_COLLABORATION_DATA1 = 1000;
    KCF_COLLABORATION_DATA2 = 1001;
    KCF_COLLABORATION_END = 1002;
};

packet WiseCameraKCFMsg extends WiseApplicationPacket {

	unsigned int pktType; //WiseKCFCPacketType

	unsigned long trackingCount;  //already defined in WiseSimplePeriodicTrackerMessage
	unsigned long iterationStep;
	unsigned int targetID; //already defined in WiseSimplePeriodicTrackerMessage
	double positionX; //already defined in WiseSimplePeriodicTrackerMessage
	double positionY; //already defined in WiseSimplePeriodicTrackerMessage
	unsigned int TypeNeighbour; //already defined in WiseSimplePeriodicTrackerMessage

	double Vx; 	// x-velocity of the target
	double Vy;	// y-velocity of the target	
	cv::Mat IF_u; // information vector of the target estimation by the node
	cv::Mat IF_U; // information matrix of the target estimation by the node
}
