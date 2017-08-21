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
//  This file describes a template to implement applications in WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#include "WiseBaseApplication.h"
#include "WirelessChannel.h"
#include "WiseUtils.h"

#define perr_app(m) error("\n[Application]:\n " m)
#define perr(m) error(m)
#define BASE_TRACE trace() << "WISEBASE: "
#define ELOGGER elogger << "[" << setw(4) << simTime() << "] @ " << self << " : "

ofstream WiseBaseApplication::elogger;

void WiseBaseApplication::initialize()
{
#if (OMNETPP_VERSION ==0x0500)
    _maxSimtime = strtod(getEnvir()->getConfig()->getConfigValue("sim-time-limit"), NULL);
    _currentRun = getEnvir()->getConfigEx()->getActiveRunNumber();
#else
    _maxSimtime = strtod(ev.getConfig()->getConfigValue("sim-time-limit"), NULL);
    _currentRun = ev.getConfigEx()->getActiveRunNumber();
#endif

	cMessage *m;
	readParameter();

	/* Send the STARTUP message to: 
	 * 1) Sensor_Manager;
	 * 2) Communication module;
	 * 3) APP (self message) so that the node starts to operate.
	 * We are using a random delay IF we must not have node synchronized
	 */
	double startup_delay = simTime().dbl();
	if (!synchronizedStartup)
		startup_delay += genk_dblrand(0) * 0.05 * cpuClockDrift;
	m = new cMessage("Communication [STARTUP]", NODE_STARTUP);
	sendDelayed(m, startup_delay, "toCommunicationModule");
	m = new cMessage("Sensor Dev Mgr [STARTUP]", NODE_STARTUP);
	sendDelayed(m, startup_delay, "toSensorDeviceManager");
	m = new cMessage("App [STARTUP]", NODE_STARTUP);
	scheduleAt(startup_delay, m);

	//compute the COMMUNICATIONS graph (ie, communication range for each camera)
	//This process is initialized at the same time as the node startup
	neighbourDiscoverCOMCompleted=false;
	latencyNeighbourDiscoverCOM = hasPar("latencyNeighbourDiscoverCOM") ? par("latencyNeighbourDiscoverCOM").doubleValue() : 10;
    discoverNeighbours(startup_delay);

	/* Latency measurement is optional. An application can not define the 
	 * following two parameters. If they are not defined then the
	 * declareHistogram and collectHistogram statement are not called.
	 */
	latencyMax = hasPar("latencyHistogramMax") ? par("latencyHistogramMax") : 0;
	latencyBuckets = hasPar("latencyHistogramBuckets") ? par("latencyHistogramBuckets") : 0;
	if (latencyMax > 0 && latencyBuckets > 0)
		declareHistogram("Application level latency, in ms", 0, latencyMax, latencyBuckets);

	last_packet_latency = -1;

	cModule *mp = getParentModule()->getParentModule(); // m=SN
	mp = mp->getSubmodule("wirelessChannel");
	WirelessChannel*w = check_and_cast<WirelessChannel*>(mp);

	double TxPowerUsed_dBm=radioModule->getTXlevel()->txOutputPower; //in CC2420.txt
	double receiverSensitivity =radioModule->getRXmode()->sensitivity; //in CC2420.txt
	double noiseFloor =radioModule->getRXmode()->noiseFloor; //in CC2420.txt
	double d0=1.0; //from wireless channel
	double pathLossExponent=2.4; //from wireless channel
	double PLd0=w->PLd0;//from wireless channel
	txDistMax = d0 * pow(10.0, (TxPowerUsed_dBm - max(receiverSensitivity, noiseFloor+5) - PLd0) / (10.0 * pathLossExponent));
	BASE_TRACE << " max distance="<< txDistMax;
}

