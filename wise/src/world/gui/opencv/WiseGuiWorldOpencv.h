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
	std::string _window_name0,_window_name1;
	std::string _realmapfile;

	cv::Mat _image0,_image1;
	cv::Mat _image0clut,_image1clut;
	cv::Mat _image0_hold,_image1_hold;
	unsigned _width0,_width1;
	unsigned _height0,_height1;

	double _offsetX_world,_offsetY_world;

	std::map<int,cv::Scalar> _color_list;
	std::map<int,cv::Scalar> _color_target;
public:
	static WiseGuiWorld* creator(bool show, unsigned w, unsigned h, float offsetX, float offsetY,float s, std::string map, bool draw_trajectory)
					{ return new WiseGuiWorldOpencv(show, w, h, offsetX,offsetY, s, map, draw_trajectory); };
	WiseGuiWorldOpencv(bool show, unsigned w, unsigned h, float offsetX, float offsetY,float scale, std::string map, bool draw_trajectory);
	virtual ~WiseGuiWorldOpencv();
	virtual void wait_key();
	virtual void draw_camera(const WiseCameraInfo&,std::string winname="WORLD");
	virtual void draw_target(const WiseTargetInfo&,std::string winname="WORLD");
    virtual void draw_noise(const WiseTargetInfo&,std::string winname="WORLD");
	virtual void hold();
	virtual void clean();

	std::map<int,cv::Scalar> getColorList(){return _color_list;}
};

#endif // __WiseWiseGuiWorldOpencv_h__
