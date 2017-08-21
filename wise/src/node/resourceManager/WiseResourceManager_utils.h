// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2016
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for consumption models of smart-cameras:
//         SanMiguel & Cavallaro, "Energy Consumption Models for Smart-Camera Networks",
//         IEEE TCSVT 2016, http://ieeexplore.ieee.org/document/7517353/
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#ifndef _WISERESOURCEMANAGER_UTILS_H_
#define _WISERESOURCEMANAGER_UTILS_H_

//function to parse an integer value from a string
int parseLine(char* line);

//function to parse a double value from a string
double parseLinef(char* line);

int parseInt(const char *, int *);
int parseFloat(const char *, double *);

/*--- System capabilities ---*/
double getProcessorSpeed();

/*--- Current resource usage ---*/
int getCurrentUsedRAM();

/* ---
   //TOTAL VIRTUAL MEMORY
   struct sysinfo memInfo;

   sysinfo (&memInfo);
   long long totalVirtualMem = memInfo.totalram;
   //Add other values in next statement to avoid int overflow on right hand side...
   totalVirtualMem += memInfo.totalswap;
   totalVirtualMem *= memInfo.mem_unit;

   //TOTAL VIRTUAL MEMORY USED
   long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
   //Add other values in next statement to avoid int overflow on right hand side...
   virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
   virtualMemUsed *= memInfo.mem_unit;

   //TOTAL PHYSICAL MEMORY (RAM)
   long long totalPhysMem = memInfo.totalram;
   //Multiply in next statement to avoid int overflow on right hand side...
   totalPhysMem *= memInfo.mem_unit;

   //TOTAL PHYSICAL MEMORY (RAM) USED
   long long physMemUsed = memInfo.totalram - memInfo.freeram;
   //Multiply in next statement to avoid int overflow on right hand side...
   physMemUsed *= memInfo.mem_unit;---*/

#endif
