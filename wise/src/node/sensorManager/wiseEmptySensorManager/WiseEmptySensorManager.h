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

#ifndef __WiseEmptySensorManager_h__
#define __WiseEmptySensorManager_h__

#include <string>
#include <vector>
#include <map>
#include "WiseBaseSensorManager.h"
#include "WiseEmptySensorMessage_m.h"

class WiseEmptySensorManager: public WiseBaseSensorManager {
protected:
	virtual void processSampleRequest(WiseSensorManagerMessage *req);
};
#endif // __WiseEmptySensorManager_h__
