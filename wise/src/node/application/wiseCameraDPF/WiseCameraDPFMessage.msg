// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
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
//  This file is part of the implementation for the DPF tracker for single targets described in:
//      - C. Nastasi, A. Cavallaro, "WiSE-MNet: an experimental environment for Wireless Multimedia Sensor Networks"
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//      - C. Nastasi, A. Cavallaro, "Distributed target tracking under realistic network conditions",
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

cplusplus {{
	#include "WiseApplicationPacket_m.h"
	#include "wise_utils_gmm.h"
}};

class WiseApplicationPacket;
class noncobject WiseUtils::Gmm::Component;

packet WiseCameraDPFMessage extends WiseApplicationPacket  {
	@customize(true);

	unsigned int targetID;
	unsigned long trackingStep;
	unsigned int aggregationStep;
	bool detectionMiss;
	bool firstStepFailed;
	bool targetLost;
	bool firstNodeSelection;
	double firstNodeSelectionScore;
	bool firstNodeSelectionCompleted;

	double firstStartTime;
	double veryFirstStartTime;

	bool useGmm;
	unsigned long fakeVoidPointer;
	abstract WiseUtils::Gmm::Component gmm[];
}
