// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the people-detect-transmit demo:
//      J. SanMiguel & A. Cavallaro,
//      "Networked Computer Vision: the importance of a holistic simulator",
//      IEEE COMPUTER 2017, http://ieeexplore.ieee.org/document/XXXX/
//      Preprint available at http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

cplusplus {{
	#include "WiseApplicationPacket_m.h"
	#include <opencv.hpp>	
	#include <vector>
	typedef std::vector<std::vector<cv::Mat> > descVector;
}};

class WiseApplicationPacket;
class noncobject cv::Mat;
class noncobject std::vector;
class noncobject descVector;

//class noncobject std::vector<cv::Mat>; 
//class noncobject std::vector<std::vector<cv::Mat> >;

packet WiseCameraPeopleDetPacket extends WiseApplicationPacket {

	unsigned long iterationStep;
	unsigned int TypeNeighbour; //already defined in WiseSimplePeriodicTrackerMessage
	
	unsigned int numTargets;
	unsigned int histSize;
	descVector descBGR; //descriptor of detected targets
	cv::Mat frame; // currentFrame	
	
	//std::vector<cv::Mat> descriptors;
	//std::vector<std::vector<cv::Mat> > descriptors;
	
	//unsigned long trackingCount;  //already defined in WiseSimplePeriodicTrackerMessage	
	//unsigned int targetID; //already defined in WiseSimplePeriodicTrackerMessage
	//double positionX; //already defined in WiseSimplePeriodicTrackerMessage
	//double positionY; //already defined in WiseSimplePeriodicTrackerMessage
	
	//double Vx; 	// x-velocity of the target
	//double Vy;	// y-velocity of the target	
	//cv::Mat IF_u; // information vector of the target estimation by the node
	//cv::Mat frame; // information matrix of the target estimation by the node
	
}
