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

#include "WiseCameraDetections.h"
#include "WiseCameraManager.h"
#include "WiseDebug.h"

//static WiseCameraHandler::Factory::Factory registrat("WiseMovingTargetMessage", WiseCameraDetections::creator);

//change for new gcc compiler versions (>4.5)
static WiseCameraHandler::Factory registrat("WiseMovingTargetMessage", WiseCameraDetections::creator);

WiseCameraDetections::WiseCameraDetections(const WiseCameraManager &m): WiseCameraHandler(m)
{
}

void WiseCameraDetections::initialize()
{
	pending_sample_reply = manager.get_num_processes();
	detections.clear();
}

WiseCameraMessage *WiseCameraDetections::process(WisePhysicalProcessMessage *msg)
{
	WISE_DEBUG_20("WiseCameraDetections::handleSample()");

	WiseMovingTargetMessage *event;
	event = check_and_cast<WiseMovingTargetMessage*>(msg); 
	WiseTargetBoundingBox t_bb = event->getBoundingBox();

	// NOTE: numProcess CANNOT be negative, checked before!
	if (pending_sample_reply == manager.get_num_processes())  
		detections.clear();
	if (!event->getVisible()) 
		goto finish_sample;
	{ // Scope Operator
	// world-to-CameraImagePlane mapping
	WiseTargetDetection d;
	if (manager.get_camera_info().get_fov_type() ==	WiseCameraInfo::BOUNDING_BOX)
	    mapping_bounding_box(t_bb, d);
	if (manager.get_camera_info().get_fov_type() == WiseCameraInfo::DIRECTIONAL)
	    mapping_directional(t_bb, d);

	if (d.valid) {
		WISE_DEBUG_20("           TargetID = " << event->getTargetID());
	}
	d.target_id = event->getTargetID();
	detections.push_back(d);
	} // Scope Operator

finish_sample:
	WiseCameraDetectionsMessage *smp = NULL;
	if (--pending_sample_reply == 0) {
		pending_sample_reply = manager.get_num_processes();
		smp = new WiseCameraDetectionsMessage("Camera Detection Meas.", SENSOR_READING_MESSAGE);
		smp->setCameraSampleType("WiseCameraDetections");
		smp->setDetectionsArraySize(detections.size());
		//vector<WiseTargetDetection>::const_iterator i;
		//for (i = detections.begin(); i != detections.end(); ++i)
		//	smp->setDetections(*i);
		for (unsigned i = 0; i != detections.size(); i++)
			smp->setDetections(i, detections[i]);
	}
	return smp;
}

#define CONST_TMP 1.0

void WiseCameraDetections::mapping_bounding_box(const WiseTargetBoundingBox &t, WiseTargetDetection &d)
{
	WiseCameraInfo::fov_bb_t fov;
	manager.get_camera_info().get_fov_bb(fov);
	// Save the ground truth (TRUE coordinates)
	d.true_bb_x_tl = t.x_tl;
	d.true_bb_y_tl = t.y_tl;
	d.true_bb_x_br = t.x_br;
	d.true_bb_y_br = t.y_br;
	// Skip BB out of the camera's FOV
	d.valid = false;
	if (t.x_tl > fov.max_x || t.x_br < fov.min_x)
		return;
	if (t.y_tl > fov.max_y || t.y_br < fov.min_y)
		return;
	// Add some gaussian noise to the view?
	double err_x = 0;
	double err_y = 0;

	//uniform, normal, exponential,...
	//double err_x = normal(0, measurementNoiseCov);
    //double err_y = normal(0, measurementNoiseCov);

	double view_x_tl = t.x_tl + err_x;
	double view_x_br = t.x_br + err_x;
	double view_y_tl = t.y_tl + err_y;
	double view_y_br = t.y_br + err_y;
	// Find overlapping between BB and the camera's FOV
	d.valid = true;
	view_x_tl = (view_x_tl >= fov.min_x) ? view_x_tl : fov.min_x;
	view_y_tl = (view_y_tl >= fov.min_y) ? view_y_tl : fov.min_y;
	view_x_br = (view_x_br <= fov.max_x) ? view_x_br : fov.max_x;
	view_y_br = (view_y_br <= fov.max_y) ? view_y_br : fov.max_y;
	// Translate the detected BB in image coordinates. (min_x,min_y)==(0,0)
	d.bb_x_tl = (unsigned) (view_x_tl - fov.min_x);
	d.bb_y_tl = (unsigned) (view_y_tl - fov.min_y);
	d.bb_x_br = (unsigned) (view_x_br - fov.min_x);
	d.bb_y_br = (unsigned) (view_y_br - fov.min_y);
	// Save also world coordinates
	d.ext_bb_x_tl = view_x_tl;
	d.ext_bb_y_tl = view_y_tl;
	d.ext_bb_x_br = view_x_br;
	d.ext_bb_y_br = view_y_br;

	WISE_DEBUG_20("DETECTION: CAM_"  << " @ (" << fov.c_x << ", " << fov.c_y << ", " << 0 << ")" << " FOV=[(" << fov.min_x << "," << fov.min_y << ") (" << fov.max_x << "," << fov.max_y << ")]");
	WISE_DEBUG_20("           Target -> tl=(" << t.x_tl << " , " << t.y_tl << ") br=(" << t.x_br << " , " << t.y_br << ")");
	WISE_DEBUG_20("           View   -> tl=(" << view_x_tl << " , " << view_y_tl << ") br=(" << view_x_br << " , " << view_y_br << ")");
	WISE_DEBUG_20("           Detect -> tl=(" << d.bb_x_tl << " , " << d.bb_y_tl  << ") br=(" << d.bb_x_br << " , " << d.bb_y_br << ")");
}

