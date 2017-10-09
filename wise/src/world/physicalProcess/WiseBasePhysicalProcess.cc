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

#include <omnetpp.h>
#include "WiseBasePhysicalProcess.h"
#include "WisePhysicalProcessMessage_m.h"
#include "WiseDebug.h"

#define perr_app(m) opp_error("\n[PhysicalProcess]:\n " m)
#define perr(m) opp_error(m)

void WiseBasePhysicalProcess::initialize()
{
	cModule *parent = getParentModule();

	if (parent->findSubmodule("wiseTerrain") == -1) {
		WISE_DEBUG_10("If you see this, it's BAAAAAAD!!!");
		perr_app("Error in getting a valid reference to WiseBaseTerrain for direct method calls.");
	}
	terrain = check_and_cast <WiseBaseTerrain*> (parent->getSubmodule("wiseTerrain"));
	self = getIndex();
}

void WiseBasePhysicalProcess::handleMessage(cMessage * msg)
{
	delete msg;
	msg = NULL;		// safeguard
}

void WiseBasePhysicalProcess::finish()
{
    CastaliaModule::finish();
	DebugInfoWriter::closeStream();
}
