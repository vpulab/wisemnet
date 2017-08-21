// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Juan C. SanMiguel
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  Developed at the:
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  DESCRIPTION:
//  This file describes the header file for the network visualizer (WiseCalibratedTerrain) with calibration data
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
#ifndef __WiseTerrainCalibrated_h__
#define __WiseTerrainCalibrated_h__

#include "WiseBaseTerrain.h"

class WiseTerrainCalibrated: public WiseBaseTerrain {
private:
	/*--- The .ned file's parameters ---*/
	/*--- Custom class parameters ---*/

protected:
	void initialize();
	//void finish();
public:
};

#endif // __WiseTerrainCalibrated_h__
