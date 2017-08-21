/* *****************************************************************************
 * Copyright (C): Christian Nastasi, 2011                                    
 * Author(s): Christian Nastasi                                              
 * Developed at the:                                                         
 * - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa)           
 * - School of Elec Eng and Computer Science, Queen Mary University (London) 
 * This file is distributed under the terms in the attached LICENSE_2 file.  
 * If you do not find this file, copies can be found by writing to:          
 * - c.nastasi@sssup.it                                                      
 * - nastasichr@gmail.com                                                    
 * - andrea.cavallaro@eecs.qmul.ac.uk                                        
 ******************************************************************************/

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

#ifndef SUBCLUSTER_H
#define SUBCLUSTER_H

int clusterMessageVerboseLevel;

int subcluster(
    struct SigSet *S,
    int Class_Index,
    int desired_num,
    int option,
    double Rmin,
    int *Max_num);

int clust_invert(
    double **a,      /* input/output matrix */
    int    n,        /* dimension */
    double *det_man, /* determinant mantisa */
    int    *det_exp, /* determinant exponent */
/* scratch space */
    int    *indx,    /* indx = G_alloc_ivector(n);  */
    double **y,      /* y = G_alloc_matrix(n,n); */
    double *col      /* col = G_alloc_vector(n); */
    );

#endif /* SUBCLUSTER_H */

