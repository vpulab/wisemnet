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


#ifndef ALLOC_UTIL_H
#define ALLOC_UTIL_H

char *G_malloc(int n);
char *G_calloc(int n,int m);
char *G_realloc(char *b,int n);
void G_dealloc(char *b);
double *G_alloc_vector(int n);
double **G_alloc_matrix(int rows,int cols);
void G_free_vector(double *v);
void G_free_matrix(double **m);
int *G_alloc_ivector(int n);
int **G_alloc_imatrix(int rows,int cols);
void G_free_ivector(int *v);
void G_free_imatrix(int **m);

#endif /* ALLOC_UTIL_H */