void WiseBaseApplication::readParameter()
{
    /* Get a valid references to the objects of the Resources Manager module
     * the Mobility module and the radio module, so that we can make direct
     * calls to their public methods.*/
    cModule *parent = getParentModule();

    if (parent->findSubmodule("ResourceManager") != -1)
        //resMgrModule = check_and_cast <ResourceManager*>(parent->getSubmodule("ResourceManager"));
        resMgr = check_and_cast <WiseResourceManager*>(parent->getSubmodule("ResourceManager"));
     else
        perr_app("Error in getting a valid reference to ResourceManager for direct method calls.");

    if (parent->findSubmodule("SensorManager") != -1)
    {
        //camMgr = check_and_cast <SensorManager*>(parent->getSubmodule("SensorManager"));

        //we first try a cast to the WiseCameraManager type. If error, we consider a generic WiseBaseSensorManager type
        // TODO: add support to different sensors extending 'WiseBaseSensorManager'
        camMgr = dynamic_cast<WiseCameraManager*>(parent->getSubmodule("SensorManager"));
        if (!camMgr)
            senMgr = dynamic_cast<WiseBaseSensorManager*>(parent->getSubmodule("SensorManager"));
        else
            senMgr = NULL;
    }
     else
        perr_app("Error in getting a valid reference to SensorManager for direct method calls.");

    if (parent->findSubmodule("MobilityManager") != -1)
        mobilityModule = check_and_cast <VirtualMobilityManager*>(parent->getSubmodule("MobilityManager"));
     else
        perr_app("Error in getting a valid reference to MobilityManager for direct method calls.");

    // we make no checks here
    radioModule = check_and_cast <Radio*>(parent->getSubmodule("Communication")->getSubmodule("Radio"));

    self = parent->getIndex();
    if (self < 0)
        perr_app("Negative node index, very bad!");
    n_nodes = parent->getParentModule()->par("numNodes");
    cpuClockDrift = resMgr->getCPUClockDrift();
    setTimerDrift(cpuClockDrift);
    disabled = 1;

    applicationID = par("applicationID").stringValue();
    priority = par("priority");
    packetHeaderOverhead = par("packetHeaderOverhead");
    constantDataPayload = par("constantDataPayload");
    isSink = hasPar("isSink") ? par("isSink") : false;

    //parameters in the NED's file (introduced by the user in the opmnetpp.ini file)
    synchronizedStartup = par("synchronizedStartup");
    neighbourDiscoverCOM = hasPar("neighbourDiscoverCOM") ? par("neighbourDiscoverCOM") : false;
    neighbourFullConnectivity = hasPar("neighbourFullConnectivity") ? par("neighbourFullConnectivity") : false;
    userDefinedConnectivity = hasPar("userDefinedConnectivity") ? par("userDefinedConnectivity").stringValue() : "";

    cModule *network = getParentModule()->getParentModule();
    _dummy_comms = network->par("dummy_communication");

    stringstream out;
    out << self;
    selfAddress = out.str();

    // Energy parameters
    maxBatteryLevel = resMgr->par("initialEnergy");
}

void WiseBaseApplication::handleMessage(cMessage * msg)
{
    WiseApplicationPacket *pkt;
	int msgKind = msg->getKind();

	if (disabled && msgKind != NODE_STARTUP){
		delete msg;
		msg = NULL;	// safeguard
		return;
	}

	switch (msgKind)
	{
        case NODE_STARTUP:
            disabled = 0;
            startup(); //to be defined in superclass
            break;
        case APPLICATION_PACKET:
            pkt = check_and_cast <WiseApplicationPacket*>(msg);
            processAppPacket(pkt);
            break;
        case TIMER_SERVICE:
            handleTimerMessage(msg);
            break;
        case SENSOR_READING_MESSAGE:
            WiseSensorManagerMessage *sensMsg;
            sensMsg = check_and_cast <WiseSensorManagerMessage*>(msg);
            handleSensorReading(sensMsg); //to be defined in superclass
            break;
        case OUT_OF_ENERGY:
            pkt = new WiseApplicationPacket("Out-of-energy", APPLICATION_PACKET);
            pkt->setType(WISE_APP_OUT_OF_ENERGY);
            toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS,0);
            BASE_TRACE << "SEND: 'Out-of-energy' (broadcast) with delay=" << 0;/**/
            disabled = 1;
            break;
        case DESTROY_NODE:
            disabled = 1;
            break;
        case NETWORK_CONTROL_MESSAGE:
            handleNetworkControlMessage(msg);
            break;
        case MAC_CONTROL_MESSAGE:
            handleMacControlMessage(msg);
            break;
        case RADIO_CONTROL_MESSAGE:
            RadioControlMessage *radioMsg;
            radioMsg = check_and_cast <RadioControlMessage*>(msg);
            handleRadioControlMessage(radioMsg);
            break;
        default:
            perr("Application module received unexpected message");
	}

	delete msg;
	msg = NULL;		// safeguard
}

