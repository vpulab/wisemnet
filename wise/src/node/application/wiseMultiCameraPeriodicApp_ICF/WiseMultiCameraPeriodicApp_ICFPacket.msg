// *****************************************************************************************
// Copyright (C) 2017 Juan C. SanMiguel and Andrea Cavallaro
// You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
// license (see the attached LICENSE_WISE file).
//
// This file is part of the WiseMnet simulator
//
// Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// Please cite the following reference when publishing results obtained with WiseMnet:
//   J. SanMiguel & A. Cavallaro,
//   "Networked Computer Vision: the importance of a holistic simulator",
//   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
// *****************************************************************************************

//NED file to describe the packet format for the wiseMultiCameraPeriodicApp_ICF class
cplusplus {{
	#include "WiseCameraPeriodicAppPacket_m.h"
	#include <opencv.hpp>
}};

class WiseCameraPeriodicAppPacket;
class noncobject cv::Mat;

enum WiseICFCPacketType {   
    ICF_COLLABORATION_DATA1 = 2001;
    ICF_COLLABORATION_END   = 2002;
};

packet WiseMultiCameraPeriodicApp_ICFPacket extends WiseCameraPeriodicAppPacket {

	unsigned int pktTypeICF; //WiseICFCPacketType

	unsigned long trackingCount;
	unsigned long iterationStep;
	unsigned int targetID;	
		
	cv::Mat ICFv; // information vector of the target estimation by the node
	cv::Mat ICFV; // information matrix of the target estimation by the node
	//cv::Mat W; // information matrix of the target estimation by the node
}
