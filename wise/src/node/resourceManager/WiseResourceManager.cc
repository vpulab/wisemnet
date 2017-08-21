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

#include "WiseResourceManager.h"
#include "WiseResourceManager_utils.h"
#include "WiseBaseApplication.h"

#include "PropertyFileReader.h"

Define_Module(WiseResourceManager);
#define BASE_TRACE trace() << "WISERESMAN: "

void WiseResourceManager::initialize()
{
    _logger = NULL;

	sigmaCPUClockDrift = par("sigmaCPUClockDrift");
	//using the "0" rng generator of the WiseResourceManager module
	cpuClockDrift = normal(0, sigmaCPUClockDrift);
	/* Crop any values beyond +/- 3 sigmas. Some protocols (e.g., MAC) rely on bounded cpuClockDrift. Although the bounds
	 * are conservative (usually 3sigmas), if you instantiate thousands of nodes (in multiple runs) we will get a couple
	 * of nodes that will be beyond this bound. Limiting/Croping the drift is actually realistic, since usually there is
	 * some kind of quality control on quartz crystals or the boards that use them (sensor node)
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

	//_energyMsg = new cMessage("Periodic energy calculation message", TIMER_SERVICE);
	//scheduleAt(simTime() + periodicEnergyCalculationInterval, _energyMsg);

	_pro.optimization_factor = (double)par("optimizationFactor");
	_pro.clockfreq = par("CPUfreq");
    _sen.clockfreq = par("SENfreq");
    //_sen.framerate = par("SENframerate");
    cModule *node = getParentModule();

    _sen.framerate = node->getSubmodule("Application")->hasPar("sampling_time") ? node->getSubmodule("Application")->par("sampling_time").doubleValue() : -1;

    if (_sen.framerate != -1) {
        _sen.orig_framerate = 1/_sen.framerate;
        _sen.framerate = 1/_sen.framerate;
        _sen.Tframe = 1/_sen.framerate;
        _sen.Tidl = 0;
        _sen.Tact[0] = 0;
        _sen.Tact[1] = 0;
        _sen.Tact[2] = 0;
        _sen.Tact[3] = 0;
        _com.bitrateTX = par("COMbitrate");
        _com.bitrateRX = par("COMbitrate");

        //INITIALIZATION
        _pro.cost.count = 0;
        _sen.cost.count = 0;
        _com.cost.count = 0;
        _lastLogS = -1;

        //LOAD CONSUMPTION MODELS
        _pro.model.type = par("CPUmodel").stringValue();
        _sen.model.type = par("SENmodel").stringValue();
        _com.model.type = par("COMmodel").stringValue();
        load_consumption_models();//load consumption models from files

        _cpuClockfreqHost = getProcessorSpeed();//Get processor speed of host machine
    }
}

void WiseResourceManager::load_consumption_models()
{
    //LOAD CPU MODEL
    PropertyFileReader props(_pro.model.type.c_str());

    //read parameters from file
    if(props.getProperty("PS", &_pro.power.Psle) == PROPS_ERROR)
        opp_error("ERROR: Property %s not found in file %s", "PS", _pro.model.type.c_str());
    else{

        props.getProperty("FMAX", &_pro.model.fmax);
        props.getProperty("FMIN", &_pro.model.fmin);
        props.getProperty("DVS_m1", &_pro.model.DVS_m1);
        props.getProperty("DVS_m2", &_pro.model.DVS_m2);

        props.getProperty("Pa_k0", &_pro.model.Pa_k[0]);
        props.getProperty("Pa_k1", &_pro.model.Pa_k[1]);
        props.getProperty("Pa_k2", &_pro.model.Pa_k[2]);
        props.getProperty("Pa_k3", &_pro.model.Pa_k[3]);

        props.getProperty("Pi_k", &_pro.model.Pi_k);
        props.getProperty("Pi_f", &_pro.model.Pi_f);
    }
    if (_pro.clockfreq == -1)
        _pro.clockfreq = _pro.model.fmin + (_pro.model.fmax - _pro.model.fmin)/2; //Hz

    //compute power for active and idle states
    _pro.power.num_active_states = 3; //dynamic and leakage power; power due to processing while camera communication+collaboration
    _pro.V = _pro.clockfreq * _pro.model.DVS_m1 + _pro.model.DVS_m2;
    _pro.power.Pact[0] =  _pro.model.Pa_k[3] * _pro.clockfreq * _pro.clockfreq * _pro.clockfreq +
                          _pro.model.Pa_k[2] * _pro.clockfreq * _pro.clockfreq +
                          _pro.model.Pa_k[1] * _pro.clockfreq + _pro.model.Pa_k[0]; //dynamic power (W)
    _pro.power.Pact[1] = _pro.power.Pact[0] * 0.001; // dynamic power (W)
    _pro.power.Pact[2] = _pro.power.Pact[0]; //power for additional operations besides processing (e.g. tasks related to communication)

    //active power at which the Pi/Pa ratio has been computed (operating at frequency '_pro.model.Pi_f')
    double Ptmp = _pro.model.Pa_k[3] * _pro.model.Pi_f * _pro.model.Pi_f * _pro.model.Pi_f +
                  _pro.model.Pa_k[2] * _pro.model.Pi_f * _pro.model.Pi_f + _pro.model.Pa_k[1] * _pro.model.Pi_f + _pro.model.Pa_k[0]; //dynamic power (W)

    _pro.power.Pidl =  _pro.model.Pi_k * Ptmp;

    //LOAD SEN MODEL
    //read parameters from file
    PropertyFileReader propSEN(_sen.model.type.c_str());
    if(propSEN.getProperty("PS", &_sen.power.Psle) == PROPS_ERROR)
           opp_error("ERROR: Property %s not found in file %s", "PS", _pro.model.type.c_str());
       else{
           propSEN.getProperty("Pi_c0", &_sen.model.Pi_c[0]);
           propSEN.getProperty("Pi_c1", &_sen.model.Pi_c[1]);
           propSEN.getProperty("Pi_c2", &_sen.model.Pi_c[2]);
           propSEN.getProperty("Pi_c3", &_sen.model.Pi_c[3]);

           propSEN.getProperty("Pa_c0", &_sen.model.Pa_c[0]);
           propSEN.getProperty("Pa_c1", &_sen.model.Pa_c[1]);
           propSEN.getProperty("Pa_c2", &_sen.model.Pa_c[2]);
           propSEN.getProperty("Pa_c3", &_sen.model.Pa_c[3]);

           propSEN.getProperty("FMAX", &_sen.model.fmax);
           propSEN.getProperty("FMIN", &_sen.model.fmin);
           propSEN.getProperty("FRMAX", &_sen.model.frmax);
           propSEN.getProperty("FRMIN", &_sen.model.frmin);
           propSEN.getProperty("ROWS", &_sen.model.cols);
           propSEN.getProperty("COLS", &_sen.model.rows);
           propSEN.getProperty("NCH", &_sen.model.nch);
       }
    if (_sen.clockfreq == -1)
            _sen.clockfreq = _sen.model.fmin + (_sen.model.fmax - _sen.model.fmin)/2; //Hz
    //compute power for active and idle states
    _sen.power.num_active_states = 1; //capture frame
    _sen.power.Pact[0] =  _sen.model.Pa_c[3] * _sen.clockfreq * _sen.clockfreq * _sen.clockfreq +
                          _sen.model.Pa_c[2] * _sen.clockfreq * _sen.clockfreq +
                          _sen.model.Pa_c[1] * _sen.clockfreq + _sen.model.Pa_c[0]; //active (mW)
    _sen.power.Pact[0] = _sen.power.Pact[0] * 1e-3;
    _sen.power.Pidl =  _sen.model.Pi_c[3] * _sen.clockfreq * _sen.clockfreq * _sen.clockfreq +
                          _sen.model.Pi_c[2] * _sen.clockfreq * _sen.clockfreq +
                          _sen.model.Pi_c[1] * _sen.clockfreq + _sen.model.Pi_c[0]; //idle (mW)
    _sen.power.Pidl = _sen.power.Pidl * 1e-3;
    //LOAD COM MODEL
    //...

}

void WiseResourceManager::initLogger(std::string filename, int self, int camID)
{
    _self = self;
    _camID = camID;
    _logger = new ofstream();

   if (!_logger->is_open()){
       _logger->open(filename.c_str());
       *_logger << "#simulation results for energy consumptions" << endl;
   }
}

/* The WiseResourceManager module is not connected with other modules. They use instead its public methods.
 * The only possible message is periodic energy consumption. There is no message object associated to that message kind.
 */
void WiseResourceManager::handleMessage(cMessage * msg)
{
	switch (msg->getKind()) {
	
		case TIMER_SERVICE:{
			calculateEnergySpent();
			return;
		}

		case RESOURCE_MANAGER_DRAW_POWER:{
			WiseResourceManagerMessage *resMsg = check_and_cast<WiseResourceManagerMessage*>(msg);
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

void WiseResourceManager::finishSpecific()
{
	calculateEnergySpent();
	declareOutput("Consumed Energy");
	collectOutput("Consumed Energy", "", getSpentEnergy());

  //  declareOutput("Sensing: captured frames");
//    collectOutput("Sensing: captured frames", "", _senE.count);

    //...

    if (_logger) {
            _logger->close();
            delete _logger;
            _logger = NULL;
        }
}

void WiseResourceManager::setSENFrameSize(int rows, int cols, int nch, double resize)
{
    _sen.model.rows = rows;
    _sen.model.cols = cols;
    _sen.model.nch = nch;
    _sen.resize = resize;

     updateSENTact();
}

void WiseResourceManager::setSENFrameRate(double newFrameRate)
{
    _sen.framerate = newFrameRate;
    updateSENTact();
}

void WiseResourceManager::setSENClk(double newFreq)
{
    if (newFreq < _sen.model.fmin)
        newFreq = _sen.model.fmin;
    if (newFreq > _sen.model.fmax)
        newFreq = _sen.model.fmax;

    _sen.clockfreq = newFreq;
    updateSENTact();
}

void WiseResourceManager::updateSENTact()
{
    //double numPixFrame = _sen.model.rows * _sen.model.cols * _sen.model.nch; //full CCD sensor
    double numPixFrame = _sen.model.rows * _sen.model.cols; //CCD sensor - Bayer color filter
    _sen.Tframe = 1/_sen.framerate;
    _sen.Tact[0] = numPixFrame/_sen.clockfreq; //onepixel is read every tick(cycle) of the CPU
    _sen.Tidl = 1/_sen.framerate - _sen.Tact[0];

    if (_sen.Tidl < 0){
        //the system cannot capture at the requested framerate
        //we set the sensing system at its maximum capacity
        BASE_TRACE << "SENSING cannot achieve desired framerate=" << _sen.framerate << "fps, setting to " << 1/_sen.Tact[0] << "fps;";
        _sen.Tframe = _sen.Tact[0];
        _sen.Tidl = 0;
        _sen.framerate = 1/_sen.Tframe;

        //we recompute power consumption models
        _sen.power.Pact[0] =  _sen.model.Pa_c[3] * _sen.clockfreq * _sen.clockfreq * _sen.clockfreq +
                                  _sen.model.Pa_c[2] * _sen.clockfreq * _sen.clockfreq +
                                  _sen.model.Pa_c[1] * _sen.clockfreq + _sen.model.Pa_c[0]; //active (watts)
        _sen.power.Pidl =  _sen.model.Pi_c[3] * _sen.clockfreq * _sen.clockfreq * _sen.clockfreq +
                                  _sen.model.Pi_c[2] * _sen.clockfreq * _sen.clockfreq +
                                  _sen.model.Pi_c[1] * _sen.clockfreq + _sen.model.Pi_c[0]; //idle (watts)

        _sen.power.Psle = 0;

        _sen.power.Pact[0] = _sen.power.Pact[0] * 1e-3;//to mW
        _sen.power.Pidl = _sen.power.Pidl * 1e-3;//to mW
        //opp_error("ERROR: Unexpected value for Tidle of sensing task: %s", _sen.Tidl);
    }
}

void WiseResourceManager::setPROClk(double newFreq)
{
    if (newFreq < _pro.model.fmin)
        newFreq = _pro.model.fmin;
    if (newFreq > _pro.model.fmax)
        newFreq = _pro.model.fmax;

    _pro.clockfreq = newFreq;

    //Dynamic Voltage Scaling
    _pro.V = _pro.clockfreq * _pro.model.DVS_m1 + _pro.model.DVS_m2;
    _pro.power.Pact[0] =  _pro.model.Pa_k[3] * _pro.clockfreq * _pro.clockfreq * _pro.clockfreq +
                              _pro.model.Pa_k[2] * _pro.clockfreq * _pro.clockfreq +
                              _pro.model.Pa_k[1] * _pro.clockfreq + _pro.model.Pa_k[0]; //dynamic power (mW)
    _pro.power.Pact[1] = _pro.power.Pact[0] * 0.001; // dynamic power (W)
    _pro.power.Pidl =  _pro.model.Pi_k * _pro.power.Pact[0];
}

void WiseResourceManager::calculateEnergySpent()
{
    /*simtime_t timePassed = simTime() - timeOfLastCalculation;
    trace() << "energy consumed in the last " << timePassed <<
            "s is " <<(timePassed * currentNodePower);
    consumeEnergy(SIMTIME_DBL(timePassed * currentNodePower / 1000.0));
    timeOfLastCalculation = simTime();
    if (remainingEnergy > 0) {
        cancelEvent(energyMsg);
        scheduleAt(simTime() + periodicEnergyCalculationInterval, energyMsg);
    } ---*/
}

double WiseResourceManager::getSpentEnergy(void)
{
    Enter_Method("getSpentEnergy()");
    return (initialEnergy - remainingEnergy);
}

double WiseResourceManager::getRemainingEnergy(void)
{
    return remainingEnergy;
}

double WiseResourceManager::getCurSpentEnergy(energy_type_t energyType)
{
    switch (energyType) {

        case WISE_ENERGY_SEN_TOT: return _sen.cost.Etot[_sen.cost.count-1];
        case WISE_ENERGY_SEN_ACT: return _pro.cost.Eact[0][_sen.cost.count-1];
        case WISE_ENERGY_SEN_IDL: return _sen.cost.Eidl[_sen.cost.count-1];

        case WISE_ENERGY_COM_TOT: return _com.cost.Etot[_com.cost.count-1];
        case WISE_ENERGY_COM_IDL: return _com.cost.Eidl[_com.cost.count-1];
        case WISE_ENERGY_COM_TX:  return _com.cost.Eact[0][_com.cost.count-1];
        case WISE_ENERGY_COM_RX:  return _com.cost.Eact[0][_com.cost.count-1];

        case WISE_ENERGY_PRO_TOT: return _pro.cost.Etot[_pro.cost.count-1];
        case WISE_ENERGY_PRO_ACT: return _pro.cost.Eact[0][_pro.cost.count-1];
        case WISE_ENERGY_PRO_LKG: return _pro.cost.Eact[0][_pro.cost.count-1];
        case WISE_ENERGY_PRO_IDL: return _pro.cost.Eidl[_pro.cost.count-1];

        default:{
            opp_error("ERROR: Unexpected 'energy_type_t' to retrieve current spent energy");
            return -1.0;
        }
    }
}

double WiseResourceManager::getTotSpentEnergy(energy_type_t energyType)
{
   switch (energyType) {

        case WISE_ENERGY_SEN_TOT: return _sen.cost.Etot_acc[_sen.cost.count-1];
        case WISE_ENERGY_SEN_ACT: return _pro.cost.Eact_acc[0][_sen.cost.count-1];
        case WISE_ENERGY_SEN_IDL: return _sen.cost.Eidl_acc[_sen.cost.count-1];

        case WISE_ENERGY_COM_TOT: return _com.cost.Etot_acc[_com.cost.count-1];
        case WISE_ENERGY_COM_IDL: return _com.cost.Eidl_acc[_com.cost.count-1];
        case WISE_ENERGY_COM_TX:  return _com.cost.Eact_acc[0][_com.cost.count-1];
        case WISE_ENERGY_COM_RX:  return _com.cost.Eact_acc[0][_com.cost.count-1];

        case WISE_ENERGY_PRO_TOT: return _pro.cost.Etot_acc[_pro.cost.count-1];
        case WISE_ENERGY_PRO_ACT: return _pro.cost.Eact_acc[0][_pro.cost.count-1];
        case WISE_ENERGY_PRO_LKG: return _pro.cost.Eact_acc[0][_pro.cost.count-1];
        case WISE_ENERGY_PRO_IDL: return _pro.cost.Eidl_acc[_pro.cost.count-1];
        default:{
            opp_error("ERROR: Unexpected 'energy_type_t' to retrieve total spent energy");
            return -1.0;
        }
    }
}

void WiseResourceManager::consumeEnergy(double amount)
{
	Enter_Method("consumeEnergy(double amount)");

	if (remainingEnergy < amount) {
	    //printf("remaining = %.2f amount = %.2f\n",remainingEnergy,amount);
	    remainingEnergy = 0;
	    //First warn the application level to send a broadcast message to other nodes
	    send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toApplication");

	    //Then send delayed messages to the other modules of the node
	    double delay = 0.1;
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toSensorDevManager");
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toNetwork");
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toMac");
	    sendDelayed(new cMessage("Out of energy message", OUT_OF_ENERGY), delay,"toRadio");

	} else
		remainingEnergy -= amount;
}

void WiseResourceManager::destroyNode(void)
{
	Enter_Method("destroyNode(void)");

	send(new cMessage("Destroy node message", DESTROY_NODE), "toSensorDevManager");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toApplication");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toNetwork");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toMac");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toRadio");
}

int WiseResourceManager::RamStore(int numBytes)
{
    Enter_Method("RamStore(int numBytes)");

    int ramHasSpace = ((totalRamData + numBytes) <= ramSize) ? 1 : 0;
    if (!ramHasSpace) {
        trace() << "\n[Resource Manager] t= " << simTime() << ": WARNING: Data not stored to Ram. Not enough space to store them.";
        return 0;
    } else
        totalRamData += numBytes;
    return 1;
}

void WiseResourceManager::RamFree(int numBytes)
{
    Enter_Method("RamFree(int numBytes)");

    totalRamData -= numBytes;
    totalRamData = (totalRamData < 0) ? 0 : totalRamData;
}

void WiseResourceManager::computeEnergySEN(int frameid, double Tidl)
{
    Enter_Method("computeEnergySEN(int frameid)");
    //NOTE: Tactive & Tidle times must be previously computed via methods setSamplingRate(...) or setFrameSize(...)

    //input data
    int count = _sen.cost.count;
    _sen.cost.frID[count] = frameid;
    _sen.cost.simTime[count] = SIMTIME_DBL(simTime());

    //compute energy consumption
    _sen.Tsleep = 0;

    if (Tidl == -1)
        computeEnergy(&_sen.cost, &_sen.power,_sen.Tact, _sen.Tidl, _sen.Tsleep); //periodic sensing mode
    else
        computeEnergy(&_sen.cost, &_sen.power,_sen.Tact, Tidl, _sen.Tsleep);//on-demand sensing mode

    //consume energy consumption
    //printf("sensing energy\n");
    consumeEnergy(_sen.cost.Etot[count]);

    //initialize the energy for processing & comms of the frame
    _pro.cost.Etot[count] = 0;
    _com.cost.Etot[count] = 0;
}

// Energy consumption when radio module is simultaneously transmitting & receiving
void WiseResourceManager::computeEnergyCOM(int frameid,int numBytesTX, int numBytesRX)
{
   Enter_Method("computeEnergyCOM(int frameid,int numBytesTX, int numBytesRX)");

   //bitrate & power settings
   _com.power.num_active_states = 2;
   Radio *radioModule = check_and_cast <Radio*>(getParentModule()->getSubmodule("Communication")->getSubmodule("Radio"));
   _com.bitrateTX  = radioModule->getRXmode()->datarate;
   _com.bitrateRX  = radioModule->getRXmode()->datarate;
   _com.power.Pact[0] = 1e-3*radioModule->getTXlevel()->txPowerConsumed; //tx power (watt)
   _com.power.Pact[1] = 1e-3*radioModule->getRXmode()->power;  //rx power (watt)
   _com.power.Pidl = 1e-3*radioModule->getSleeplevel()->power; //idle power (watt)

   //input data
   int count = _com.cost.count;
   _com.cost.frID[count] = frameid;
   _com.cost.simTime[count] = SIMTIME_DBL(simTime());

   //requested data to TX/RX
   _com.data.TXbit_req[count] = (int)numBytesTX * 8;
   _com.data.RXbit_req[count] = (int)numBytesRX * 8;

   //required activation time for the requested TX/RX
   _com.Tact[0] = _com.data.TXbit_req[count]/_com.bitrateTX;//tx
   _com.Tact[1] = _com.data.RXbit_req[count]/_com.bitrateRX; //rx
   _com.Tidl = _sen.Tframe - _com.Tact[0] - _com.Tact[1];
   _com.Tsleep = 0;

   //TX the maximum data if Tact exceed the time allocated for each frame
   _com.dropData = 0;
   if (_com.Tidl < 0){
       _com.Tidl=0;
       _com.Tact[0]=_sen.Tframe;
       _com.dropData = 1;
       _com.data.TXbit_done[count] = _com.bitrateTX*_sen.Tframe;
       _com.data.RXbit_done[count] = _com.bitrateRX*_sen.Tframe;
      //opp_error("ERROR: Unexpected value for Tidle of COMMS-TX task: %s", _com.Tidl);
  }
   else{
       _com.data.TXbit_done[count] = _com.data.TXbit_req[count];
       _com.data.RXbit_done[count] = _com.data.RXbit_req[count];
   }

   //compute energy consumption
   computeEnergy(&_com.cost, &_com.power,_com.Tact, _com.Tidl, _com.Tsleep);
   double transitionPower = 2 * 1e-3*0.194 * 1e-3*62; //transition power between states (TX/RX->Sleep & Sleep->TX/RX)- 0.194ms/transition - 62mW/transition
   _com.cost.Eidl[count] = _com.cost.Eidl[count] + transitionPower;
   _com.cost.Eidl_acc[count] = _com.cost.Eidl_acc[count] + transitionPower;
   _com.cost.Etot[count] = _com.cost.Etot[count] + transitionPower;
   _com.cost.Etot_acc[count] = _com.cost.Etot_acc[count] + transitionPower;

   //consume energy consumption
   //printf("comms energy\n");
   consumeEnergy(_com.cost.Etot[count]);
}

void WiseResourceManager::computeEnergyPRO(int frameid, double execTime, double execTime2)
{
    Enter_Method("computeEnergyPRO(double time)");

    ////printf("execTime=%.2f execTime2=%.2f\n",execTime,execTime2);

    int count = _pro.cost.count;
    _pro.exeTimeR[count] = execTime;
    _pro.cost.frID[count] = frameid;
    _pro.cost.simTime[count] = SIMTIME_DBL(simTime());

    //double ticks = time*_cpuClockfreqHost; //number of clock cycles

    getProcessorSpeed();//update '_cpuClockfreqHost' variable
    //_cpuClockfreqHost = 3.166e+09;
    _pro.exeTimeS[count] = execTime*_cpuClockfreqHost/_pro.clockfreq; //execution time for simulated HW
    _pro.exeTimeO[count] = _pro.exeTimeS[count] * 1.0/_pro.optimization_factor;//execution time for simulated HW (applying 'code optimization' factor)

    _pro.Tact[0] = _pro.exeTimeO[count]; //for dynamic power
    _pro.Tact[1] = _pro.exeTimeO[count]; //for leakage power

    if (execTime2 != -1)
        //_pro.Tact[2] = execTime2 * _cpuClockfreqHost/_pro.clockfreq * 1.0/_pro.optimization_factor;
        _pro.Tact[2] = execTime2 * _cpuClockfreqHost/_pro.clockfreq;
    else
        _pro.Tact[2] = 0;
    _pro.exeTimeC[count] = _pro.Tact[2];

    _pro.Tidl = _sen.Tframe - _pro.Tact[0];
    _pro.Tsleep = 0;
    if (_pro.Tidl < 0){
         _pro.Tidl=0;
         //_pro.Tact = _Tframe;
         //opp_error("ERROR: Unexpected value for Tidle of COMMS-TX-RX task: %s", _com.Tidl);
         _pro.missData = 1;
      }
      else
         _pro.missData = 0;

    //compute energy consumption
    ////printf("_pro.Tact=%.2f _pro.Tact=%.2f _pro.Tact=%.2f _pro.Tact=%.2f\n",_pro.Tact[0],_pro.Tact[1],_pro.Tact[2],_pro.Tact[3]);
    ////printf("_pro.power=%.2f _pro.power=%.2f _pro.power=%.2f _pro.power=%.2f\n",_pro.power.Pact[0],_pro.power.Pact[1],_pro.power.Pact[2],_pro.power.Pact[3]);
    ////printf("_pro.Tidl=%.2f _pro.Tsle=%.2f \n",_pro.Tidl,_pro.Tsleep);
    ////printf("_pro.powerID=%.2f _pro.powerSL=%.2f \n",_pro.power.Pidl,_pro.power.Psle);
    computeEnergy(&_pro.cost, &_pro.power,_pro.Tact, _pro.Tidl, _pro.Tsleep);

    //consume energy consumption
    //printf("processing energy\n");
    consumeEnergy(_pro.cost.Etot[count]);
}
void WiseResourceManager::computeEnergy(state_energy_s *cost, model_power_s *power, double Tact[MAX_ACTIVE_STATES], double Tidl, double Tsle)
{
    int *count = &cost->count;

    //CURRENT ENERGY CONSUMPTION
    for (int i = 0; i<power->num_active_states;i++)
        cost->Eact[i][*count] = power->Pact[i] * Tact[i]; //active state 'i'
    //printf("Energy act[0]=%.2f act[1]=%.2f act[2]=%.2f act[3]=%.2f\n",cost->Eact[0][*count],cost->Eact[1][*count],cost->Eact[2][*count],cost->Eact[3][*count]);

    cost->Eidl[*count] = power->Pidl * Tidl; //idle state
    cost->Esle[*count] = power->Psle * Tsle; //sleep state
    //printf("Energy Idle=%.2f (_sen.Tidl=%.2f) Sleep=%.2f\n",cost->Eidl[*count],Tidl, cost->Esle[*count]);

    //compute energy for active+idle states
    cost->Etot[*count] = cost->Eidl[*count];
    for (int i = 0; i<power->num_active_states;i++)
        cost->Etot[*count] = cost->Etot[*count] + cost->Eact[i][*count]; //Active energy for state 'i'

    //ACUMULATED ENERGY CONSUMPTION
    if (*count > 0)    {
        for (int i = 0; i<power->num_active_states;i++)
                cost->Eact_acc[i][*count] = cost->Eact_acc[i][*count-1] + cost->Eact[i][*count]; //state 'i'

        cost->Eidl_acc[*count] = cost->Eidl_acc[*count-1] + cost->Eidl[*count];
        cost->Etot_acc[*count] = cost->Etot_acc[*count-1] + cost->Etot[*count];
   }

    (*count)++;
}

void WiseResourceManager::logCurrentData()
{
    double time_scale = 1e3; //convert to ms
    double ener_scale = 1e3; //convert to mJ
    double pow_scale = 1e3; //convert to mW

    bool found = false;
    if (_logger == NULL)
        return;

#if (OMNETPP_VERSION ==0x0500)
    double currentRun = getEnvir()->getConfigEx()->getActiveRunNumber();
#else
    double currentRun = ev.getConfigEx()->getActiveRunNumber();
#endif

    if (_lastLogS == -1) {
        *_logger << "#run,node,camID,cpuClockfreq,cpuClockfreqHost,Voltage,FPS,oFPS,H,W,resize,freqSen,Tframe,optF,sTact,sTidl,sPact,sPidl,pPact,pPlea,pPidl,pOptF,cPacttx,cPactrx, cPidl" << endl;
        *_logger << "#" << currentRun << "," << _self << "," << _camID << "," << _pro.clockfreq << "," << _cpuClockfreqHost << "," << _pro.V
                 << "," << _sen.framerate << "," << _sen.orig_framerate << "," << _sen.model.rows << "," << _sen.model.cols
                 << "," << _sen.resize << "," << _sen.clockfreq << "," << 1/_sen.framerate << "," << _pro.optimization_factor
                 << "," << _sen.Tact[0] << "," << _sen.Tidl << "," << pow_scale*_sen.power.Pact[0] << "," << pow_scale*_sen.power.Pidl << "," << pow_scale*_pro.power.Pact[0] << "," << pow_scale*_pro.power.Pact[1] << "," << pow_scale*_pro.power.Pidl << "," << _pro.optimization_factor
                 << "," << _com.power.Pact[0]  << "," << _com.power.Pact[1] << "," << _com.power.Pidl << endl;
        *_logger << "#" << "t_sim - Simulation time" << endl;
        *_logger << "#" << "frID - Frame ID" << endl;
        *_logger << "#" << "t_sim - Simulation time" << endl;
        *_logger << "#" << "Seac - Energy for sensing (active state)" << endl;
        *_logger << "#" << "Seid - Energy for sensing (idle state)" << endl << endl;
        //*_logger << "#" << "ESto - Energy for sensing (Total)" << endl << endl;
        *_logger << "#" << "DrpD - FLAG indicating that tx/rx data needs more than T_frame (overloaded bandwidth)" << endl;
        *_logger << "#" << "Ctxraw - Data to TX (bytes) required by application" << endl;
        *_logger << "#" << "Ctxreq - Data to TX (bytes) after compression"  << endl;
        *_logger << "#" << "Ctxdone - Data TX (bits) done considering available bandwidth" << endl;
        //*_logger << "#" << "TXcomr - Compression ratio for communication" << endl;
        *_logger << "#" << "Crx - Data RX (bits)" << endl;
        *_logger << "#" << "Cetx - Energy for communication (active tx)" << endl;
        *_logger << "#" << "Cerx - Energy for communication (active rx)" << endl;
        *_logger << "#" << "Ceid - Energy for communication (idle)" << endl << endl;
        //*_logger << "#" << "ECto - Energy for communication (total)" << endl << endl;
        *_logger << "#" << "DrpP - FLAG indicating processing needs more than T_frame (overloaded processing)" << endl;
        *_logger << "#" << "Ptrun - Time for processing - general (host machine)" << endl;
        *_logger << "#" << "Ptemu - Time for processing - general (emulated HW)" << endl;
        *_logger << "#" << "Ptopt - Time for processing - general (emulated HW and optimization factor)" << endl;
        *_logger << "#" << "Ptcol - Time for processing - collaborative tasks  (emulated HW)" << endl;
        *_logger << "#" << "Peac - Energy for processing - general (active state)" << endl;
        *_logger << "#" << "Pelk - Energy for processing - general (active state, leakage)" << endl;
        *_logger << "#" << "Peco - Energy for processing - collaborative tasks (active state)" << endl;
        *_logger << "#" << "Peid - Energy for processing - general (idle state)" << endl << endl;

        *_logger << "#" << "Units: energy (mJ), power (mw), time (ms), data (bits)" << endl;
        //*_logger << "#" << "t_sim\tfrID\tESac\tESid\tESto\tDrpD\tTXraw\tTXReq\tTXdone\tTXcomr\tRXdone\tECtx\tECrx\tECid\tECto\tDrpP\tPtR\tPtS\tPtO\tPtC\tEPro\tEPlk\tEPco\tEPid\tEPto\t" << endl;
        *_logger << "#" << "t_sim\tfrID\tSeac\tSeid\tDrpD\tCtxraw\tCtxreq\tCtxdone\tCrx\tCetx\tCerx\tCeid\tDrpP\tPtrun\tPtemu\tPtopt\tPtcol\tPeac\tPelk\tPeco\tPeid\t" << endl;
        _lastLogS = 0;
    }

    for (int i=_lastLogS;i<_sen.cost.count-1;i++)
    {
        *_logger << std::setprecision(4) << _sen.cost.simTime[i] << "\t" << _sen.cost.frID[i]  << "\t"
                   << std::setprecision(3) << ener_scale*_sen.cost.Eact[0][i] << "\t"
                   << std::setprecision(3) << ener_scale*_sen.cost.Eidl[i] << "\t";
                   //<< std::setprecision(3) << factor*_sen.cost.Etot[i] << "\t";

        found = false;
        for(int j = 0;j<_pro.cost.count-1;j++)
            if(_sen.cost.frID[i]==_pro.cost.frID[j])
            {
                found = true;
                //*_logger << (double)_com.dropData << " \t" << (double)_com.data.numDet[j] << "\t"
                *_logger
                        << std::setprecision(3) <<(double)_com.dropData << "\t"
                        << std::setprecision(4) << (double)_com.data.TXbit_raw[j]/8  << "\t"
                        << std::setprecision(4) << (double)_com.data.TXbit_req[j]/8  << "\t"
                        << std::setprecision(4) << (double)_com.data.TXbit_done[j]/8  << "\t"
                        //<< std::setprecision(4) << (double)_com.data.compresionRatio[j]  << "\t"
                        << std::setprecision(4) << (double)_com.data.RXbit_done[j]/8  << "\t"
                        << std::setw(6) << std::setprecision(3) << ener_scale*_com.cost.Eact[0][j] << "\t"
                        << std::setw(6) << std::setprecision(3) << ener_scale*_com.cost.Eact[1][j] << "\t"
                        << std::setw(6) << std::setprecision(3) << ener_scale*_com.cost.Eidl[j]<< "\t"
                        //<< std::setprecision(3) << factor*_com.cost.Etot[j]<< "\t"

                        << std::setprecision(3) <<(double)_pro.missData << "\t"
                        << std::setw(5) << std::setprecision(3) << _pro.exeTimeR[j] * time_scale << " \t"
                        << std::setw(5) << std::setprecision(3) << _pro.exeTimeS[j] * time_scale << " \t"
                        << std::setw(5) << std::setprecision(3) << _pro.exeTimeO[j] * time_scale << " \t"
                        << std::setw(5) << std::setprecision(3) << _pro.exeTimeC[j] * time_scale << " \t"
                        << std::setw(5) << std::setprecision(3) << ener_scale*_pro.cost.Eact[0][j]  << " \t"
                        << std::setw(5) << std::setprecision(2) << ener_scale*_pro.cost.Eact[1][j] << " \t"
                        << std::setw(5) << std::setprecision(3) << ener_scale*_pro.cost.Eact[2][j] << " \t"
                        << std::setw(5) << std::setprecision(3) << ener_scale*_pro.cost.Eidl[j] << " \t" << endl;
                        //<< std::setprecision(3) << factor*_pro.cost.Etot[j] << "\t" << endl;
            }

        if (found == false)
        {
            for (int k=0;k<17;k++)
                *_logger << -1.0 << "\t";
            *_logger << endl;
        }
    }
    _lastLogS = _sen.cost.count-1;
 }

double WiseResourceManager::getSpentTime(int index)
{
    int count = _pro.cost.count;

    if (index==-1)
        return _pro.exeTimeO[count-1];
    else
        return _pro.exeTimeO[index];
}