void WiseBaseApplication::finish()
{
    //baseLineConsumedEnergy=SIMTIME_DBL(simTime()*resMgrModule->par("baselineNodePower") / 1000.0);
    //nodeConsumedEnergy = resMgrModule->getSpentEnergy();
    //radioConsumedEnergy = nodeConsumedEnergy-captureConsumedEnergy-processingConsumedEnergy-baseLineConsumedEnergy;

    //ELOGGER <<"Consumed AppEnergy 1-NodeAll  = " << nodeConsumedEnergy << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 2-Baseline = " << baseLineConsumedEnergy  << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 3-Radio    = " << radioConsumedEnergy << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 4-Capture  = " << captureConsumedEnergy << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 5-Process  = " << processingConsumedEnergy << " Joules" << endl;

    CastaliaModule::finish();
}

void WiseBaseApplication::requestSensorReading(int index)
{
	// send the request message to the Sensor Device Manager
	WiseSensorManagerMessage *reqMsg = new WiseSensorManagerMessage("application-to-sensorManager (sample request)", SENSOR_READING_MESSAGE);
	//we need the index of the vector in the sensorTypes vector
	//to distinguish the self messages for each sensor
	reqMsg->setSensorIndex(index);
	send(reqMsg, "toSensorDeviceManager");
}

void WiseBaseApplication::toNetworkLayer(cMessage * msg)
{
	if (msg->getKind() == APPLICATION_PACKET)
		perr("toNetworkLayer() function used incorrectly to send APPLICATION_PACKET without destination Network address");
	send(msg, "toCommunicationModule");
}

void WiseBaseApplication::toNetworkLayer(cPacket * pkt, const char *dst, double delay)
{
	WiseApplicationPacket *appPkt = check_and_cast <WiseApplicationPacket*>(pkt);
	appPkt->getApplicationInteractionControl().destination = string(dst);
	appPkt->getApplicationInteractionControl().source = string(SELF_NETWORK_ADDRESS);
	appPkt->getApplicationInteractionControl().applicationID = applicationID;
	appPkt->getApplicationInteractionControl().timestamp = simTime();

	if (delay == 0)
		send(appPkt, "toCommunicationModule");
	else
		sendDelayed(appPkt, delay, "toCommunicationModule");
}

void WiseBaseApplication::sendDirectApplicationMessage(WiseApplicationPacket *m, const char *dst, unsigned delay)
{
	int idx = atoi(dst);
	ApplicationInteractionControl_type &ctrl = m->getApplicationInteractionControl();
	ctrl.source = string(SELF_NETWORK_ADDRESS);
	ctrl.destination = string(dst);
	ctrl.timestamp = simTime();
	m->setType(delay);
	BASE_TRACE << "SEND_DIRECT_APP: to node=" << idx;

	if (idx >= 0) {
		if (idx == self) {
			// Cannot send to myself
			delete m;
			return;
		}
		send(m, "toApplicationDirect", idx);
		return;
	} 
	// To all application modules
	for (int i = 0; i < gateSize("toApplicationDirect"); i++) {
		if (i == self) // DON'T send to myself
			continue;
		send(m->dup(), "toApplicationDirect", i);
	}
	delete m;
}

