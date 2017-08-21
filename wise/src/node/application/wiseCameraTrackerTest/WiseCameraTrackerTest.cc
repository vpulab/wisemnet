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
//  This file describes a template to test cameratracker applications
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#include "WiseCameraTrackerTest.h"

Define_Module(WiseCameraTrackerTest);

#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE CastaliaModule::trace() << "WISECAMTRACKERAPP: "

ofstream WiseCameraTrackerTest::logger;

#define MULTILOG(str)        \
{                            \
    LOGGER << str << endl;   \
    BASE_TRACE << str;       \
}

/* ************************************************************************** */
/*                 EVENTS from (camera) simple periodic tracker               */
/* ************************************************************************** */
void WiseCameraTrackerTest::at_startup() 
{
	// Called upon simulation start-up
	if (!logger.is_open())
		logger.open("myLog.txt");
	MULTILOG("START-UP");

	// Read module parameters
	some_parameter = par("some_parameter");
	// Access related-module parameters (read number of targets)
	cModule *network = getParentModule()->getParentModule();
	n_targets = network->par("numPhysicalProcesses");
}

void WiseCameraTrackerTest::at_tracker_init() 
{
	// Called upon tracker init
	LOGGER << "INIT" << endl;
	BASE_TRACE << "INIT";

	// Internal structure initialization should take place here!
}

bool WiseCameraTrackerTest::at_tracker_first_sample()
{
	// Called when the first sample (image) is ready
	LOGGER << "FIRST SAMPLE" << endl;
	BASE_TRACE << "FIRST SAMPLE";
	
	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_tracker_sample(); // option 2
}

bool WiseCameraTrackerTest::at_tracker_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
	LOGGER << "END FIRST SAMPLE" << endl;
	BASE_TRACE << "END FIRST SAMPLE";

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_tracker_end_sample(); // option 2
}

bool WiseCameraTrackerTest::at_tracker_sample()
{
	// Called when a new sample (image) is ready
	LOGGER << "NEW SAMPLE" << endl;
	BASE_TRACE << "NEW SAMPLE (SEND BROADCAST)";
	
	// A tracking iteration generally starts here!
	tracking_step_counter++;

	//return if network to ready to process the data
    if (!network_ready)
        return false;

	// NOTE: Measurement has been made through the make_measurements() 
	//       method and is available in the observation vector
	for(vector<measurement_t>::const_iterator m = observations.begin(); m != observations.end(); ++m)
	{
		LOGGER << "\tDetection for Target " << m->tid << " is (" << m->x << "," << m->y << "). To be processed by the tracker..." << endl;

		// Example: Send some information in broadcasts
		WiseCameraTrackerTestMessage *pkt;
		pkt = new WiseCameraTrackerTestMessage("Wise Test Packet", APPLICATION_PACKET);
		pkt->setTrackingCount(tracking_step_counter);
		pkt->setTargetID(m->tid);
		pkt->setPositionX(m->x);
		pkt->setPositionY(m->y);

		pkt->setByteLength(100); // Packet size must be set explicitly

		// Send in broadcast:
		// 1- either using the network (normal case)
		send_message(pkt);              // option 1
		// 2- or using the DirectApplication mechanism (idealistic comm)
		//sendDirectApplicationMessage(pkt, BROADCAST_NETWORK_ADDRESS);	// option 2
	}
	return true;
}

bool WiseCameraTrackerTest::at_tracker_end_sample()
{
	// Called when a new sample (image) is no longer valid
	LOGGER << "END NEW SAMPLE" << endl;
	BASE_TRACE << "END NEW SAMPLE";
	return true;

	// A tracking iteration generally ends here!
}

void WiseCameraTrackerTest::make_measurements(const vector<WiseTargetDetection>&dt)
{
	// Called to properly read the sample: when a new sample is available 
	// a measurement has to be created from it
	LOGGER << "MAKE MEASUREMENT" << endl;
    BASE_TRACE << "MAKE MEASUREMENT";

	// Empty previous observation vector
	observations.clear();

	// Fill the observation vector with the measurement
	for(vector<WiseTargetDetection>::const_iterator d = dt.begin(); d != dt.end(); ++d) {
		// Measurement is: Target ID, and box's center (image plane)
		measurement_t m;
		double w_x, w_y, t_x, t_y;
		m.tid = d->target_id;
		m.x = (d->bb_x_tl + d->bb_x_br) / 2;
		m.y = (d->bb_y_tl + d->bb_y_br) / 2;
		observations.push_back(m);
		w_x = (d->ext_bb_x_tl + d->ext_bb_x_br) / 2;
		w_y = (d->ext_bb_y_tl + d->ext_bb_y_br) / 2;
		t_x = (d->true_bb_x_tl + d->true_bb_x_br) / 2;
		t_y = (d->true_bb_y_tl + d->true_bb_y_br) / 2;
		LOGGER << "\tTarget "<< m.tid << " coords -> Image plane (" << m.x << "," << m.y << ") World (" << w_x << "," << w_y << ") True (" << t_x << "," << t_y << ")" << endl;
	}
} 

void WiseCameraTrackerTest::process_network_message(WiseApplicationPacket *pkt) 
{
	// Called when a packet is received from the network
	LOGGER << "PROCESS NETWORK MESSAGE" << endl;
	BASE_TRACE << "PROCESS NETWORK MESSAGE";

	WiseCameraTrackerTestMessage *m;
	m = check_and_cast<WiseCameraTrackerTestMessage*>(pkt);
	ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();

	LOGGER << "RX from " << ctl.source << ". Packet content: [ k=" << m->getTrackingCount() << "  TID=" << m->getTargetID() << "  Pos=(" << m->getPositionX() << "," << m->getPositionY() << ")  ]" << endl;
    BASE_TRACE << "RX from " << ctl.source << ". Packet content: [k=" << m->getTrackingCount() << "  TID=" << m->getTargetID() << "  Pos=(" << m->getPositionX() << "," << m->getPositionY() << ")]";
	// The received information might be used to write the distributed tracking algorithm
} 

void WiseCameraTrackerTest::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
	// Called when a DirectApplication Message is received
	LOGGER << "HANDLE DIRECT APPLICATION MESSAGE" << endl;
	BASE_TRACE << "HANDLE DIRECT APPLICATION MESSAGE";

	// In this case we treat the message received through DirectApplication as a normal
	// network message. However, the two mechanisms could be used independently.
	process_network_message(pkt);
}
