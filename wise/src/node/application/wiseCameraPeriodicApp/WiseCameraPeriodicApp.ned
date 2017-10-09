// *****************************************************************************************
// Copyright (C) 2017 Juan C. SanMiguel and Andrea Cavallaro
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

//NED description for wiseCameraPeriodicApp interface
package node.application.wiseCameraPeriodicApp;

moduleinterface WiseCameraPeriodicApp extends node.application.wiseCameraApp.WiseCameraApp {

parameters:
    //log settings
    bool logResourceData; //!< FLAG to enable/disable the log for employed resources
    
    //sensing settings
    string sensing_mode; //!< Defines the mode for sensing frames
    double sampling_time;              //!< frequency to get new samples (in secs) from physical process (through SensorDeviceManager)
    double sample_lifetime;            //!< Lifetime in secs of the captured samples
    
	//ground-truth settings	
    string filenameGT;    //!< Filename with the ground-truth data
	string formatGT;      //!< Format of the ground-truth data	
	bool show_gtruth;          //!< FLAG to enable/disable the display of ground-truth data	
    
    //display settings
  	bool pause_execution;      //!< FLAG to pause the execution for each iteration
	bool pause_place_GUI;      //!< FLAG to pause the execution only at the beginning
	double displayWinScale;    //!< Scale factor of all display windows
	int pause_executionID;     //!< ID of the camera/node required to be paused during execution (used jointly with "_pause_execution"
}


