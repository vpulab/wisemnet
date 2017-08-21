// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the MTIC-consensus tracker for multiple targets:
//         Kamal et al, "Distributed Multi-Target Tracking and Data Association in Vision Networks",
//         IEEE TPAMI 2016.
//         http://ieeexplore.ieee.org/document/7286852/
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

enum WiseICFMTICCPacketType {   
    MTIC_COLLABORATION_DATA1 = 2001;
    MTIC_COLLABORATION_END = 2002;
};

packet WiseCameraMTIC_Msg extends WiseApplicationPacket {

	unsigned int pktType; //WiseICFCPacketType

	unsigned long trackingCount;  //already defined in WiseSimplePeriodicTrackerMessage
	unsigned long iterationStep;
	unsigned int targetID; //already defined in WiseSimplePeriodicTrackerMessage
	unsigned int TypeNeighbour; //already defined in WiseSimplePeriodicTrackerMessage
		
	cv::Mat ICFv; // information vector of the target estimation by the node
	cv::Mat ICFV; // information matrix of the target estimation by the node
	cv::Mat ICFW; // information matrix of the target estimation by the node
}
