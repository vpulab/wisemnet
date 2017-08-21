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

/** 
* @file wise_utils_gmm.h
* @brief Guassian Mixture Model (library from Bouman's code)
* @author Christian Nastasi
* @version 0.1
* @date 2011-02-07
*/


/*
* All questions regarding the software should be addressed to
* 
*       Prof. Charles A. Bouman
*       Purdue University
*       School of Electrical and Computer Engineering
*       1285 Electrical Engineering Building
*       West Lafayette, IN 47907-1285
*       USA
*       +1 765 494 0340
*       +1 765 494 3358 (fax)
*       email:  bouman@ecn.purdue.edu
*       http://www.ece.purdue.edu/~bouman
* 
* Copyright (c) 1995 The Board of Trustees of Purdue University.
*
* Permission to use, copy, modify, and distribute this software and its
* documentation for any purpose, without fee, and without written agreement is
* hereby granted, provided that the above copyright notice and the following
* two paragraphs appear in all copies of this software.
*
* IN NO EVENT SHALL PURDUE UNIVERSITY BE LIABLE TO ANY PARTY FOR DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
* USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF PURDUE UNIVERSITY HAS
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* PURDUE UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS,
* AND PURDUE UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
* UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

#ifndef __wise_utils_gmm_h__
#define __wise_utils_gmm_h__

#include <vector>
extern "C" {
#include "clust_defs.h"
}

#include <string.h>

namespace WiseUtils {

class Gmm {
public:
	class Component {
	private:
		unsigned size;
		double w;
		double *mean;
		double *covar;
	public:
		Component() : size(0), mean(NULL), covar(NULL) {}

		Component(unsigned s) : size(s) 
		{
			mean = new double[s];
			covar = new double[s * s];
		}

		Component(const Component &c)  
		{
			size = 0;
			mean = NULL;
			covar = NULL;
			*this = c;
		}

		Component& operator=(const Component &c)
		{
			w = c.w;
			if (size != c.size) {
				size = c.size;
				if (mean)
					delete[] mean;
				if (covar)
					delete[] covar;
				mean = new double[size];
				covar = new double[size * size];
			}
			memcpy(mean, c.mean, sizeof(double) * size);
			memcpy(covar, c.covar, sizeof(double) * size * size);
			return *this;
		}

		~Component() 
		{
			if (mean)
				delete[] mean;
			if (covar)
				delete[] covar;
		}

		inline double get_w() const { return w; }
		inline double get_mean(unsigned i) const
					{ return mean[i]; }
		inline double get_covar(unsigned i, unsigned j) const
					{ return covar[(i * size) + j]; }
		inline void set_w(double v) { w = v; }
		inline void set_mean(unsigned i, double v)
					{ mean[i] = v; }
		inline void set_covar(unsigned i, unsigned j, double v)
					{ covar[(i * size) + j] = v; }
	};

private:
	unsigned v_size;
	unsigned n_classes;
	unsigned n_init_clusters;
	unsigned n_clusters;
	int covar_type;
	std::vector<unsigned long> n_samples;

	struct SigSet sig_set;

public:
	Gmm(unsigned vec_size, unsigned init_clusters, unsigned wanted_clusters,
	    bool use_diagonal_covariance, 
	    const std::vector<unsigned long> &samples_per_class);
	Gmm(unsigned vec_size, unsigned init_clusters, unsigned wanted_clusters,
	    bool use_diagonal_covariance, unsigned long samples);
	virtual ~Gmm();

	bool cluster(const std::vector<double*> &samples, 
		     std::vector< std::vector<Component> > &clusters);
	bool cluster(const double *samples, std::vector<Component> &mixture);

private:
	void set_results(const struct ClassSig *s, std::vector<Component> &gmm);
};

}; // namespace WiseUtils

#endif // __wise_utils_gmm_h__
