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

#include "WiseResourceManager_utils.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "sys/types.h"
#include "sys/sysinfo.h"

//function to parse an integer value from a string
int parseLine(char* line){
    int i = strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i-3] = '\0';
    return atoi(line);
}

//function to parse a double value from a string
double parseLinef(char* line){
    int i = strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i-3] = '\0';
    return atof(line);
}

//wrapper function for atoi(...) call. returns 1 on error, 0 on success
int parseInt(const char *c, int *dst)
{
    while (c[0] && (c[0] == ' ' || c[0] == '\t'))
        c++;
    if (!c[0] || c[0] < '0' || c[0] > '9')
        return 1;
    *dst = atoi(c);
    return 0;
}

//wrapper function for strtof(...) call. returns 1 on error, 0 on success
int parseFloat(const char *c, double *dst)
{
    char *tmp;
    *dst = strtof(c, &tmp);
    if (c == tmp)
        return 1;
    return 0;
}

double getProcessorSpeed()
{
   FILE* file = fopen("/proc/cpuinfo", "r");
   double result = -1, tmp = -1;
   char line[128];

   //for multi-core and multithreaded systems, the description often contains half the max frequency
   //Thus, scan all cores and get the maximum frequency
   while (fgets(line, 128, file) != NULL){
       if (strncmp(line, "cpu MHz", 7) == 0){
           tmp = parseLinef(line);
       }

       if (tmp > result)
           result = tmp;
   }
   fclose(file);
   return result * 1e6;//as the obtained value is in Mhz
}

int getCurrentUsedRAM()
{
    //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}
