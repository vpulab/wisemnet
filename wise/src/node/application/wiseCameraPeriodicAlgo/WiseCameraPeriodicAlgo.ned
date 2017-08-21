// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the template for a periodic algorithm that provides an interface
//  to develop algorithms such as WiseCameraICF, WiseCameraKCF,...
//
//  This template iteratively performs the following operations (modeled as a finite-state-machine):
//          1. First performs sensing
//          2. Second processes the sensed data
//          3. Third performs communication with other cameras, if needed
//
//  This template provides also a synchronization in the network initialization
//          1. Set the running parameters of each camera (see the *.ini files)
//          2. Discovery of neighbors (i.e. cameras that can exchange data) by:
//              - FOV spatial overlap
//              - Communication range
//          3. Iterative sensing, processing & comms until the simulation is finished
//
//  Moreover, this template also provides synchronous/asynchronous sensing
//  by means of the parameter 'sensing_mode':
//          - _sensing_mode = IDEAL; //frames captured each 'sampling_time', does not consider processing time
//          - _sensing_mode = REAL_PERIOD; //frames captured each 'sampling_time', considers processing time
//          - _sensing_mode = REAL_DEMAND; //frames captured after processing, considers processing time
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

package node.application.wiseCameraPeriodicAlgo;

moduleinterface WiseCameraPeriodicAlgo extends node.application.wiseCameraApplication.WiseCameraApplication {

parameters:
	double sampling_time;
	double sample_lifetime;
	string sensing_mode; //"periodic" or "on-demand"
	
	double resize;	
	bool show_results;		
}


