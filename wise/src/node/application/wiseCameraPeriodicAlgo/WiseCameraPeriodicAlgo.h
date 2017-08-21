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

#ifndef __WiseCameraPeriodicAlgo_H__
#define __WiseCameraPeriodicAlgo_H__

#include <vector>
#include <map>
#include "WiseCameraApplication.h"
#include "WiseCameraDetectionsMessage_m.h"
#include "WiseCameraVideoMessage_m.h"
#include "WiseCameraPeriodicAlgoPacket_m.h"
#include "WiseDefinitionsTracking.h"

// Alarms handled by the periodic algorithm
const int ALARM_WAIT_GRAPH        = 0; //!< Periodic alarm to check completion of vision&comms graphs discovery
const int ALARM_SENSOR_SAMPLE     = 1; //!< Periodic alarm to request a new sample to SensorManager
const int ALARM_PROCESS_SAMPLE    = 2; //!< Periodic alarm to check new data to be processed

/*! \class WiseCameraPeriodicAlgo
 *  \brief This class implements the template for a periodic execution of three tasks: sensing, processing & communication.
 *
 *   - At initialization, the topology for vision and comms can be set via the NED parameter 'neighbourDiscoverCOM' & 'neighbourDiscoverFOV'
 *   - A finite-state-machine implements the transitions between the three tasks (sensing, processing & communication)
 *   - The frequency for acquiring new samples (eg, frames) is managed by the NED parameter 'sampling_time'
 *   - The consumption of each tasks is considered by the WiseResourceManager module.
 *
 */
class WiseCameraPeriodicAlgo : public WiseCameraApplication {

protected:

    /*! \enum sample_type_t
    *  Describes whether the samples obtained by the node are valid or not.
    */
   typedef enum {
       INVALID     = 0, //!< Samples/measurements are not valid
       DETECTIONS  = 1, //!< Samples/measurements are valid and correspond to detections
       FRAMES      = 2, //!< Samples/measurements are valid and correspond to video frames
   } sample_type_t;

   /*! \enum sample_type_t
    *  Describes whether the samples obtained by the node are valid or not.
    */
   typedef enum {
       IDEAL            = 0, //!< Samples/measurements are periodically captured without considering time spent in processing
       REAL_PERIOD      = 1, //!< Samples/measurements are periodically captured
       REAL_DEMAND      = 2, //!< Samples/measurements are captured when needed
   } sen_mode_type_t;

   /*! \enum fsm_algorithm_state_t
    *  Describes the actions or states of algorithm to periodically analyze frames/data.
    */
   typedef enum {
           FSM_UNDEFINED               = 0,
           FSM_INIT                    = 1, //!< state for algorithm initialization
           FSM_WAIT_SAMPLE             = 2, //!< state for waiting until the 1st sample is captured
           FSM_PROCESS_SAMPLE          = 3, //!< state to indicate that the lifetime of 1st sample has expired and a new sample will be captured
           FSM_PROCESS_END_SAMPLE      = 4,
   } fsm_algo_state_t;
private:
   static map<int,std::string> create_ALGO_FSM_str() {

       std::map<int,std::string> m;
       m.insert(std::make_pair(FSM_UNDEFINED, "FSM_UNDEFINED"));
       m.insert(std::make_pair(FSM_INIT, "FSM_INIT"));
       m.insert(std::make_pair(FSM_WAIT_SAMPLE, "FSM_WAIT_SAMPLE"));
       m.insert(std::make_pair(FSM_PROCESS_SAMPLE, "FSM_PROCESS_SAMPLE"));
       m.insert(std::make_pair(FSM_PROCESS_END_SAMPLE, "FSM_PROCESS_END_SAMPLE"));
       return m;
   }

