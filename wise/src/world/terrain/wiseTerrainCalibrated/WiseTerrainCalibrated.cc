// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Juan C. SanMiguel
//
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  Developed at the:
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  DESCRIPTION:
//  This file describes the source file for the network visualizer (WiseCalibratedTerrain) with calibration data
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#include <WiseTerrainCalibrated.h>

Define_Module(WiseTerrainCalibrated);

void WiseTerrainCalibrated::initialize()
{
    //call the baseline initialization
    WiseBaseTerrain::initialize();

    //load calibration data for the GUI
    if (_useCalibration == true)
    {
        _GPmap_path = par("GPmap_path").stringValue(); //path to the image containing the ground-plane
    }
    else
        error("Loading Calibrated Terrain without available calibration data");

    //Create the GUI
    gui = (gui_type == "") ? NULL : WiseGuiWorld::Factory::create(gui_type,gui_show,(unsigned)x_size,(unsigned)y_size,_xmin,_ymin,_scale_world,_GPmap_path,draw_trajectory);
}
