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

#ifndef __WiseGuiWorldOpencv_h__ 
#define __WiseGuiWorldOpencv_h__ 

#include <string>
#include <opencv.hpp>
#include "WiseGuiWorld.h"

class WiseGuiWorldOpencv : public WiseGuiWorld {
private:
	std::string _window_name;
	std::string _realmapfile;

	cv::Mat _image;
	cv::Mat _image_hold;
	unsigned _width;
	unsigned _height;

	std::map<int,cv::Scalar> _color_list;
	std::map<int,cv::Scalar> _color_target;
public:
	static WiseGuiWorld* creator(bool show, unsigned w, unsigned h, float s, std::string map, bool draw_trajectory)
					{ return new WiseGuiWorldOpencv(show, w, h, s, map, draw_trajectory); };
	WiseGuiWorldOpencv(bool show, unsigned w, unsigned h, float scale, std::string map, bool draw_trajectory);
	virtual ~WiseGuiWorldOpencv();
	virtual void wait_key();
	virtual void draw_camera(const WiseCameraInfo&);
	virtual void draw_target(const WiseTargetInfo&);
	virtual void hold();
	virtual void clean();
};

#endif // __WiseWiseGuiWorldOpencv_h__