   static map<int,std::string> create_ALGO_ALARM_str() {

       std::map<int,std::string> m;
       m.insert(std::make_pair(ALARM_WAIT_GRAPH, "ALARM_WAIT_GRAPH"));
       m.insert(std::make_pair(ALARM_SENSOR_SAMPLE, "ALARM_SENSOR_SAMPLE"));
       m.insert(std::make_pair(ALARM_PROCESS_SAMPLE, "ALARM_PROCESS_SAMPLE"));
       return m;
   }

protected:
    //associated strings to the fsm states and alarms
    std::map<int,std::string> _state_str, _alarm_str;

    double _sampling_time;              //!< frequency to get new samples (in secs) from physical process (through SensorDeviceManager)
	unsigned long _step_counter;        //!< counter for the number of times the data is analyzed by the algorithm
	sen_mode_type_t _sensing_mode;                  //!< Defines the mode for sensing frames (1-periodic, 2-on-demand)

	bool _network_ready;                          //!< Flag to indicate that comms and fov graphs of the network are computed
	bool _databuf_ready;                          //!< Flag to indicate that new data has arrived from the sensing module
	bool _running;                                //!< Flag to indicate that processing is currently being done

	std::vector<WiseTargetDetection> detections;  //!< List of ordered detections/measurements/ground-truth. If a target is not within the FOV, no measurement is provided (WiseTargetDetection.valid=false)

    int _curFrame;
    cv::Mat _frame;
    double _frameRate,_frameRateSRC,_resize,_resizeSRC;
    double _scaleCols,_scaleRows;

    double _time_atsample,_time_pkt_processing;

    int _bytesRX, _bytesTX,_bytesRXtot,_bytesTXtot; //statistics for received/sent data

    bool _show_results;
    std::ostringstream _winName;

	fsm_algo_state_t _fsm_state;      //!< FSM that defines the current state of the algorithm
	double _sample_lifetime;         //!< Lifetime in secs of the captured samples
	double _sampling_end2start_time; //!< Time to start next sampling stage after "sample_lifetime" expired
	double _lastSenTime;

protected:
	void startup();
	void finishSpecific();
	void fromNetworkLayer(WiseApplicationPacket *, const char *, double, double);
	void handleSensorReading(WiseCameraMessage *);
	void timerFiredCallback(int index);

	void send_message(WiseApplicationPacket*);
	void send_message(WiseApplicationPacket*, const std::string&);

	int send_messageNeighboursCOM(WiseApplicationPacket*);
    int send_messageNeighboursFOV(WiseApplicationPacket*);

    void handleMacControlMessage(cMessage *);

    //Functions to be defined in implemented superclass (algorithms)
	virtual void at_startup() = 0 ;                     //!< Init internal variables. To define in superclass for each specific algorithm (mandatory)
	virtual void at_timer_fired(int index) = 0;        //!< Response to alarms generated by specific algorithm. To define in superclass (optional)
	virtual void at_finishSpecific() = 0;
	virtual bool at_init() = 0;                //!< Init resources. To define in superclass for each specific algorithm (mandatory)
	//virtual bool at_first_sample() = 0;       //!< Operations at 1st example. To define in superclass for each specific algorithm (mandatory)
	//virtual bool at_end_first_sample() = 0;  //!< Operations at the end of 1st example. To define in superclass for each specific algorithm (mandatory)
	virtual bool at_sample() = 0;              //!< Operations at the >1st example. To define in superclass for each specific algorithm (mandatory)
	virtual bool at_end_sample() = 0;         //!< Operations at the end of >1st example. To define in superclass for each specific algorithm (mandatory)
	virtual bool process_network_message(WiseApplicationPacket *m) = 0 ; //!< Processing of packets received from network. To define in superclass for each specific algorithm (mandatory)
	virtual void make_measurements(const std::vector<WiseTargetDetection>&) = 0 ; //!< Conversion of camera detections into ordered lists of measurements for tracking. To define in superclass for each specific algorithm (mandatory)

	void fsm_algo(sample_type_t t, bool restart = false); //!< Logic for jumping between the states of the algorithm
	bool check_graph_completion(); //!< Checks whether all network nodes have completed the discovery of the COM and FOV graphs
};
#endif // __WiseCameraPeriodicAlgo_H__
