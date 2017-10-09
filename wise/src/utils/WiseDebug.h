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
 * \file WiseDebug.h
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Header file for the Debug utilities
 * \version 1.4
 */

#ifndef __WISEDEBUG_H__
#define __WISEDEBUG_H__

#include <iomanip>
#include <fstream>
#include <omnetpp.h>

class WiseDebugLogger {
private:
    static std::fstream writer;
public:
    static inline std::ostream& get_stream();
public:
    WiseDebugLogger(std::string filename);
    WiseDebugLogger& operator=(const WiseDebugLogger&);
};

std::ostream& WiseDebugLogger::get_stream()
{
    return writer << "[" << std::setfill('0') << std::setw(10) << omnetpp::simTime() << "] ";
}

//This function writes logs in two separated files
// - WiseDebugLogger --> selected/determined by the user
// - trace() --> "wise_trace.txt" file which contains output from Castalia and Wise components/modules
#define LOGGER(str)        \
{                            \
    WiseDebugLogger::get_stream() << "@ " << self << " : " << str << std::endl; \
    trace() << str;       \
}

#define WISE_DEBUG_LEVEL 3 //logging levels (see "WiseDebug.h" for details)
// Description:
//  - WISE_DEBUG_LEVEL = -1 //none
//  - WISE_DEBUG_LEVEL = 0 //all
//  - WISE_DEBUG_LEVEL = 1 //PhysicalProcesses (moving target, video files,...)
//  - WISE_DEBUG_LEVEL = 2 //Node modules (sensorManager,resourceManager,...)
//  - WISE_DEBUG_LEVEL = 3 //application layer
//  - WISE_DEBUG_LEVEL = 31 //only for application interfaces/templates (WiseBaseApp, WiseCamApp & WiseCameraPeriodicApp)
//  - WISE_DEBUG_LEVEL = 32 //only for last application class (i.e. subclasses of WiseBaseApp, WiseCamApp & WiseCameraPeriodicApp)
//  - WISE_DEBUG_LEVEL = ...

//Default DEBUG level
#ifndef WISE_DEBUG_LEVEL
#define WISE_DEBUG_LEVEL -1
#endif //#ifndef WISE_DEBUG_LEVEL

//No DEBUG Information
#if (WISE_DEBUG_LEVEL==-1)
    #define WISE_DEBUG_10(str)
    #define WISE_DEBUG_20(str)
    #define WISE_DEBUG_31(str)
    #define WISE_DEBUG_32(str)
#endif //#if (WISE_DEBUG_LEVEL==-1)

//All DEBUG Information
#if (WISE_DEBUG_LEVEL==0)
    #define WISE_DEBUG_10(str) LOGGER(str)
    #define WISE_DEBUG_20(str) LOGGER(str)
    #define WISE_DEBUG_31(str) LOGGER(str)
    #define WISE_DEBUG_32(str) LOGGER(str)
#endif  //#if (WISE_DEBUG_LEVEL==0)

//DEBUG Information for PhysicalProcesses (moving target, video files,...)
#if (WISE_DEBUG_LEVEL==1)
    #define WISE_DEBUG_10(str) LOGGER(str)
    #define WISE_DEBUG_20(str)
    #define WISE_DEBUG_31(str)
    #define WISE_DEBUG_32(str)
#endif  //#if (WISE_DEBUG_LEVEL==10)

//DEBUG Information for all modules (sensorManager,resourceManager,...)
#if (WISE_DEBUG_LEVEL==2)
    #define WISE_DEBUG_10(str)
    #define WISE_DEBUG_20(str) LOGGER(str)
    #define WISE_DEBUG_31(str)
    #define WISE_DEBUG_32(str)
#endif //#if (WISE_DEBUG_LEVEL==20)

//DEBUG Information for application layer
#if (WISE_DEBUG_LEVEL==3)
    #define WISE_DEBUG_10(str)
    #define WISE_DEBUG_20(str)
    #define WISE_DEBUG_31(str) LOGGER(str)
    #define WISE_DEBUG_32(str) LOGGER(str)
#endif  //#if (WISE_DEBUG_LEVEL==30)


//DEBUG Information for application interfaces/templates (WiseBaseApp, WiseCamApp & WiseCameraPeriodicApp)
#if (WISE_DEBUG_LEVEL==31)
    #define WISE_DEBUG_10(str)
    #define WISE_DEBUG_20(str)
    #define WISE_DEBUG_31(str) LOGGER(str)
    #define WISE_DEBUG_32(str)
#endif  //#if (WISE_DEBUG_LEVEL==31)

//DEBUG Information for last application layer implementing node's behavior
#if (WISE_DEBUG_LEVEL==32)
    #define WISE_DEBUG_10(str)
    #define WISE_DEBUG_20(str)
    #define WISE_DEBUG_31(str)
    #define WISE_DEBUG_32(str) LOGGER(str)
#endif  //#if (WISE_DEBUG_LEVEL==32)

#endif //#ifndef __WISEDEBUG_H__
