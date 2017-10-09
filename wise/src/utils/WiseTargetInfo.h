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
    int id;
private: 
	double pos_x;
	double pos_y;
	double pos_z;
	double bb_width;
	double bb_height;
	double bb_depth;

	// Other stuff
	bool unique_color;

public:
	inline void get_position(double&, double&, double&) const;
	inline void get_bb(double&, double&) const;
	inline void get_ucolor(bool&) const;

private:
	WiseTargetInfo() :pos_x(0), pos_y(0), pos_z(0), bb_width(0), bb_height(0),bb_depth(0),unique_color(false)
		{};

public:
	friend class WiseMovingTarget;
    friend class WiseMultiCameraPeriodicApp_ICF;
    friend class WiseMultiCameraPeriodicApp_MTIC;
    friend class WiseMultiCameraPeriodicApp_ICFnet;

};

void WiseTargetInfo::get_position(double &x, double &y, double &z) const
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
}

void WiseTargetInfo::get_bb(double &w, double &h) const
{
	w = bb_width;
	h = bb_height;
}
void WiseTargetInfo::get_ucolor(bool &b) const
{
    b=unique_color;
}
#endif // __WiseTargetInfo_h__
