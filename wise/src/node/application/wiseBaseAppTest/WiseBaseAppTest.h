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
 * \file WiseBaseAppTest.cc
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header file for the WiseBaseAppTest class
 * \version 1.4
 */

#ifndef __WISEBASEAPP_TEST_H__
#define __WISEBASEAPP_TEST_H__

#include <wise/src/node/application/wiseBaseApp/WiseBaseApp.h>
#include <fstream>

/*! \class WiseBaseAppTest
 *  \brief This class tests the template WiseBaseApp
 *
 *  The class implements a basic functionality test to send packets
 *  to network, receive data and perform sensor readings. This class must
 *  be used to test the correct installation of WiseMnet.
 *
 */
class WiseBaseAppTest : public WiseBaseApp {
private:

public:

protected:
	void startup();
    void finishSpecific();
    void timerFiredCallback(int);
    void handleSensorReading(WiseSensorManagerMessage *);
    void fromNetworkLayer(WiseBaseAppPacket *, const char *, double, double);
    void handleDirectApplicationMessage(WiseBaseAppPacket *){};
};
#endif // __WISEBASEAPP_TEST_H__
