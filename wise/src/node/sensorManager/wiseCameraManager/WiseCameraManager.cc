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
#include "WiseUtils.h"

#include <algorithm>

using namespace std;

float angleBetween(const cv::Point2f &v1, const cv::Point2f &v2);
double angleDistance(double alpha_rad, double beta_rad);

Define_Module(WiseCameraManager);

WiseCameraManager::~WiseCameraManager()
{
        WISE_DEBUG_20("WiseCameraManager::~WiseCameraManager()");
	delete_handlers();
}

void WiseCameraManager::initialize()
{
        WISE_DEBUG_20("WiseCameraManager::initialize()");
	WiseBaseSensorManager::initialize();

	this->_cam_info.id = self;
	_calibType = par("calib_type").stringValue();
	_calibFile = par("calib_filename").stringValue();
	_calibFileMap = par("calib_world2map_filename").stringValue();
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
	        _cam_info.set_fov_bb(par("fov_bb_width"), par("fov_bb_height"), terrain->get_x_min(), terrain->get_y_min(),terrain->get_x_max(),terrain->get_y_max());

	    if (s == "directional")
	        _cam_info.set_fov_di(par("fov_di_dov"),par("fov_di_los"),par("fov_di_aov"), terrain->get_x_min(), terrain->get_y_min(),terrain->get_x_max(),terrain->get_y_max());
	}
	else
	{
	    //read xml calibration file
        _calibModel->fromXmlCalib(_calibFile); //camera calibration
        _calibModel->fromXmlMap(_calibFileMap);//mapping world-to-groundplane image (map to display)

        //get FOV limits in world coordinates
        double width  = _calibModel->width();
        double height = _calibModel->height();

        //farest points from the camera FOV
        std::vector<cv::Point2f> plist;
        double Xw=0,Yw=0;
        _calibModel->imageToWorld(1,1,0,Xw,Yw);         cv::Point2f p1=cv::Point2f(Xw,Yw); plist.push_back(p1);
        _calibModel->imageToWorld(width,1,0,Xw,Yw);     cv::Point2f p2=cv::Point2f(Xw,Yw); plist.push_back(p2);
        _calibModel->imageToWorld(1,height,0,Xw,Yw);    cv::Point2f p3=cv::Point2f(Xw,Yw); plist.push_back(p3);
        _calibModel->imageToWorld(width,height,0,Xw,Yw);cv::Point2f p4=cv::Point2f(Xw,Yw); plist.push_back(p4);

        //get the two farest points among these four
        cv::Point min_loc,max_loc;
        double min,max;
        cv::Mat dist = cv::Mat::zeros(4,1,CV_32F);
        for(int i = 0;i<4;i++)
            dist.at<float>(i,0) = cv::norm(cv::Mat(plist[i]),cv::Mat(cv::Point2f(_calibModel->cposx(),_calibModel->cposy())));

        //1st point
        cv::minMaxLoc(dist,&min,&max,&min_loc,&max_loc);
        cv::Point2f p1min = plist[min_loc.y];

        //2nd point
        dist.at<float>(min_loc.x,min_loc.y)=std::numeric_limits<float>::max(); //set to max value
        cv::minMaxLoc(dist,&min,&max,&min_loc,&max_loc);
        cv::Point2f p2min = plist[min_loc.y];

        //camera center in world coordinates
        cv::Point2f camW = cv::Point2f(_calibModel->cposx(), _calibModel->cposy());

         //float angle1 = 180/PI*angleBetween(cc, p1max);//angle corresponding to the 1st point
        float angle1 = angleBetween(camW, p1min);//angle corresponding to the 1st point (in radians)
        float angle2 = angleBetween(camW, p2min);//angle corresponding to the 2nd point (in radians)

        //angle/amplitude of view
        double aov = angleDistance(angle1,angle2)/2;

        //line of sight
        double Xmw=0,Ymw=0;
        _calibModel->imageToWorld(width/2,height/2,0,Xmw,Ymw);
        float los = angleBetween(camW, cv::Point(Xmw,Ymw));//angle corresponding to the FOV optical center (in radians)

        //depth of view
        double dov = sqrt((Xmw-camW.x)*(Xmw-camW.x) + (Ymw-camW.y)*(Ymw-camW.y));//depth of view

      //check if we have world-to-map calibration data
      double cposx=0,cposy=0,px=0,py=0,direction=0;
      if (_calibModel->worldToMapCoord(1.0,1.0,0.0,Xw,Yw) == true)
        {
            //world to map coordinates: projection
            _calibModel->worldToMapCoord(camW.x,camW.y,_calibModel->cposz(), cposx,cposy); //project camera center
            _calibModel->worldToMapCoord(Xmw,Ymw,0, px,py);                                //project mean point
            dov = sqrt((px-cposx)*(px-cposx) + (py-cposy)*(py-cposy));         //recompute depth of view
            direction = -1;
        }
        else
        {
            //otherwise, project to an image representing the world given by x/y min/max coordinates
            cposx = (_calibModel->cposx() - terrain->get_x_min());
            cposy = (_calibModel->cposy() - terrain->get_y_min());

            px = (Xmw - terrain->get_x_min());
            py = (Ymw - terrain->get_y_min());

            direction = 1;
        }

        std::cout << "Cam "<<self<<"cx="<<cposx<<" cy="<<cposy<<" dov="<<dov<<" los="<<180/PI*los<<" aov="<<180/PI*aov<<std::endl;
        //std::cout<<":worldcoords points-> p1="<<plist[0].x<<","<<plist[0].y<<" p2="<<plist[1].x<<","<<plist[1].y<<" p3="<<plist[2].x<<","<<plist[2].y<<" p4="<<plist[3].x<<","<<plist[3].y<<std::endl;

        //set camera position & orientation in the display map
        _cam_info.set_position(cposx,cposy,0);//position
        _cam_info.set_fov_di(dov,direction*180/PI*los,180/PI*aov, terrain->get_x_min(), terrain->get_y_min(),terrain->get_x_max(),terrain->get_y_max());//orientation
	}

	//Placing Camera on Terrain
	if (numProcesses < 0)
		opp_error("WiseCameraManager::initialize\n parameter numProcess CANNOT be negative");
	terrain->place_camera(_cam_info);
	init_handlers();
}

