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

WiseGuiWorldOpencv::WiseGuiWorldOpencv(bool show, unsigned w, unsigned h, float offsetX, float offsetY,float s, std::string realmapfile,bool draw_trajectory)
    : WiseGuiWorld(show, w, h, offsetX, offsetY,s,realmapfile,draw_trajectory), _image0(cv::Size(scale(w), scale(h)), CV_8UC3), _image0_hold(cv::Size(scale(w), scale(h)), CV_8UC3)
{
    _show_gui = show;
    _realmapfile = realmapfile;//gui_show
    _draw_trajectory = draw_trajectory;

    _offsetX_world = offsetX;
    _offsetY_world = offsetY;

    if (_show_gui && _realmapfile.compare("") != 0)
    {
        _window_name0 = "WORLD";
        cv::namedWindow(_window_name0.c_str());
        _image0.setTo(cv::Scalar(255,255,255));//white background for GUI
        _width0 = scale(w);
        _height0 = scale(h);
        _image0.copyTo(_image0_hold);
        cv::imshow(_window_name0, _image0);

        _window_name1 = "GROUND-PLANE MAP";
        cv::namedWindow(_window_name1.c_str());
        _image1 = cv::imread(_realmapfile.c_str(), CV_LOAD_IMAGE_COLOR);
        _width1 = (unsigned)_image1.size().width;
        _height1= (unsigned)_image1.size().height;
        _image1.copyTo(_image1_hold);
        cv::imshow(_window_name1, _image1);

        cv::waitKey(1);
    }
    else
    {
        _image0.setTo(cv::Scalar(255,255,255));//white background for GUI
        //_image.setTo(cv::Scalar(0,0,0));//black background for GUI
    }

    //define unique colors for each camera to be plotted
    // white reserved for background
    // black reserved for common target plots
    _color_list.insert(std::make_pair(0, cv::Scalar(255,0,0)));
    _color_list.insert(std::make_pair(1, cv::Scalar(0,255,0)));
    _color_list.insert(std::make_pair(2, cv::Scalar(0,0,255)));
    _color_list.insert(std::make_pair(3, cv::Scalar(255,255,0)));
    _color_list.insert(std::make_pair(4, cv::Scalar(255,0,255)));
    _color_list.insert(std::make_pair(5, cv::Scalar(0,255,255)));
    _color_list.insert(std::make_pair(6, cv::Scalar(50,50,50)));
    _color_list.insert(std::make_pair(7, cv::Scalar(100,100,100)));
    _color_list.insert(std::make_pair(8, cv::Scalar(150,150,150)));
    _color_list.insert(std::make_pair(9, cv::Scalar(200,200,200)));
    _color_list.insert(std::make_pair(10, cv::Scalar(250,250,250)));
    _color_list.insert(std::make_pair(11, cv::Scalar(100,200,100)));
    _color_list.insert(std::make_pair(12, cv::Scalar(50,50,100)));

    //define unique colors for each target to be plotted
    _color_target.insert(std::make_pair(0, cv::Scalar(255,0,0)));
    _color_target.insert(std::make_pair(1, cv::Scalar(0,255,0)));
    _color_target.insert(std::make_pair(2, cv::Scalar(0,0,255)));
    _color_target.insert(std::make_pair(3, cv::Scalar(255,255,0)));
    _color_target.insert(std::make_pair(4, cv::Scalar(255,0,255)));
    _color_target.insert(std::make_pair(5, cv::Scalar(0,255,255)));
    _color_target.insert(std::make_pair(6, cv::Scalar(50,50,50)));
    _color_target.insert(std::make_pair(7, cv::Scalar(100,100,100)));
    _color_target.insert(std::make_pair(8, cv::Scalar(150,150,150)));
    _color_target.insert(std::make_pair(9, cv::Scalar(200,200,200)));
    _color_target.insert(std::make_pair(10, cv::Scalar(250,250,250)));
    _color_target.insert(std::make_pair(11, cv::Scalar(100,200,100)));
    _color_target.insert(std::make_pair(12, cv::Scalar(50,50,100)));

}

