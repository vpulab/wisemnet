// *****************************************************************************
//  Copyright (C): Christian Nastasi, 2011                                    
//  Author(s): Christian Nastasi                                              
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa)           
//  - School of Elec Eng and Computer Science, Queen Mary University (London) 
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:          
//  - c.nastasi@sssup.it                                                      
//  - nastasichr@gmail.com                                                    
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#include "WiseVideoFile.h"
#include "WiseResourceManager.h"
#include "WiseDebug.h"
#include <sstream>

#define perr_app(m) opp_error("\n[WiseVideoFile]:\n " m)
#define perr(m) opp_error(m)

using namespace std;

Define_Module(WiseVideoFile);

void WiseVideoFile::initialize()
{
	WiseBasePhysicalProcess::initialize();

	//read user-defined parameters
	_filename = std::string (par("file_name").stringValue());
	_show_video = par("show_video");
	_frameRate = par("frame_rate");

	_moveLater = par("move_later");
	_iniFrame = par("iniFrame");
	_endFrame = par("endFrame");
	_resize = par("resize");

	//connect to video file
	_cap = new cv::VideoCapture(_filename.c_str());
	if (!_cap->isOpened())
        perr_app("Error reading video file");

	//read its framerate
	if (_frameRate == -1)
	    _frameRate = _cap->get(CV_CAP_PROP_FPS);

	if (_frameRate != _frameRate)//checking for NaN values
	    _frameRate = 25.0;

	//select as first frame to read 0 or the indicated number
	_curFrame = (_iniFrame == -1) ? 1 : _iniFrame;

	//get the total number of frames
	_numFrames = _cap->get(CV_CAP_PROP_FRAME_COUNT);
	if (_endFrame == -1 || _endFrame > _numFrames)
	    _endFrame = _numFrames;

	//read for positioning in required frame
	for (int i=0;i<=_curFrame;i++)
	    *_cap >> _tmpFrame;

	if (_resize != -1)
	    cv::resize(_tmpFrame,_frame,cv::Size(),_resize,_resize);
	else
	    _frame = _tmpFrame;

	_os << "ORIGINAL FRAMERATE (SENSOR " << self << "@" << _frameRate << "fps )";

	//compute the capture frequency based on framerate and schedule first capture
	_updateTime = 1 / _frameRate;
	scheduleAt(simTime() + _updateTime + _moveLater, new cMessage("CaptureFrame", TIMER_SERVICE));
}

void WiseVideoFile::finishSpecific()
{
    delete _cap;
}

void WiseVideoFile::handleMessage(cMessage * msg)
{
	WiseVideoFileMessage *f_msg;
	switch (msg->getKind()) {
	case PHYSICAL_PROCESS_SAMPLING: 
		// NOTE: substitute the req message with a specific one
		WisePhysicalProcessMessage *s_msg;
		s_msg = check_and_cast <WisePhysicalProcessMessage*>(msg);

		f_msg = new WiseVideoFileMessage("VideoFile Message", PHYSICAL_PROCESS_SAMPLING);
		if (s_msg->getSrcID() == self){
	        //cModule *m = getParentModule(); // m=SN
            //m = m->getSubmodule("node", self); // get node'0' of the network
            //m = m->getSubmodule("node", 0)->getSubmodule("Application");
            //WiseResourceManager *resMgrModule = check_and_cast <WiseResourceManager*>(m->getSubmodule("ResourceManager"));

            // include message data
		    f_msg->setFrameRateSRC(_frameRate);
            f_msg->setFileName(_filename.c_str());
            f_msg->setValid(true);
            f_msg->setFrame(_frame);
            f_msg->setResize(_resize);
            f_msg->setCurFrame(_curFrame);

            // Send reply back to the node which made the request
            send(f_msg, "toNode", s_msg->getSrcID());
	    }

		delete s_msg;
		s_msg = f_msg;
		break;

	case TIMER_SERVICE:
	    //grab new frame
	    _curFrame++;

	    if (_curFrame < _endFrame){
	        *_cap >> _tmpFrame;

	        if (_resize != -1)
	            cv::resize(_tmpFrame,_frame,cv::Size(),_resize,_resize);
            else
                _frame = _tmpFrame;
	    }
	    else
	        _frame.setTo(cv::Scalar(0));

	    if (_show_video){
	        cv::imshow(_os.str(),_frame);
	        cv::waitKey(1);
	    }

	    //re-schedule the capture of new frame
	    scheduleAt(simTime() + _updateTime, msg);
        break;
	default:
        perr_app("Received message other than PHYSICAL_PROCESS_SAMPLING or TIME_SERVICE");
        delete msg;
	}
}
