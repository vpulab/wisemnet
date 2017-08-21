// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#include "WiseCameraApplication.h"
#include "WiseCameraManager.h"
#include "WiseDebug.h"

#define BASE_TRACE trace() << "WISECAMERA: "

/*! Initialization of resources for WiseCameraApplication class. \n This method is re-implemented
 * in startup() method of derived superclasses. However, WiseCameraApplication::startup() should
 * be called in startup() of superclass to compute the Vision graph, thus making it available
 * for further processing.\n
 * The class WiseCameraSimplePeriodicTracker already contains this call to WiseCameraApplication::startup(),
 * so there is no need of including this calling if the application developed derives from WiseCameraSimplePeriodicTracker.
 */
void WiseCameraApplication::startup() 
{
	WISE_DEBUG_3("WiseCameraApplication::startup()"); 

	cModule *m = getParentModule()->getSubmodule("SensorManager");
	WiseCameraManager *c = check_and_cast<WiseCameraManager*>(m);
	camera_info = c->get_camera_info();

	//compute the VISION graph (ie, overlapped cameras)
	neighbourDiscoverFOV = hasPar("neighbourDiscoverFOV") ? par("neighbourDiscoverFOV") : true;

	if (neighbourDiscoverFOV){
	    neighbourDiscoverFOVCompleted=false;
	    calculate_overlapping_fovs(camera_info);
	}
	else
	    neighbourDiscoverFOVCompleted=true; //we indicate an empty neighborhood

	WiseCameraInfo::fov_bb_t fov;
	c->get_camera_info().get_fov_bb(fov);
}

void WiseCameraApplication::finishSpecific() 
{
	WISE_DEBUG_3("WiseCameraApplication::finishSpecific()"); 
}

void WiseCameraApplication::requestSensorReading(int index)
{
	WISE_DEBUG_3("WiseCameraApplication::requestSensorReading()");

	WiseCameraMessage *reqMsg = new WiseCameraMessage("application-to-WiseCameraManager (sample request)", SENSOR_READING_MESSAGE);
	reqMsg->setSensorIndex(index);
	send(reqMsg, "toSensorDeviceManager");
}

void WiseCameraApplication::handleSensorReading(WiseSensorManagerMessage *msg) 
{
	WISE_DEBUG_3("WiseCameraApplication:handleSensorReading (WiseSensorManagerMessage *msg)");
	WiseCameraMessage *cam_msg = check_and_cast<WiseCameraMessage*>(msg);
	handleSensorReading(cam_msg);
}

void WiseCameraApplication::calculate_overlapping_fovs(const WiseCameraInfo &a)
{
    // TODO: Generalize to non-bounding-box FOV type
    WiseCameraInfo::fov_bb_t mine;
    a.get_fov_bb(mine);

    cv::Mat m1(1000,1000, CV_8UC1, cv::Scalar(0,0,0));
    if (a.fov_type == WiseCameraInfo::DIRECTIONAL){
        WiseCameraInfo::fov_di_t mine_;
        a.get_fov_di(mine_);

        const cv::Point *pts = (const cv::Point*) (cv::Mat(mine_.vertex)).data;
        int npts = (cv::Mat(mine_.vertex)).rows;
        cv::fillPoly(m1, &pts,&npts, 1,cv::Scalar(255,255,255));
    }

	neighborsFOV.clear();
	// Access other nodes information (through Omnet's modules)
	for (int i = 0; i < n_nodes; i++) {
		if (i == self)	
			continue;

        cModule *m = getParentModule()->getParentModule(); // m=SN
		m = m->getSubmodule("node", i)->getSubmodule("SensorManager");
		WiseCameraManager *c = check_and_cast<WiseCameraManager*>(m);

		//check overlapping condition for BOUNDING_BOX
		if (a.fov_type == WiseCameraInfo::BOUNDING_BOX){
		    WiseCameraInfo::fov_bb_t other;
		    c->get_camera_info().get_fov_bb(other);

            // check overlapping condition
            if (other.min_x > mine.max_x || other.max_x < mine.min_x)
                continue;
            if (other.min_y > mine.max_y || other.max_y < mine.min_y)
                continue;
		}

		//check overlapping condition for DIRECTIONAL
		if (a.fov_type == WiseCameraInfo::DIRECTIONAL){

		    WiseCameraInfo::fov_di_t other;
		    c->get_camera_info().get_fov_di(other);

		    cv::Mat m2(1000,1000, CV_8UC1, cv::Scalar(0,0,0));

		    const cv::Point *pts = (const cv::Point*) (cv::Mat(other.vertex)).data;
		    int npts = (cv::Mat(other.vertex)).rows;

		    cv::fillPoly(m2, &pts,&npts, 1,cv::Scalar(255,255,255));

		    //cv::imshow("test", m1);cv::waitKey(0);
		    //cv::imshow("test", m2);cv::waitKey(0);
		    //cv::Mat res = m1.mul(m2);
		    //cv::imshow("test",res);cv::waitKey(0);

		    if (cv::sum(m1.mul(m2)).val[0] == 0)
		        continue;
		}

		ostringstream os;
		os << i;
		neighbour_cam_t i_info;
		i_info.node_id = os.str();
		i_info.cam_info = c->get_camera_info();
		neighborsFOV.push_back(i_info);
	}

	//create the list of nodes with overlapped FOV
	vector<neighbour_cam_t>::const_iterator n;
    for (n = neighborsFOV.begin(); n != neighborsFOV.end(); ++n)
        connectivity_map_fov[n->node_id] = true;

	notifyNeighbourDiscoveredFOV();
}

void WiseCameraApplication::notifyNeighbourDiscoveredFOV()
{
    // Print the neighbor list to the log file
    ostringstream os;

    os << "FOV: Neighbors Discovered!  LIST = [ ";
    vector<neighbour_cam_t>::const_iterator n;
    for (n = neighborsFOV.begin(); n != neighborsFOV.end(); ++n)
        os << n->node_id << " ";

    neighbourDiscoverFOVCompleted=true;
    BASE_TRACE << os.str() << "] neighboursFOV Discover COMPLETED";
}/**/
