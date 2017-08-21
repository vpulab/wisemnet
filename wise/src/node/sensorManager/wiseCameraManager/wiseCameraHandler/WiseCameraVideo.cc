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

#include "WiseCameraVideo.h"
#include "WiseCameraManager.h"
#include "WiseDebug.h"

//using namespace std;
//using namespace wise;

//static WiseCameraHandler::Factory::Factory registrat("WiseMovingTargetMessage", WiseCameraVideo::creator);

//change for new gcc compiler versions (>4.5)
static WiseCameraHandler::Factory registrat("WiseVideoFileMessage", WiseCameraVideo::creator);

WiseCameraVideo::WiseCameraVideo(const WiseCameraManager &m): WiseCameraHandler(m)
{
    p = &m;
}

void WiseCameraVideo::initialize()
{
	pending_sample_reply = manager.get_num_processes();
	//detections.clear();
}

WiseCameraMessage *WiseCameraVideo::process(WisePhysicalProcessMessage *msg)
{
	WISE_DEBUG_3("WiseCameraVideo::handleSample()");

	WiseVideoFileMessage *event = check_and_cast<WiseVideoFileMessage*>(msg);

    WiseCameraVideoMessage *smp = NULL;
    smp = new WiseCameraVideoMessage("Camera Detection Video", SENSOR_READING_MESSAGE);;
    smp->setCameraSampleType("WiseCameraVideo");
    smp->setFrame(event->getFrame());
    smp->setFrameRateSRC(event->getFrameRateSRC());
    smp->setCurFrame(event->getCurFrame());
    smp->setResize(event->getResize());

    return smp;
}
