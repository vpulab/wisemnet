// *****************************************************************************************
// Copyright (C) 2011 Christian Nastasi, 2017 Juan C. SanMiguel and Andrea Cavallaro
// You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
// license (see the attached LICENSE_WISE file).
//
// This file is part of the WiseMnet simulator
//
// Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// Please cite the following reference when publishing results obtained with WiseMnet:
//   J. SanMiguel & A. Cavallaro,
//   "Networked Computer Vision: the importance of a holistic simulator",
//   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
// *****************************************************************************************

/**
 * \file WiseCameraInfo.h
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header/source file for the WiseCameraInfo class
 * \version 1.4
 */

#ifndef __WISECAMERAINFO_H__
#define __WISECAMERAINFO_H__

#include <opencv.hpp>
#include <math.h>

#ifndef PI
#define PI 3.14159265359
#endif

/*! \class WiseCameraInfo
* \brief Class to describe the 2D model for the camera's FOV
*
* This class is meant to provide a range of 2D models for defining the Field
* of View (FOV) of cameras. Currently, it supports two FOV types:
* - directional (triangular and polygonal shapes) \n
* - omnidirectional (rectangular and square shapes)
*
* TODO: extend this class for 3D models
*
*/
class WiseCameraInfo {
public:

    /**
    * \brief Type of Field of View (FOV)
    */
	typedef enum {
		NONE = 0,       //!< No 2D model available
		BOUNDING_BOX,   //!< Boundingbox 2D model (omnidirectional FOV)
		POLYGON,        //!< Polygonal 2D model (directional FOV)
		DIRECTIONAL,    //!< Triangular 2D model (directonal FOV)
		REAL,           //!< No description provided. A video file is assumed where the 2D model cannot be extracted
	} fov_t;

public:

	/**
	 * \brief Description for omnidirectional Fields of View via bounding box shapes
	 */
	struct fov_bb_t {
		double c_x;     //!< Camera center 2D x-coordinate in the common ground-plane
		double c_y;     //!< Camera center 2D y-coordinate in the common ground-plane
		double width;   //!< Camera FOV 2D width in the common ground-plane
		double height;  //!< Camera FOV 2D height in the common ground-plane
		double max_x;   //!< Camera maximum 2D x-coordinate in the common ground-plane
		double min_x;   //!< Camera minimum 2D x-coordinate in the common ground-plane
		double max_y;   //!< Camera maximum 2D y-coordinate in the common ground-plane
		double min_y;   //!< Camera minimum 2D y-coordinate in the common ground-plane
	public:
		fov_bb_t() : c_x(0), c_y(0), width(0), height(0), max_x(0), min_x(0), max_y(0), min_y(0) {} ;
		fov_bb_t(double x, double y) : c_x(x), c_y(y), width(0), height(0), max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	};

	/**
	 * \brief Description for directional Fields of View via polygonal shapes with four points
	 */
	struct fov_poly_t {
	        double c_x;  //!< 2D Camera center x-coordinate in the common ground-plane
	        double c_y;  //!< 2D Camera center y-coordinate in the common ground-plane
	        double c_1x; //!< 2D x-position of the first point in the common ground-plane
            double c_1y; //!< 2D y-position of the first point in the common ground-plane
            double c_2x; //!< 2D x-position of the second point in the common ground-plane
            double c_2y; //!< 2D y-position of the second point in the common ground-plane
            double c_3x; //!< 2D x-position of the third point in the common ground-plane
            double c_3y; //!< 2D y-position of the third point in the common ground-plane
            double c_4x; //!< 2D x-position of the fourth point in the common ground-plane
            double c_4y; //!< 2D y-position of the fourth point in the common ground-plane

            double max_x;   //!< Camera maximum 2D x-coordinate in the common ground-plane
            double min_x;   //!< Camera minimum 2D x-coordinate in the common ground-plane
            double max_y;   //!< Camera maximum 2D y-coordinate in the common ground-plane
            double min_y;   //!< Camera minimum 2D y-coordinate in the common ground-plane

