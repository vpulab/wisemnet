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

#ifndef __WiseCameraManager_h__
#define __WiseCameraManager_h__

#include <string>
#include <vector>
#include <map>
#include "WiseBaseSensorManager.h"
#include "WiseCameraMessage_m.h"
#include "WiseMovingTargetMessage_m.h"
#include "WiseCameraHandler.h"
#include "cameraModel.h"

class WiseCameraManager: public WiseBaseSensorManager {
protected:
	// NOTE: for more camera per sensor this shall become a vector. Sure ?
	WiseCameraInfo _cam_info;
	string _type_src; //"Target", "Video"
	std::map<std::string, WiseCameraHandler*> _handlers;

	std::string _calibFile, _calibType;
	std::string _calibFileMap;
	Etiseo::CameraModel *_calibModel;

	cv::Mat _worldmap;

public:
	virtual ~WiseCameraManager();
	inline const WiseCameraInfo& get_camera_info() const {return _cam_info;};
	inline unsigned get_num_processes() const { return numProcesses; };

	//! Coordinate manipulation
    //! from image coordinate to world coordinate
    void imageToWorld(double Xi, double Yi, double Zw, double& Xw, double &Yw);

    //! from world coordinate to image coordinate
    void worldToImage(double Xw, double Yw, double Zw, double& Xi, double& Yi);

protected:
	virtual void initialize();
	virtual void startup();
	virtual void handleSample(WisePhysicalProcessMessage *msg);
	//virtual void processCommandRequest(WiseSensorManagerMessage *req);
	//void processSampleRequest(WiseSensorManagerMessage *req);
private:
	inline void init_handlers();
	inline void delete_handlers();
	inline WiseCameraHandler *get_handler(const std::string&);
};

inline void WiseCameraManager::init_handlers()
{
	std::map<std::string, WiseCameraHandler*>::iterator i = _handlers.begin();
	for (; i != _handlers.end(); ++i)
		i->second->initialize();
}

inline void WiseCameraManager::delete_handlers()
{
	std::map<std::string, WiseCameraHandler*>::iterator i = _handlers.begin();
	for (; i != _handlers.end(); ++i)
	    delete i->second;

	_handlers.clear();
}
	
inline WiseCameraHandler *WiseCameraManager::get_handler(const string &n)
{
    // Here the class "std::map" is used to retrieve the appropriate element using as key the string (advantage is logaritmic time)
	if (_handlers.find(n) == _handlers.end()) {
		_handlers[n] = WiseCameraHandler::Factory::create(n, *this);
		_handlers[n]->initialize();
	}
	return _handlers[n];
}

#endif // __WiseCameraManager_h__
