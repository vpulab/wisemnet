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

#ifndef __WiseMovingTarget_h__
#define __WiseMovingTarget_h__

#include <fstream>
#include "WiseBasePhysicalProcess.h"
#include "WiseMovingTargetMessage_m.h"

using namespace std;

class WiseMovingTarget: public WiseBasePhysicalProcess {
private:
	/*--- The .ned file's parameters ---*/
	double x_init;
	double y_init;
	double z_init;
	double target_width;
	double target_height;
	double target_depth;
	double update_time;
	double noise_min;
	double noise_max;
	double move_min_x;
	double move_max_x;
	double move_min_y;
	double move_max_y;
	double move_later;
	bool log_enabled;
	bool random_init;
	bool random_noise;
	double noise;

	/*--- Custom class member variables ---*/
	double x_curr;
	double y_curr;
	double z_curr;
	WiseTargetInfo target_info;
	double lin_x_step;
	double lin_y_step;
	double diagonal;
	double radius;
	double rotation_angle;
	double rotation_step;
	void (WiseMovingTarget::*move_func)(void);

	static std::ofstream *writer;

public: 
	virtual ~WiseMovingTarget();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage * msg);
	virtual void finishSpecific();

private:
	void load_parameters();
	void log_information();
	void calculate_bounding_box(WiseTargetBoundingBox &bb);
	void move_linear_noise();
	void move_linear_random();
	void move_circular_noise();
	void move_circular_noise(double r);
	void move_lincirc_noise();
	void move_random_walk();
	void move_random_walk_8();
};

#endif // __WiseMovingTarget_h__
