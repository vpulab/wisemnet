// *****************************************************************************
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
#if !defined(PROPERTYFILE_READER_H_INCLUDED_)
#define PROPERTYFILE_READER_H_INCLUDED_

#include <stdio.h>

#define PROPS_OK		1
#define PROPS_NO_EXIST	0
#define PROPS_ERROR		-1


class PropertyFileReader
{
	char filename[50];
	FILE *filePtr;

public:
	PropertyFileReader(const char *filename, bool create=false);
	virtual ~PropertyFileReader();

	int getProperty(const char *name, char *valor);
	int getProperty(const char *name, int *valor);
	int getProperty(const char *name, long *valor);
	int getProperty(const char *name, double *valor);

	void readLines();

	int setProperty(const char *name, char *valor);
	int setProperty(const char *name, int valor);
	int setProperty(const char *name, long valor);
	int setProperty(const char *name, double value);
};

#endif // !defined(PROPERTYFILE_READER_H_INCLUDED_)
