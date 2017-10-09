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
 * \file WiseCameraPeriodicAppTypes.h
 * \author Juan C. SanMiguel (2017)
 * \brief Header file for types/constants required by the WiseCameraPeriodicApp class
 * \version 1.4
 */
#ifndef __WISECAMERAAPPTYPES_H__
#define __WISECAMERAAPPTYPES_H__

//avoid warnings
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma GCC diagnostic ignored "-Wunused-function"
//#pragma GCC diagnostic pop

#include <opencv.hpp> //opencv library

#include <string> //required by "create_ALARM_APP_str" &·"create_FSM_APP_str"
#include <vector> //required by "create_ALARM_APP_str" &·"create_FSM_APP_str"
#include <map>    //required by "create_ALARM_APP_str" &·"create_FSM_APP_str"

//messages for received data
#include "WiseCameraDetectionsMessage_m.h" //detections
#include "WiseCameraVideoMessage_m.h"   //frames

/*! \enum alarm_app_type_t
*  Describes the alarms handled by the periodic algorithm.
*/
//typedef enum {
//   ALARM_WAIT_GRAPH               = 0,//!< Periodic alarm to check completion of vision&comms graphs discovery
//   ALARM_SENSOR_SAMPLE            = 1, //!< Periodic alarm to request a new sample to SensorManager
//   ALARM_PROCESS_SAMPLE           = 2, //!< Periodic alarm to check new data to be processed
//} alarm_app_type_t;
#define ALARM_WAIT_GRAPH               0 //!< Periodic alarm to check completion of vision&comms graphs discovery
#define ALARM_SENSOR_SAMPLE            1 //!< Periodic alarm to request a new sample to SensorManager
#define ALARM_PROCESS_SAMPLE           2 //!< Periodic alarm to check new data to be processed
#define ALARM_START_SAMPLE_PERIOD      3 //!< Periodic alarm to indicate start of lifetime of sample (and prepare the tracker for next capture)
#define ALARM_END_SAMPLE_PERIOD        4 //!< Periodic alarm to indicate end of lifetime of sample (and prepare the tracker for next capture)
#define ALARM_START_NEGOTIATION        5 //!< Periodic alarm to indicate the start of negotiations among cameras
#define ALARM_END_NEGOTIATION          6 //!< Periodic alarm to indicate the finish of negotiations among cameras
#define ALARM_WAIT_NEGOTIATION         7 //!< Periodic alarm to indicate the waiting status of negotiations among cameras

/*! \enum sen_mode_type_t
   *  Describes whether the samples obtained by the node are valid or not.
   */
  typedef enum {
      SEN_IDEAL            = 0, //!< Samples/measurements are periodically captured without considering time spent in processing
      SEN_REAL_PERIOD      = 1, //!< Samples/measurements are periodically captured
      SEN_REAL_DEMAND      = 2, //!< Samples/measurements are captured when needed
  } sen_mode_type_t;

/*! \enum sample_type_t
*  Describes whether the samples obtained by the node are valid or not.
*/
typedef enum {
   INVALID     = 0, //!< Samples/measurements are not valid
   DETECTIONS  = 1, //!< Samples/measurements are valid and correspond to detections
   FRAMES      = 2, //!< Samples/measurements are valid and correspond to video frames
} sample_type_t;

/*! \enum fsm_algorithm_state_t
*  Describes the actions or states of algorithm to periodically analyze frames/data.
*/
typedef enum {
       FSM_UNDEFINED               = 0,
       FSM_INIT                    = 1, //!< state for algorithm initialization
       FSM_WAIT_SAMPLE             = 2, //!< state for waiting until each sample is captured
       FSM_PROCESS_SAMPLE          = 3, //!< state to indicate that the lifetime of each sample has expired and it is processed
       FSM_PROCESS_END_SAMPLE      = 4, //!< state to indicate that the sample has been processed
} fsm_app_state_t;

/*! \struct sample_buffer_type_t
*  \brief Internal buffer for sensed data in WiseCameraAppTemplate
*/
struct sample_buffer_type_t {
   sample_type_t type; //!< type of buffered data

   std::vector<WiseTargetDetection> detections; //!< List of ordered detections within camera's FOV
   int curFrame;
   cv::Mat frame;
   double frameRate,frameRateSRC,resize;
};


#endif // __WISECAMERAAPPTYPES_H__
