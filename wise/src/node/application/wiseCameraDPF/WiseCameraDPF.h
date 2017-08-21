// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
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
//  This file is part of the implementation for the DPF tracker for single targets described in:
//      - C. Nastasi, A. Cavallaro, "WiSE-MNet: an experimental environment for Wireless Multimedia Sensor Networks"
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//      - C. Nastasi, A. Cavallaro, "Distributed target tracking under realistic network conditions",
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WiseCameraDPF_h__
#define __WiseCameraDPF_h__ 

#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "WiseCameraSimplePeriodicTracker.h"
#include "WiseCameraDPFMessage_custom.h"
#include "wise_utils_gmm.h"

#include "WiseDefinitionsTracking.h" //include for definitions of states and measurements

class WiseCameraDPF : public WiseCameraSimplePeriodicTracker {
private:

    struct particle_set_t {
       std::vector<state_t_2D> particles;
       std::vector<double> weights;
   };
   struct node_ctrl_t {
       bool initialized;
       bool initialized_once;
       bool last_node;
       bool very_first_node;
       bool first_node;
       std::string next_node;
       bool use_gmm_input;
       unsigned int aggregation_step;
       bool detection_miss;
       bool first_step_failed;
       bool target_lost;
       bool first_node_candidate;
       multimap<double, string> first_node_candidates;
       double first_start_time;
       double very_first_start_time;
   };
   struct rng_draw_t {
       double rand_x;
       double rand_y;
   };

   typedef std::vector<WiseUtils::Gmm::Component> gmm_t;

private:
	static std::ofstream *final_writer;
	static std::ofstream *partial_writer;
	static std::vector<rng_draw_t> rng_draw;
	
	bool trace_particles;
	unsigned count_draws;
	unsigned n_targets;
	unsigned n_particles;
	double particle_spread;
	int n_gmm_components;

	// Assuming l -> target
	std::vector<state_t_2D> init_states; 		// x_0
	std::vector<measurement_t_2D> target_measurements; // z_l
	std::vector<state_t_2D> target_states; 		// x_l
	std::vector<particle_set_t> particle_sets;	// P_l = {p,w}_l
	std::vector<node_ctrl_t> node_controls;
	std::vector<WiseUtils::Gmm*> gmm_clusterers;
	std::vector<gmm_t> gmm_mixtures;
	// Support structures
	double *cumulative_w;	// for resampling
	double *random_u;	// for resampling
	std::vector<state_t_2D> ground_truths;
	double *flat_particles; // A vector could be used, but this is faster

public: 
	virtual ~WiseCameraDPF();

protected:
	virtual void handleMacControlMessage(cMessage *);

	virtual void at_startup();
	virtual void at_finishSpecific() {};
	virtual void at_timer_fired(int index) {} ;
	virtual void at_tracker_init();
	virtual bool at_tracker_first_sample();
	virtual bool at_tracker_end_first_sample();
	virtual bool at_tracker_sample();
	virtual bool at_tracker_end_sample();
	virtual void make_measurements(const std::vector<WiseTargetDetection>&);
	virtual void process_network_message(WiseApplicationPacket *);
	virtual void handleDirectApplicationMessage(WiseApplicationPacket *);

private:
	void init_structures();

	void start_first_node_selection(unsigned);
	void complete_first_node_selection(unsigned);
	void perform_first_step(unsigned);
	void perform_intermediate_step(unsigned);
	void perform_last_step(unsigned);
	void select_next_node(unsigned);

	void store_truth(unsigned);
	void log_final_result(unsigned);
	void log_partial_result(unsigned);

	void draw_from_gmm(const gmm_t &c, state_t_2D &s);
	double likelihood(const measurement_t_2D &z, const state_t_2D &x_p);
	void process_model(state_t_2D &x);

	void draw_initial_particles(unsigned, particle_set_t&);
	void importance_sampling(particle_set_t&, const measurement_t_2D&);
	void resampling(particle_set_t&);
	void predict_and_update(particle_set_t &ps, const measurement_t_2D &z);
	void estimate(unsigned, const particle_set_t&);
	void create_gmm(unsigned);

	bool check_visibility(const state_t_2D &, const WiseCameraInfo &) const;
	double visibility_score(const state_t_2D &, const WiseCameraInfo &, bool normalized=false) const;

	void send_information(unsigned);
	void send_target_lost(unsigned);
};
#endif // __WiseCameraDPF_h__	
