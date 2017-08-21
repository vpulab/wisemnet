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

#include "WiseCameraManager.h"
#include "WiseDebug.h"

#include <algorithm>

using namespace std;

Define_Module(WiseCameraManager);

WiseCameraManager::~WiseCameraManager()
{
	delete_handlers();
}

void WiseCameraManager::initialize()
{
	WiseBaseSensorManager::initialize();

	this->_cam_info.id = self;
	_calibType = par("calib_type").stringValue();
	_calibFile = par("calib_filename").stringValue();
	_calibModel = new Etiseo::CameraModel(_calibType);

	//double a = this->terrain->_xmin;
	if (_calibFile.compare("none") == 0)
	{
	    NodeLocation_type loc;
	    get_node_location(loc);
	    _cam_info.set_position(loc.x, loc.y, loc.z);
	    string s = par("fov_type");

	    const char *aux = par("type_src"); //"Video" or "Target"
	    _type_src = aux;

	    if (s == "bounding_box")
	        _cam_info.set_fov_bb(par("fov_bb_width"), par("fov_bb_height"), terrain->get_x_size(), terrain->get_y_size());

	    if (s == "directional")
	        _cam_info.set_fov_di(par("fov_di_dov"),par("fov_di_los"),par("fov_di_aov"), terrain->get_x_size(), terrain->get_y_size());
	}
	else
	{
	    //read xml calibration file
	    //cout << _calibFile << endl;
        _calibModel->fromXml(_calibFile);

        double posx=0,posy=0;
	    if (_calibType.compare("tsai") == 0)
	    {
            //double s = terrain->get_scale_factor();
            posx = (_calibModel->cposx() -terrain->get_x_min());
            posy = (_calibModel->cposy() -terrain->get_y_min());
	    }

	    if (_calibType.compare("homography") == 0)
        {
	        posx = terrain->get_x_min();
            posy = terrain->get_y_min();
        }
	    //compute the camera location
        //_cam_info.set_position(_calibModel->cposx(),_calibModel->cposy(),_calibModel->cposz());
        _cam_info.set_position(posx,posy,_calibModel->cposz());

        //compute the camera FOV
        //_cam_info.set_fov_di(par("fov_di_dov"),par("fov_di_los"),par("fov_di_aov"), terrain->get_x_size(), terrain->get_y_size());
        //_cam_info.set_fov_di(200,45,15, terrain->get_x_size(), terrain->get_y_size());

        double Xw_=0,Yw_=0,Xw0=0,Yw0=0,Xw1=0,Yw1=0;
        //two closest points to the camera
        _calibModel->imageToWorld(1,570,0, Xw0, Yw0);
        _calibModel->imageToWorld(700,570,0, Xw1, Yw1);

        _calibModel->imageToWorld(350,300,0, Xw_, Yw_);

        double p1x = Xw0 -terrain->get_x_min();
        double p1y = Yw0 -terrain->get_y_min();
        double p2x = Xw1 -terrain->get_x_min();
        double p2y = Yw1 -terrain->get_y_min();

        int angle0 = int(atan((posy-p1y)/(p1x-posx))*180.0/3.14);
        if (posy<p1y && posx>p1x)
            angle0 = angle0 -180;
        int angle1 = int(atan((posy-p2y)/(p2x-posx))*180.0/3.14);
        if (posy>p2y && posx>p2x)
           angle1 = angle1 + 180;
        if (posy<p2y && abs(angle1-90)<10)
           angle1 = angle1 - 180;

        double dov = sqrt((Yw_-posy)*(Yw_-posy) + (Xw_-posx)*(Xw_-posx));
        double los = (angle0+angle1)/2;
        double aov = (angle0-angle1)/2;
        _cam_info.set_fov_di(dov,-los,aov, terrain->get_x_size(), terrain->get_y_size());
	}

	//Placing Camera on Terrain
	if (numProcesses < 0)
		opp_error("WiseCameraManager::initialize\n parameter numProcess CANNOT be negative");
	terrain->place_camera(_cam_info);
	init_handlers();
}

void WiseCameraManager::startup()
{
	WISE_DEBUG_3("WiseCameraManager::startup()");
}

//void WiseCameraManager::processSampleRequest(WiseSensorManagerMessage *req)
//{
//	WiseBaseSensorManager::processSampleRequest(req);
//}

void WiseCameraManager::handleSample(WisePhysicalProcessMessage *msg)
{
	WISE_DEBUG_3("WiseCameraManager::handleSample()");

	const char *type = msg->getClassName();

    WiseCameraMessage *smp = get_handler(type)->process(msg);
    if (smp)
        send(smp, "toApplicationModule");
}

//! from image coordinate to world coordinate
void WiseCameraManager::imageToWorld(double Xi, double Yi, double Zw, double& Xw, double &Yw)
{
    if(!_calibModel->imageToWorld(Xi, Yi, Zw, Xw, Yw))
        opp_error("WiseCameraManager::imageToWorld\n error to compute imageToWorld coordinates");
}

//! from world coordinate to image coordinate
void WiseCameraManager::worldToImage(double Xw, double Yw, double Zw, double& Xi, double& Yi)
{
    if(!_calibModel->worldToImage(Xw, Yw, Zw, Xi, Yi))
        opp_error("WiseCameraManager::imageToWorld\n error to compute worldToImage coordinates");
}
