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
//  This file describes the NED file for the network visualizer (WiseBaseTerrain)
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WiseBaseTerrain_h__
#define __WiseBaseTerrain_h__

#include "CastaliaModule.h"
#include "WiseGuiWorld.h"
#include "WiseCameraInfo.h"
#include "WiseTargetInfo.h"
#include <string>



class WiseBaseTerrain: public CastaliaModule {
private:

protected:
	/*--- The .ned file's parameters ---*/
	std::string gui_type;
	bool gui_wait_start;
	bool gui_show;
	bool draw_trajectory;

	/*--- Custom class parameters ---*/
	double x_size;
	double y_size;
	double z_size;
	WiseGuiWorld *gui;

	/*--- Custom class parameters ---*/
	cModule *_net;

	bool _useCalibration;
	string _GPmap_path;

	double _xmin,_xmax,_ymin,_ymax;
	double _scale_world;

	unsigned n_processes;

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage * msg);
	virtual void finish();
	virtual void finishSpecific();

public:
	WiseBaseTerrain() : gui(NULL) {};
	inline double get_x_size() const { return x_size; };
	inline double get_y_size() const { return y_size; };
	inline double get_z_size() const { return z_size; };
	inline double get_scale_factor() const { return _scale_world; };
	inline double get_x_min() const { return _xmin; };
	inline double get_x_max() const { return _xmax; };
	inline double get_y_min() const { return _ymin; };
	inline double get_y_max() const { return _ymax; };

	inline WiseGuiWorld* get_GUI() const { return gui; };

	//Method to place a camera within the image displayed by the GUI
	virtual void place_camera(const WiseCameraInfo&, int GUI_idx=0);

	//Method to place a target within the image displayed by the GUI
	virtual void place_target(const WiseTargetInfo&, int GUI_idx=0);

	//Method to place a target within the image displayed by the GUI
	virtual void place_noise(const WiseTargetInfo&, int GUI_idx=0);

	virtual inline bool free_point(double x, double y, double z) const 
								{return true;};
	virtual inline bool free_box(double tx, double ty, double tz, 
				     double bl, double bw, double h) const 
								{return true;};
};

#endif // __WiseBaseTerrain_h__