WiseGuiWorldOpencv::~WiseGuiWorldOpencv()
{
    cv::destroyAllWindows();
}

void WiseGuiWorldOpencv::wait_key()
{
	cv::waitKey(0);
}

//Method to draw a camera within the image displayed by the GUI
void WiseGuiWorldOpencv::draw_camera(const WiseCameraInfo &cam,string winname)
{
    //select the image and offsets to draw data
    cv::Mat image;
    float dX,dY;
    if(winname=="WORLD")
    {
        image = _image0;
        dX = scale(-_offsetX_world);
        dY = scale(-_offsetY_world);
    }

    if(winname=="GROUND-PLANE MAP")
    {
        image = _image1;
        dX = 0;
        dY = 0;
    }

    //draw center position
	double c_x, c_y, c_z;
	cam.get_position(c_x, c_y, c_z);
	if(winname=="WORLD")
    {
	    c_x = scale(c_x);
        c_y = scale(c_y);
        c_z = scale(c_z);
    }

    if(winname=="GROUND-PLANE MAP")
    {
        //c_x = scale(c_x);
        //c_y = scale(c_y);
        //c_z = scale(c_z);
    }
	WISE_DEBUG_20("WiseGuiWorld::draw_camera() in " << winname.c_str() << ": " << "x=" << c_x << " y=" << c_y << " z=" << c_z);

	cv::circle(image, cv::Point(c_x+dX, c_y+dY), (int)scale(2.0), _color_list[cam.id],-1);
	std::ostringstream str;
    str << cam.id;
    WiseCameraInfo::fov_di_t fov_;
    cam.get_fov_di(fov_);
    double los = fov_.los;
    cv::putText(image, str.str(), cv::Point(c_x+10*cos(-los/6.28)+dX, c_y+10*cos(-los/6.28)+dY), 3, scale(0.5), _color_list[cam.id], 1, CV_AA);
    //putText(_image, str.str(), cv::Point(c_x+10*cos(los/6.28), c_y+10*cos(los/6.28)), 3, 0.5, _color_list[12], 1, CV_AA);

	if (cam.get_fov_type() == WiseCameraInfo::BOUNDING_BOX) {
		WiseCameraInfo::fov_bb_t fov;
		cam.get_fov_bb(fov);

		double tl_x, br_x,tl_y,br_y;
		if(winname=="WORLD")
        {
            tl_x = scale(fov.c_x) - scale(fov.width / 2);
            br_x = scale(fov.c_x) + scale(fov.width / 2);
            tl_y = scale(fov.c_y) - scale(fov.height / 2);
            br_y = scale(fov.c_y) + scale(fov.height / 2);
        }
		if(winname=="GROUND-PLANE MAP")
        {
            tl_x = (fov.c_x) - (fov.width / 2);
            br_x = (fov.c_x) + (fov.width / 2);
            tl_y = (fov.c_y) - (fov.height / 2);
            br_y = (fov.c_y) + (fov.height / 2);
        }

		cv::rectangle(image, cv::Point(tl_x+dX, tl_y+dY), cv::Point(br_x+dX, br_y+dY), _color_list[cam.id]);
	}

	if (cam.get_fov_type() == WiseCameraInfo::POLYGON) {
	    WiseCameraInfo::fov_poly_t fov;
        cam.get_fov_poly(fov);

        vector<cv::Point> points;
        points.clear();

        if(winname=="WORLD")
        {
            points.push_back(cv::Point(scale(fov.c_1x)+dX,scale(fov.c_1y)+dY));
            points.push_back(cv::Point(scale(fov.c_2x)+dX,scale(fov.c_2y)+dY));
            points.push_back(cv::Point(scale(fov.c_3x)+dX,scale(fov.c_3y)+dY));
            points.push_back(cv::Point(scale(fov.c_4x)+dX,scale(fov.c_4y)+dY));
        }
        if(winname=="GROUND-PLANE MAP")
        {
            points.push_back(cv::Point((fov.c_1x)+dX,(fov.c_1y)+dY));
            points.push_back(cv::Point((fov.c_2x)+dX,(fov.c_2y)+dY));
            points.push_back(cv::Point((fov.c_3x)+dX,(fov.c_3y)+dY));
            points.push_back(cv::Point((fov.c_4x)+dX,(fov.c_4y)+dY));
        }

        const cv::Point *pts = (const cv::Point*) (cv::Mat(points)).data;
        int npts = (cv::Mat(points)).rows;

        cv::polylines(image, &pts,&npts, 1,true,_color_list[cam.id],1);
   }

    if (cam.get_fov_type() == WiseCameraInfo::DIRECTIONAL) {
        WiseCameraInfo::fov_di_t fov;
        cam.get_fov_di(fov);

        vector<cv::Point> points;
        points.clear();

        if(winname=="WORLD")
        {
            points.push_back(cv::Point(scale(fov.c_px)+dX,scale(fov.c_py)+dY));
            points.push_back(cv::Point(scale(fov.c_cx)+dX,scale(fov.c_cy)+dY));
            points.push_back(cv::Point(scale(fov.c_bx)+dX,scale(fov.c_by)+dY));
            points.push_back(cv::Point(scale(fov.c_px)+dX,scale(fov.c_py)+dY));
        }
        if(winname=="GROUND-PLANE MAP")
        {
            points.push_back(cv::Point(scale(fov.c_px)+dX,scale(fov.c_py)+dY));
            points.push_back(cv::Point(scale(fov.c_cx)+dX,scale(fov.c_cy)+dY));
            points.push_back(cv::Point(scale(fov.c_bx)+dX,scale(fov.c_by)+dY));
            points.push_back(cv::Point(scale(fov.c_px)+dX,scale(fov.c_py)+dY));
        }
        const cv::Point *pts = (const cv::Point*) (cv::Mat(points)).data;
        int npts = (cv::Mat(points)).rows;

        cv::polylines(image, &pts,&npts, 1,
                     true,           // draw closed contour (i.e. joint end to start)
                     _color_list[cam.id],// colour RGB ordering
                     2);              // line thickness
    }/**/

	cv::imshow(winname.c_str(), image);
	cv::waitKey(10);
}