void WiseBaseApplication::processAppPacket(WiseApplicationPacket *pkt)
{
	switch(pkt->getType()) {
	case WISE_APP_NORMAL:
	case WISE_APP_OUT_OF_ENERGY:
		normalAppPacket(pkt);
		break;
	case WISE_APP_DIRECT_COMMUNICATION:
		handleDirectApplicationMessage(pkt); //to be defined in superclass
		break;
	case WISE_APP_NEIGHBOUR_DISCOVER_REQUEST:
		procDiscoverNeighboursRequest(pkt);
		break;
	case WISE_APP_NEIGHBOUR_DISCOVER_REPLY:
		procDiscoverNeighboursReply(pkt);
		break;
	case WISE_APP_NEIGHBOUR_DISCOVER_TIMEOUT:
		// Should happen only on the last node
		if (!lastNode()) {
			BASE_TRACE << "BAD: WISE_APP_NEIGHBOUR_DISCOVER_TIMEOUT: should be activated only on the last node";
			return;
		}
		discoverNeighboursCompleted();
		break;
	case WISE_APP_NEIGHBOUR_DISCOVER_DONE:
		// Should happen on all the nodes except the last
		if (lastNode()) {
			BASE_TRACE << "BAD: WISE_APP_NEIGHBOUR_DISCOVER_DONE should not be received by the last node";
			return;
		}
		notifyNeighbourDiscoveredCOM();
		break;
	default:
		BASE_TRACE << "Unknown WiseApplicationPacketType = " << pkt->getType();
		break;
	}
}

void WiseBaseApplication::normalAppPacket(WiseApplicationPacket *pkt)
{
	ApplicationInteractionControl_type ctl = pkt->getApplicationInteractionControl();
	if (applicationID.compare(ctl.applicationID.c_str()) != 0) 
		return;
	last_packet_latency = SIMTIME_DBL(simTime() - ctl.timestamp);
	if (latencyMax > 0 && latencyBuckets > 0) {
		double l = 1000 * last_packet_latency; // in [ms]
		collectHistogram("Application level latency [ms]", l);
	}
	fromNetworkLayer(pkt, ctl.source.c_str(), ctl.RSSI, ctl.LQI); //to be defined in a superclass
}
	
void WiseBaseApplication::discoverNeighbours(double startup_delay)
{
    //No neighborgh discovery if we assume that
    if (neighbourFullConnectivity == true)
    {
        BASE_TRACE << "All camera nodes are connected neighbourFullConnectivity=" << neighbourFullConnectivity;

        for (int i=0;i < n_nodes;i++)
            if (i!=self)
                neighborsCOM.push_back(to_string(i));

        BASE_TRACE << "COM: neighbours Discovered!  LIST = " <<  print_vector(neighborsCOM);

        vector<string>::const_iterator n = neighborsCOM.begin();
        for (n = neighborsCOM.begin(); n != neighborsCOM.end(); ++n)
            connectivity_map_comms[*n] = true;

        neighbourDiscoverCOMCompleted=true;
        return;
    }

    if(userDefinedConnectivity.compare("") != 0 && _dummy_comms == true){
        std::vector<string> t;
        Tokenize(userDefinedConnectivity, t, " ");
        int i = -1;
        for (auto c : t) {
            i++;
            //cout << c << endl;
            if(c.compare("1") == 0 && i!=self )
                neighborsCOM.push_back(to_string(i));
        }
        vector<string>::const_iterator n = neighborsCOM.begin();
        for (n = neighborsCOM.begin(); n != neighborsCOM.end(); ++n)
            connectivity_map_comms[*n] = true;

        neighbourDiscoverCOMCompleted=true;

        BASE_TRACE << "COM: user-defined neighbours!  LIST = " <<  print_vector(neighborsCOM);
        return;
    }

	neighborsCOM.clear();
	if (!neighbourDiscoverCOM) {
		notifyNeighbourDiscoveredCOM();
		return;
	}

	// Accounting for startup operations: DEPENDS on the protocols! 
	startup_delay += 0.1;
	// Add a deterministic delay to avoid collision on neighbor discovering
	// messages: DEPENDS on the protocols! delay = node_id * base_sec ... with base_sec = 0.5s
	double base_sec = latencyNeighbourDiscoverCOM;
	startup_delay += self * base_sec; 
	if (lastNode()) {
		// Note: Only the last node has the TIMEOUT; the TIMEOUT might or might not work depending on the protocols!
		WiseApplicationPacket *tout = new WiseApplicationPacket("Neighbor Discover TimeOut",APPLICATION_PACKET);
		tout->setType(WISE_APP_NEIGHBOUR_DISCOVER_TIMEOUT);

		//printf("startup_delay=%.2f\n", startup_delay + (base_sec * 1));
		scheduleAt(startup_delay + (base_sec * 1), tout);
	}
	WiseApplicationPacket *m = new WiseApplicationPacket("Neighbor Discover", APPLICATION_PACKET);
	m->setType(WISE_APP_NEIGHBOUR_DISCOVER_REQUEST);
	//printf("startup_delay=%.2f\n", startup_delay);
	toNetworkLayer(m, BROADCAST_NETWORK_ADDRESS, startup_delay);
	BASE_TRACE << "SEND: 'Neighbor Discover Request' (broadcast) with delay=" << startup_delay;
}

