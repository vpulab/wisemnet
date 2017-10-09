// *****************************************************************************************
// Copyright (C) 2011  Christian Nastasi, 2017 Juan C. SanMiguel and Andrea Cavallaro
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
 * \file wiseMultiCameraPeriodicApp_DPF.h
 * \author Christian Nastasi (2011)
 * \author Juan C. SanMiguel (2017)
 * \brief Header file for the wiseMultiCameraPeriodicApp_DPF class
 * \version 1.4
 */

#ifndef __WISEMULTICAMERAPERIODICAPP_DPF__
#define __WISEMULTICAMERAPERIODICAPP_DPF__

#include <vector>
//#include <map>
//#include <sstream>
//#include <fstream>

#include <wiseCameraPeriodicApp/WiseCameraPeriodicApp.h>
#include <wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_m.h>
#include <wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_custom.h> //include specific-structures for single-target tracking using ICF (in 'icf' namespace)

//#include "wise_utils_gmm.h"

//#include "WiseDefinitionsTracking.h" //include for definitions of states and measurements

/*! \class WiseMultiCameraPeriodicApp_DPF
 *  \brief This class implements distributed single-target tracking based on the Particle Filter
 *
 * This file is part of the implementation for the DPF tracker for single targets described in:
 *      - C. Nastasi, A. Cavallaro, "WiSE-MNet: an experimental environment for Wireless Multimedia Sensor Networks"
 *        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
 *      - C. Nastasi, A. Cavallaro, "Distributed target tracking under realistic network conditions",
 *        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
 *
 */
class WiseMultiCameraPeriodicApp_DPF : public WiseCameraPeriodicApp {
private:
    int _tracking_step_counter;  //!< internal counter for tracking steps

   /*! \struct state_t_2D
    *  \brief 2D State vector of target (posx, posy)
    */
    struct state_t_2D
    {
       unsigned int tid;   //!< Target ID
       double x;           //!< Target x-position
       double y;           //!< Target y-position

       /*!
        * To print target data as string following the format "(posx, posy)"
        * @return The string to be printed
        */
       inline std::string str() const
       {
           std::ostringstream os;
           os << "(" << x << ", " << y << ")";
           return os.str();
       }
    };

    /*! \struct measurement_t_2D
     *  \brief 2D Measurement vector of target (posx and posy)
     */
    struct measurement_t_2D
    {
        unsigned int tid;   //!< Target ID
        double x;           //!< x-position
        double y;           //!< y-position

        /*!
         * To print target data as string following the format "(observationx, observationy)"
         * @return The string to be printed
         */
        inline std::string str() const
        {
            std::ostringstream os;
            os << "(" << x << ", " << y << ")";
            return os.str();
        }
    };

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

protected:
    //Functions to be defined in sub-classes (mandatory)
    void at_timer_fired(int index){};  //!< Response to alarms generated by specific algorithm. To define in superclass (mandatory)
    void at_startup();                 //!< Initialize internal variables. To define in sub-classes for each specific algorithm (mandatory)
    void at_finishSpecific();           //!< Release resources. To define in sub-classes for each specific algorithm (mandatory)
    bool at_init();                     //!< Initialize resources based on sampled data. To define in sub-classes for each specific algorithm (mandatory)
    bool at_sample();                   //!< Operations for processing each sample. To define in sub-classes for each specific algorithm (mandatory)
    bool at_end_sample();               //!< Operations after processing each sample. To define in sub-classes for each specific algorithm (mandatory)
    void make_measurements(const std::vector<WiseTargetDetection>&); //!< Conversion of camera detections into ordered lists of measurements for tracking. To define in sub-classes for each specific algorithm (mandatory)
    bool process_network_message(WiseBaseAppPacket *m); //!< Operations for processing each packet from network. To define in sub-classes for each specific algorithm (mandatory)
    void handleDirectApplicationMessage(WiseBaseAppPacket *); //!< Process a received packet from a direct node-to-node links (to be implemented in superclasses of WiseBaseApp)

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
#endif // __WISEMULTICAMERAPERIODICAPP_DPF__
