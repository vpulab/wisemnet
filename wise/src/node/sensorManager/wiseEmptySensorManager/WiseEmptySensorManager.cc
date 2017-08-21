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
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#include "WiseEmptySensorManager.h"

Define_Module(WiseEmptySensorManager);

void WiseEmptySensorManager::processSampleRequest(WiseSensorManagerMessage *req)
{
	WiseEmptySensorMessage *smp;
	smp = new WiseEmptySensorMessage("Empty Random reading", SENSOR_READING_MESSAGE);
	if (!smp)
		return;
	smp->setRandomValue(uniform(0, 1));
	send(smp, "toApplicationModule");
}
