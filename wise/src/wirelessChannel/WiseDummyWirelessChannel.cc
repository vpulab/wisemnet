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

#include "WiseDummyWirelessChannel.h"
#include "CastaliaMessages.h"
#include "ApplicationPacket_m.h"
#include "WiseDebug.h"

Define_Module(WiseDummyWirelessChannel);

bool WiseDummyWirelessChannel::check_connectivity(int tx, int rx)
{
	if (connectivity_map[tx].size() == 0)
		return true;
	if (connectivity_map[tx].find(rx) != connectivity_map[tx].end())
		return true;
	return false;
}

void WiseDummyWirelessChannel::initialize()
{
	WISE_DEBUG_3("WiseDummyWirelessChannel::initialize()");

	int n_nodes = getParentModule()->par("numNodes");
	connectivity_map = new std::set<int>[n_nodes];

	for (int i = 0; i < n_nodes; i++) {
		connectivity_map[i].clear();
		cModule *node = getParentModule()->getSubmodule("node", i);
		const char *str = node->par("dummy_connectivity_map");
		WISE_DEBUG_3("\tNODE_ " << i << " dummy_connectivity_map = '" << str << "'");
		if (strlen(str) == 0)
			continue;
		cStringTokenizer ratesTokenizer(str);
		const char *token;
		for (token = ratesTokenizer.nextToken(); token != NULL; token = ratesTokenizer.nextToken())
			connectivity_map[i].insert(atoi(token));
	}
}

void WiseDummyWirelessChannel::finish()
{
	WISE_DEBUG_3("WiseDummyWirelessChannel::finish()");
	if (connectivity_map)
		delete[] connectivity_map;
}

void WiseDummyWirelessChannel::handleMessage(cMessage * msg)
{
	const char *src;
	const char *dst;
	int out_node, in_node, msg_kind;

	WISE_DEBUG_3("WiseDummyWirelessChannel::handleMessage()");
	msg_kind = msg->getKind();
	switch (msg_kind) {
	case APPLICATION_PACKET:
		WISE_DEBUG_3("\t APPLICATION_PACKET: ");
		ApplicationGenericDataPacket *p;
		p = check_and_cast<ApplicationGenericDataPacket*>(msg);
		dst = p->getApplicationInteractionControl().destination.c_str();
		src = p->getApplicationInteractionControl().source.c_str();
		trace() << "Got APPLICATION_PACKET: '" << p->getName() << "' src=" << src << " dst=" << dst;
		out_node = resolveNetworkAddress(dst);
		in_node = resolveNetworkAddress(src);
		if (out_node == in_node) {
			trace() << "\tBAD: Attempt to send to itself: src=dst (dropping message)";
			delete msg;
			return;
		} 
		if (out_node != BROADCAST_MAC_ADDRESS) { 
			if (!check_connectivity(in_node, out_node)) {
				trace() << "\tDrop packet to unconnected destination";
				delete msg;
				return;
			}
			send(msg, "toNode", out_node);
		} else {
			for (int i = 0; i < gateSize("toNode"); i++) {
				// DON'T send to src itself or unconnected nodes
				if (i == in_node || 
				    !check_connectivity(in_node, i)) 
					continue;
				send(msg->dup(), "toNode", i);
			}
			// Duplicate is important, but then we need delete
			delete msg;
		}
		break;
	default:
		WISE_DEBUG_3("\t Unknown message: (delete it) ");
		delete msg;
	}
}

void WiseDummyWirelessChannel::finishSpecific()
{
	WISE_DEBUG_3("WiseDummyWirelessChannel::finishSpecific()");
}
	

int WiseDummyWirelessChannel::resolveNetworkAddress(const char *netAddr)
{
	if (!netAddr[0] || netAddr[0] < '0' || netAddr[0] > '9')
		return BROADCAST_MAC_ADDRESS;
	return atoi(netAddr);
}