void WiseBaseApplication::procDiscoverNeighboursRequest(WiseApplicationPacket *m)
{
	ApplicationInteractionControl_type &ctrl = m->getApplicationInteractionControl();
	const char *requesting_node = ctrl.source.c_str();
	BASE_TRACE << "RECV: 'Neighbour Discover Request' from node=" << requesting_node << "  (reply by direct Appmsg)";
	m = new WiseApplicationPacket("Neighbour Discovered", APPLICATION_PACKET);
	sendDirectApplicationMessage(m, requesting_node, WISE_APP_NEIGHBOUR_DISCOVER_REPLY);
}

void WiseBaseApplication::procDiscoverNeighboursReply(WiseApplicationPacket *m)
{
	ApplicationInteractionControl_type &ctrl = m->getApplicationInteractionControl();
	neighborsCOM.push_back(string(ctrl.source.c_str()));
	ostringstream os;
	os << " new LIST = [ ";
	vector<string>::const_iterator n;
	for (n = neighborsCOM.begin(); n != neighborsCOM.end(); ++n)
		os << *n << " ";
	BASE_TRACE << "RECV: 'Neighbour Discover Reply' from node=" << ctrl.source << os.str() << "]";
}

void WiseBaseApplication::discoverNeighboursCompleted()
{
	// NOTE: should be activated only on the last node!
	BASE_TRACE << "neighborsCOM Discover COMPLETED";
	WiseApplicationPacket *m = new WiseApplicationPacket("Neighbour Discover COMPLETED", APPLICATION_PACKET);
 	// notify all the other nodes
	sendDirectApplicationMessage(m, BROADCAST_NETWORK_ADDRESS, WISE_APP_NEIGHBOUR_DISCOVER_DONE);
	// notify myself (the last node)
	notifyNeighbourDiscoveredCOM();
}

void WiseBaseApplication::notifyNeighbourDiscoveredCOM()
{
    if (!neighbourDiscoverCOM) {
        // In this case we just build a fake connectivity map all-to-all
        for (int i = 0; i < n_nodes; i++) {
            ostringstream oss;
            oss << i;
            neighborsCOM.push_back(oss.str());
        }
    }
    BASE_TRACE << "COM: neighbours Discovered!  LIST = " <<  print_vector(neighborsCOM);

    vector<string>::const_iterator n = neighborsCOM.begin();
    for (n = neighborsCOM.begin(); n != neighborsCOM.end(); ++n)
        connectivity_map_comms[*n] = true;

    neighbourDiscoverCOMCompleted=true;
}

void WiseBaseApplication::handleNetworkControlMessage(cMessage *) {}; //!< Process a network control message (to be implemented in superclass, not mandatory?)
void WiseBaseApplication::handleMacControlMessage(cMessage *) {}; //!< Process a MAC control message (to be implemented in superclass, not mandatory?)
void WiseBaseApplication::handleRadioControlMessage(RadioControlMessage *) {}; //!< Process a radio control message (to be implemented in superclass, not mandatory?)
