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
//  This file describes the NED file for the network
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
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

network SN
{
    //GENERIC NETWORK PARAMETERS
    parameters:
        int numNodes;						// the number of nodes/cameras in the network
        
        int numPhysicalProcesses = default(1);	// the number of physical processes attached to the network (e.g. videofeeds, moving targets,...)
        string physicalProcessName = default("CustomizablePhysicalProcess");
                
        int field_x = default(30);			// the length of the deployment field
        int field_y = default(30);			// the width of the deployment field
        int field_z = default(0);			// the height of the deployment field (2-D field by default)

        bool use_calibration = default(false); //FLAG to indicate if calibration needs to be used (e.g. cameras or real ground-plane maps)
        double xmin = default(-1);			// the minimum X-coordinate of the area covered by the network
        double xmax = default(-1);			// the maximum X-coordinate of the area covered by the network
        double ymin = default(-1);			// the minimum Y-coordinate of the area covered by the network
        double ymax = default(-1);			// the maximum Y-coordinate of the area covered by the network

        bool dummy_communication = default(false); //FLAG to employ dummy communication        

        string deployment = default("");	// ??

        string TerrainName = default("WiseTerrainEmpty"); 		// default module to visualize the network (camera, targets,...)
        string debugInfoFileName = default("Wise-Trace.txt");	// default filename for debugging

	//GATES TO/FROM MODULES IN THE NETWORK
    submodules:
        //gates for connecting nodes to the wireless channel
        wirelessChannel: wirelessChannel.WirelessChannel {
            gates:
                toNode[numNodes];
                fromNode[numNodes];
        }

		//gates for connecting nodes to the dummy channel
        dummyChannel: wirelessChannel.WiseDummyWirelessChannel {
            gates:
                toNode[numNodes];
                fromNode[numNodes];
        }

        //gates for connecting physical processes to nodes
        physicalProcess[numPhysicalProcesses]: <physicalProcessName> like physicalProcess.iPhysicalProcess {
            gates:
                toNode[numNodes];
                fromNode[numNodes];
        }
        
        //module to visualize network (added in v1.0)
        wiseTerrain: <TerrainName> like world.terrain.WiseBaseTerrain;

        //basic description of to/from gates for a single node
        node[numNodes]: node.Node {
            dummy_communication = dummy_communication;
            gates:
                toPhysicalProcess[numPhysicalProcesses];
                fromPhysicalProcess[numPhysicalProcesses];
                
                //gates for connecting each node to all the others 
                // NOTE that numNodes-1 connections for each node will be created!
                toNodeDirect[numNodes];
                fromNodeDirect[numNodes];
        }

    connections allowunconnected:
        
        //connect to/from gates with wireless channel if "dummy_communication" is disabled 
        for i=0..numNodes - 1 {
            node[i].toWirelessChannel --> wirelessChannel.fromNode[i] if (!dummy_communication);
            node[i].fromWirelessChannel <-- wirelessChannel.toNode[i] if (!dummy_communication);
        }
        
        //connect to/from gates with dummy channel if "dummy_communication" is enabled
        for i=0..numNodes - 1 {
            node[i].toWirelessChannel --> dummyChannel.fromNode[i] if (dummy_communication);
            node[i].fromWirelessChannel <-- dummyChannel.toNode[i] if (dummy_communication);
        }

		//connect to/from gates with physical processes (ideally, one node can sense all processes)
        for i=0..numNodes - 1, for j=0..numPhysicalProcesses - 1 {
            node[i].toPhysicalProcess[j] --> physicalProcess[j].fromNode[i];
            node[i].fromPhysicalProcess[j] <-- physicalProcess[j].toNode[i];
        }

		//connect to/from gates with other nodes (direct communication)
        for i=0..numNodes - 1, for j=0..numNodes - 1 {
            node[i].toNodeDirect[j] --> node[j].fromNodeDirect[i] if (i != j);
        }
}
