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

#ifndef __WiseCameraInfo_h__
#define __WiseCameraInfo_h__


#ifndef PI
#define PI 3.141592654
#endif

#include <opencv.hpp>
#include <math.h>

class WiseCameraInfo {
public:
	typedef enum {
		NONE = 0,
		BOUNDING_BOX,
		POLYGON,
		DIRECTIONAL,
	} fov_t;

public:
	struct fov_bb_t {
		double c_x;
		double c_y;
		double width;
		double height;
		double max_x;
		double min_x;
		double max_y;
		double min_y;
	public:
		fov_bb_t() : c_x(0), c_y(0), width(0), height(0), max_x(0), min_x(0), max_y(0), min_y(0) {} ;
		fov_bb_t(double x, double y) : c_x(x), c_y(y), width(0), height(0), max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	};

	struct fov_poly_t {
	        double c_x;
	        double c_y;
	        double c_1x; //x-position of the second point
            double c_1y; //y-position of the second point
            double c_2x; //x-position of the second point
            double c_2y; //y-position of the second point
            double c_3x; //x-position of the third point
            double c_3y; //y-position of the third point
            double c_4x; //x-position of the third point
            double c_4y; //y-position of the third point

	    public:
            fov_poly_t() : c_x(0), c_y(0), c_1x(0), c_1y(0), c_2x(0), c_2y(0), c_3x(0), c_3y(0), c_4x(0), c_4y(0) {} ;
            fov_poly_t(double x, double y) : c_x(x), c_y(y), c_1x(0), c_1y(0), c_2x(0), c_2y(0), c_3x(0), c_3y(0), c_4x(0), c_4y(0) {} ;
	    };


	struct fov_di_t {
	        // Representation of the FOV with angles
	        double c_px; //x-position of the camera's FOV (in pixels)
	        double c_py; //y-position of the camera's FOV (in pixels)
	        double dov; //depth of view (length in c_vxy direction) of the camera's FOV (in pixels)
	        double los; //lineOfSigth of the camera's FOV (degrees)
	        double aov; //angle of view (angle) of the camera's FOV wrt (degrees)

	        // Representation of the FOV with three points (ie, as a triangle)
	        //double c_px; //x-position of the camera's FOV
            //double c_px; //y-position of the camera's FOV
            double c_cx; //x-position of the second point
            double c_cy; //y-position of the second point
            double c_bx; //x-position of the third point
            double c_by; //y-position of the third point

            cv::Point v;
            std::vector<cv::Point> vertex;

	        double max_x;
	        double min_x;
	        double max_y;
	        double min_y;
	    public:
	        fov_di_t() : c_px(0), c_py(0), dov(0), los(0), aov(0), c_cx(0), c_cy(0), c_bx(0), c_by(0), max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	        fov_di_t(double x, double y) : c_px(x), c_py(y), dov(0), los(0), aov(0),   c_cx(0), c_cy(0),  c_bx(0), c_by(0),  max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	        fov_di_t(double x, double y, double dov, double los, double aov) : c_px(x), c_py(y), dov(dov), los(los), aov(aov), c_cx(0), c_cy(0),  c_bx(0), c_by(0),  max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	    };

private: 
	double pos_x;
	double pos_y;
	double pos_z;
	fov_t fov_type;
	fov_bb_t fov_bb; //bounding box FOV
	fov_di_t fov_di; //directional FOV
	fov_poly_t fov_poly; //polygonal FOV

	// Other stuff


public:
	int id;

	inline void get_position(double&, double&, double&) const;
	inline fov_t get_fov_type() const;
	inline void get_fov_bb(fov_bb_t&) const;
	inline void get_fov_di(fov_di_t&) const;
	inline void get_fov_poly(fov_poly_t&) const;

private:
	WiseCameraInfo() : pos_x(0), pos_y(0), pos_z(0),
			   fov_type(NONE), fov_bb(0, 0) {};

	inline void set_position(double, double, double);
	inline void set_fov_bb(double, double, double x_max=0, double y_max=0);
	inline void set_fov_di(double, double, double aov=15, double x_max=0, double y_max=0);
	inline void set_fov_poly(double, double, double, double,double, double,double, double);

public:
	//friend class WiseBaseSensorManager;
	friend class WiseCameraManager;
	friend class WiseCameraApplication;
};


void WiseCameraInfo::get_position(double &x, double &y, double &z) const
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
}

