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
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WiseCameraAppTest_h__
#define __WiseCameraAppTest_h__ 

#include "WiseCameraApplication.h"

class WiseCameraAppTest : public WiseCameraApplication {
private:
	static ofstream logger; //!< Used to collect node print-out

	unsigned int detection_counter;

protected:
	void startup();
	void finishSpecific();
	void fromNetworkLayer(WiseApplicationPacket *, const char *, double, double);
	void handleDirectApplicationMessage(WiseApplicationPacket *);
	void handleSensorReading(WiseCameraMessage *);
	void timerFiredCallback(int);
};
#endif // __WiseCameraAppTest_h__	
