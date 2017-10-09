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
 * \file WiseCameraAppTest.h
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header file for the WiseCameraApp class
 * \version 1.4
 */
#ifndef __WISECAMERAAPPTEST_H__
#define __WISECAMERAAPPTEST_H__

#include <wise/src/node/application/wiseCameraApp/WiseCameraApp.h>

/*! \class WiseCameraAppTest
* @brief This class tests the template WiseCameraApp
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
class WiseCameraAppTest : public WiseCameraApp {
private:
	unsigned int detection_counter;

protected:
	void startup();
	void finishSpecific();
	void timerFiredCallback(int);
	void handleSensorReading(WiseCameraMessage *);
	void fromNetworkLayer(WiseBaseAppPacket *, const char *, double, double);
	void handleDirectApplicationMessage(WiseBaseAppPacket *){};
};
#endif // __WISECAMERAAPPTEST_H__
