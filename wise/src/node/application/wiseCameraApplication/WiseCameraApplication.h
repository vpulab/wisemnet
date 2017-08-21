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

#ifndef __WISECAMERAAPPLICATION_H__
#define __WISECAMERAAPPLICATION_H__

#include "WiseBaseApplication.h"
#include "WiseCameraInfo.h"
#include "WiseCameraMessage_m.h"

/*! \class WiseCameraApplication
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
class WiseCameraApplication : public WiseBaseApplication {
protected:

   /*! \struct neighbour_cam_t
    *  \brief Detailed information for neigbour camera
    */
	struct neighbour_cam_t {
		std::string node_id;  //!< Camera ID
		WiseCameraInfo cam_info; //!< Detailed camera description
	};

protected:
	WiseCameraInfo camera_info; //!< Detailed camera description (own)
	std::vector<neighbour_cam_t> neighborsFOV; //!< Detailed information about neigbour cameras

	/*--- Vision graph (FOV)---*/
    bool neighbourDiscoverFOV; //!< FLAG to indicate that nodes are currently being discovered
    bool neighbourDiscoverFOVCompleted; //!< FLAG to indicate that nodes have been discovered (Vision graph)
    std::map<std::string, bool> connectivity_map_fov;//!< List of neigbourg IDs for Vision graph (as pairs <ID,status>)
    unsigned int max_NeighboursFOV; //!< Maximum number of neigbourgs (per camera node) in the network for FOV graph

protected:
	virtual void startup(); 
	virtual void finishSpecific();

	void requestSensorReading(int index = 0);

	virtual void handleSensorReading(WiseSensorManagerMessage *);
	virtual void handleSensorReading(WiseCameraMessage *) = 0; //!< Process a received WiseCameraMessage packet from the SensorManager (to be implemented in superclass of WiseCameraApplication)

private:
	void calculate_overlapping_fovs(const WiseCameraInfo&); //!< Calculates the spatial overlap between camera's FOV through direct links at the application layer
	void notifyNeighbourDiscoveredFOV(); //!< Notification of the Vision graph for each camera
};

#endif //__WISECAMERAAPPLICATION_H__
