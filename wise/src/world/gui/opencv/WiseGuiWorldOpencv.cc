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

#include "WiseGuiWorldOpencv.h"
#include "WiseDebug.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace std;

//static GuiWorld::Factory::Factory registrat("opencv", &WiseGuiWorldOpencv::creator);

//change for compilers gcc >4.5 
static WiseGuiWorld::Factory registrat("opencv", &WiseGuiWorldOpencv::creator);

WiseGuiWorldOpencv::WiseGuiWorldOpencv(bool show, unsigned w, unsigned h, float s, std::string realmapfile,bool draw_trajectory)
    : WiseGuiWorld(show, w, h, s,realmapfile,draw_trajectory), _image(cv::Size(scale(w), scale(h)), CV_8UC3), _image_hold(cv::Size(scale(w), scale(h)), CV_8UC3)
{
    _show_gui = show;
    _realmapfile = realmapfile;//gui_show
    _draw_trajectory = draw_trajectory;

    if (_show_gui && _realmapfile.compare("") != 0)
    {
        _window_name = "WORLD";
        cv::namedWindow(_window_name.c_str());
        _width = scale(w);
        _height = scale(h);
        cv::Mat tmp = cv::imread(_realmapfile.c_str(), CV_LOAD_IMAGE_COLOR);
        cv::resize(tmp,_image,cv::Size(scale(w), scale(h)));
        cv::imshow(_window_name, _image);
        cv::waitKey(10);
    }
    else
    {
        _image.setTo(cv::Scalar(255,255,255));//white background for GUI
        //_image.setTo(cv::Scalar(0,0,0));//black background for GUI
    }

    //define unique colors for each camera to be plotted
    _color_list.insert(std::make_pair(0, cv::Scalar(125,125,125)));
    _color_list.insert(std::make_pair(1, cv::Scalar(255,0,0)));
    _color_list.insert(std::make_pair(2, cv::Scalar(0,255,0)));
    _color_list.insert(std::make_pair(3, cv::Scalar(0,0,255)));
    _color_list.insert(std::make_pair(4, cv::Scalar(255,0,255)));
    _color_list.insert(std::make_pair(5, cv::Scalar(255,255,0)));
    _color_list.insert(std::make_pair(6, cv::Scalar(0,255,255)));
    _color_list.insert(std::make_pair(7, cv::Scalar(0,100,200)));
    _color_list.insert(std::make_pair(8, cv::Scalar(100,100,200)));
    _color_list.insert(std::make_pair(9, cv::Scalar(150,0,225)));
    _color_list.insert(std::make_pair(10, cv::Scalar(200,200,225)));
    _color_list.insert(std::make_pair(11, cv::Scalar(125,255,150)));
    _color_list.insert(std::make_pair(12, cv::Scalar(0,0,0)));

    //define unique colors for each target to be plotted
    _color_target.insert(std::make_pair(0, cv::Scalar(0,0,0)));
    _color_target.insert(std::make_pair(1, cv::Scalar(255,0,0)));
    _color_target.insert(std::make_pair(2, cv::Scalar(0,255,0)));
    _color_target.insert(std::make_pair(3, cv::Scalar(0,0,255)));
}

WiseGuiWorldOpencv::~WiseGuiWorldOpencv()
{
    if (_show_gui)
        cv::destroyWindow(_window_name.c_str());
}

void WiseGuiWorldOpencv::wait_key()
{
	cv::waitKey(0);
}