//Method to draw a target within the image displayed by the GUI
void WiseGuiWorldOpencv::draw_target(const WiseTargetInfo &target,string winname)
{
    //select the image and offsets to draw data
    cv::Mat image;
    float dX,dY;
    if(winname=="WORLD")
    {
        image = _image0;
        dX = scale(-_offsetX_world);
        dY = scale(-_offsetY_world);
    }

    if(winname=="GROUND-PLANE MAP")
    {
        image = _image1;
        dX = 0;
        dY = 0;
    }

    //draw center position
    double c_x, c_y, c_z;
    target.get_position(c_x, c_y, c_z);
    if(winname=="WORLD")
    {
        c_x = scale(c_x);
        c_y = scale(c_y);
        c_z = scale(c_z);
    }

    if(winname=="GROUND-PLANE MAP")
    {
        //c_x = scale(c_x);
        //c_y = scale(c_y);
        //c_z = scale(c_z);
    }
	WISE_DEBUG_20("WiseGuiWorld::draw_target() in " << winname.c_str()<< " : " << "x=" << c_x << "y=" << c_y << "z=" << c_z);

	bool unique_color;
	target.get_ucolor(unique_color);

	cv::Scalar color;
	if (unique_color==true)
	    color = cv::Scalar(0,0,0);
	else
	    color =  _color_target[target.id];

	if (_draw_trajectory)
	    cv::circle(image, cv::Point(c_x+dX, c_y+dY), (int)scale(2.0), color,-1);
	else{

	    cv::circle(image, cv::Point(c_x+dX, c_y+dY), 2, color);

        double bb_w;
        double bb_h;
        target.get_bb(bb_w, bb_h);
        if(winname=="WORLD")
        {
            bb_w = scale(bb_w);
            bb_h = scale(bb_h);
        }

        if(winname=="GROUND-PLANE MAP")
        {
            //bb_w = scale(bb_w);
            //bb_h = scale(bb_h);
        }
        double tl_x = c_x - bb_w / 2;
        double br_x = c_x + bb_w / 2;
        double tl_y = c_y - bb_h / 2;
        double br_y = c_y + bb_h / 2;
        cv::rectangle(image, cv::Point(tl_x+dX, tl_y+dY), cv::Point(br_x+dX, br_y+dY), color);
	}
	cv::imshow(winname.c_str(),image);
	cv::waitKey(10);
}

