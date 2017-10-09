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

#include "WiseBaseTerrain.h"
#include "WiseDebug.h"

void WiseBaseTerrain::initialize() 
{
	_net = getParentModule();
	if (!_net)
		opp_error("Unable to obtain SN pointer");

    //Get the FLAG for using calibration data
    _useCalibration = (bool)_net->par("use_calibration");

    //number of physical processes to display (e.g. moving targets, cameras,...)
    n_processes = _net->par("numPhysicalProcesses");

    // type of GUI to display data (currently only supported "opencv")
    const char *type = par("gui");
    gui_type = type;

    // read the FLAG to wait for a key-pressed event before starting the application
    gui_wait_start = par("gui_wait_start");

    // read the FLAG to display target trajectories
    draw_trajectory = hasPar("draw_trajectory") ? par("draw_trajectory") : false;

    // read the FLAG to show the GUI
    gui_show = hasPar("gui_show") ? par("gui_show") : false;

     _scale_world = par("scale_world");

    _xmin = (double)_net->par("xmin");  // the minimum X-coordinate of the area covered by the network (i.e. world coordinates)
    _xmax = (double)_net->par("xmax");  // the maximum X-coordinate of the area covered by the network (i.e. world coordinates)
    _ymin = (double)_net->par("ymin");  // the minimum Y-coordinate of the area covered by the network (i.e. world coordinates)
    _ymax = (double)_net->par("ymax");  // the maximum Y-coordinate of the area covered by the network (i.e. world coordinates)
     x_size = (double)_net->par("field_x");  // width of the area covered by the network (user defined)
     y_size = (double)_net->par("field_y");  // length of the area covered by the network (user defined)
     z_size = (double)_net->par("field_z");  // height of the area covered by the network (user defined)

    if (_xmin==-1) _xmin=1;
    if (_ymin==-1) _ymin=1;
    if (_xmax==-1) _xmax=x_size;
    if (_ymax==-1) _ymax=y_size;

    if (x_size==-1) x_size = _xmax-_xmin;  // width of the area covered by the network (i.e. world coordinates)
    if (y_size==-1) y_size = _ymax-_ymin;  // length of the area covered by the network (i.e. world coordinates)

	//_FOV_display_scale = hasPar("FOV_display_scale") ? (double) par("FOV_display_scale") : 100.0;

	//Create the GUI
	//gui = (gui_type == "") ? NULL : WiseGuiWorld::Factory::create(gui_type,gui_show,(unsigned)x_size,(unsigned)y_size, _scale_factor,_GPmap_path,draw_trajectory);
}

void WiseBaseTerrain::handleMessage(cMessage * msg)
{
	delete msg;
}

void WiseBaseTerrain::finish()
{
	if (gui) {
		delete gui;
		gui = NULL;
	}
}

void WiseBaseTerrain::finishSpecific()
{
}

//Method to place a camera within the image displayed by the GUI
// This method calls the "draw_camera" functionality of the GUI
void WiseBaseTerrain::place_camera(const WiseCameraInfo &cam, int GUI_idx)
{
    WISE_DEBUG_20("WiseBaseTerrain::place_camera() called");

    if (!gui_show)
        return;

    if (!gui)
        return;

    switch (GUI_idx)
    {
        case 0:
            gui->draw_camera(cam,"WORLD");
            break;
        case 1:
            gui->draw_camera(cam,"GROUND-PLANE MAP");
            break;
    }
    gui->hold();
    if(gui_wait_start)
        gui->wait_key();
}

//Method to place a camera within the image displayed by the GUI
// This method calls the "draw_target" functionality of the GUI
void WiseBaseTerrain::place_target(const WiseTargetInfo& tgt, int GUI_idx)
{
    WISE_DEBUG_20("WiseBaseTerrain::place_target() called");

    if (!gui_show)
        return;
    if (!gui)
        return;

    static bool once = false;     // FIXME: TEMPORARY SOLUTION, I don't like
    static unsigned expected = 0; // FIXME: TEMPORARY SOLUTION, I don't like

    if (draw_trajectory==false && expected == 0)
        gui->clean();
        expected = (expected + 1) % n_processes;

    switch (GUI_idx)
    {
        case 0:
            gui->draw_target(tgt,"WORLD");
            break;
        case 1:
            gui->draw_target(tgt,"GROUND-PLANE MAP");
            break;
    }

    //wait if first time the target is draw
    if (gui_wait_start && !once){
        gui->wait_key();
        once = true;
    }
}


//Method to place a camera within the image displayed by the GUI
// This method calls the "draw_target" functionality of the GUI
void WiseBaseTerrain::place_noise(const WiseTargetInfo& tgt, int GUI_idx)
{
    WISE_DEBUG_20("WiseBaseTerrain::place_target() called");

    if (!gui_show)
        return;
    if (!gui)
        return;

    static bool once = false;     // FIXME: TEMPORARY SOLUTION, I don't like
    static unsigned expected = 0; // FIXME: TEMPORARY SOLUTION, I don't like

    if (draw_trajectory==false && expected == 0)
        gui->clean();
        expected = (expected + 1) % n_processes;

    switch (GUI_idx)
    {
        case 0:
            gui->draw_noise(tgt,"WORLD");
            break;
        case 1:
            gui->draw_noise(tgt,"GROUND-PLANE MAP");
            break;
    }

    //wait if first time the target is draw
    if (gui_wait_start && !once){
        gui->wait_key();
        once = true;
    }
}
