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

#include "WiseMovingTarget.h"
#include "WiseDebug.h"
#include <sstream>
#include <cmath>
#include <opencv.hpp>

#define perr_app(m) opp_error("\n[WiseMovingTarget]:\n " m)
#define perr(m) opp_error(m)

#ifndef PI
#define PI (3.141592653589793)
#endif

//#define MIN(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

Define_Module(WiseMovingTarget);

ofstream *WiseMovingTarget::writer = NULL;

WiseMovingTarget::~WiseMovingTarget()
{
	if (writer != NULL) {
		writer->close();
		delete writer;
		writer = NULL;
	}
}
	
#define TMP_STEP_SIZE 2

void WiseMovingTarget::initialize()
{
	WiseBasePhysicalProcess::initialize();
	WISE_DEBUG_10("WiseMovingTarget::initialize()");
	load_parameters();

	if (random_init == true){
	    //srand(time(NULL)); // Seed the time
	    srand(cv::getTickCount()); // Seed the time
	    x_init = fmod(rand(),(move_max_x-move_min_x + 1)) + move_min_x;
	    y_init = fmod(rand(),(move_max_y-move_min_y + 1)) + move_min_y;
	}

	if (random_init == true)
	    noise = fmod(rand(),(noise_max-noise_min + 1)) + noise_min;

    std::cout << "target=" << self << " xinit= " << x_init << " yinit= " << y_init << " noise=" << noise << std::endl;
	x_curr = x_init;
	y_curr = y_init;
	z_curr = z_init;
	target_info.id = self;
	target_info.pos_x = x_init;
	target_info.pos_y = y_init;
	target_info.pos_z = z_init;
	target_info.bb_width = target_width;
	target_info.bb_height = target_height;
	target_info.bb_depth = target_depth;
	target_info.unique_color = unique_color;
	lin_x_step = TMP_STEP_SIZE;
	lin_y_step = TMP_STEP_SIZE;
	diagonal = lin_x_step / sqrt(TMP_STEP_SIZE);
	rotation_angle = 0;
	radius = MIN(terrain->get_x_size(), terrain->get_y_size()) / 3.0;
	rotation_step = (5.0 / 180.0) * PI;
	if (move_func != NULL)
		scheduleAt(simTime() + update_time + move_later, new cMessage("Move", TIMER_SERVICE));
	else
		terrain->place_target(target_info);
	if (log_enabled) {
		if (writer == NULL) {
		    std::ostringstream os;

#if (OMNETPP_VERSION ==0x0500)
    double curRun = getEnvir()->getConfigEx()->getActiveRunNumber();
#else
    double curRun = ev.getConfigEx()->getActiveRunNumber();
#endif
		    os << "targets_info" << "_r" << std::setfill('0') << std::setw(4) << curRun << ".txt";
			writer = new ofstream(os.str().c_str());
		}
		log_information();
	}
}

void WiseMovingTarget::handleMessage(cMessage * msg)
{
	WISE_DEBUG_10("WiseMovingTarget::handleMessage()");

	WiseMovingTargetMessage *tgt_msg;
	WiseTargetBoundingBox bb;
	switch (msg->getKind()) {
	case PHYSICAL_PROCESS_SAMPLING: 
		// NOTE: substitute the req message with a specific one
		WisePhysicalProcessMessage *s_msg;
		s_msg = check_and_cast <WisePhysicalProcessMessage*>(msg);
		//WISE_DEBUG_2("WiseMovingTarget: PHYSICAL_PROCESS_SAMPLING:");
		//WISE_DEBUG_2("\tsrc_node = " << s_msg->getSrcID());
		//WISE_DEBUG_2("\tsrc_sensor = " << s_msg->getSensorIndex());
		//WISE_DEBUG_2("\ttarget ID (phyProc ID) = " << self);
		tgt_msg = new WiseMovingTargetMessage("Target Message", PHYSICAL_PROCESS_SAMPLING);
		tgt_msg->setTargetID(self);
		calculate_bounding_box(bb);
		tgt_msg->setBoundingBox(bb);
		// Send reply back to the node which made the request
		send(tgt_msg, "toNode", s_msg->getSrcID());
		delete s_msg;
		s_msg = tgt_msg;
		break;
	case TIMER_SERVICE: 
		//WISE_DEBUG_2("WiseMovingTarget: TIME_SERVICE:");
		if (move_func) // Should not be necessary
			(this->*move_func)();
		if (log_enabled)
			log_information();
	        target_info.pos_x = x_curr;
	        target_info.pos_y = y_curr;
	        target_info.pos_z = z_curr;
	        terrain->place_target(target_info);
		scheduleAt(simTime() + update_time, msg);
		break;
	default:
		perr_app("Received message other than PHYSICAL_PROCESS_SAMPLING or TIME_SERVICE");
		delete msg;
	}
}

