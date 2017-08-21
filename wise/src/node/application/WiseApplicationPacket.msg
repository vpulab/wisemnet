// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011 (nastasichr@gmail.com)
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file describes a template to implement applications in WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

cplusplus {{
        #include "ApplicationPacket_m.h"
        #include "CastaliaMessages.h"
}};

class ApplicationGenericDataPacket;

//!< \enum WiseApplicationPacketType
//!<  \brief Type of application package
enum WiseApplicationPacketType {
	WISE_APP_NORMAL 					= 0;	
	WISE_APP_DIRECT_COMMUNICATION 		= 10;
	WISE_APP_NEIGHBOUR_DISCOVER_REQUEST = 20;
	WISE_APP_NEIGHBOUR_DISCOVER_REPLY 	= 21;
	WISE_APP_NEIGHBOUR_DISCOVER_TIMEOUT = 22;
	WISE_APP_NEIGHBOUR_DISCOVER_DONE 	= 23;
	WISE_APP_OUT_OF_ENERGY				= 30;
};

//!< \enum WiseNeigborhoodPacketType
//!<  \brief Type of package when communicating with neigbourgs 
enum WiseNeigborhoodPacketType {
    WISE_NEIGHBOUR_RESET      = 0; //!< Reset
    WISE_NEIGHBOUR_UNKNOWN    = 1; //!< Unknown neigbourghood is used
    WISE_NEIGHBOUR_COM        = 2; //!< Communications graph is used
    WISE_NEIGHBOUR_FOV        = 3; //!< Vision graph is used
};

packet WiseApplicationPacket extends ApplicationGenericDataPacket {
	unsigned char payload[]; //!< 
	unsigned int type = WISE_APP_NORMAL; //!< type of package (WiseApplicationPacketType)
	unsigned int TypeNeighbour = WISE_NEIGHBOUR_UNKNOWN; // Type of neigbourghood employed	 (WiseNeigborhoodPacketType)	
}