	    public:
            fov_poly_t() : c_x(0), c_y(0), c_1x(0), c_1y(0), c_2x(0), c_2y(0), c_3x(0), c_3y(0), c_4x(0), c_4y(0) {} ;
            fov_poly_t(double x, double y) : c_x(x), c_y(y), c_1x(0), c_1y(0), c_2x(0), c_2y(0), c_3x(0), c_3y(0), c_4x(0), c_4y(0) {} ;
	    };


	/**
     * \brief Description for directional Fields of View via triangular shapes
     */
	struct fov_di_t {

            // Camera center
            double c_px; //!< 2D x-position of the camera's FOV (in pixels) in the common ground-plane
            double c_py; //!< 2D y-position of the camera's FOV (in pixels) in the common ground-plane

            // Representation of the FOV with angles
            double dov; //!< 2D depth of view (length in c_vxy direction) of the camera's FOV (in pixels)
            double los; //!< 2D lineOfSigth of the camera's FOV (degrees)
            double aov; //!< 2D angle of view (angle) of the camera's FOV wrt (degrees)

            // Representation of the FOV with three points (ie, as a triangle)
            double c_cx; //!< 2D x-position of the second point in the common ground-plane
            double c_cy; //!< 2D y-position of the second point in the common ground-plane
            double c_bx; //!< 2D x-position of the third point in the common ground-plane
            double c_by; //!< 2D y-position of the third point in the common ground-plane

            double max_x;   //!< Camera maximum 2D x-coordinate in the common ground-plane
            double min_x;   //!< Camera minimum 2D x-coordinate in the common ground-plane
            double max_y;   //!< Camera maximum 2D y-coordinate in the common ground-plane
            double min_y;   //!< Camera minimum 2D y-coordinate in the common ground-plane

            cv::Point v;
            std::vector<cv::Point> vertex;

	    public:
	        fov_di_t() : c_px(0), c_py(0), dov(0), los(0), aov(0), c_cx(0), c_cy(0), c_bx(0), c_by(0), max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	        fov_di_t(double x, double y) : c_px(x), c_py(y), dov(0), los(0), aov(0),   c_cx(0), c_cy(0),  c_bx(0), c_by(0),  max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	        fov_di_t(double x, double y, double dov, double los, double aov) : c_px(x), c_py(y), dov(dov), los(los), aov(aov), c_cx(0), c_cy(0),  c_bx(0), c_by(0),  max_x(0), min_x(0), max_y(0), min_y(0) {} ;
	    };

private: 
	double pos_x;           //!< 3D Camera location x-coordinate in the network/world
	double pos_y;           //!< 3D Camera location y-coordinate in the network/world
	double pos_z;           //!< 3D Camera location z-coordinate in the network/world
	fov_t fov_type;         //!< Type of FOV model
	fov_bb_t fov_bb;        //!< Model for omnidirectional FOV (bounding box shape)
	fov_di_t fov_di;        //!< Model for directional FOV (triangular shape)
	fov_poly_t fov_poly;    //!< Model for directional FOV (polygonal shape)
	bool available2Dmodel;

public:
	int id;

	inline void get_position(double&, double&, double&) const;
	inline fov_t get_fov_type() const {return fov_type;};
	inline void get_fov_bb(fov_bb_t& fov) const {fov = fov_bb;};
	inline void get_fov_di(fov_di_t& fov) const {fov = fov_di;};
	inline void get_fov_poly(fov_poly_t& fov) const {fov = fov_poly;};

private:
	WiseCameraInfo() : pos_x(0), pos_y(0), pos_z(0), fov_type(NONE), fov_bb(0, 0) {};

	inline void set_position(double, double, double);
	inline void set_fov_bb(double, double, double x_min, double y_min, double x_max, double y_max);
	inline void set_fov_di(double, double, double aov,double x_min, double y_min, double x_max, double y_max);
	inline void set_fov_poly(double, double, double, double,double, double,double, double);

public:
	//friend class WiseBaseSensorManager;
	friend class WiseCameraManager;
	friend class WiseCameraApp;
};