void WiseCameraInfo::set_position(double x, double y, double z)
{
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

WiseCameraInfo::fov_t WiseCameraInfo::get_fov_type() const
{
	return fov_type;
}

void WiseCameraInfo::get_fov_bb(fov_bb_t &fov) const
{
	fov = fov_bb;
}

void WiseCameraInfo::get_fov_di(fov_di_t &fov) const
{
    fov = fov_di;
}

void WiseCameraInfo::get_fov_poly(fov_poly_t &fov) const
{
    fov = fov_poly;
}

void WiseCameraInfo::set_fov_bb(double w, double h, double x_max, double y_max)
{
    fov_type = BOUNDING_BOX;
    fov_bb.c_x = pos_x;
    fov_bb.c_y = pos_y;
    fov_bb.width = w;
    fov_bb.height = h;
    w /= 2;
    h /= 2;
    fov_bb.min_x = pos_x - w;
    fov_bb.max_x = pos_x + w;
    fov_bb.min_y = pos_y - h;
    fov_bb.max_y = pos_y + h;
    if (fov_bb.min_x < 0)
        fov_bb.min_x = 0;
    if (fov_bb.min_y < 0)
        fov_bb.min_y = 0;
    if (x_max > 0 && fov_bb.max_x > x_max)
         fov_bb.max_x = x_max;
    if (y_max > 0 && fov_bb.max_y > y_max)
         fov_bb.max_y = y_max;
}

void WiseCameraInfo::set_fov_poly(double p1x, double p1y, double p2x, double p2y,double p3x, double p3y,double p4x, double p4y)
{
	fov_type = POLYGON;
	fov_poly.c_1x = p1x;
	fov_poly.c_1y = p1y;
	fov_poly.c_2x = p2x;
    fov_poly.c_2y = p2y;
    fov_poly.c_3x = p3x;
    fov_poly.c_3y = p3y;
    fov_poly.c_4x = p4x;
    fov_poly.c_4y = p4y;
}

void WiseCameraInfo::set_fov_di(double dov, double los, double aov, double x_max, double y_max)
{
    fov_type = DIRECTIONAL;
    //camera position
    fov_di.c_px = pos_x;
    fov_di.c_py = pos_y;

    //orientation
    fov_di.los = los;
    fov_di.dov = dov;
    fov_di.aov = aov;

    // find coordinate of point v of vector pv: set a direction for the camera
    // node that can rotate their camera will update their lineOfSight during the simulation

    double lineOfSight = (los * 2 * PI) / 360; //degrees to radians
    fov_di.v.x=dov*cos(lineOfSight)+pos_x;
    fov_di.v.y=dov*sin(lineOfSight)+pos_y;

    // find Triangle coordinates
    double angleOfSight = (aov * 2 * PI) / 360; //degrees to radians
    double h = dov*sin(angleOfSight);
    double d = dov*cos(angleOfSight);

    fov_di.c_bx = fov_di.v.x + h*(fov_di.v.y - pos_y)/d;
    fov_di.c_by = fov_di.v.y - h*(fov_di.v.x - pos_x)/d;

    fov_di.c_cx = fov_di.v.x - h*(fov_di.v.y - pos_y)/d;
    fov_di.c_cy = fov_di.v.y + h*(fov_di.v.x - pos_x)/d;

    //check value range (of image limits)
    if (fov_di.c_cx < 0) fov_di.c_cx = 0;
    if (fov_di.c_cy < 0) fov_di.c_cy = 0;
    if (fov_di.c_bx < 0) fov_di.c_bx = 0;
    if (fov_di.c_by < 0) fov_di.c_by = 0;

    if (fov_di.c_cx > x_max) fov_di.c_cx = x_max;
    if (fov_di.c_cy > y_max) fov_di.c_cy = y_max;
    if (fov_di.c_bx > x_max) fov_di.c_bx = x_max;
    if (fov_di.c_by > y_max) fov_di.c_by = y_max;

    fov_di.min_x = std::min(fov_di.c_px, std::min(fov_di.c_cx, fov_di.c_bx));
    fov_di.max_x = std::max(fov_di.c_px, std::max(fov_di.c_cx, fov_di.c_bx));
    fov_di.min_y = std::min(fov_di.c_py, std::min(fov_di.c_cy, fov_di.c_by));
    fov_di.max_y = std::max(fov_di.c_py, std::max(fov_di.c_cy, fov_di.c_by));

    fov_di.vertex.clear();
    fov_di.vertex.push_back(cvPoint(fov_di.c_px,fov_di.c_py));
    fov_di.vertex.push_back(cvPoint(fov_di.c_bx,fov_di.c_by));
    fov_di.vertex.push_back(cvPoint(fov_di.c_px,fov_di.c_py));
}

#endif // __WiseCameraInfo_h__