void WiseCameraDetections::mapping_directional(const WiseTargetBoundingBox &t, WiseTargetDetection &d)
{
    WiseCameraInfo::fov_di_t fov;
    manager.get_camera_info().get_fov_di(fov);
    // Save the ground truth (TRUE coordinates)
    d.true_bb_x_tl = t.x_tl;
    d.true_bb_y_tl = t.y_tl;
    d.true_bb_x_br = t.x_br;
    d.true_bb_y_br = t.y_br;
    // Skip BB out of the camera's FOV
    d.valid = false;

    //check if target is inside camera's FOV
    vector<vector<cv::Point> > contours;
    vector<cv::Point> points;
    points.clear();
    points.push_back(cvPoint(fov.c_px,fov.c_py));
    points.push_back(cvPoint(fov.c_cx,fov.c_cy));
    points.push_back(cvPoint(fov.c_bx,fov.c_by));
    points.push_back(cvPoint(fov.c_px,fov.c_py));
    contours.push_back(points);

    double dist = cv::pointPolygonTest(points, cvPoint(t.x_tl, t.y_tl), false);

    if (dist == -1) //the point lies outside the FOV (dist == 0, on the edge; dist == 1, inside)
        return;

    // Add some gaussian noise to the view?
    double err_x = 0;
    double err_y = 0;

    //uniform, normal, exponential,...
    //double err_x = normal(0, measurementNoiseCov);
    //double err_y = normal(0, measurementNoiseCov);

    double view_x_tl = t.x_tl + err_x;
    double view_x_br = t.x_br + err_x;
    double view_y_tl = t.y_tl + err_y;
    double view_y_br = t.y_br + err_y;
    // Find overlapping between BB and the camera's FOV
    d.valid = true;
    view_x_tl = (view_x_tl >= fov.min_x) ? view_x_tl : fov.min_x;
    view_y_tl = (view_y_tl >= fov.min_y) ? view_y_tl : fov.min_y;
    view_x_br = (view_x_br <= fov.max_x) ? view_x_br : fov.max_x;
    view_y_br = (view_y_br <= fov.max_y) ? view_y_br : fov.max_y;
    // Translate the detected BB in image coordinates. (min_x,min_y)==(0,0)
    d.bb_x_tl = (unsigned) (view_x_tl - fov.min_x);
    d.bb_y_tl = (unsigned) (view_y_tl - fov.min_y);
    d.bb_x_br = (unsigned) (view_x_br - fov.min_x);
    d.bb_y_br = (unsigned) (view_y_br - fov.min_y);
    // Save also world coordinates
    d.ext_bb_x_tl = view_x_tl;
    d.ext_bb_y_tl = view_y_tl;
    d.ext_bb_x_br = view_x_br;
    d.ext_bb_y_br = view_y_br;

    WISE_DEBUG_20("DETECTION: CAM_"  << " @ (" << fov.c_px << ", " << fov.c_py << ", " << 0 << ")" << " FOV=[(" << fov.min_x << "," << fov.min_y << ") (" << fov.max_x << "," << fov.max_y << ")]");
    WISE_DEBUG_20("           Target -> tl=(" << t.x_tl << " , " << t.y_tl << ") br=(" << t.x_br << " , " << t.y_br << ")");
    WISE_DEBUG_20("           View   -> tl=(" << view_x_tl << " , " << view_y_tl << ") br=(" << view_x_br << " , " << view_y_br << ")");
    WISE_DEBUG_20("           Detect -> tl=(" << d.bb_x_tl << " , " << d.bb_y_tl  << ") br=(" << d.bb_x_br << " , " << d.bb_y_br << ")");
}
