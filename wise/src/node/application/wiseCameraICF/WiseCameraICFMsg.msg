// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the ICF tracker for single targets described in:
//      Kamal et al, "Information Weighted Consensus Filters and Their Application
//      in Distributed Camera Networks", IEEE TAC 2013
//      http://ieeexplore.ieee.org/document/6576197/
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

enum WiseICFCPacketType {   
    ICF_COLLABORATION_DATA1 = 2001;
    ICF_COLLABORATION_END = 2002;
};

packet WiseCameraICFMsg extends WiseApplicationPacket {

	unsigned int pktType; //WiseICFCPacketType

	unsigned long trackingCount;  //already defined in WiseSimplePeriodicTrackerMessage
	unsigned long iterationStep;
	unsigned int targetID; //already defined in WiseSimplePeriodicTrackerMessage
	unsigned int TypeNeighbour; //already defined in WiseSimplePeriodicTrackerMessage
		
	cv::Mat ICFv; // information vector of the target estimation by the node
	cv::Mat ICFV; // information matrix of the target estimation by the node
	//cv::Mat W; // information matrix of the target estimation by the node
}
