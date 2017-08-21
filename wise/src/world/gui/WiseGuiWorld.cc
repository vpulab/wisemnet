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

#include "WiseGuiWorld.h"
#include "WiseException.h"

using namespace std;

map<string, WiseGuiWorld::Factory::creator_t> *WiseGuiWorld::Factory::registry = NULL;

WiseGuiWorld::Factory::Factory(const string &name, WiseGuiWorld::Factory::creator_t fun)
{ 
	if (!registry)
		registry = new map<string, creator_t>();
        if (registry->find(name) != registry->end()) {
		string s = "\nwcns::WiseGuiWorld::Factory : ERROR calling Factory(...) :\n"
			   "Attempt to register a concrete WiseGuiWorld creator with a name already in the registry (name = '";
		s += name + "').\n"; 
        throw WiseException(s);
	}
        registry->insert(make_pair(name, fun));
}

WiseGuiWorld* WiseGuiWorld::Factory::create(const string &name, bool show, unsigned w, unsigned h, float scale, std::string mapfile, bool draw_trajectory)
{
	if (!registry) {
		string s = "\nwise::WiseGuiWorld::Factory : ERROR calling create(...) :\n"
			   "Attempt to create a concrete WiseGuiWorld but registry is empty (name = '";
		s += name + "').\n";
        throw WiseException(s);
	}
	if (registry->find(name) == registry->end()) {
		string s = "\nwise::WiseGuiWorld::Factory : ERROR calling create(...) :\n "
		        "Attempt to create a concrete WiseGuiWorld with name not in the registry (name = '";
		s += name + "').\n";
        throw WiseException(s);
	}
	return registry->at(name)(show,w,h,scale,mapfile,draw_trajectory);
}

WiseGuiWorld::WiseGuiWorld(bool show, unsigned w, unsigned h, float s, std::string mapfile,bool draw_trajectory)
{
	_scaling_factor = (s == 0) ?  320.f / w : s;
}