void WiseCameraManager::startup()
{
    WISE_DEBUG_20("WiseCameraManager::startup()");
}

//void WiseCameraManager::processSampleRequest(WiseSensorManagerMessage *req)
//{
//	WiseBaseSensorManager::processSampleRequest(req);
//}

void WiseCameraManager::handleSample(WisePhysicalProcessMessage *msg)
{
    WISE_DEBUG_20("WiseCameraManager::handleSample()");
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

//https://stackoverflow.com/questions/15888180/calculating-the-angle-between-points
float angleBetween(const cv::Point2f &v1, const cv::Point2f &v2)
{
    float direction = (v1.cross(v2) >= 0 ? 1.0 : -1.0);
    float angle = atan2(v2.y - v1.y, v2.x - v1.x);
    float angle2=angle;

    if (direction ==-1.0)
       angle2 = 2*PI + angle;
    else if (angle<0.0)
        angle2 = 2*PI + angle;

    //std::cout << "angle="<<180/PI*angle<<" angle2="<<180/PI*angle2<<" direction="<<direction<<std::endl;

    return angle2;/**/

}
double angleDistance(double alpha_rad, double beta_rad) {
       int alpha = 180/PI*alpha_rad;
       int beta = 180/PI*beta_rad;
       int phi = abs(beta - alpha) % 360;       // This is either the distance or 360 - distance
       int distance = phi > 180 ? 360 - phi : phi;
       return distance*PI/180;
   }
