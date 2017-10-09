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

/**
 * \file WiseBaseApp.cc
 * \author Juan C. SanMiguel (2017)
 * \author C. Nastasi (2011)
 * \brief Source file for the WiseBaseApp class
 * \version 1.4
 */

#include <castalia/src/wirelessChannel/WirelessChannel.h>   //Castalia wireless channel
#include <castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h> //Castalia MAC for "TMAC_TX_SUCCESS" & "TMAC_TX_FAILURE"

#include <wise/src/node/application/wiseBaseApp/WiseBaseApp.h> //header class
#include <wise/src/utils/WiseUtils.h> //required for "print_vector" and "Tokenize" methods
#include <wise/src/utils/WiseDebug.h> //for logs/debug

#include <sys/stat.h> //dir utilities

#define perr_app(m) error("\n[WiseBaseApp]:\n " m) // Error messages from the application layer
#define perr(m) error(m)                           // Error messages from the node itself

/*
 * \brief Method for resource initialization (variables and structures)
 */
void WiseBaseApp::initialize()
{
    WISE_DEBUG_31("WiseBaseApp::initialize() called");

#if (OMNETPP_VERSION ==0x0500)
    _maxSimtime = strtod(getEnvir()->getConfig()->getConfigValue("sim-time-limit"), NULL);
    _currentRun = getEnvir()->getConfigEx()->getActiveRunNumber();
#else
    _maxSimtime = strtod(ev.getConfig()->getConfigValue("sim-time-limit"), NULL);
    _currentRun = ev.getConfigEx()->getActiveRunNumber();
#endif

	//read input parameters
	readParameter();

	/* Send the STARTUP message to: 
	 * 1) Sensor_Manager;
	 * 2) Communication module;
	 * 3) APP (self message) so that the node starts to operate.
	 * We are using a random delay IF we must not have node synchronized
	 */
	double startup_delay = simTime().dbl(); //init time equal for all nodes
	if (!synchronizedStartup)
		startup_delay += genk_dblrand(0) * 0.05 * cpuClockDrift;
	cMessage *m = new cMessage("Communication [STARTUP]", NODE_STARTUP);
	sendDelayed(m, startup_delay, "toCommunicationModule");
	m = new cMessage("Sensor Dev Mgr [STARTUP]", NODE_STARTUP);
	sendDelayed(m, startup_delay, "toSensorDeviceManager");
	m = new cMessage("App [STARTUP]", NODE_STARTUP);
	scheduleAt(startup_delay, m);

	//compute the COMMUNICATIONS graph (ie, communication range for each camera)
	//This process is initialized at the same time as the node startup
	_neighborDiscoverCOMCompleted=false;
	latencyNeighborDiscoverCOM = hasPar("latencyNeighborDiscoverCOM") ? par("latencyNeighborDiscoverCOM").doubleValue() : 10;
    discoverNeighbors(startup_delay);

	//Latency measurement is optional. An application can not define the
	//following two parameters. If they are not defined then the
	//declareHistogram and collectHistogram statement are not called.
	latencyMax = hasPar("latencyHistogramMax") ? par("latencyHistogramMax") : 0;
	latencyBuckets = hasPar("latencyHistogramBuckets") ? par("latencyHistogramBuckets") : 0;
	if (latencyMax > 0 && latencyBuckets > 0)
		declareHistogram("Application level latency, in ms", 0, latencyMax, latencyBuckets);

	last_packet_latency = -1;
	_bytesTX = 0;
	_bytesRX = 0;

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
	WISE_DEBUG_31("WiseBaseApp:: TX max distance="<< txDistMax);

}

/*
 * \brief Method to read configuration parameters (application layer)
 */
void WiseBaseApp::readParameter()
{
    WISE_DEBUG_31("WiseBaseApp::readParameter() called");

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
    _neighborDiscoverCOM = hasPar("neighborDiscoverCOM") ? par("neighborDiscoverCOM") : false;
    _fullConnectivityCOM = hasPar("fullConnectivityCOM") ? par("fullConnectivityCOM") : false;
    _manualConnectivityCOM = hasPar("manualConnectivityCOM") ? par("manualConnectivityCOM").stringValue() : "";

    cModule *network = getParentModule()->getParentModule();
    _dummy_comms = network->par("dummy_communication");

    //own address/id
    selfAddress = std::to_string(self);

    // Energy parameters
    maxBatteryLevel = resMgr->par("initialEnergy");

    //baseline output path to generate log files
    base_out_path = par("base_out_path").stringValue();

    //check if output path exists (create if not)
    if (dirExists(base_out_path.c_str()) == true)
    {
        WISE_DEBUG_31("WiseBaseApp::output directory exists at " << base_out_path.c_str());
    }
    else
    {
        const int dir_err = mkdir(base_out_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            WISE_DEBUG_31("WiseBaseApp::Error creating output directory");
            exit(1);
        }
        else
            WISE_DEBUG_31("WiseBaseApp::output directory created at " << base_out_path.c_str());
    }
}

