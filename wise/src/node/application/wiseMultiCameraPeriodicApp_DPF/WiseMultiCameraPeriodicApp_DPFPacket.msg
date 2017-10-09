/// *****************************************************************************************
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

cplusplus {{
	#include "WiseCameraPeriodicAppPacket_m.h"
	#include "wise_utils_gmm.h"
}};

class WiseCameraPeriodicAppPacket ;
class noncobject WiseUtils::Gmm::Component;

packet WiseMultiCameraPeriodicApp_DPFPacket extends WiseCameraPeriodicAppPacket   {
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
