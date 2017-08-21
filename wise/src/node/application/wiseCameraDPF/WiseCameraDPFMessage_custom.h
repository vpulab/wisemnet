// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2017
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:                                                         
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the DPF tracker for single targets described in:
//      - C. Nastasi, A. Cavallaro, "WiSE-MNet: an experimental environment for Wireless Multimedia Sensor Networks"
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//      - C. Nastasi, A. Cavallaro, "Distributed target tracking under realistic network conditions",
//        Proc. of Sensor Signal Processing for Defence (SSPD), London, UK, 28-29 September, 2011
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************

#ifndef __WiseCameraDPFMessage_custom_h__
#define __WiseCameraDPFMessage_custom_h__ 

#include "WiseCameraDPFMessage_m.h"
#include <vector>

class WiseCameraDPFMessage : public WiseCameraDPFMessage_Base {
public:
	std::vector<WiseUtils::Gmm::Component> gmm;

public:
	WiseCameraDPFMessage(const char *name=NULL, int kind=0) : WiseCameraDPFMessage_Base(name, kind) { }

	WiseCameraDPFMessage(const WiseCameraDPFMessage& other) : WiseCameraDPFMessage_Base(other) {	gmm = other.gmm; }

	virtual inline WiseCameraDPFMessage *dup() const {return new WiseCameraDPFMessage(*this); }

	virtual inline void setGmmArraySize(unsigned int size) { gmm.resize(size); }

	virtual inline unsigned int getGmmArraySize() const {	return gmm.size(); }

	virtual inline WiseUtils::Gmm::Component& getGmm(unsigned int k) { return gmm[k]; }

	virtual inline void setGmm(unsigned int k, const WiseUtils::Gmm::Component& c) { gmm[k] = c; }
};

#endif // __WiseCameraDPFMessage_custom_h__ 
