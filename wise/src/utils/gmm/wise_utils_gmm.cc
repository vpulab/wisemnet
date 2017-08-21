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
* @file wise_utils_gmm.cc
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

#include "wise_utils_gmm.h"
#include "WiseException.h"

extern "C" {

#include "clust_defs.h"
#include "alloc_util.h"
#include "clust_util.h"
#include "subcluster.h"

}

static double AverageVariance(struct ClassSig *Sig, int nbands);

using namespace std;
using namespace WiseUtils;

Gmm::Gmm(unsigned vec_size, unsigned init_clusters, unsigned wanted_clusters,
	 bool use_diagonal_covar, 
	 const vector<unsigned long> &samples_per_class)
{

	if (wanted_clusters > init_clusters) 
		throw WiseException("The desired number of clusters must be higher than the initial number of clusters");

	n_clusters = wanted_clusters;
	n_init_clusters = init_clusters;
	v_size = vec_size;	
	covar_type = (int) (use_diagonal_covar? CLUSTER_DIAG : CLUSTER_FULL);
	n_samples = samples_per_class;
	n_classes = samples_per_class.size();

	/* Initialize SigSet data structure */
	I_InitSigSet(&sig_set);
	I_SigSetNBands(&sig_set, v_size);

	/* Allocate memory for cluster signatures */
	for(unsigned k = 0; k < n_classes; k++) {
		struct ClassSig *s;
		s = I_NewClassSig(&sig_set);
		for(unsigned i = 0; i < n_init_clusters; i++)
			I_NewSubSig(&sig_set, s);
		I_AllocClassData(&sig_set, s, n_samples[k]);
	}
}

Gmm::Gmm(unsigned vec_size, unsigned init_clusters, unsigned wanted_clusters,
	 bool use_diagonal_covar, unsigned long samples)
{

	if (wanted_clusters > init_clusters) 
		throw WiseException("The desired number of clusters must be higher than the initial number of clusters");

	n_clusters = wanted_clusters;
	n_init_clusters = init_clusters;
	v_size = vec_size;	
	covar_type = (int) (use_diagonal_covar? CLUSTER_DIAG : CLUSTER_FULL);
	n_samples.push_back(samples);
	n_classes = 1;

	/* Initialize SigSet data structure */
	I_InitSigSet(&sig_set);
	I_SigSetNBands(&sig_set, v_size);

	/* Allocate memory for cluster signatures */
	struct ClassSig *s;
	s = I_NewClassSig(&sig_set);
	for(unsigned i = 0; i < n_init_clusters; i++)
		I_NewSubSig(&sig_set, s);
	I_AllocClassData(&sig_set, s, n_samples[0]);
}

Gmm::~Gmm()
{
	for(unsigned k = 0; k < n_classes; k++)
		I_DeallocClassData(&sig_set, sig_set.ClassSig + k);
	I_DeallocSigSet(&sig_set); 
}

	
bool Gmm::cluster(const vector<double*> &samples, 
		  vector< vector<Component> > &clusters)
{
	if (samples.size() != n_classes)
		return false;

	// Load data for each class
	vector<double*>::const_iterator it = samples.begin();
	for(unsigned k = 0; k < n_classes; k++) {
		struct ClassSig *s = sig_set.ClassSig + k;
		double *d = *it;
		for(unsigned i = 0; i < n_samples[k]; i++) 
			for(unsigned j = 0; j < v_size; j++) 
				s->ClassData.x[i][j] = *(d++);
		// Set unity weights and compute SummedWeights
		s->ClassData.SummedWeights = 0.0;
		for(unsigned i = 0; i < n_samples[k]; i++) {
			s->ClassData.w[i] = 1.0;
			s->ClassData.SummedWeights += s->ClassData.w[i]; 
		}
	}
	// Compute the average variance over all classes
	double r_min = 0;
	for(unsigned k = 0; k < n_classes; k++)
		r_min += AverageVariance(sig_set.ClassSig + k, v_size);
	r_min = r_min / (double) (COVAR_DYNAMIC_RANGE * n_classes);
	// Perform clustering for each class
	for(unsigned k = 0; k < n_classes; k++) {
		int m;
		subcluster(&sig_set, k, n_clusters, covar_type, r_min, &m);
	}

	clusters.clear();
	for(unsigned k = 0; k < n_classes; k++) {
		vector<Component> mixture;
		set_results(sig_set.ClassSig + k, mixture);
		clusters.push_back(mixture);
	}

	return true;
}

