// *****************************************************************************
//  Copyright (C): Christian Nastasi, 2011                                    
//  Author(s): Christian Nastasi                                              
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa)           
//  - School of Elec Eng and Computer Science, Queen Mary University (London) 
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:          
//  - c.nastasi@sssup.it                                                      
//  - nastasichr@gmail.com                                                    
//  - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WiseAppTest_h__
#define __WiseAppTest_h__ 

#include "WiseBaseApplication.h"
#include "WiseEmptySensorMessage_m.h"
#include <fstream>

class WiseAppTest : public WiseBaseApplication {
private:
	static ofstream logger; //!< Used to collect node print-out
protected:
	void startup();
	void finishSpecific();
	void timerFiredCallback(int);
	void handleSensorReading(WiseSensorManagerMessage *);
	void fromNetworkLayer(WiseApplicationPacket *, const char *, double, double);
	void handleDirectApplicationMessage(WiseApplicationPacket *);
};
#endif // __WiseAppTest_h__	
