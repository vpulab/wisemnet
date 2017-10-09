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

/**
 * \file WiseCameraPeriodicApp.h
 * \author Juan C. SanMiguel (2017)
 * \brief Header file for the WiseCameraPeriodicApp class
 * \version 1.4
 */

#ifndef __WISECAMERAPERIODICAPP_H__
#define __WISECAMERAPERIODICAPP_H__

#include <wise/src/utils/WiseGTreader.h> //ground-truth reader
#include <wise/src/node/application/wiseCameraApp/WiseCameraApp.h>
#include <wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h> // constants & types
#include <vector>
#include <map>

/*! \class WiseCameraPeriodicApp
 *  \brief This class implements the template for a periodic execution of three tasks: sensing, processing & communication.
 *
 *   - At initialization, the topology for vision and comms can be set via the NED parameter 'neighbourDiscoverCOM' & 'neighbourDiscoverFOV'
 *   - A finite-state-machine implements the transitions between the three tasks (sensing, processing & communication)
 *   - The frequency for acquiring new samples (eg, frames) is managed by the NED parameter 'sampling_time'
 *   - The consumption of each tasks is considered by the WiseResourceManager module.

 *   This template iteratively performs the following operations (modeled as a finite-state-machine):
 *          1. First performs sensing
 *          2. Second processes the sensed data
 *          3. Third performs communication with other cameras, if needed
 *
 *  This template provides also a synchronization in the network initialization
 *          1. Set the running parameters of each camera (see the *.ini files)
 *          2. Discovery of neighbors (i.e. cameras that can exchange data) by:
 *              - FOV spatial overlap
 *              - Communication range
 *          3. Iterative sensing, processing & comms until the simulation is finished
 *
 *  Moreover, this template also provides synchronous/asynchronous sensing
 *  by means of the parameter 'sensing_mode':
 *          - _sensing_mode = IDEAL; //frames captured each 'sampling_time', does not consider processing time
 *          - _sensing_mode = REAL_PERIOD; //frames captured each 'sampling_time', considers processing time
 *          - _sensing_mode = REAL_DEMAND; //frames captured after processing, considers processing time
 *
 */
class WiseCameraPeriodicApp: public WiseCameraApp {

protected:
    std::map<int,std::string> _state_str, _alarm_str;  //!< associated strings to the fsm states and alarms (to print out in cmd)
    std::map<int,cv::Scalar> _colorList; //!< associated list of colors for plotting

    //sensing settings
    sen_mode_type_t _sensing_mode;      //!< Defines the mode for sensing frames
    unsigned long _step_counter;        //!< counter for the number of times the data is analyzed by the algorithm
    double _sampling_time;              //!< frequency to get new samples (in secs) from physical process (through SensorDeviceManager)
    double _sample_lifetime;            //!< Lifetime in secs of the captured samples
    double _sampling_end2start_time;    //!< Time to start next sampling stage after "sample_lifetime" expired
    double _lastSenTime;

    //buffer settings
    sample_buffer_type_t _buf;           //!< Structure to store received data
    bool _databuf_ready;                //!< FLAG to indicate that new data has arrived from the sensing module
	bool _network_ready;                //!< FLAG to indicate that comms and fov graphs of the network are computed
	bool _running;                      //!< FLAG to indicate that processing is currently being done

    //execution control settings
    fsm_app_state_t _fsm_state;      //!< FSM that defines the current state of the application layer

    //log settings
    bool _logResourceData;           //!< FLAG to enable/disable the log for employed resources

    //statistics collectors
    double _time_atsample,_time_pkt_processing; //!< time for processing sensed data and packets
	double _bytesTXround, _bytesRXround;        //!< number of bytes TX/RX for each round of the FSM
	double _bytesTXprev,_bytesRXprev;

	//ground-truth settings
	std::string _filenameGT;    //!< Filename with the ground-truth data
	std::string _formatGT;      //!< Format of the ground-truth data
	WiseGTreader *_gtreader;    //!< Class to process ground-truth data and make it available at the application layer
	bool _show_gtruth;          //!< FLAG to enable/disable the display of ground-truth data
	std::ostringstream _winGT;  //!< Windonw name to display ground-truth data

	//visualization settings
	bool _pause_execution;      //!< FLAG to pause the execution for each iteration
	bool _pause_place_GUI;      //!< FLAG to pause the execution only at the beginning
	double _displayWinScale;    //!< Scale factor of all display windows
	int _pause_executionID;     //!< ID of the camera/node required to be paused during execution (used jointly with "_pause_execution")

protected:
	void startup();
	void startup_sensing();
	void startup_gtruth();
	void startup_logs();
	void finishSpecific();
	void fromNetworkLayer(WiseBaseAppPacket *, const char *, double, double);
	void handleSensorReading(WiseCameraMessage *);
	void timerFiredCallback(int index);

	void send_message(WiseBaseAppPacket*);
	void send_message(WiseBaseAppPacket*, const std::string&);

	int send_messageNeighboursCOM(WiseBaseAppPacket*);
    int send_messageNeighboursFOV(WiseBaseAppPacket*);

    void fsm_app(sample_type_t t, bool restart = false); //!< Logic for jumping between the states of the algorithm
    bool check_graph_completion(); //!< Checks whether all network nodes have completed the discovery of the COM and FOV graphs
    void display_gtruth();

    //Functions to be defined in sub-classes (mandatory)
    virtual void at_timer_fired(int index) = 0;     //!< Response to alarms generated by specific algorithm. To define in superclass (mandatory)
	virtual void at_startup() = 0 ;                 //!< Initialize internal variables. To define in sub-classes for each specific algorithm (mandatory)
	virtual void at_finishSpecific() = 0;           //!< Release resources. To define in sub-classes for each specific algorithm (mandatory)
	virtual bool at_init() = 0;                     //!< Initialize resources based on sampled data. To define in sub-classes for each specific algorithm (mandatory)
	virtual bool at_sample() = 0;                   //!< Operations for processing each sample. To define in sub-classes for each specific algorithm (mandatory)
	virtual bool at_end_sample() = 0;               //!< Operations after processing each sample. To define in sub-classes for each specific algorithm (mandatory)
    virtual void make_measurements(const std::vector<WiseTargetDetection>&) = 0 ; //!< Conversion of camera detections into ordered lists of measurements for tracking. To define in sub-classes for each specific algorithm (mandatory)
	virtual bool process_network_message(WiseBaseAppPacket *m) = 0 ; //!< Operations for processing each packet from network. To define in sub-classes for each specific algorithm (mandatory)
    virtual void handleDirectApplicationMessage(WiseBaseAppPacket *) = 0; //!< Process a received packet from a direct node-to-node links (to be implemented in superclasses of WiseBaseApp)
};
#endif // __WISECAMERAPERIODICAPP_H__
