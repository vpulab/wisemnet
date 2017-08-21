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


#ifndef _WISERESOURCEMANAGER_H_
#define _WISERESOURCEMANAGER_H_

#include <map>
#include "CastaliaModule.h"
#include "WiseResourceManagerMessage_m.h"

using namespace std;

    typedef enum {
        WISE_ENERGY_SEN_TOT = 01,
        WISE_ENERGY_SEN_ACT = 02,
        WISE_ENERGY_SEN_IDL = 03,
        WISE_ENERGY_COM_TOT = 10,
        WISE_ENERGY_COM_IDL = 11,
        WISE_ENERGY_COM_TX  = 12,
        WISE_ENERGY_COM_RX  = 13,
        WISE_ENERGY_PRO_TOT = 20,
        WISE_ENERGY_PRO_ACT = 21,
        WISE_ENERGY_PRO_LKG = 22,
        WISE_ENERGY_PRO_IDL = 23,
    } energy_type_t;

    enum wiseResourceManagerTimers {
        WISE_PERIODIC_ENERGY_CALCULATION = 1,
    };

    //Maximum number of active states for the consumption models within each module
    const int MAX_ACTIVE_STATES=4;

    //Energy Consumption for each state
    struct state_energy_s {

        int count;

        map<int,double> frID;//ID of the frame where cost is computed
        map<int,double> simTime;//timestamp of the frame where cost is computed

        std::map<int,std::map<int,double> > Eact;//Energy for the active state (we consider up to MAX_ACTIVE_STATES active states)
        map<int,double> Eidl;//Energy for the idle state
        map<int,double> Esle;//Energy for the sleep state
        map<int,double> Etot;//Energy for all states

        std::map<int,std::map<int,double> > Eact_acc;//Energy for the active state (we consider up to MAX_ACTIVE_STATES active states)
        map<int,double> Eidl_acc;//Energy for the idle state
        map<int,double> Esle_acc;//Energy for the sleep state
        map<int,double> Etot_acc;//Energy for all states
    };

    //Power consumption for each state
    struct model_power_s {
        int num_active_states;
        double Pact[MAX_ACTIVE_STATES],Pidl,Psle; //Power for active (dynamic & leaked), idle and sleep states
    };

    struct pro_info_t {

            map<int,double> exeTimeR;//execution time of the machine employed for running the experiment
            map<int,double> exeTimeS;//previous execution time corrected for the simulated HW
            map<int,double> exeTimeO;//previous execution time corrected for the simulated HW (applying a 'code optimization' factor)
            map<int,double> exeTimeC;//execution time corrected for the simulated HW (collaborative tasks)
            double busy;

            //running parameters
            double clockfreq;     //Current frequency
            double V;             //Current Circuit Voltage
            double Tact[MAX_ACTIVE_STATES],Tidl, Tsleep; //Active, idle and sleep times
            int missData;

            double optimization_factor;

            //model;
            struct pro_model_s {
                    string type;
                    double fmax, fmin;    //Maximum and minimum operating frequency
                    double Vmax, Vmin;    //Maximum and minimum operating Voltage

                    //Active power models
                    double Pa_k[4];//constants for the 3rd-order models for Pactive

                    //Idle power models
                    double Pi_k;//Pactive/Pidle ratio (factor)
                    double Pi_f;//Pactive/Pidle ratio (frequency)

                    //Voltage-Frequency relation (Dynamic Voltage Scaling)
                    double DVS_m1, DVS_m2;//Parameters of 1st-order polynomial model
                }model;

            //power consumption of active, idle and sleep states
            model_power_s power;

            //energy consumption of active, idle and sleep states
            state_energy_s cost;
        };

    struct sen_info_t {

           //running parameters
           double clockfreq; //Current frequency
           double framerate; //framerate for capturing video frames (real framerate achieved by the sensing module)
           double orig_framerate; //framerate for capturing video frames (user-defined value)
           double src_framerate; //framerate for capturing video frames
           double Tframe;//Time required for capturing a frame
           double Tact[MAX_ACTIVE_STATES],Tidl, Tsleep; //Active, idle and sleep times

           double resize; // enable resizing of input frames

           struct sen_model_s {
               string type;

               //Active power models
               double Pa_c[4];//coeffs for the 3rd-order models for Pactive

               //Idle power models
               double Pi_c[4];//coeffs for the 3rd-order models for Pactive

               double fmax, fmin;    //Maximum and minimum operating frequency
               double frmax, frmin;    //Maximum and minimum operating framerate
               int rows, cols, nch; //rows, columns and channels of input frame
            }model;

           //power consumption of active, idle and sleep states
           model_power_s power;

           //energy consumption of active, idle and sleep states
           state_energy_s cost;
        };

    struct com_info_t {

            //running parameters
            double bitrateTX, bitrateRX;
            double Tact[MAX_ACTIVE_STATES],Tidl, Tsleep; //Active, idle and sleep times
            int dropData;

            //model;
            struct com_model_s {
               string type;

               double Eele;    //Electrical energy required by circuitry to send/receive one bit
               double Efs, Emp;//constant for free-space & multipath propagations
               double d;       //distance between two communicating nodes
               double d0;      //threshold distance to apply 'fs' or 'mp' models

           }model;

           struct com_data_s {
               map<int,double> TXbit_raw, RXbit_raw;     //raw data to transmit
               map<int,double> TXbit_req, RXbit_req;     //requested data to transmit (maybe be raw or codification over raw)
               map<int,double> TXbit_done, RXbit_done;   //achieved datarate
               map<int,double> compresionRatio;     //achieved compression ratio for TX
               map<int,double> numDet;     //number of detections
           }data;

           //power consumption of active, idle and sleep states
           model_power_s power;

           //energy consumption of active, idle and sleep states
           state_energy_s cost;
        };

