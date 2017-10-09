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
 * \file WiseCameraApp.cc
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header file for the WiseCameraApp class
 * \version 1.4
 */
#include <wise/src/node/application/wiseCameraApp/WiseCameraApp.h>
#include <wise/src/utils/WiseDebug.h> //for logs/debug

#define perr_app(m) error("\n[WiseCamApp]:\n " m)  // Error messages from the application layer
#define perr(m) error(m)                           // Error messages from the node itself

/* \brief Initialization of resources for WiseCameraApp class.
 *
 * This method is re-implemented in startup() method of derived superclasses. However,
 * WiseCameraApp::startup() should be called in startup() of superclass to compute the
 * Vision graph, thus making it available for further processing.
 * The class WiseCameraPeriodicApp already contains this call to WiseCameraApp::startup(),
 * so there is no need of calling this function if the application developed derives from
 * WiseCameraPeriodicApp.
 */
void WiseCameraApp::startup()
{
    WISE_DEBUG_31("WiseCameraApp::startup() called");

	cModule *m = getParentModule()->getSubmodule("SensorManager");
	WiseCameraManager *c = check_and_cast<WiseCameraManager*>(m);
	_cam_info = c->get_camera_info();

	_camID = hasPar("camID") ? par("camID") : "";

	if (_camID.compare("")==0)
	    _camID = std::to_string(self);

	//compute the VISION graph to determine overlapped cameras
	_neighborDiscoverFOVoverlap = hasPar("findOverlappedFOV") ? par("findOverlappedFOV") : true;
	_neighborDiscoverFOVCompleted = false;

	//TODO: discover FOV neighbors by projecting 3D data. Currently only for 2D data
	if (_neighborDiscoverFOVoverlap && _cam_info.available2Dmodel==true)
	    calculate_overlapping_2Dfovs(_cam_info);

	_neighborDiscoverFOVCompleted=true; //we indicate an empty neighborhood

	WiseCameraInfo::fov_bb_t fov;
	c->get_camera_info().get_fov_bb(fov);
}

/*
 * \brief Method for specific resource destroy (variables and structures) after WiseBaseApp::finish()
 */
void WiseCameraApp::finishSpecific()
{
    // This function is called when simulation is finishing
    WISE_DEBUG_31("WiseCameraApp::finishSpecific() called");

    //destroy base class resources
    WiseBaseApp::finish();
}

/*
 * \brief Method to request data from the sensing module
 *
 *  Method to request data from the sensing module. A message is
 *  generated and sent to the "sensorManager" via the associated
 *  gate (see Node.ned). The "sensorManager" can contain a variable
 *  number of sensors which are referenced by "index".
 *  This method overrides "requestSensorReading" from WiseBaseApp class.
 *
 * \param index Identifier for the sensor to be requested
 */
void WiseCameraApp::requestSensorReading(int index)
{
    WISE_DEBUG_31("WiseCameraApp::requestSensorReading() called");

	WiseCameraMessage *reqMsg = new WiseCameraMessage("application-to-WiseCameraManager (sample request)", SENSOR_READING_MESSAGE);
	reqMsg->setSensorIndex(index);
	send(reqMsg, "toSensorDeviceManager");
}

/*
 * \brief Method to handle data received from the sensor
 *
 * Method to handle data received from the sensor after a request
 * sensor reading. This function must extract the relevant data from
 * the received message and make it available for the application layer.
 * This method extends the "handleSensorReading" method of the WiseBaseApp class.
 *
 * \param msg Message containing the sensed data
 */
void WiseCameraApp::handleSensorReading(WiseSensorManagerMessage *msg)
{
    WISE_DEBUG_31("WiseCameraApp::handleSensorReading(msg) called");

	WiseCameraMessage *cam_msg = check_and_cast<WiseCameraMessage*>(msg);
	handleSensorReading(cam_msg);
}

/*
 * \brief Method to determine cameras with overlapped fields of view
 *
 * This method perfoms a 2D geometrical analysis to build the co-visibility
 * graph of the network by determining which cameras have overlapped fields
 * of view (FOVs) with the current own FOV of the node/camera. Such overlapping
 * is based on projecting all FOVs to a common ground-plane and computing the
 * intersection among projections.
 *
 * FOV data from other cameras is automatically gathered by direct access to
 * each camera without exchanging packets/messages.
 *
 * Currently all processing is based on 2D analysis where FOVs can defined manually
 * by the user or computed automatically by external calibration data.
 *
 * TODO: extend this function to 3D overlapping FOVs
 * TODO: implement a network protocol to avoid direct access to each camera's FOV description
 *
 * \param a Description of own FOV
 */
