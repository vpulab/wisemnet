// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file is part of the implementation for the cost-aware coalition-based
//  tracking (CAWC) for single targets described in the paper:
//      Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
//      Tracker tracking", IEEE Sensors Journal, May 2015
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

enum WiseCAWCPacketType {
    CAWC_UTILITY = 100;
    CAWC_NEWMANAGER = 101;
    CAWC_NEWMANAGER_ACK = 102;
    CAWC_NEWMANAGER_ACK_SEND = 103;
    CAWC_NEWMANAGER_SEND = 104;
    CAWC_NEGOTIATION_JOIN = 105;
    CAWC_NEGOTIATION_REPLY = 106;
    CAWC_COLLABORATION_REQUEST = 107;
    CAWC_COLLABORATION_DATA = 108;
    CAWC_COLLABORATION_END = 109;
};


//class noncobject std::vector<cv::Mat>; 
//class noncobject std::vector<std::vector<cv::Mat> >;

//NOTE: each 'pktType' should be defined as a different packet. 
// For simplification, all packets are defined in the same structure 
// and depending on 'pktType', we use selected parameters of the packet
packet WiseCameraCAWCTrackerPkt extends WiseApplicationPacket {

	unsigned int pktType; //WiseCAWCPacketType
	
	int nodeID;
	int camID;
	int frameID;
	
	//CAWC_UTILITY
	double utility;
	double priority;
	double battery_level;
	double load_level;
	
	//CAWC_ANNOUNCE_MANAGER
	int newManager;	
	cv::Mat x;
	cv::Mat P;
	bool initialized;
	
	//CAWC_ANNOUNCE_MANAGER_ACK
	
	//CAWC_NEGOTIATION_MANAGER
	
	//CAWC_NEGOTIATION_CAMERA_REPLY
	bool reply;
	
	//CAWC_COLLABORATION_REQUEST
	
	//CAWC_COLLABORATION_SEND_DATA
	cv::Mat z; //measurement	
	cv::Mat H; //measurement matrix
	cv::Mat Ht; //measurement matrix (transpose)
	cv::Mat Rinv; //covariance measurement
	
	//CAWC_COLLABORATION_END
	
}
