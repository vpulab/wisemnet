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

#ifndef __WiseDummyWirelessChannel_h__
#define __WiseDummyWirelessChannel_h__

#include <vector>
#include "CastaliaModule.h"

class WiseDummyWirelessChannel: public CastaliaModule {
private:
	std::set<int> *connectivity_map;
protected:
	virtual void initialize();
	virtual void finish();
	virtual void handleMessage(cMessage * msg);
	virtual void finishSpecific();
private:
	// NOTE: same implementation of VirtualRouting.h/cc
	int resolveNetworkAddress(const char *);
	inline bool check_connectivity(int tx, int rx);
};

#endif	// __WiseDummyWirelessChannel_h__
