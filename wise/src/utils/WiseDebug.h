// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011 (nastasichr@gmail.com)
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file describes the debugging method for WiSEMNET++.
//  CURRENTLY NOT USED BUT MAINTAINED FOR LEGACY
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WiseDebug_h__
#define __WiseDebug_h__

//#define WISE_DEBUG 1 //define the debug level for the log file
// Description:
//  - WISE_DEBUG = 1 //Application only messages
//  - WISE_DEBUG = 2 //Node modules (sensorManager,resourceManager,...)
//  - WISE_DEBUG = 3 //PhysicalProcesses (moving target, video files,...)

#if (defined WISE_DEBUG) && (WISE_DEBUG > 0) && (WISE_DEBUG < 4)

#include <iomanip>
#include <fstream>
#include <omnetpp.h>

class WiseDebugLogger {
private: 
	static std::fstream writer;
public:
	static inline std::ostream& get_stream();
private:
	WiseDebugLogger();
	WiseDebugLogger(const WiseDebugLogger&);
	WiseDebugLogger& operator=(const WiseDebugLogger&);
};

std::ostream& WiseDebugLogger::get_stream()
{
	return writer << "\n[" << std::setw(16) << omnetpp::simTime() << "] ";
}

#if (WISE_DEBUG > 0) && (WISE_DEBUG < 2)
#define WISE_DEBUG_1(m) WiseDebugLogger::get_stream() << m
#define WISE_DEBUG_2(m)  
#define WISE_DEBUG_3(m)  
#endif

#if (WISE_DEBUG > 1) && (WISE_DEBUG < 3)
#define WISE_DEBUG_1(m) WiseDebugLogger::get_stream() << m
#define WISE_DEBUG_2(m) WISE_DEBUG_1(m)
#define WISE_DEBUG_3(m)  
#endif

#if (WISE_DEBUG > 2) && (WISE_DEBUG < 4)
#define WISE_DEBUG_1(m) WiseDebugLogger::get_stream() << m
#define WISE_DEBUG_2(m) WISE_DEBUG_1(m)
#define WISE_DEBUG_3(m) WISE_DEBUG_1(m)
#endif

#else 

#define WISE_DEBUG_1(m)  
#define WISE_DEBUG_2(m)  
#define WISE_DEBUG_3(m)  

#endif // WISE_DEBUG

#endif // __WiseDebug_h__