void WiseCameraApp::calculate_overlapping_2Dfovs(const WiseCameraInfo &a)
{
    WISE_DEBUG_31("WiseCameraApp::calculate_overlapping_2Dfovs(...) called");

    //estimating overlapped FOVs restricted to 2D FOV models
    //since it can be easily done with simple 2D geometry
    _neighborsFOVoverlap.clear(); //clear the list of overlapped FOVs

    //Compute an image representing the camera FOV: 255(inside), 0(outside)
    cv::Mat m1(1000,1000, CV_8UC1, cv::Scalar(0,0,0));
    switch(a.fov_type) {

        case WiseCameraInfo::BOUNDING_BOX:
        {
            WiseCameraInfo::fov_bb_t mine;
            a.get_fov_bb(mine);

            cv::Point pt1 = cv::Point(mine.min_x, mine.min_y);
            cv::Point pt2 = cv::Point(mine.max_x, mine.max_y);
            cv::rectangle(m1, pt1, pt2, cv::Scalar(255,255,255),CV_FILLED);
            break;
        }
        case WiseCameraInfo::DIRECTIONAL:
        {
            WiseCameraInfo::fov_di_t mine_;
            a.get_fov_di(mine_);
            const cv::Point *pts = (const cv::Point*) (cv::Mat(mine_.vertex)).data;
            int npts = (cv::Mat(mine_.vertex)).rows;
            cv::fillPoly(m1, &pts,&npts, 1,cv::Scalar(255,255,255));
            break;
        }
        default:
            break;
    }

	// Access other nodes information (through Omnet's modules)
	for (int i = 0; i < n_nodes; i++) {
		if (i == self)	
			continue;

		//get the FOV descriptor
		cModule *m = getParentModule()->getParentModule(); // m=SN
		m = m->getSubmodule("node", i)->getSubmodule("SensorManager");
		WiseCameraManager *c = check_and_cast<WiseCameraManager*>(m);

        cv::Mat m2(1000,1000, CV_8UC1, cv::Scalar(0,0,0));

		//check overlapping condition for BOUNDING_BOX
		if (a.fov_type == WiseCameraInfo::BOUNDING_BOX){
		    WiseCameraInfo::fov_bb_t other;
		    c->get_camera_info().get_fov_bb(other);

		    cv::Point pt1 = cv::Point(other.min_x, other.min_y);
		    cv::Point pt2 = cv::Point(other.max_x, other.max_y);
		    cv::rectangle(m2,pt1,pt2,cv::Scalar(255,255,255),CV_FILLED);

		}

		//check overlapping condition for DIRECTIONAL
		if (a.fov_type == WiseCameraInfo::DIRECTIONAL){
		    WiseCameraInfo::fov_di_t other;
		    c->get_camera_info().get_fov_di(other);

		    const cv::Point *pts = (const cv::Point*) (cv::Mat(other.vertex)).data;
		    int npts = (cv::Mat(other.vertex)).rows;

		    cv::fillPoly(m2, &pts,&npts, 1,cv::Scalar(255,255,255));
		}

		//cv::imshow("test1", m1);cv::waitKey(0);
		//cv::imshow("test2", m2);cv::waitKey(0);
		//cv::Mat res = m1.mul(m2);
		//cv::imshow("test3",res);cv::waitKey(0);
		//cv::waitKey(0);

        if (cv::sum(m1.mul(m2)).val[0] == 0)
            continue;

		neighbour_cam_t i_info;
		i_info.node_id = to_string(i);
		i_info.cam_info = c->get_camera_info();
		_neighborsFOVoverlap.push_back(i_info);
	}

	//create the list of nodes with overlapped FOV
	vector<neighbour_cam_t>::const_iterator n;
    for (n = _neighborsFOVoverlap.begin(); n != _neighborsFOVoverlap.end(); ++n)
        _connectivity_map_fov[n->node_id] = true;

	notifyNeighbourDiscoveredFOV();
}

/*
 * \brief Method to save all data computed and log it
 */
void WiseCameraApp::notifyNeighbourDiscoveredFOV()
{
    WISE_DEBUG_31("WiseCameraApp::notifyNeighbourDiscoveredFOV() called");

    // Print the neighbor list to the log file
    ostringstream os;

    os << "FOV: Neighbors Discovered!  LIST = [ ";
    vector<neighbour_cam_t>::const_iterator n;
    for (n = _neighborsFOVoverlap.begin(); n != _neighborsFOVoverlap.end(); ++n)
        os << n->node_id << " ";

    _neighborDiscoverFOVCompleted=true;
    WISE_DEBUG_31("WiseCameraApp::\t" << os.str() << "] neighboursFOV Discover COMPLETED");
}
