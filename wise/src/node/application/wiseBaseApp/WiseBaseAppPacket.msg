// *****************************************************************************************
// Copyright (C) 2011 Christian Nastasi, 2017 Juan C. SanMiguel and Andrea Cavallaro
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

// Description for the packet format exchanged by the wiseBaseApp interface
cplusplus {{
        #include "ApplicationPacket_m.h"
        #include "CastaliaMessages.h"
}};

class ApplicationGenericDataPacket;

//!< \enum WiseApplicationPacketType
//!<  \brief Type of application package
enum WiseApplicationPacketSubType {
	WISE_APP_NORMAL 					= 01;	//!< Normal packets processed by the Application layer
	WISE_APP_DIRECT_COMMUNICATION 		= 10;	//!< Packets received from direct communication without using the network
	WISE_APP_NEIGHBOR_DISCOVER_REQUEST 	= 20;	//!< Packets received to discover neighborgs
	WISE_APP_NEIGHBOR_DISCOVER_REPLY 	= 21;	//!< Packets received to reply a neighbor discovery request
	WISE_APP_NEIGHBOR_DISCOVER_TIMEOUT 	= 22;	//!< Packets received when discovery timeouts are triggered
	WISE_APP_NEIGHBOR_DISCOVER_DONE 	= 23;	//!< Packets received to announce the end of discover neighborgs
	WISE_APP_OUT_OF_ENERGY				= 30;	//!< Packets received when a layer or camera depletes its energy
};

//!< \enum WiseNeigborhoodPacketType
//!<  \brief Type of package when communicating with neigbourgs 
enum WiseApplicationPacketType {
    WISE_NEIGHBOR_RESET      = 1000; //!< Reset
    WISE_NEIGHBOR_UNKNOWN    = 1001; //!< Unknown neigbourghood is used
    WISE_NEIGHBOR_COM        = 1002; //!< Communications graph is used
    WISE_NEIGHBOR_FOV        = 1003; //!< Vision graph is used
};

packet WiseBaseAppPacket extends ApplicationGenericDataPacket {
	unsigned char payload[]; 								//!< raw data
	unsigned int subType = WISE_APP_NORMAL; 				//!< type of package (WiseApplicationPacketType)
	unsigned int subTypeNeighbor = WISE_NEIGHBOR_UNKNOWN; 	//!< Type of neigbourghood employed	 (WiseNeigborhoodPacketType)	
}