//Method to draw a target within the image displayed by the GUI
void WiseGuiWorldOpencv::draw_noise(const WiseTargetInfo &target,string winname)
{
    //select the image and offsets to draw data
    cv::Mat image;
    float dX,dY;
    if (target.id == -100)
    {

        if(winname=="WORLD")
            _image0.copyTo(_image0clut);

        if(winname=="GROUND-PLANE MAP")
            _image1.copyTo(_image1clut);
    }

    if(winname=="WORLD")
    {
        image = _image0clut;
        dX = scale(-_offsetX_world);
        dY = scale(-_offsetY_world);
    }

    if(winname=="GROUND-PLANE MAP")
    {
        image = _image1clut;
        dX = 0;
        dY = 0;
    }


    //draw center position
    double c_x, c_y, c_z;
    target.get_position(c_x, c_y, c_z);
    if(winname=="WORLD")
    {
        c_x = scale(c_x);
        c_y = scale(c_y);
        c_z = scale(c_z);
    }

    if(winname=="GROUND-PLANE MAP")
    {
        //c_x = scale(c_x);
        //c_y = scale(c_y);
        //c_z = scale(c_z);
    }
    WISE_DEBUG_20("WiseGuiWorld::draw_target() in " << winname.c_str()<< " : " << "x=" << c_x << "y=" << c_y << "z=" << c_z);

    bool unique_color;
    target.get_ucolor(unique_color);

    cv::Scalar color;
    if (unique_color==true)
        color = cv::Scalar(0,0,0);
    else
        color =  _color_target[target.id];

    if (_draw_trajectory)
        cv::circle(image, cv::Point(c_x+dX, c_y+dY), (int)scale(2.0), color,-1);
    else{

        cv::circle(image, cv::Point(c_x+dX, c_y+dY), 2, color);

        double bb_w;
        double bb_h;
        target.get_bb(bb_w, bb_h);
        if(winname=="WORLD")
        {
            bb_w = scale(bb_w);
            bb_h = scale(bb_h);
        }

        if(winname=="GROUND-PLANE MAP")
        {
            //bb_w = scale(bb_w);
            //bb_h = scale(bb_h);
        }
        double tl_x = c_x - bb_w / 2;
        double br_x = c_x + bb_w / 2;
        double tl_y = c_y - bb_h / 2;
        double br_y = c_y + bb_h / 2;
        cv::rectangle(image, cv::Point(tl_x+dX, tl_y+dY), cv::Point(br_x+dX, br_y+dY), color);
    }
    cv::imshow(winname.c_str(),image);
    cv::waitKey(10);
}


void WiseGuiWorldOpencv::hold()
{
    _image0.copyTo(_image0_hold);
	_image1.copyTo(_image1_hold);
}

void WiseGuiWorldOpencv::clean()
{
	_image0_hold.copyTo(_image0);
    _image1_hold.copyTo(_image1);
}
