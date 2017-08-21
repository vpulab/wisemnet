// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk                                        
// *****************************************************************************

#include "WiseCameraMultiVideo.h"
#include "TMacControlMessage_m.h"

#include "WiseCameraMultiVideoPacket_m.h"
#include "WiseCameraMultiVideoPacketFull_m.h"

Define_Module(WiseCameraMultiVideo);

#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE trace() << "WISEGMSN: "

ofstream WiseCameraMultiVideo::logger;
std::ofstream *final_writerMV=NULL;

/*! Class destructor */
WiseCameraMultiVideo::~WiseCameraMultiVideo()
{
    if (final_writerMV) {
        final_writerMV->close();
        delete final_writerMV;
        final_writerMV = NULL;
    }
}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraMultiVideo::at_startup()
{
    // Called upon simulation start-up
    BASE_TRACE << "START-UP";

	if (!logger.is_open())
		logger.open("myLog.txt");

    if (final_writerMV == NULL)
        final_writerMV = new ofstream();

	// Access related-module parameters (read number of targets)
	//cModule *network = getParentModule()->getParentModule();
	mode = par("mode");
	isSink = par("isSink");

    LOGGER << " mode=" << mode << endl;

    //determine the sink node via direct connection
    sinkNode = self;
    for (int i = 0; i < n_nodes; i++) {
            if (i == self)
                continue;
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");

            WiseCameraMultiVideo *c = check_and_cast<WiseCameraMultiVideo*>(m);
            if (c->isSink == true)
                sinkNode = i;
    }
}

/*!
 * From the WiseBaseApplication class.
 *
 * @param[in] c Message received
 */
void WiseCameraMultiVideo::handleMacControlMessage(cMessage *c)
{
    TMacControlMessage *m;
    try {
        m = check_and_cast<TMacControlMessage*>(c);
    } catch (exception& e) {
        // Ignore the control message if it is not from TMac
        return;
    }
    if (m->getType() == TMAC_TX_SUCCESS)
        BASE_TRACE << "packet SENT with T-MAC: retries = " << m->getTxRetries() << "  (max " << m->getMaxTxRetries() << ")";
    else
        if (m->getType() == TMAC_TX_FAILURE)
            BASE_TRACE << "packet NOT SENT with T-MAC: max retries reached (" << m->getMaxTxRetries() << ")";
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by KFs.
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseCameraMultiVideo::make_measurements(const vector<WiseTargetDetection>&dt)
{

}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraMultiVideo::at_init()
{
    return true;
}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraMultiVideo::at_first_sample()
{
	// Called when the first sample (image) is ready
	BASE_TRACE << "FIRST SAMPLE";
	
	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_sample(); // option 2
}

/*!
 * KF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraMultiVideo::at_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
	BASE_TRACE << "END FIRST SAMPLE";

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraMultiVideo::at_sample()
{
    BASE_TRACE << "PROCESSING!!!!!";

    // Called when a new sample (image) is ready
    _step_counter++;

    std::ostringstream os;
    //os << "NODE" << self << " Processing framerate @" << 1/this->sampling_time << "fps (Source @" << this->resMgrModule->getFrameRate() << "fps)";

    //IplImage img = _frame;

    if ((int)this->_step_counter == 1)
    {
        pMOG2 = cv::createBackgroundSubtractorMOG2(); //MOG2 approach
    }

    //perform background subtraction
    if (mode == 2)
    {
        pMOG2->apply(_frame, fgMaskMOG);; //perform background subtraction
        cv::imshow("IMG", _frame); //show current image
        cv::imshow("FGMASK", fgMaskMOG); //show Foreground mask
        cv::waitKey(1);/**/
    }

    // SINK NODE
    BASE_TRACE << "SEND MESSAGE";
    std::ostringstream dst;
    dst << sinkNode;

    // SEND FULL _frame
    WiseCameraMultiVideoPacketFull *pkt1 = new WiseCameraMultiVideoPacketFull("TX:_frame", APPLICATION_PACKET);
    pkt1->setType(WISE_APP_NORMAL); //normal APP for the network
    pkt1->setTypeNeighbour(WISE_NEIGHBOUR_COM);

    switch (mode)
    {
        case 1:
            pkt1->setFrame(_frame);
            break;
        case 2:
            pkt1->setFrame(fgMaskMOG);
            break;
    }

    toNetworkLayer(pkt1->dup(), dst.str().c_str()); // send pkt to sink
    delete pkt1;

    return true;
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicAlgo".
 */
bool WiseCameraMultiVideo::at_end_sample()
{
	// Called when a new sample (image) is no longer valid
	BASE_TRACE << "END NEW SAMPLE";
	return true;
}


/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraMultiVideoMessage type)
 */
bool WiseCameraMultiVideo::process_network_message(WiseApplicationPacket *pkt)
{
    BASE_TRACE << "PROCESS NETWORK MESSAGE";
    LOGGER << "PROCESS NETWORK MESSAGE";

    const WiseCameraMultiVideoPacketFull *m = check_and_cast<const WiseCameraMultiVideoPacketFull*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();

    std::ostringstream os;
    os << "NODE" << self << " Received frame from node " << ctl.source;

    cv::imshow(os.str(), m->getFrame());
    cv::waitKey(1);/**/

    return true;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraMultiVideo::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
    // Called when a DirectApplication Message is received
    BASE_TRACE << "HANDLE DIRECT APPLICATION MESSAGE";

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}
