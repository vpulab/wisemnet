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

#include <vector>
#include "pft_exception.h"
#include "WiseMultiCameraPeriodicApp_DPF.h"

namespace pft {

template<typename X, typename W>
void particles_resampling(cRNG * rng, std::vector<X> &particles, std::vector<W> &weights)
{
	if (particles.size() != weights.size())
		throw pft::Exception("Sizes of particle and weight vectors are "
                                     "different");
    double u0 = uniform(rng, 0, 1);
	unsigned n_p = particles.size();
	X *old_particles = new X[n_p];
        W *cumulative_w = new W[n_p + 1];
        cumulative_w[0] = 0;
        double *random_u = new double[n_p];
        unsigned idx = 0;
	for (unsigned i = 0; i < n_p; i++) {
                cumulative_w[idx + 1] = cumulative_w[idx] + weights[i];
                random_u[idx] = (u0 + idx) / (double) n_p;
		old_particles[idx] = particles[i];
                idx++;
	}
        idx = 0;
	for (unsigned i = 0; i < n_p; i++) {
                unsigned j = 0;
                while (random_u[idx] > cumulative_w[j])
                        j++;
                particles[i] =  old_particles[j - 1];
                weights[i] = 1 / (double) n_p;
                idx++;
        }
	delete[] old_particles;
	delete[] cumulative_w;
	delete[] random_u;
}

}; //namespace pft
