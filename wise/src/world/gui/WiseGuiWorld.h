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

#ifndef __WiseWiseGuiWorld_h__
#define __WiseWiseGuiWorld_h__

#include <string>
#include <map>
#include "WiseCameraInfo.h"
#include "WiseTargetInfo.h"

//namespace wise {

class WiseGuiWorld {
public:
	class Factory {
	private: 
		typedef WiseGuiWorld* (*creator_t)(bool, unsigned, unsigned, float, std::string, bool);
	private:
		static std::map<std::string, creator_t> *registry;
	public:
		Factory(const std::string&, creator_t);
		static WiseGuiWorld *create(const std::string&, bool, unsigned, unsigned, float scaling_factor, std::string mapfile, bool draw_trajectory);
	};

protected:
	bool _show_gui;
	float _scaling_factor;
	bool _draw_trajectory;

public:
	WiseGuiWorld(bool show, unsigned w, unsigned h, float scale, std::string mapfile,bool draw_trajectory);
	virtual ~WiseGuiWorld() {} ;
	virtual void wait_key() = 0;
	virtual void draw_camera(const WiseCameraInfo&) = 0;
	virtual void draw_target(const WiseTargetInfo&) = 0;
	virtual void hold() = 0;
	virtual void clean() = 0;

protected:
	inline unsigned scale(unsigned);
	inline double scale(double);
};

inline unsigned WiseGuiWorld::scale(unsigned c)
{
	return (unsigned) ((float)c * _scaling_factor);
}

inline double WiseGuiWorld::scale(double c)
{
	return  c * _scaling_factor;
}

//} // namespace wise

#endif // __WiseWiseGuiWorld_h__