/*
 * \brief Method to handle generic messages received in the application layer
 *
 *  Method to handle a message received in the application layer from
 *  other layers (sensing/sensor, network, resource manager) or timers
 *  that control the node's behavior. It redirects each type of message
 *  to the corresponding function according to its "kind".
 *
 * \param msg Message sent to the application layer
 */
void WiseBaseApp::handleMessage(cMessage * msg)
{
    WISE_DEBUG_31("WiseBaseApp::handleMessage() called");

    WiseBaseAppPacket *pkt;
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
            pkt = check_and_cast <WiseBaseAppPacket*>(msg);
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
            pkt = new WiseBaseAppPacket("Out-of-energy", APPLICATION_PACKET);
            pkt->setSubType(WISE_APP_OUT_OF_ENERGY);
            toNetworkLayer(pkt, BROADCAST_NETWORK_ADDRESS,0);
            WISE_DEBUG_31("WiseBaseApp:: SEND: 'Out-of-energy' (broadcast) with delay=" << 0);
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

/*
 * \brief Method to call upon terminating the application layer.
 *
 */
void WiseBaseApp::finish()
{
    WISE_DEBUG_31("WiseBaseApp::finish() called");

    //baseLineConsumedEnergy=SIMTIME_DBL(simTime()*resMgrModule->par("baselineNodePower") / 1000.0);
    //nodeConsumedEnergy = resMgrModule->getSpentEnergy();
    //radioConsumedEnergy = nodeConsumedEnergy-captureConsumedEnergy-processingConsumedEnergy-baseLineConsumedEnergy;

    //ELOGGER <<"Consumed AppEnergy 1-NodeAll  = " << nodeConsumedEnergy << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 2-Baseline = " << baseLineConsumedEnergy  << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 3-Radio    = " << radioConsumedEnergy << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 4-Capture  = " << captureConsumedEnergy << " Joules" << endl;
    //ELOGGER <<"Consumed AppEnergy 5-Process  = " << processingConsumedEnergy << " Joules" << endl;

    declareOutput("Bytes TX");
    collectOutput("Bytes TX", "bytes", _bytesTX);

    declareOutput("Bytes RX");
    collectOutput("Bytes RX", "bytes", _bytesRX);

    CastaliaModule::finish();
}

/*
 * \brief Method to request data from the sensing module
 *
 *  Method to request data from the sensing module. A message is
 *  generated and sent to the "sensorManager" via the associated
 *  gate (see Node.ned). The "sensorManager" can contain a variable
 *  number of sensors which are referenced by "index".
 *
 * \param index Identifier for the sensor to be requested
 */
void WiseBaseApp::requestSensorReading(int index)
{
    WISE_DEBUG_31("WiseBaseApp::requestSensorReading() called");

	// create the request message to the Sensor Device Manager
	WiseSensorManagerMessage *reqMsg = new WiseSensorManagerMessage("application-to-sensorManager (sample request)", SENSOR_READING_MESSAGE);
	//we need the index of the vector in the sensorTypes vector
	//to distinguish the self messages for each sensor
	reqMsg->setSensorIndex(index);
	// send the request message to the Sensor Device Manager
	send(reqMsg, "toSensorDeviceManager");
}

/*
 * \brief Method to broadcast a message to the network
 * \param msg Message to be sent (required APPLICATION_PACKET kind)
 */
void WiseBaseApp::toNetworkLayer(cMessage * msg)
{
    WISE_DEBUG_31("WiseBaseApp::toNetworkLayer(msg) called");

	if (msg->getKind() == APPLICATION_PACKET)
		perr("toNetworkLayer() function used incorrectly to send APPLICATION_PACKET without destination Network address");
	send(msg, "toCommunicationModule");
}

/*
 * \brief Method to send a packet to the network with parameters
 *
 *  Note that cPacket is a subclass of cMessage. CPacket is used for network
 *  packets in a communication network and cMessage is used for everything
 *  else. Both classes are free to subclass according to user needs.
 *
 * \param pkt Packet to be sent (required APPLICATION_PACKET kind)
 * \param dst Destination node (-1 for broadcast)
 * \param delay Associated delay (default 0)
 *
 */
void WiseBaseApp::toNetworkLayer(cPacket * pkt, const char *dst, double delay)
{
    WISE_DEBUG_31("WiseBaseApp::toNetworkLayer(pkt,dst,delay) called");

    //create the packet
	WiseBaseAppPacket *appPkt = check_and_cast <WiseBaseAppPacket*>(pkt);
	appPkt->getApplicationInteractionControl().destination = string(dst);
	appPkt->getApplicationInteractionControl().source = string(SELF_NETWORK_ADDRESS);
	appPkt->getApplicationInteractionControl().applicationID = applicationID;
	appPkt->getApplicationInteractionControl().timestamp = simTime();

	//Update stats for sent data
	_bytesTX = _bytesTX + appPkt->getByteLength();

	//send the packet
	if (delay == 0)
		send(appPkt, "toCommunicationModule");
	else
		sendDelayed(appPkt, delay, "toCommunicationModule");
}

/*
 * \brief Method to send a packet without passing through the network
 *
 *  This method implements an idealistic situation where nodes communicate without
 *  any delays or protocols. Therefore, data/packets can arrive instantly to the
 *  destination. This method emulates a typical environment such as Matlab where
 *  each function can have instantaneous access to all source code/functions.
 *
 * \param m Packet to be sent (required APPLICATION_PACKET kind)
 * \param dst Destination node (-1 for broadcast)
 * \param delay Associated delay (default 0)
 *
 */
void WiseBaseApp::sendDirectApplicationMessage(WiseBaseAppPacket *m, const char *dst, unsigned delay)
{
    WISE_DEBUG_31("WiseBaseApp::sendDirectApplicationMessage(...) called");

	int idx = atoi(dst);
	ApplicationInteractionControl_type &ctrl = m->getApplicationInteractionControl();
	ctrl.source = string(SELF_NETWORK_ADDRESS);
	ctrl.destination = string(dst);
	ctrl.timestamp = simTime();
	WISE_DEBUG_31("WiseBaseApp: SEND_DIRECT_APP: to node=" << idx);

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

/*
 * \brief Method to handle packets received from the network
 *
 *  This method performs a second-hierarchy of routing for packets of
 *  APPLICATION_PACKET type according to their "subType". For example,
 *  initialization packets are redirected to specific functions whereas
 *  "generic" packets are redirected to the function "normalAppPacket"
 *  for further processing.
 *
 * \param pkt Packet to be processed (required APPLICATION_PACKET kind)
 *
 */
void WiseBaseApp::processAppPacket(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_31("WiseBaseApp::processAppPacket(..) called");

    //Update stats for received data
    _bytesRX = _bytesRX + pkt->getByteLength();

	switch(pkt->getSubType()) {
        case WISE_APP_NORMAL:
            normalAppPacket(pkt);
            break;
        case WISE_APP_OUT_OF_ENERGY:
            normalAppPacket(pkt);
            break;
        case WISE_APP_DIRECT_COMMUNICATION:
            handleDirectApplicationMessage(pkt); //to be defined in superclass
            break;
        case WISE_APP_NEIGHBOR_DISCOVER_REQUEST:
            procDiscoverNeighborsRequest(pkt);
            break;
        case WISE_APP_NEIGHBOR_DISCOVER_REPLY:
            procDiscoverNeighborsReply(pkt);
            break;
        case WISE_APP_NEIGHBOR_DISCOVER_TIMEOUT:
            // Should happen only on the last node
            if (!lastNode()) {
                WISE_DEBUG_31("WiseBaseApp:: WISE_APP_Neighbor_DISCOVER_TIMEOUT: should be activated only on the last node");
                return;
            }
            discoverNeighborsCompleted();
            break;
        case WISE_APP_NEIGHBOR_DISCOVER_DONE:
            // Should happen on all the nodes except the last
            if (lastNode()) {
                WISE_DEBUG_31("WiseBaseApp:: WISE_APP_Neighbor_DISCOVER_DONE should not be received by the last node");
                return;
            }
            notifyNeighborDiscoveredCOM();
            break;
        default:
            WISE_DEBUG_31("WiseBaseApp:: Unknown WiseBaseAppPacketSubType = " << pkt->getSubType());
            break;
	}
}

/*
 * \brief Method to process a network packet received from the network
 *
 *  This method extracts some metadata from the received packets and redirects them
 *  to the function "fromNetworkLayer" that needs to be implemented in sub-classes
 *  to provide specific functionality for each application.
 *
 * \param pkt Packet to be processed (required APPLICATION_PACKET kind)
 *
 */
void WiseBaseApp::normalAppPacket(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_31("WiseBaseApp::normalAppPacket(..) called");

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
	
/*
 * \brief Method to start the discovery of neighbors in the network
 *
 *  This method broadcast packets to discover the node neighbors (i.e. other nodes
 *  that can be reached via communication capabilities). If the communication is
 *  manually defined (FLAG "_manualConnectivityCOM" is true), there is no broadcast
 *  and the communication connectivity is read from the configuration file.
 *  The "startup_delay" variable may need to be increased as the number of nodes in
 *  the network increases to avoid TX/RX failures due to collisions.
 *
 * \param startup_delay Delay between two consecutive broadcast of packets
 *
 */
void WiseBaseApp::discoverNeighbors(double startup_delay)
{
    WISE_DEBUG_31("WiseBaseApp::discoverNeighbors(..) called");

    //No neighborgh discovery if we assume that
    if (_fullConnectivityCOM == true)
    {
        WISE_DEBUG_31("WiseBaseApp: All camera nodes are connected NeighborFullConnectivity=" << _fullConnectivityCOM);

        for (int i=0;i < n_nodes;i++)
            if (i!=self)
                _neighborsCOM.push_back(to_string(i));

        WISE_DEBUG_31("WiseBaseApp: COM Neighbors Discovered!  LIST = " <<  print_vector(_neighborsCOM));

        vector<string>::const_iterator n = _neighborsCOM.begin();
        for (n = _neighborsCOM.begin(); n != _neighborsCOM.end(); ++n)
            _connectivity_map_comms[*n] = true;

        _neighborDiscoverCOMCompleted=true;
        return;
    }

    //if(_manualConnectivityCOM.compare("") != 0 && _dummy_comms == true){
    if(_manualConnectivityCOM.compare("") != 0){

        std::vector<string> t;
        Tokenize(_manualConnectivityCOM, t, " ");
        int i = -1;
        for (auto c : t) {
            i++;
            //cout << c << endl;
            if(c.compare("1") == 0 && i!=self )
                _neighborsCOM.push_back(to_string(i));
        }
        vector<string>::const_iterator n = _neighborsCOM.begin();
        for (n = _neighborsCOM.begin(); n != _neighborsCOM.end(); ++n)
            _connectivity_map_comms[*n] = true;

        _neighborDiscoverCOMCompleted=true;

        WISE_DEBUG_31("WiseBaseApp: COM user-defined Neighbors!  LIST = " <<  print_vector(_neighborsCOM));
        return;
    }

	_neighborsCOM.clear();
	if (!_neighborDiscoverCOM) {
		notifyNeighborDiscoveredCOM();
		return;
	}

	// Accounting for startup operations: DEPENDS on the protocols! 
	startup_delay += 0.1;
	// Add a deterministic delay to avoid collision on neighbor discovering
	// messages: DEPENDS on the protocols! delay = node_id * base_sec ... with base_sec = 0.5s
	double base_sec = latencyNeighborDiscoverCOM;
	startup_delay += self * base_sec; 
	if (lastNode()) {
		// Note: Only the last node has the TIMEOUT; the TIMEOUT might or might not work depending on the protocols!
		WiseBaseAppPacket *tout = new WiseBaseAppPacket("Neighbor Discover TimeOut",APPLICATION_PACKET);
		tout->setSubType(WISE_APP_NEIGHBOR_DISCOVER_TIMEOUT);

		//printf("startup_delay=%.2f\n", startup_delay + (base_sec * 1));
		scheduleAt(startup_delay + (base_sec * 1), tout);
	}
	WiseBaseAppPacket *m = new WiseBaseAppPacket("Neighbor Discover", APPLICATION_PACKET);
	m->setSubType(WISE_APP_NEIGHBOR_DISCOVER_REQUEST);
	//printf("startup_delay=%.2f\n", startup_delay);
	toNetworkLayer(m, BROADCAST_NETWORK_ADDRESS, startup_delay);
	WISE_DEBUG_31("WiseBaseApp: SEND 'Neighbor Discover Request' (broadcast) with delay=" << startup_delay);
}

/*
 * \brief Method to process a packet received during the discovery of neighbors in the network
 * \param m Packet received
 *
 */
void WiseBaseApp::procDiscoverNeighborsRequest(WiseBaseAppPacket *m)
{
    WISE_DEBUG_31("WiseBaseApp::procDiscoverNeighborsRequest(..) called");

	ApplicationInteractionControl_type &ctrl = m->getApplicationInteractionControl();
	const char *requesting_node = ctrl.source.c_str();
	WISE_DEBUG_31("WiseBaseApp: RECV 'Neighbor Discover Request' from node=" << requesting_node << "  (reply by direct Appmsg)");
	m = new WiseBaseAppPacket("Neighbor Discovered", APPLICATION_PACKET);
	sendDirectApplicationMessage(m, requesting_node, WISE_APP_NEIGHBOR_DISCOVER_REPLY);
}

/*
 * \brief Method to reply a neighbor node acknowledging the packet received
 * \param m Packet received
 *
 */
void WiseBaseApp::procDiscoverNeighborsReply(WiseBaseAppPacket *m)
{
    WISE_DEBUG_31("WiseBaseApp::procDiscoverNeighborsRequest(..) called");

	ApplicationInteractionControl_type &ctrl = m->getApplicationInteractionControl();
	_neighborsCOM.push_back(string(ctrl.source.c_str()));
	ostringstream os;
	os << " new LIST = [ ";
	vector<string>::const_iterator n;
	for (n = _neighborsCOM.begin(); n != _neighborsCOM.end(); ++n)
		os << *n << " ";
	WISE_DEBUG_31("WiseBaseApp: RECV 'Neighbor Discover Reply' from node=" << ctrl.source << os.str() << "]");
}

/*
 * \brief Method to establish the completion of the neighbor discovery phase (timeout)
 *
 */
void WiseBaseApp::discoverNeighborsCompleted()
{
    // NOTE: should be activated only on the last node!
    WISE_DEBUG_31("WiseBaseApp::discoverNeighborsCompleted(..) called - neighborsCOM Discover COMPLETED");

	WiseBaseAppPacket *m = new WiseBaseAppPacket("Neighbor Discover COMPLETED", APPLICATION_PACKET);
 	// notify all the other nodes
	sendDirectApplicationMessage(m, BROADCAST_NETWORK_ADDRESS, WISE_APP_NEIGHBOR_DISCOVER_DONE);
	// notify myself (the last node)
	notifyNeighborDiscoveredCOM();
}

/*
 * \brief Method to save all data received from the nodes replying to our "discovery request"
 *
 */
void WiseBaseApp::notifyNeighborDiscoveredCOM()
{
    WISE_DEBUG_31("WiseBaseApp::notifyNeighborDiscoveredCOM(..) called");
    if (!_neighborDiscoverCOM) {
        // In this case we just build a fake connectivity map all-to-all
        for (int i = 0; i < n_nodes; i++) {
            ostringstream oss;
            oss << i;
            _neighborsCOM.push_back(oss.str());
        }
    }
    WISE_DEBUG_31("WiseBaseApp: COM neighbors Discovered!  LIST = " <<  print_vector(_neighborsCOM));

    vector<string>::const_iterator n = _neighborsCOM.begin();
    for (n = _neighborsCOM.begin(); n != _neighborsCOM.end(); ++n)
        _connectivity_map_comms[*n] = true;

    _neighborDiscoverCOMCompleted=true;
}

/*
 * \brief Method to process a MAC control message
 * \param c Message received
 */
void WiseBaseApp::handleMacControlMessage(cMessage *c)
{
    TMacControlMessage *m;
    try {
        m = check_and_cast<TMacControlMessage*>(c);
    } catch (exception& e) {
        // Ignore the control message if it is not from TMac
        return;
    }

    if (m->getType() == TMAC_TX_SUCCESS)
    {
        WISE_DEBUG_31("WiseBaseApp: packet SENT with T-MAC: retries = " << m->getTxRetries() << "  (max " << m->getMaxTxRetries() << ")");
    }
    else
    {
        if (m->getType() == TMAC_TX_FAILURE)
            WISE_DEBUG_31("WiseBaseApp: packet NOT SENT with T-MAC: max retries reached (" << m->getMaxTxRetries() << ")");
    }
}