/*
 * \brief Method to get the current 3D position of the camera node
 *
 * \param[in,out] x 3D Camera location x-coordinate in the network/world
 * \param[in,out] y 3D Camera location y-coordinate in the network/world
 * \param[in,out] z 3D Camera location z-coordinate in the network/world
 */
void WiseCameraInfo::get_position(double &x, double &y, double &z) const
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
}

/*
 * \brief Method to set the current 3D position of the camera node
 *
 * \param[in] x 3D Camera location x-coordinate in the network/world
 * \param[in] y 3D Camera location y-coordinate in the network/world
 * \param[in] z 3D Camera location z-coordinate in the network/world
 */
void WiseCameraInfo::set_position(double x, double y, double z)
{
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

/*
 * \brief Method to set the 2D bounding box model (omnidirectional FOV)
 *
 * \param w  Camera FOV 2D width in the common ground-plane
 * \param h  Camera FOV 2D heigth in the common ground-plane
 * \param x_min Camera minimum 2D x-coordinate in the common ground-plane
 * \param y_min Camera minimum 2D y-coordinate in the common ground-plane
 * \param x_max Camera maximum 2D x-coordinate in the common ground-plane
 * \param y_max Camera maximum 2D y-coordinate in the common ground-plane
 */
void WiseCameraInfo::set_fov_bb(double w, double h, double x_min, double y_min,double x_max, double y_max)
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
    if (fov_bb.min_x < x_min)
        fov_bb.min_x = x_min;
    if (fov_bb.min_y < y_min)
        fov_bb.min_y = y_min;
    if (x_max > 0 && fov_bb.max_x > x_max)
         fov_bb.max_x = x_max;
    if (y_max > 0 && fov_bb.max_y > y_max)
         fov_bb.max_y = y_max;
}

/*
 * \brief Method to set the 2D polygon model (directional FOV)
 *
 * \param p1x 2D x-position of the first point in the common ground-plane
 * \param p1y 2D y-position of the first point in the common ground-plane
 * \param p2x 2D x-position of the second point in the common ground-plane
 * \param p2y 2D y-position of the second point in the common ground-plane
 * \param p3x 2D x-position of the third point in the common ground-plane
 * \param p3y 2D y-position of the third point in the common ground-plane
 * \param p4x 2D x-position of the fourth point in the common ground-plane
 * \param p4y 2D y-position of the fourth point in the common ground-plane
 */
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

/*
 * \brief Method to set the 2D triangle model (directional FOV)
 *
 * \param doh  2D depth of view (length in c_vxy direction) of the camera's FOV (in pixels)
 * \param los 2D lineOfSigth of the camera's FOV (degrees)
 * \param aov 2D angle of view (angle) of the camera's FOV wrt (degrees)
 * \param x_min Camera minimum 2D x-coordinate in the common ground-plane
 * \param y_min Camera minimum 2D y-coordinate in the common ground-plane
 * \param x_max Camera maximum 2D x-coordinate in the common ground-plane
 * \param y_max Camera maximum 2D y-coordinate in the common ground-plane
 */
void WiseCameraInfo::set_fov_di(double dov, double los, double aov,double x_min, double y_min, double x_max, double y_max)
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
    if (fov_di.c_cx < x_min) fov_di.c_cx = x_min;
    if (fov_di.c_cy < y_min) fov_di.c_cy = y_min;
    if (fov_di.c_bx < x_min) fov_di.c_bx = x_min;
    if (fov_di.c_by < y_min) fov_di.c_by = y_min;

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
    fov_di.vertex.push_back(cvPoint(fov_di.c_cx,fov_di.c_cy));
    fov_di.vertex.push_back(cvPoint(fov_di.c_px,fov_di.c_py));
}

#endif // __WISECAMERADESCRIPTOR_H__