void WiseMovingTarget::finishSpecific()
{
	WISE_DEBUG_10("WiseMovingTarget::finishSpecific()");
}

void WiseMovingTarget::load_parameters()
{
    unique_color = par("unique_color").boolValue();
	x_init = par("x_init");
	y_init = par("y_init");
	z_init = par("z_init");
	random_init = par("random_init");
	random_noise = par("random_noise");
	target_width = par("bb_width");
	target_height = par("bb_height");
	target_depth = par("bb_height");
	update_time = par("update_time");
	noise_max = par("noise_max");
	noise_min = par("noise_min");
	move_min_x = par("move_min_x");
	move_max_x = par("move_max_x");
	move_min_y = par("move_min_y");
	move_max_y = par("move_max_y");
	move_later = par("move_later");
	log_enabled = par("log_enabled");
	noise = par("noise");
	if (move_min_x != 0 && x_init < move_min_x)
		x_init = move_min_x;
	else if (move_max_x != 0 && x_init > move_max_x)
		x_init = move_max_x;
	if (move_min_y != 0 && y_init < move_min_y)
		y_init = move_min_y;
	else if (move_max_y != 0 && y_init > move_max_y)
		y_init = move_max_y;
	if (par("move_type").stdstringValue() == "lin_noise")
		move_func = &WiseMovingTarget::move_linear_noise;
	else if (par("move_type").stdstringValue() == "circ_noise")
		move_func = &WiseMovingTarget::move_circular_noise;
	else if (par("move_type").stdstringValue() == "lin_random")
		move_func = &WiseMovingTarget::move_linear_random;
	else if (par("move_type").stdstringValue() == "lincirc_noise")
		move_func = &WiseMovingTarget::move_lincirc_noise;
	else if (par("move_type").stdstringValue() == "random_walk")
		move_func = &WiseMovingTarget::move_random_walk;
	else if (par("move_type").stdstringValue() == "random_walk8")
		move_func = &WiseMovingTarget::move_random_walk_8;
	else
		move_func = NULL;
}

void WiseMovingTarget::log_information()
{
	static bool first_row = true;
	WiseTargetBoundingBox bb;
	calculate_bounding_box(bb);
	const char *sep = "  ";
	if (first_row) {
		*writer << " sim_time" << sep << "nID" << sep;
		*writer << " x_center" << sep; 
		*writer << " y_center" << sep; 
		*writer << " z_center" << sep; 
		*writer << "  bb_x_tl" << sep; 
		*writer << "  bb_y_tl" << sep; 
		*writer << "  bb_z_tl" << sep; 
		*writer << "  bb_x_br" << sep; 
		*writer << "  bb_y_br" << sep; 
		*writer << "  bb_z_br" << endl; 
		first_row = false;
	}
	*writer << setw(9) << simTime() << sep;
	*writer << setw(3) << self << sep;
	*writer << setw(9) << x_curr << sep;
	*writer << setw(9) << y_curr << sep;
	*writer << setw(9) << z_curr << sep;
	*writer << setw(9) << bb.x_tl << sep;
	*writer << setw(9) << bb.y_tl << sep;
	*writer << setw(9) << bb.z_tl << sep;
	*writer << setw(9) << bb.x_br << sep;
	*writer << setw(9) << bb.y_br << sep;
	*writer << setw(9) << bb.z_br << endl;
}

void WiseMovingTarget::calculate_bounding_box(WiseTargetBoundingBox &bb)
{
	double w, h, d;

	w = target_width / 2;
	h = target_height / 2;
	d = target_depth / 2;

	bb.x_tl = (x_curr >= w) ? x_curr - w : 0;
	bb.y_tl = (y_curr >= h) ? y_curr - h : 0;
	bb.z_tl = (z_curr >= d) ? z_curr - d : 0;
	bb.x_br = x_curr + w;
	bb.y_br = y_curr + h;
	bb.z_br = z_curr + d;
}
	
void WiseMovingTarget::move_linear_noise()
{
	double s, min, max, rnd;

	min = (move_min_x != 0) ? move_min_x : 0;
	max = (move_max_x != 0) ? move_max_x : terrain->get_x_size();
	//rnd = normal(0, noise, 0);
	rnd = uniform(-(noise / 2), (noise / 2), 0);
	s = x_curr + lin_x_step + rnd;
	if (s > max) {
		s = max;
		lin_x_step *= -1;
	} else if (s < min) { 
		s = min;
		lin_x_step *= -1;
	}
	x_curr = s;

	min = (move_min_y != 0) ? move_min_y : 0;
	max = (move_max_y != 0) ? move_max_y : terrain->get_y_size();
	//rnd = normal(0, noise, 0);
	rnd = uniform(-(noise / 2), (noise / 2), 0);
	s = y_curr + lin_y_step + rnd;
	if (s > max) {
		s = max;
		lin_y_step *= -1;
	} else if (s < min) { 
		s = min;
		lin_y_step *= -1;
	}
	y_curr = s;
}