//Method to draw a camera within the image displayed by the GUI
void WiseGuiWorldOpencv::draw_camera(const WiseCameraInfo &cam)
{
	double c_x, c_y, c_z;

	cam.get_position(c_x, c_y, c_z);
	c_x = scale(c_x);
	c_y = scale(c_y);
	c_z = scale(c_z);
	WISE_DEBUG_3("WiseGuiWorld::draw_camera() : " << "x=" << c_x << " y=" << c_y << " z=" << c_z);

	cv::circle(_image, cv::Point(c_x, c_y), 3, _color_list[cam.id],-1);
	//cv::circle(_image, cv::Point(c_x, c_y), 5, _color_list[0],-1);
	std::ostringstream str;
    str << cam.id;
    WiseCameraInfo::fov_di_t fov_;
    cam.get_fov_di(fov_);
    double los = fov_.los;
    putText(_image, str.str(), cv::Point(c_x+10*cos(los/6.28), c_y+10*cos(los/6.28)), 3, 0.25, _color_list[cam.id], 1, CV_AA);
    //putText(_image, str.str(), cv::Point(c_x+10*cos(los/6.28), c_y+10*cos(los/6.28)), 3, 0.5, _color_list[12], 1, CV_AA);

	if (cam.get_fov_type() == WiseCameraInfo::BOUNDING_BOX) {
		WiseCameraInfo::fov_bb_t fov;
		cam.get_fov_bb(fov);
		double tl_x = scale(fov.c_x) - scale(fov.width / 2);
		double br_x = scale(fov.c_x) + scale(fov.width / 2);
		double tl_y = scale(fov.c_y) - scale(fov.height / 2);
		double br_y = scale(fov.c_y) + scale(fov.height / 2);
		cv::rectangle(_image, cv::Point(tl_x, tl_y), cv::Point(br_x, br_y), _color_list[cam.id]);
	}

	if (cam.get_fov_type() == WiseCameraInfo::POLYGON) {
	    WiseCameraInfo::fov_poly_t fov;
        cam.get_fov_poly(fov);

        vector<cv::Point> points;
        points.clear();

        points.push_back(cv::Point(scale(fov.c_1x),scale(fov.c_1y)));
        points.push_back(cv::Point(scale(fov.c_2x),scale(fov.c_2y)));
        points.push_back(cv::Point(scale(fov.c_3x),scale(fov.c_3y)));
        points.push_back(cv::Point(scale(fov.c_4x),scale(fov.c_4y)));

        const cv::Point *pts = (const cv::Point*) (cv::Mat(points)).data;
        int npts = (cv::Mat(points)).rows;

        cv::polylines(_image, &pts,&npts, 1,true,_color_list[cam.id],1);
   }

    if (cam.get_fov_type() == WiseCameraInfo::DIRECTIONAL) {
        WiseCameraInfo::fov_di_t fov;
        cam.get_fov_di(fov);

        vector<cv::Point> points;
        points.clear();

        points.push_back(cv::Point(scale(fov.c_px),scale(fov.c_py)));
        points.push_back(cv::Point(scale(fov.c_cx),scale(fov.c_cy)));
        points.push_back(cv::Point(scale(fov.c_bx),scale(fov.c_by)));
        points.push_back(cv::Point(scale(fov.c_px),scale(fov.c_py)));

        const cv::Point *pts = (const cv::Point*) (cv::Mat(points)).data;
        int npts = (cv::Mat(points)).rows;

        cv::polylines(_image, &pts,&npts, 1,
                     true,           // draw closed contour (i.e. joint end to start)
                     _color_list[cam.id],// colour RGB ordering
                     2);              // line thickness/**/
    }

	cv::imshow(_window_name, _image);
	cv::waitKey(10);
}

//Method to draw a target within the image displayed by the GUI
void WiseGuiWorldOpencv::draw_target(const WiseTargetInfo &target)
{
	double c_x, c_y, c_z;

	target.get_position(c_x, c_y, c_z);
	c_x = scale(c_x);
	c_y = scale(c_y);
	c_z = scale(c_z);
	WISE_DEBUG_3("WiseGuiWorld::draw_target() : " << "x=" << c_x << "y=" << c_y << "z=" << c_z);

	if (_draw_trajectory)
	    cv::circle(_image, cv::Point(c_x, c_y), 1, _color_target[target.id],-1);
	else{

	    cv::circle(_image, cv::Point(c_x, c_y), 2, _color_target[target.id]);

        double bb_w;
        double bb_h;
        target.get_bb(bb_w, bb_h);
        bb_w = scale(bb_w);
        bb_h = scale(bb_h);
        double tl_x = c_x - bb_w / 2;
        double br_x = c_x + bb_w / 2;
        double tl_y = c_y - bb_h / 2;
        double br_y = c_y + bb_h / 2;
        cv::rectangle(_image, cv::Point(tl_x, tl_y), cv::Point(br_x, br_y), _color_target[target.id]);
	}
	cv::imshow(_window_name,_image);
	cv::waitKey(10);
}

void WiseGuiWorldOpencv::hold()
{
	_image.copyTo(_image_hold);
}

void WiseGuiWorldOpencv::clean()
{
	_image_hold.copyTo(_image);
}
