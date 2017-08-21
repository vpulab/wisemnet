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

#ifndef __WiseTargetInfo_h__
#define __WiseTargetInfo_h__

class WiseTargetInfo {
public:
//	typedef enum {
		//NONE = 0,
		//BOUNDING_BOX,
	//} fov_t;
    int id;
private: 
	double pos_x;
	double pos_y;
	double pos_z;
	//fov_t fov_type;
	double bb_width;
	double bb_height;
	double bb_depth;


	// Other stuff

public:
	inline void get_position(double&, double&, double&) const;
	//inline fov_t get_fov_type();
	//inline void get_bb(double&, double&, double&);
	inline void get_bb(double&, double&) const;

private:
	WiseTargetInfo() :pos_x(0), pos_y(0), pos_z(0)
		            //fov_type(NONE), fov_bb_width(0), fov_bb_height(0)
		{};

public:
	friend class WiseMovingTarget;
};

void WiseTargetInfo::get_position(double &x, double &y, double &z) const
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
}

//fov_t WiseTargetInfo::get_fov_type()
//{
	//return fov_type;
//}

void WiseTargetInfo::get_bb(double &w, double &h) const
{
	w = bb_width;
	h = bb_height;
}

#endif // __WiseTargetInfo_h__
