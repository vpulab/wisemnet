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
 * \file WiseCameraApp.h
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header file for the WiseCameraApp class
 * \version 1.4
 */
#ifndef __WISECAMERAAPP_H__
#define __WISECAMERAAPP_H__

#include <wise/src/node/application/wiseBaseApp/WiseBaseApp.h>         //template class
#include <wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h> //packet descriptor
#include <wise/src/node/application/wiseCameraApp/WiseCameraInfo.h>    //FOV's models

/*! \class WiseCameraApp
* @brief Base class for camera-based application
* 
* This class is meant to be used as a base class for camera-based application,
* in particular when a WiseCameraManager is connected to the application module.
*
* The class hides the interaction with the WiseCameraManager and exports an
* overload (specialized) version of handleSensorReading callback.
*
* The class provides a mechanism to calculate the camera-node neighborhood
* based on the overlapping field-of-view of adjacent cameras.
*/
class WiseCameraApp : public WiseBaseApp {
protected:

   /*! \struct neighbour_cam_t
    *  \brief Detailed information for neighbors of each camera
    */
	struct neighbour_cam_t {
		std::string node_id;        //!< Camera ID
		WiseCameraInfo cam_info;    //!< Detailed camera description
	};

protected:
	WiseCameraInfo _cam_info;       //!< Detailed camera description

	std::string _camID;

	/*--- Vision co-visibility graph (FOV)---*/
    bool _neighborDiscoverFOVoverlap;                   //!< FLAG to indicate that nodes are currently being discovered
    bool _neighborDiscoverFOVCompleted;                 //!< FLAG to indicate that nodes have been discovered (Vision graph)
    std::map<std::string, bool> _connectivity_map_fov;  //!< List of neighbors IDs for Vision graph (as pairs <ID,status>)
    std::vector<neighbour_cam_t> _neighborsFOVoverlap;  //!< Detailed information about neighbor cameras considering overlapped FOV
    unsigned int _max_neighborsFOV;                     //!< Maximum number of neighbors (per camera node) in the network for FOV graph

protected:
	virtual void startup(); 
	virtual void finishSpecific();

	void requestSensorReading(int index = 0);

	virtual void handleSensorReading(WiseSensorManagerMessage *);
	virtual void handleSensorReading(WiseCameraMessage *) = 0; //!< Process a received WiseCameraMessage packet from the SensorManager (to be implemented in superclass of WiseCameraApplication)

private:
	void calculate_overlapping_2Dfovs(const WiseCameraInfo&); //!< Calculates the spatial overlap between camera's FOV through direct links at the application layer
	void notifyNeighbourDiscoveredFOV(); //!< Notification of the Vision graph for each camera
};

#endif //__WISECAMERAAPP_H__
