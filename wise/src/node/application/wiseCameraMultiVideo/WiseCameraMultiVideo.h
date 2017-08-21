// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#ifndef __WiseCameraMultiVideo_H__
#define __WiseCameraMultiVideo_H__

#include "WiseCameraPeriodicAlgo.h"
#include "WiseCameraMultiVideoPacket_m.h"
#include "WiseCameraMultiVideoPacketFull_m.h"
#include <opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>

/*! \class WiseCameraMultiVideo
 *  \brief This class implements a typical distributed video application where each node sends
 *  video streams to a single sink node. Behavior of sink and transmitting node can be configured in
 *  associated ini file
 *
 */
class WiseCameraMultiVideo : public WiseCameraPeriodicAlgo
{
private:

private:
    static ofstream logger; //!< Used to collect node print-out

    //Generic params
    int mode;               //!< 1-full frame 2-foreground segmentation (fg)
    bool isSink;               //!< status of being server to RX data
    int sinkNode;              //!< server to TX data

    cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2; //MOG Background subtractor
    cv::Mat fgMaskMOG; //fg mask generated by MOG method

public:
    virtual ~WiseCameraMultiVideo();

protected:
    // Functions to be implemented from WiseCameraPeriodicAlgo class
    void at_startup();                       //!< Init internal variables. To implement in superclasses of WiseCameraPeriodicAlgo.
    void at_finishSpecific() {};
    void at_timer_fired(int index) {} ;     //!< Response to alarms generated by specific tracker. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_init();                          //!< Init resources. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_first_sample();                 //!< Operations at 1st example. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_end_first_sample();            //!< Operations at the end of 1st example. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_sample();                        //!< Operations at the >1st example. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_end_sample();                   //!< Operations at the end of >1st example. To implement in superclasses of WiseCameraPeriodicAlgo.

    // Functions to be implemented from WiseBaseApplication class
    bool process_network_message(WiseApplicationPacket *); //!< Processing of packets received from network. To implement in superclasses of WiseBaseApplication.
    void handleDirectApplicationMessage(WiseApplicationPacket *); //!< Processing of packets received from network. To implement in superclasses of WiseBaseApplication.
    void make_measurements(const std::vector<WiseTargetDetection>&);  //!< Conversion of camera detections into ordered lists of measurements for tracking. To implement in superclasses of WiseBaseApplication.

    void handleMacControlMessage(cMessage *);

private:
};

#endif // __WiseCameraMultiVideo_H__