class WiseResourceManager: public CastaliaModule {
 private:

	// parameters and variables
    int _self,_camID;

	/*--- The default parameters ---*/
	double sigmaCPUClockDrift;
	double cpuClockDrift;
	double initialEnergy;
	double ramSize;
	double baselineNodePower;
	double currentNodePower;
	simtime_t timeOfLastCalculation;
	double periodicEnergyCalculationInterval;

    map<int,double> storedPowerConsumptions;

	double remainingEnergy;
	double totalRamData;

	/*--- Custom class parameters ---*/
	double _cpuClockfreqHost;//CPU frequency of the host PC for simulation

    /*--- Log data---*/
	cMessage *_energyMsg;
	std::ofstream *_logger;
	int _lastLogS;

 public:
    /*--- Models & costs (structures) ---*/
    sen_info_t _sen;
    pro_info_t _pro;
    com_info_t _com;


 protected:
	virtual void initialize();
	void load_consumption_models();
	virtual void handleMessage(cMessage * msg);
	virtual void finishSpecific();
	void calculateEnergySpent();

 public:
	/*--- Set/Get methods for SENSING module ---*/
    void setSENFrameRate(double newFrameRate);
    void setSENFrameSize(int rows, int cols, int nch, double resize);
    void setSENClk(double newFreq);

    double getSENClk(){return _sen.clockfreq;}
    double getSENFrameRate(){return _sen.framerate;};
    double getSENFrameRate_user(){return _sen.orig_framerate;};
    sen_info_t getSENInfo(){return _sen;}

    void updateSENTact();

    /*--- Set/Get methods for PROCESSING module ---*/
    void setPROClk(double newFreq);

	double getCPUClockDrift(){return (1.0f + cpuClockDrift);}
	double getPROClk(){return _pro.clockfreq;}
	double getPROV(){return _pro.V;}
	double getPROTimeR(){return _pro.exeTimeR[_pro.cost.count-1];}
	double getPROTimeC(){return _pro.exeTimeC[_pro.cost.count-1];}
	double getPROTimeO(){return _pro.exeTimeO[_pro.cost.count-1];}
	int getPROmissData(){return _pro.missData;}
	pro_info_t getPROInfo(){return _pro;}

    /*--- Set/Get methods for COMMS module ---*/
	int getCOMBytesTXraw(){return _com.data.TXbit_raw[_com.cost.count-1]*8;}
	int getCOMBytesRXraw(){return _com.data.RXbit_raw[_com.cost.count-1]*8;}
	int getCOMBytesTXreq(){return _com.data.TXbit_req[_com.cost.count-1]*8;}
	int getCOMBytesRXreq(){return _com.data.RXbit_req[_com.cost.count-1]*8;}
	int getCOMBytesTXdone(){return _com.data.TXbit_done[_com.cost.count-1]*8;}
	int getCOMBytesRXdone(){return _com.data.RXbit_done[_com.cost.count-1]*8;}
	int getCOMDrop(){return _com.dropData;}
	com_info_t getCOMInfo(){return _com;}

   	/*--- Compute-consumption methods ---*/
    void consumeEnergy(double amount);

	void computeEnergyCOM(int frameid,int numBytesTX, int numBytesRX);
	void computeEnergySEN(int frameid,double Tidl=-1);
	void computeEnergyPRO(int frameid,double execTime, double execTime2=-1);
	void computeEnergy(state_energy_s *cost, model_power_s *power, double Tact[MAX_ACTIVE_STATES], double Tidl, double Tsle);

	double getSpentEnergy();
	double getRemainingEnergy();
	double getCurSpentEnergy(energy_type_t energyType);
	double getTotSpentEnergy(energy_type_t energyType);

    /*--- Miscelanea ---*/
    void destroyNode(void);
    int RamStore(int numBytes);
    void RamFree(int numBytes);

    void parseRadioParameterFile(const char *fileName);

    void initLogger(std::string _filename, int self ,int camID);
    void logCurrentData();

    double getSpentTime(int index=-1);
};

#endif
