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

#include "WiseBaseSensorManager.h"
#include "WiseDebug.h"

void WiseBaseSensorManager::initialize()
{
	simtime_t sampleInterval;
	const char *token;
	const char *in_str;
	cModule *m;

	disabled = 1;
	cModule *node = getParentModule();
	self = node->getIndex();
	m = node->getSubmodule("MobilityManager");
	nodeMobilityModule = check_and_cast<VirtualMobilityManager*>(m);
	m = node->getParentModule()->getSubmodule("wiseTerrain");
	terrain = check_and_cast<WiseBaseTerrain*>(m);
	numSensingDevices = par("numSensingDevices");
	in_str = par("maxSampleRates");
	numProcesses = gateSize("toNodeContainerModule");
	WISE_DEBUG_3("WiseBaseSensorManager::initialize()");
	WISE_DEBUG_3("\tnumSensingDevices = " << numSensingDevices);
	WISE_DEBUG_3("\tnumProcess = " << numProcesses);
	WISE_DEBUG_3("\tmaxSampleRates = " << in_str);

	minSamplingIntervals.clear();
	lastSampleTime.clear();
	for (int i = 0; i < numSensingDevices; i++) {
		minSamplingIntervals.push_back(0);
		lastSampleTime.push_back(-100000.0);
	}

	//get samplerate for each sensor and calculate minSamplingIntervals 
	cStringTokenizer ratesTokenizer(in_str);
	while ((token = ratesTokenizer.nextToken()) != NULL) {
		sampleInterval = (double)(1.0f / atof(token));
		minSamplingIntervals.push_back(sampleInterval);
	}

	cModule *parent = getParentModule();
	physicalProcessName= parent->getParentModule()->par("physicalProcessName");
}

void WiseBaseSensorManager::finish()
{
}

void WiseBaseSensorManager::handleMessage(cMessage * msg)
{
	int msgKind = msg->getKind();

	WISE_DEBUG_3("WiseBaseSensorManager::handleMessage() kind=" << msgKind);
	if (disabled && msgKind != NODE_STARTUP) {
		delete msg;
		msg = NULL;	// safeguard
		return;
	}

	switch (msgKind) {
	case NODE_STARTUP:
	/* Sent by the Application submodule in order to start (switch-on) the
	 * Sensor Device Manager submodule. */
		disabled = 0;
		trace() << "Received STARTUP MESSAGE";
		startup();
		break;
	case SENSOR_READING_MESSAGE:
	/* Assplication to Sensor:  */
		WISE_DEBUG_3("\tSENSOR_READING_MESSAGE");
		WiseSensorManagerMessage *req;
		req = check_and_cast<WiseSensorManagerMessage*>(msg);
		if (req->getType() == WISE_SENS_NORMAL) // Sample Request
			processSampleRequest(req);
		else if (req->getType() == WISE_SENS_COMMAND) // Command Request
			processCommandRequest(req);
		break;
	case PHYSICAL_PROCESS_SAMPLING:
	/* Message received by the physical process. It holds a value and the 
	 * index of the sensor that sent the sample request.  */
		WISE_DEBUG_3("\tPHYSICAL_PROCESS_SAMPLING");
		trace() << "\tPHYSICAL_PROCESS_SAMPLING";
		WisePhysicalProcessMessage *proc_rep;
		proc_rep = check_and_cast<WisePhysicalProcessMessage*>(msg);
		handleSample(proc_rep);
		break;
	case OUT_OF_ENERGY:
		disabled = 1;
		break;
	case DESTROY_NODE:
		disabled = 1;
		send(msg->dup(), "toApplicationModule");
		break;
	default:
		trace() << "WARNING: received packet of unknown type";
	}

	delete msg;
	msg = NULL;		// safeguard
}

/* Sent from Application to initiate a new sample request to the 
 * physical process.
 * The message contains information (its index) about the specific 
 * sensor device that is asking the sample request. 
 * Each sensor device has its own sample-rate and so its sample requests
 * occur/are schedules with different intervals that are held inside 
 * vector minSamplingIntervals[].  */
void WiseBaseSensorManager::processSampleRequest(WiseSensorManagerMessage *req)
{
	if (numProcesses == 0)
		return;
	int s_idx = req->getSensorIndex();
	simtime_t t = simTime(); 			// Current Time
	simtime_t interval = t - lastSampleTime[s_idx]; // Inter sampling

	if (interval < minSamplingIntervals[s_idx]) {
		// We could either send the last available sample or do nothing
		// NOTE: Current solution is to do nothing, the following 
		//       commented lines can be used to in the first case.
		// req->setSensorType(sensorTypes[s_idx].c_str());
		// req->setSensedValue(sensorLastValue[s_idx]);
		// send(req, "toApplicationModule");
		return;
	}
	WisePhysicalProcessMessage *proc_req;
	proc_req = new WisePhysicalProcessMessage("sample request", PHYSICAL_PROCESS_SAMPLING);
	proc_req->setSrcID(self);		//Add the node's ID 
	proc_req->setSensorIndex(s_idx);	//Add sensor's Index
	// Add node's position (3rd coordinate is not used)
	proc_req->setXCoor(nodeMobilityModule->getLocation().x);
	proc_req->setYCoor(nodeMobilityModule->getLocation().y);


	if (strcmp(physicalProcessName, "WiseVideoFile") == 0)
	{
	    // send the req to ONE physical process (the video file captured by the camera)
         send(proc_req, "toNodeContainerModule", self);
	}
	else
	{    // send the req to ALL physical processes
        for (int i = 0; i < numProcesses; i++)
            if (i == 0)
                send(proc_req, "toNodeContainerModule", i);
            else
                send(proc_req->dup(), "toNodeContainerModule", i);
	}
	lastSampleTime[s_idx] = t;
}
