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

#ifndef __WiseBasePhysicalProcess_h__
#define __WiseBasePhysicalProcess_h__

#include "CastaliaModule.h"
#include "WiseBaseTerrain.h"

class WiseBasePhysicalProcess: public CastaliaModule {
protected:
	/*--- The .ned file's parameters ---*/
	int self;			// the node's ID

	/*--- Custom class parameters ---*/
	WiseBaseTerrain *terrain;

	virtual void initialize();
	virtual void handleMessage(cMessage * msg);
	virtual void finish();
	virtual void finishSpecific() {};
};

#endif //__WiseBaseApplication_h__
