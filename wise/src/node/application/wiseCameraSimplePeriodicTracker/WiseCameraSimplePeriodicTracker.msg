// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2013
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file describes a template to implement tracking algorithms. Currently only used by WiseCameraDPF
//  TODO: remove this template in future releases of WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
//
cplusplus {{
	#include "WiseApplicationPacket_m.h"
	#include "WiseDefinitionsTracking.h"
}};

class WiseApplicationPacket;

packet WiseSimplePeriodicTrackerMessage extends WiseApplicationPacket  {

	unsigned long trackingCount; 			//tracking step counter	
	unsigned int targetID; 				// ID of the target
	double positionX; 						// x-pos of the target
	double positionY;						// y-pos the target
	unsigned int TypeNeighbour;// Type of neigbourgs employed
}