bool Gmm::cluster(const double *d, std::vector<Component> &mixture)
{
	// Load data for the single class
	struct ClassSig *s = sig_set.ClassSig;
	for (unsigned i = 0; i < n_samples[0]; i++)
		for (unsigned j = 0; j < v_size; j++) 
			s->ClassData.x[i][j] = *(d++);
	// Set unity weights and compute SummedWeights
	s->ClassData.SummedWeights = 0.0;
	for(unsigned i = 0; i < n_samples[0]; i++) {
		s->ClassData.w[i] = 1.0;
		s->ClassData.SummedWeights += s->ClassData.w[i]; 
	}
	// Compute the average variance over a single classes
	double r_min = AverageVariance(sig_set.ClassSig, v_size);
	r_min = r_min / (double) (COVAR_DYNAMIC_RANGE * 1);
	if (r_min < 1.0e-10) {
		mixture.clear();
		unsigned lim = (n_clusters == 0) ? 1 : n_clusters;
		for (unsigned k = 0; k < lim; k++) {
			Component comp(v_size);
			comp.set_w(1 / (double)lim);
			for (unsigned i = 0; i < v_size; i++) {
				comp.set_mean(i, s->ClassData.x[0][i]);
				for (unsigned j = 0; j < v_size; j++) 
					if (j == i) 
						comp.set_covar(i, j, 1.0e-10);
					else
						comp.set_covar(i, j, 0);
			}
			mixture.push_back(comp);
		}
		return true;
	}
	// Perform clustering for single class
	int m;
	subcluster(&sig_set, 0, n_clusters, covar_type, r_min, &m);
	// Set result for single class
	set_results(sig_set.ClassSig, mixture);

	return true;
}
	
void Gmm::set_results(const struct ClassSig *s, vector<Component> &mixture)
{
	mixture.clear();
	if (!s->used) 
		return;
	for (int c = 0; c < s->nsubclasses; c++) {
		struct SubSig *t = s->SubSig + c;
		Component comp(v_size);
		comp.set_w(t->pi);
		for (unsigned i = 0; i < v_size; i++) {
			comp.set_mean(i, t->means[i]);
			for (unsigned j = 0; j < v_size; j++) 
				comp.set_covar(i, j, t->R[i][j]);
		}
		mixture.push_back(comp);
	}
}


static double AverageVariance(struct ClassSig *Sig, int nbands)
{
	int i, b1;
	double Rmin;
	double *mean;
	double **R;

	/* Compute the mean of variance for each band */
	mean = G_alloc_vector(nbands);
	R = G_alloc_matrix(nbands, nbands);
	
	for (b1 = 0; b1 < nbands; b1++) {
		mean[b1] = 0.0;
		for (i = 0; i < Sig->ClassData.npixels; i++) {
			mean[b1] += (Sig->ClassData.x[i][b1]) * 
				    (Sig->ClassData.w[i]);
		}
		mean[b1] /= Sig->ClassData.SummedWeights;
	}
	for(b1 = 0; b1 < nbands; b1++) {
		R[b1][b1] = 0.0;
		for(i = 0; i < Sig->ClassData.npixels; i++) {
			R[b1][b1] += (Sig->ClassData.x[i][b1]) * 
				     (Sig->ClassData.x[i][b1]) *
				     (Sig->ClassData.w[i]);
		}
		R[b1][b1] /= Sig->ClassData.SummedWeights;
		R[b1][b1] -= mean[b1]*mean[b1];
	}
	/* Compute average of diagonal entries */
	Rmin = 0.0;
	for(b1 = 0; b1 < nbands; b1++) 
		Rmin += R[b1][b1];
	Rmin = Rmin/(nbands);

	G_free_vector(mean);
	G_free_matrix(R);
	
	return(Rmin);
}
