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

#ifndef __WiseCameraVideo_h__
#define __WiseCameraVideo_h__

#include <vector>
#include "WiseCameraHandler.h"
#include "WiseVideoFileMessage_m.h"
#include "WiseCameraVideoMessage_m.h"

//namespace wise {

class WiseCameraVideo : public WiseCameraHandler {
private:
	unsigned pending_sample_reply;
	//std::vector<WiseTargetDetection> detections;

	const WiseCameraManager *p;
public:
	static WiseCameraHandler* creator(const WiseCameraManager &m) { return new WiseCameraVideo(m); };
	WiseCameraVideo(const WiseCameraManager &m);
	virtual void initialize();
	virtual WiseCameraMessage *process(WisePhysicalProcessMessage*);
private:
	//void mapping_bounding_box(const WiseTargetBoundingBox &, WiseTargetDetection &);
};

//} // namespace wise

#endif // __WiseCameraVideo_h__
