/*******************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                            *
 *  Developed at the ATP lab, Networked Systems research theme                 *
 *  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis, Yuriy Tselishchev *
 *  This file is distributed under the terms in the attached LICENSE file.     *
 *  If you do not find this file, copies can be found by writing to:           *
 *                                                                             *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                *
 *      Attention:  License Inquiry.                                           *
 *                                                                             *  
 *******************************************************************************/

#include "ResourceManager.h"
#include <wiseBaseApp/WiseBaseApp.h>

Define_Module(ResourceManager);

void ResourceManager::initialize()
{
	sigmaCPUClockDrift = par("sigmaCPUClockDrift");
	//using the "0" rng generator of the ResourceManager module
	cpuClockDrift = normal(0, sigmaCPUClockDrift);
	/* Crop any values beyond +/- 3 sigmas. Some protocols (e.g., MAC) rely on
	 * bounded cpuClockDrift. Although the bounds are conservative (usually 3sigmas),
	 * if you instantiate thousands of nodes (in multiple runs) we will get a
	 * couple of nodes that will be beyond this bound. Limiting/Croping the drift
	 * is actually realistic, since usually there is some kind of quality
	 * control on quartz crystals or the boards that use them (sensor node)
	 */
	if (cpuClockDrift > 3 * sigmaCPUClockDrift)
		cpuClockDrift = 3 * sigmaCPUClockDrift;
	if (cpuClockDrift < -3 * sigmaCPUClockDrift)
		cpuClockDrift = -3 * sigmaCPUClockDrift;

	initialEnergy = par("initialEnergy");
	ramSize = par("ramSize");
	baselineNodePower = par("baselineNodePower");
	periodicEnergyCalculationInterval = (double)par("periodicEnergyCalculationInterval") / 1000;

	if (baselineNodePower < 0 || periodicEnergyCalculationInterval < 0)
		opp_error("Illegal values for baselineNodePower and/or periodicEnergyCalculationInterval in resource manager module");

	currentNodePower = baselineNodePower;
	remainingEnergy = initialEnergy;
	timeOfLastCalculation = simTime();
	totalRamData = 0;

	energyMsg = new cMessage("Periodic energy calculation message", TIMER_SERVICE);
	scheduleAt(simTime() + periodicEnergyCalculationInterval, energyMsg);
}

void ResourceManager::calculateEnergySpent()
{
	simtime_t timePassed = simTime() - timeOfLastCalculation;
	trace() << "energy consumed in the last " << timePassed << 
			"s is " <<(timePassed * currentNodePower);
	consumeEnergy(SIMTIME_DBL(timePassed * currentNodePower / 1000.0));
	timeOfLastCalculation = simTime();
	if (remainingEnergy > 0) {
		cancelEvent(energyMsg);
		scheduleAt(simTime() + periodicEnergyCalculationInterval, energyMsg);
	}
}

/* The ResourceManager module is not connected with other modules. They use instead its public methods.
 * The only possible message is periodic energy consumption. There is no message object associated to that message kind.
 */
void ResourceManager::handleMessage(cMessage * msg)
{
	switch (msg->getKind()) {
	
		case TIMER_SERVICE:{
			calculateEnergySpent();
			return;
		}

		case RESOURCE_MANAGER_DRAW_POWER:{
			ResourceManagerMessage *resMsg = check_and_cast<ResourceManagerMessage*>(msg);
			int id = resMsg->getSenderModuleId();
			double oldPower = storedPowerConsumptions[id];
			trace() << "New power consumption, id = " << id << ", oldPower = " << currentNodePower << ", newPower = "
			        << currentNodePower - oldPower + resMsg->getPowerConsumed();
			calculateEnergySpent();
			currentNodePower = currentNodePower - oldPower + resMsg->getPowerConsumed();
			storedPowerConsumptions[id] = resMsg->getPowerConsumed();
			break;
		}

		default:{
			opp_error("ERROR: Unexpected message received by resource manager: %s", msg->getKind());
		}
	}
	delete msg;
}

void ResourceManager::finishSpecific()
{
	calculateEnergySpent();
	declareOutput("Consumed Energy");
	collectOutput("Consumed Energy", "", getSpentEnergy());
}

double ResourceManager::getSpentEnergy(void)
{
	Enter_Method("getSpentEnergy()");
	return (initialEnergy - remainingEnergy);
}

double ResourceManager::getCPUClockDrift(void)
{
	Enter_Method("getCPUClockDrift(void)");
	return (1.0f + cpuClockDrift);
}

void ResourceManager::consumeEnergy(double amount)
{
	Enter_Method("consumeEnergy(double amount)");

	if (remainingEnergy < amount) {

	    remainingEnergy = 0;
	    //First warn the application level to send a broadcast message to other nodes
	    send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toApplication");

	    //Then send delayed messages to the other modules of the node
	    double delay = 0.1;
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay, "toSensorDevManager");
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toNetwork");
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toMac");
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toRadio");

		//send(new cMessage("Destroy node message", DESTROY_NODE), "toSensorDevManager");
		//send(new cMessage("Destroy node message", DESTROY_NODE), "toApplication");
		//send(new cMessage("Destroy node message", DESTROY_NODE), "toNetwork");
		//send(new cMessage("Destroy node message", DESTROY_NODE), "toMac");
		//send(new cMessage("Destroy node message", DESTROY_NODE), "toRadio");
	} else
		remainingEnergy -= amount;
}

void ResourceManager::destroyNode(void)
{
	Enter_Method("destroyNode(void)");

	send(new cMessage("Destroy node message", DESTROY_NODE), "toSensorDevManager");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toApplication");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toNetwork");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toMac");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toRadio");
}

int ResourceManager::RamStore(int numBytes)
{
	Enter_Method("RamStore(int numBytes)");

	int ramHasSpace = ((totalRamData + numBytes) <= ramSize) ? 1 : 0;
	if (!ramHasSpace) {
		trace() << "\n[Resource Manager] t= " << simTime() <<
				": WARNING: Data not stored to Ram. Not enough space to store them.";
		return 0;
	} else
		totalRamData += numBytes;
	return 1;
}

void ResourceManager::RamFree(int numBytes)
{
	Enter_Method("RamFree(int numBytes)");
	totalRamData -= numBytes;
	totalRamData = (totalRamData < 0) ? 0 : totalRamData;
}

