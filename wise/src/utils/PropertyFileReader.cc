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

#include "PropertyFileReader.h"
#include <string.h> //strncmp, strcmp,strncmp
#include <sstream> // std::string
#include <algorithm>    // std::replace
#include <iostream>

#define MAX_LINE 255

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PropertyFileReader::PropertyFileReader(const char *filename, bool create)
{
	if (filename == NULL)
	{
		printf("ERROR: No filename given for the property file\n");
		return;
	}

	sprintf(this->filename, "%s", filename);

	// Abrir el fichero para actualizacion
	filePtr = fopen(filename,"r");

	if (filePtr == NULL)
	{
		if (create)
		{
			filePtr = fopen(filename,"w+");			
		}
	}

	
	if (filePtr == NULL)
	{
		printf("ERROR the file '%s' cannot be opened\n", filename);
		return;
	}
}


PropertyFileReader::~PropertyFileReader()
{
	if (filePtr != NULL)
		fclose(filePtr);
}

int PropertyFileReader::getProperty(const char *name, char *value)
{
	if ((filePtr == NULL) || (name == NULL) || (filePtr == NULL))
		return PROPS_ERROR;

	char linea[MAX_LINE];
	char nameAux[80];
	char valueAux[80];

	fseek(filePtr, 0, SEEK_SET);

	while (fgets(linea, MAX_LINE, filePtr) != NULL)
	{
		// Saltar comentarios
		if (strncmp(linea, "//", 2) == 0)
			continue;

		// Saltar lineas en blanco
		if (strcmp(linea, "\n") == 0)
			continue;

		sscanf(linea, "%[^'=']=%s\n", nameAux, valueAux);

		if (strcmp(name, nameAux) == 0)
		{
			strcpy(value, valueAux);
			return PROPS_OK;
		}
	}

	// Si no ha encontrado la propiedad, pone el value a NULL
	return PROPS_NO_EXIST;
}

int PropertyFileReader::getProperty(const char *name, int *value)
{
	char valueStr[80];
	int res = getProperty(name, valueStr);
	if (res == PROPS_OK)
		*value = atoi(valueStr);

	return res;
}

int PropertyFileReader::getProperty(const char *name, long *value)
{
	char valueStr[80];
	int res = getProperty(name, valueStr);
	if (res == PROPS_OK)
		*value = atol(valueStr);

	return res;
}

int PropertyFileReader::getProperty(const char *name, double *value)
{
    std::string prevLocale = setlocale(LC_NUMERIC, NULL);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); //use '.' as decimal separator
    //std::setlocale(LC_NUMERIC, "es_ES.UTF-8"); //use ',' as decimal separator

    char valueStr[80];
    int res = getProperty(name, valueStr);
    if (res == PROPS_OK){
        std::string s = valueStr;
        //std::cout << s.c_str() << std::endl;
        std::replace(s.begin(), s.end(), ',', '.');
        //std::cout << s.c_str() << std::endl;
        //std::cout << std::atof(s.c_str()) << std::endl;
        *value = (float)std::atof(s.c_str());
    }

    setlocale(LC_NUMERIC, prevLocale.c_str()); // restablish the previous locale

	return res;
}


void PropertyFileReader::readLines()
{
	char linea[MAX_LINE];
	char nameAux[80];
	char valueAux[80];

	fseek(filePtr, 0, SEEK_SET);

	while (fgets(linea, MAX_LINE, filePtr) != NULL)
	{
		// Saltar comentarios
		if (strncmp(linea, "//", 2) == 0)
			continue;

		// Saltar lineas en blanco
		if (strcmp(linea, "\n") == 0)
			continue;

		sscanf(linea, "%s\t%s\n", nameAux, valueAux);
		printf("'%s'='%s'\n", nameAux, valueAux);
	}
}

int PropertyFileReader::setProperty(const char *name, char *value)
{
	if ((filePtr == NULL) || (name == NULL) || (filePtr == NULL))
		return PROPS_ERROR;

	char linea[MAX_LINE];
	char nameAux[80];
	char valueAux[80];
	fpos_t posicion;

	fseek(filePtr, 0, SEEK_SET);

	while (fgets(linea, MAX_LINE, filePtr) != NULL)
	{
		// Guardar la posicion por si es la linea buena
		fgetpos(filePtr, &posicion);

		// Saltar comentarios
		if (strncmp(linea, "//", 2) == 0)
			continue;

		// Saltar lineas en blanco
		if (strcmp(linea, "\n") == 0)
			continue;

//		sscanf(linea, "%s=%s\n", nameAux, valueAux);
		sscanf(linea, "%[^'=']=%s\n", nameAux, valueAux);

		// Si encuentra el name de la propiedad, reescribe la linea
		if (strcmp(name, nameAux) == 0)
		{
			fsetpos(filePtr, &posicion);
			fprintf(filePtr,"%s=%s\n", name, value);
			return PROPS_OK;
		}
	}

	// Si no ha encontrado la propiedad, la escribe
	fprintf(filePtr,"%s=%s\n", name, value);
	return PROPS_OK;
}


int PropertyFileReader::setProperty(const char *name, int value)
{
	char valueStr[20];
	sprintf(valueStr, "%d\n", value);
	return setProperty(name, valueStr);
}

int PropertyFileReader::setProperty(const char *name, long value)
{
	char valueStr[20];
	sprintf(valueStr, "%d\n", (int)value);
	return setProperty(name, valueStr);
}

int PropertyFileReader::setProperty(const char *name, double value)
{
	char valueStr[20];
	sprintf(valueStr, "%f\n", value);
	return setProperty(name, valueStr);
}
