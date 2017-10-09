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

#ifndef __pft_exception_h__
#define __pft_exception_h__

#include <exception>
#include <string>

namespace pft {

class Exception : public std::exception {
public:
	Exception(const std::string &msg) throw() : err_msg(msg) {} ;
	~Exception(void) throw() {} ;
	inline const char* what(void) const throw() { return err_msg.c_str(); };
private:
        std::string err_msg;
        Exception(void) throw() {} ;
};

}; //namespace pft

#endif // __pft_exception_h__
