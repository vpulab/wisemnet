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

#include "WiseCameraHandler.h"
#include "WiseCameraManager.h"
#include "WiseException.h"

//using namespace std;

map<string, WiseCameraHandler::Factory::creator_t>*WiseCameraHandler::Factory::registry = NULL;

WiseCameraHandler::Factory::Factory(const string &name, WiseCameraHandler::Factory::creator_t func)
{
	if (!registry)
		registry = new map<string, creator_t>();
        if (registry->find(name) != registry->end()) {
		std::string s = "\nwcns::WiseCameraHandler::Factory : ERROR calling Factory(...) :\nAttempt to register "
		        " a concrete WiseCameraHandler creator with a name already in the registry (name = '";
		s += name + "').\n"; 
        throw WiseException(s);
	}
        registry->insert(make_pair(name, func));
}

WiseCameraHandler* WiseCameraHandler::Factory::create(const string &name, const WiseCameraManager &m)
{
	if (!registry) {
	    std::string s = "\nwise::WiseCameraHandler::Factory : ERROR calling create(...) :\n"
			   "Attempt to create a concrete WiseCameraHandler but registry is empty (name = '";
		s += name + "').\n";
        throw WiseException(s);
	}
	if (registry->find(name) == registry->end()) {
	    std::string s = "\nwise::WiseCameraHandler::Factory : ERROR calling create(...) :\n"
			   "Attempt to create a concrete WiseCameraHandler with name not in the registry (name = '";
		s += name + "').\n";
        throw WiseException(s);
	}
	return registry->at(name)(m);
}