void WiseMovingTarget::move_circular_noise(double r)
{
	double x, y, cos_diff, sin_diff, min, max, rnd;

	// motion equation for x (y uses sin):
	//    cx = x - r*cos(a);
	//    x = r*cos(a + h) + cx = cos (a + h) + x - r *cos(a)
	//    x = x + r*cos(a + h) - r*cos(a) = x + r*(cos(a+h) - cos(a))

	if (r <= 0)
		return;

	cos_diff = cos(rotation_angle + rotation_step) - cos(rotation_angle);
	sin_diff = sin(rotation_angle + rotation_step) - sin(rotation_angle);
	rotation_angle += rotation_step;

	x = x_curr + (cos_diff * r); 
	y = y_curr + (sin_diff * r); 

	min = (move_min_x != 0) ? move_min_x : 0;
	max = (move_max_x != 0) ? move_max_x : terrain->get_x_size();
	//rnd = normal(0, noise, 0);
	rnd = uniform(-(noise / 2), (noise / 2), 0);
	x += rnd;
	x_curr = (x > max) ? max : (x < min) ? min : x;

	min = (move_min_y != 0) ? move_min_y : 0;
	max = (move_max_y != 0) ? move_max_y : terrain->get_y_size();
	//rnd = normal(0, noise, 0);
	rnd = uniform(-(noise / 2), (noise / 2), 0);
	y += rnd;
	y_curr = (y > max) ? max : (y < min) ? min : y;
}

void WiseMovingTarget::move_circular_noise()
{
	move_circular_noise(radius);
}

void WiseMovingTarget::move_lincirc_noise()
{
	move_linear_noise();
	move_circular_noise(radius);
}

void WiseMovingTarget::move_linear_random()
{
	double rnd_x = uniform(0, 1, 0);
	double rnd_y = uniform(0, 1, 0);

	if (rnd_x < 0.100) 
		//lin_x_step = normal(0, 3, 1);
		lin_x_step = normal(0, TMP_STEP_SIZE * 0.5, 1);
		//lin_x_step = uniform(-2, 2, 1);
	if (rnd_y < 0.100) 
		//lin_y_step = normal(0, 3, 1);
		lin_y_step = normal(0, TMP_STEP_SIZE * 0.5, 1);
		//lin_y_step = uniform(-2, 2, 1);
	move_linear_noise();
}

void WiseMovingTarget::move_random_walk()
{
	double x, y, rnd, min, max;

	rnd = uniform(0, 1, 0);

	x = x_curr;
	y = y_curr;
	if (rnd < 0.25)
		x = x_curr + lin_x_step;
	else if (rnd < 0.5)
		x = x_curr - lin_x_step;
	else if (rnd < 0.75)
		y = y_curr + lin_y_step;
	else
		y = y_curr - lin_y_step;

	min = (move_min_x != 0) ? move_min_x : 0;
	max = (move_max_x != 0) ? move_max_x : terrain->get_x_size();
	x_curr = (x > max) ? max : (x < min) ? min : x;

	min = (move_min_y != 0) ? move_min_y : 0;
	max = (move_max_y != 0) ? move_max_y : terrain->get_y_size();
	y_curr = (y > max) ? max : (y < min) ? min : y;
}

void WiseMovingTarget::move_random_walk_8()
{
	double x, y, rnd, min, max;

	rnd = uniform(0, 1, 0);

	x = x_curr;
	y = y_curr;
	if (rnd < 0.125) {
		x = x_curr + lin_x_step;
	} else if (rnd < 0.250) {
		x = x_curr - lin_x_step;
	} else if (rnd < 0.375) {
		y = y_curr + lin_y_step;
	} else if (rnd < 0.5) {
		y = y_curr - lin_y_step;
	} else if (rnd < 0.625) {
		x = x_curr + diagonal;
		y = y_curr + diagonal;
	} else if (rnd < 0.750) {
		x = x_curr + diagonal;
		y = y_curr - diagonal;
	} else if (rnd < 0.875) {
		x = x_curr - diagonal;
		y = y_curr - diagonal;
	} else {
		x = x_curr - diagonal;
		y = y_curr + diagonal;
	}

	min = (move_min_x != 0) ? move_min_x : 0;
	max = (move_max_x != 0) ? move_max_x : terrain->get_x_size();
	x_curr = (x > max) ? max : (x < min) ? min : x;

	min = (move_min_y != 0) ? move_min_y : 0;
	max = (move_max_y != 0) ? move_max_y : terrain->get_y_size();
	y_curr = (y > max) ? max : (y < min) ? min : y;
}
