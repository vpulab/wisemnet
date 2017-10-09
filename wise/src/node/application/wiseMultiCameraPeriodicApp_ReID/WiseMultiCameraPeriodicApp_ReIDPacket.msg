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

// Description of packet format for WiseMultiCameraPeriodicApp_ReID class
cplusplus {{
	#include "WiseCameraPeriodicAppPacket_m.h"
	#include <opencv.hpp>	
	#include <vector>
	//typedef std::vector<std::vector<cv::Mat> > descVector;
	//typedef std::vector<char> JPEGdata; //to be fixed
}};

class WiseCameraPeriodicAppPacket;
class noncobject cv::Mat;
class noncobject std::vector;
//class noncobject descVector;
//class noncobject JPEGdata; //to be fixed
//class noncobject std::string;

//class noncobject std::vector<cv::Mat>; 
//class noncobject std::vector<std::vector<cv::Mat> >;

packet WiseMultiCameraPeriodicApp_ReIDPacket extends WiseCameraPeriodicAppPacket {

	unsigned int numDetections;
	unsigned int histSize;
	//descVector descBGR; //descriptor of detected targets
	cv::Mat frame; // currentFrame		
	cv::Mat descriptorData;		
	//JPEGdata buff; 
}
