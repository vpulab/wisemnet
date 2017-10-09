// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011 (nastasichr@gmail.com)
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  This file is distributed under the terms in the attached LICENSE_2 file.
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//	DESCRIPTION:
//  This file describes the source file for the network visualizer (WiseEmptyTerrain)
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
#include <WiseTerrainEmpty.h>

Define_Module(WiseTerrainEmpty);

void WiseTerrainEmpty::initialize()
{
    //call the baseline initialization
    WiseBaseTerrain::initialize();

    //Load data without using calibration data
    if (_useCalibration == false)
    {
        _GPmap_path = "";
    }
    else
        error("Loading Empty Terrain with available calibration data");

    //Create the GUI
    gui = (gui_type == "") ? NULL : WiseGuiWorld::Factory::create(gui_type,gui_show,(unsigned)x_size,(unsigned)y_size, 0.0,0.0,_scale_world,_GPmap_path,draw_trajectory);
}
