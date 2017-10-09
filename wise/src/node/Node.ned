// *****************************************************************************************
// Copyright (C) 2011 Christian Nastasi, 2017 Juan C. SanMiguel and Andrea Cavallaro
// You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
// license (see the attached LICENSE_WISE file).
//
// This file is part of the WiseMnet simulator
//
// Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// Please cite the following reference when publishing results obtained with WiseMnet:
//   J. SanMiguel & A. Cavallaro,
//   "Networked Computer Vision: the importance of a holistic simulator",
//   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
// *****************************************************************************************

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

//********************************************************************************
//*  Copyright: National ICT Australia,  2007 - 2010                             *
//*  Developed at the ATP lab, Networked Systems research theme                  *
//*  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis, Yuriy Tselishchev  *
//*  This file is distributed under the terms in the attached LICENSE file.      *
//*  If you do not find this file, copies can be found by writing to:            *
//*                                                                              *
//*      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                 *
//*      Attention:  License Inquiry.                                            *
//*                                                                              *
//*******************************************************************************/

package node;

module Node
{
    //basic parameters
    parameters:
        //location and orientation of node in 3D world coordinates
        double xCoor = default(0);
        double yCoor = default(0);
        double zCoor = default(0);
        double phi = default(0);
        double theta = default(0);

        //dummy communication settings
        bool dummy_communication = default(false); 					//chris's add-up: see usage of this
        string dummy_connectivity_map = default("");				// chris's add-up: should be used by dummy wireless channel

        string SensorManagerName = default("SensorManager"); 		// the name of the sensor type (eg, the camera)
        string ApplicationName = default("WiseBaseAppTest"); 		// the name of the implemented Application Module (eg, logic)
        string MobilityManagerName = default("NoMobilityManager");	// the name of the implemented Mobility Module

    //connections from/to other modules
    gates:
        output toWirelessChannel;
        output toPhysicalProcess[];
        input fromWirelessChannel;
        input fromPhysicalProcess[];
        // chris' add-up: direct (ideal) communication among nodes 
        //                for simplistic assumptions (neighbours discover, locations)
        output toNodeDirect[];
        input fromNodeDirect[];

    submodules:
        // SubModule for defining node's motion behavior (if any)
        MobilityManager: <MobilityManagerName> like node.mobilityManager.iMobilityManager;
        // SubModule for defining node's resources (ie, energy consumption if any)
        //ResourceManager: node.resourceManager.ResourceManager;
        //ResourceManager: <ResourceManagerName> like wise.node.resourceManager.WiseResourceManager;
        ResourceManager: node.resourceManager.WiseResourceManager;
        // SubModule managing connections to physical processes (eg, targets)	
        SensorManager: <SensorManagerName> like node.sensorManager.WiseBaseSensorManager {
            gates:
                fromNodeContainerModule[sizeof(toPhysicalProcess)];
                toNodeContainerModule[sizeof(toPhysicalProcess)];
        }

        // SubModule for communication with other nodes
        Communication: node.communication.CommunicationModule;
        // SubModule for defining the application
        //Application: <ApplicationName> like node.application.iApplication {
        Application: <ApplicationName> like node.application.wiseBaseApp.WiseBaseApp {
            gates:
                toApplicationDirect[sizeof(toNodeDirect)];
                fromApplicationDirect[sizeof(fromNodeDirect)];
        }

    connections allowunconnected:
        Communication.toNodeContainerModule --> toWirelessChannel if (!dummy_communication);
        fromWirelessChannel --> Communication.fromNodeContainerModule if (!dummy_communication);
        Application.toCommunicationModule --> Communication.fromApplicationModule if (!dummy_communication);
        Application.toSensorDeviceManager --> SensorManager.fromApplicationModule;
        Communication.toApplicationModule --> Application.fromCommunicationModule if (!dummy_communication);
        SensorManager.toApplicationModule --> Application.fromSensorDeviceManager;

        Application.toCommunicationModule --> toWirelessChannel if (dummy_communication);
        fromWirelessChannel --> Application.fromCommunicationModule if (dummy_communication);

        // Direct connections from other nodes (accessible through the Application layer)
        for i=0..sizeof(fromNodeDirect) - 1 {
            fromNodeDirect[i] --> Application.fromApplicationDirect[i];
        }

        // Direct connections to other nodes (accessible through the Application layer)
        for i=0..sizeof(toNodeDirect) - 1 {
            toNodeDirect[i] <-- Application.toApplicationDirect[i];
        }

        // Direct connections from/to the physical processes (accessible through the SensorManager)
        for i=0..sizeof(toPhysicalProcess) - 1 {
            fromPhysicalProcess[i] --> SensorManager.fromNodeContainerModule[i];
            SensorManager.toNodeContainerModule[i] --> toPhysicalProcess[i];
        }

        ResourceManager.toSensorDevManager --> SensorManager.fromResourceManager;
        ResourceManager.toApplication --> Application.fromResourceManager;
        ResourceManager.toNetwork --> Communication.fromResourceManager2Net if (!dummy_communication);
        ResourceManager.toMac --> Communication.fromResourceManager2Mac if (!dummy_communication);
        ResourceManager.toRadio --> Communication.fromResourceManager2Radio if (!dummy_communication);
}
