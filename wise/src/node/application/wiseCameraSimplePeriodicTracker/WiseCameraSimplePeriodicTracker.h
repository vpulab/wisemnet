// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2013
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file describes a template to implement tracking algorithms. Currently only used by WiseCameraDPF
//  TODO: remove this template in future releases of WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WISECAMERASIMPLEPERIODICTRACKER_H__
#define __WISECAMERASIMPLEPERIODICTRACKER_H__

#include <vector>
#include <map>
#include "WiseCameraApplication.h"
#include "WiseCameraDetectionsMessage_m.h"
#include "WiseCameraSimplePeriodicTracker_m.h"
#include "WiseDefinitionsTracking.h"

// Alarms handled by the periodic tracker
const int ALARM_WAIT_GRAPH        = 0; //!< Periodic alarm to check completion of vision&comms graphs discovery
const int ALARM_SENSOR_SAMPLE     = 1; //!< Periodic alarm to request a new sample to SensorManager
const int ALARM_END_SAMPLE_PERIOD = 2; //!< Periodic alarm to indicate end of lifetime of sample (and prepare the tracker for next capture)
const int ALARM_WAIT_NEGOTIATION = 2; //!< Periodic alarm to indicate end of lifetime of sample (and prepare the tracker for next capture)

/*! \class WiseCameraSimplePeriodicTracker
 *  \brief This class implements the template for periodic distributed target tracking.
 *
 *  More detailed description to be provided...
 */
class WiseCameraSimplePeriodicTracker : public WiseCameraApplication {
private:

    /*! \enum fsm_tracker_state_t
    *  Describes the actions or states of tracker to periodically analyze frames/data.
    */
   typedef enum {
           FSM_INIT                    = 0, //!< state for tracker initialization
           FSM_WAIT_GRAPHS             = 1, //!< state for waiting until graphs (vision & comms) are discovered in the network
           FSM_WAIT_FIRST_SAMPLE       = 2, //!< state for waiting until the 1st sample is captured
           FSM_WAIT_END_FIRST_SAMPLE   = 3, //!< state to indicate that the lifetime of 1st sample has expired and a new sample will be captured
           FSM_WAIT_SAMPLE             = 4, //!< state for waiting until the >1st sample is captured
           FSM_WAIT_END_SAMPLE         = 5, //!< state to indicate that the lifetime of >1st sample has expired and a new sample will be captured
   } fsm_tracker_state_t;

   static map<int,std::string> create_ALGO_FSM_str() {

          std::map<int,std::string> m;
          m.insert(std::make_pair(FSM_INIT, "FSM_INIT"));
          m.insert(std::make_pair(FSM_WAIT_GRAPHS, "FSM_WAIT_GRAPHS"));
          m.insert(std::make_pair(FSM_WAIT_FIRST_SAMPLE, "FSM_WAIT_FIRST_SAMPLE"));
          m.insert(std::make_pair(FSM_WAIT_END_FIRST_SAMPLE, "FSM_WAIT_END_FIRST_SAMPLE"));
          m.insert(std::make_pair(FSM_WAIT_SAMPLE, "FSM_WAIT_SAMPLE"));
          m.insert(std::make_pair(FSM_WAIT_END_SAMPLE, "FSM_WAIT_END_SAMPLE"));

          return m;
      }

      static map<int,std::string> create_ALGO_ALARM_str() {

          std::map<int,std::string> m;
          m.insert(std::make_pair(ALARM_WAIT_GRAPH, "ALARM_WAIT_GRAPH"));
          m.insert(std::make_pair(ALARM_SENSOR_SAMPLE, "ALARM_SENSOR_SAMPLE"));
          m.insert(std::make_pair(ALARM_END_SAMPLE_PERIOD, "ALARM_END_SAMPLE_PERIOD"));
          m.insert(std::make_pair(ALARM_WAIT_NEGOTIATION, "ALARM_WAIT_NEGOTIATION"));
          return m;
      }

protected:
      /*! \enum sample_type_t
       *  Describes whether the samples obtained by the node are valid or not.
       */
      typedef enum {
          INVALID     = 0, //!< Samples/measurements are not valid
          DETECTIONS  = 1, //!< Samples/measurements are valid and correspond to detections
      } sample_type_t;

    //associated strings to the fsm states and alarms
    std::map<int,std::string> _state_str, _alarm_str;

	double sampling_time;                        //!< frequency to get new samples (in secs) from physical process (through SensorDeviceManager)
	long tracking_step_counter;        //!< counter for the number of times the data is analyzed by the tracker

	bool network_ready;                          //!< Flag to indicate that comms and fov graphs of the network are computed

	std::vector<WiseTargetDetection> detections;  //!< List of ordered detections/measurements/ground-truth. If a target is not within the FOV, no measurement is provided (WiseTargetDetection.valid=false)

	double _time_atsample,_time_pkt_processing;

	fsm_tracker_state_t fsm_state; //!< FSM that defines the current state of the tracker
	double sample_lifetime; //!< Lifetime in secs of the captured samples
	double sampling_end2start_time; //!< Time to start next sampling stage after "sample_lifetime" expired

	int _bytesRX, _bytesTX,_bytesRXtot,_bytesTXtot; //statistics for received/sent data

protected:
	void startup();
	void finishSpecific();
	void fromNetworkLayer(WiseApplicationPacket *, const char *, double, double);
	void handleSensorReading(WiseCameraMessage *);
	void timerFiredCallback(int index);

	void send_message(WiseApplicationPacket*);
	void send_message(WiseApplicationPacket *m, double delay);
	void send_message(WiseApplicationPacket*, const std::string&);

	int send_messageNeighboursCOM(WiseApplicationPacket*,double base_delay=0);
    int send_messageNeighboursFOV(WiseApplicationPacket*,double base_delay=0,double step_delay=0);

    void handleMacControlMessage(cMessage *);

    //Functions to be defined in implemented superclass (trackers)
	virtual void at_startup() = 0 ;                     //!< Init internal variables. To define in superclass for each specific tracker (mandatory)
	virtual void at_finishSpecific() = 0;
	virtual void at_timer_fired(int index) = 0;        //!< Response to alarms generated by specific tracker. To define in superclass (optional)
	virtual void at_tracker_init() = 0;                //!< Init resources. To define in superclass for each specific tracker (mandatory)
	virtual bool at_tracker_first_sample() = 0;       //!< Operations at 1st example. To define in superclass for each specific tracker (mandatory)
	virtual bool at_tracker_end_first_sample() = 0;  //!< Operations at the end of 1st example. To define in superclass for each specific tracker (mandatory)
	virtual bool at_tracker_sample() = 0;              //!< Operations at the >1st example. To define in superclass for each specific tracker (mandatory)
	virtual bool at_tracker_end_sample() = 0;         //!< Operations at the end of >1st example. To define in superclass for each specific tracker (mandatory)
	virtual void process_network_message(WiseApplicationPacket *m) = 0 ; //!< Processing of packets received from network. To define in superclass for each specific tracker (mandatory)
	virtual void make_measurements(const std::vector<WiseTargetDetection>&) = 0 ; //!< Conversion of camera detections into ordered lists of measurements for tracking. To define in superclass for each specific tracker (mandatory)
	void fsm_tracker(sample_type_t t, bool restart = false); //!< Logic for jumping between the states of the tracker

private:
	bool check_graph_completion(); //!< Checks whether all network nodes have completed the discovery of the COM and FOV graphs
};
#endif // __WISECAMERASIMPLEPERIODICTRACKER_H__
