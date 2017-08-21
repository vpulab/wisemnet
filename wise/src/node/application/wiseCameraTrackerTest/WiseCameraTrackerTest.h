// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011 (nastasichr@gmail.com)
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file describes a template to test cameratracker applications
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
#ifndef __WiseCameraTrackerTest_h__
#define __WiseCameraTrackerTest_h__ 

#include <vector>
#include <fstream>
#include "WiseCameraSimplePeriodicTracker.h"
#include "WiseCameraTrackerTestMessage_m.h"

class WiseCameraTrackerTest : public WiseCameraSimplePeriodicTracker {
private: 
	struct measurement_t {
		unsigned int tid;
		double x;
		double y;
	};
private:
	static ofstream logger; //!< Used to collect node print-out

	int some_parameter;
	int n_targets;
	//unsigned int tracking_step;
	std::vector<measurement_t> observations;

protected:
	virtual void at_startup();
	virtual void at_finishSpecific() {};
	virtual void at_timer_fired(int index) {} ;
	virtual void at_tracker_init();
	virtual bool at_tracker_first_sample();
	virtual bool at_tracker_end_first_sample();
	virtual bool at_tracker_sample();
	virtual bool at_tracker_end_sample();
	virtual void make_measurements(const std::vector<WiseTargetDetection>&);
	virtual void process_network_message(WiseApplicationPacket *);
	virtual void handleDirectApplicationMessage(WiseApplicationPacket *);
};
#endif // __WiseCameraTrackerTest_h__	
