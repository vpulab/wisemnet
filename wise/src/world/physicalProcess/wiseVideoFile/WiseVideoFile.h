// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#ifndef __WiseVideoFile_h__
#define __WiseVideoFile_h__

#include <string>
#include "WiseBasePhysicalProcess.h"
#include "WiseVideoFileMessage_m.h"

#include <opencv.hpp>

class WiseVideoFile: public WiseBasePhysicalProcess {
private:
    std::string _filename;
	double _frameRate;
	double _updateTime;
	double _moveLater;

	cv::VideoCapture *_cap;
	cv::Mat _frame,_tmpFrame;

	int _iniFrame,_endFrame, _curFrame; // initial, final and current index of frames read
    int _numFrames;//total number of frames
    double _resize;

	bool _show_video;
	std::ostringstream _os;

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage * msg);
	virtual void finishSpecific();
};

#endif // __WiseVideoFile_h__
