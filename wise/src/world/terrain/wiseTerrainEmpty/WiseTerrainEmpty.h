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

#ifndef __WiseTerrainEmpty_h__
#define __WiseTerrainEmpty_h__

#include "WiseBaseTerrain.h"

class WiseTerrainEmpty: public WiseBaseTerrain {
private:
	/*--- The .ned file's parameters ---*/
	/*--- Custom class parameters ---*/

protected:
	void initialize();
	//void finish();
public:
};

#endif // __WiseTerrainEmpty_h__
