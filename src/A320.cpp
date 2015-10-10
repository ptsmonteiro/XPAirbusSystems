#include <vector>
#include "core\core.h"
#include "A320.h"
#include "sim_interface\XPlaneInterface.h"

/* Globals */
A320* Aircraft;
SimulatorInterface* SimInterface;
MessageLogger* Logger;

A320::A320()
{
	Aircraft = this;
	SimInterface = new XPlaneInterface();
	Logger = new MessageLogger();
	GlobalState = new AircraftState();

	lastUpdateElapsedMe = -1;
	lastUpdateElapsedSimulator = -1;
	updateCounter = -1;

	this->electricNetwork = new ElectricNetwork;

	// Probes and sensors
	this->aoaProbeCapt = new AOAProbe(Captain);
	this->aoaProbeFO = new AOAProbe(FO);
	this->aoaProbeStandby = new AOAProbe(Standby);

	this->tatProbeCapt = new TATProbe;
	this->tatProbeFO = new TATProbe;

	this->pitotProbeCapt = new PitotProbe(Captain);
	this->pitotProbeFO = new PitotProbe(FO);
	this->pitotProbeStandby = new PitotProbe(Standby);

	this->staticProbeCapt1 = new StaticProbe(Captain1);
	this->staticProbeCapt2 = new StaticProbe(Captain2);
	this->staticProbeFO1 = new StaticProbe(FO1);
	this->staticProbeFO2 = new StaticProbe(FO2);
	this->staticProbeStandby1 = new StaticProbe(StandBy1);
	this->staticProbeStandby2 = new StaticProbe(StandBy2);

	this->ra1 = new RadioAlt(1);
	this->ra2 = new RadioAlt(2);

	// Computers
	this->lgciu1 = new ATA32_LGCIU(1);
	this->lgciu2 = new ATA32_LGCIU(2);

	this->adiru1 = new ADIRU(1, this->staticProbeCapt1, this->staticProbeCapt2, this->aoaProbeCapt, this->pitotProbeCapt);
	this->adiru2 = new ADIRU(2, this->staticProbeFO1, this->staticProbeFO2, this->aoaProbeFO, this->pitotProbeStandby);
	this->adiru3 = new ADIRU(3, this->staticProbeStandby1, this->staticProbeStandby2, this->aoaProbeStandby, this->pitotProbeFO);

	this->elac1 = new ATA22_ELAC(1, this->ra1, this->lgciu1, this->adiru1);
	this->elac2 = new ATA22_ELAC(2, this->ra2, this->lgciu2, this->adiru2);

	this->fwc1 = new ATA31_FWC(1);
	this->fwc2 = new ATA31_FWC(2);

	this->du1 = new ATA31_DU(1);
	this->du2 = new ATA31_DU(2);
	this->du3 = new ATA31_DU(3);
	this->du4 = new ATA31_DU(4);
	this->du5 = new ATA31_DU(5);
	this->du6 = new ATA31_DU(6);

	//lots of things missing here
}

A320::~A320()
{
}

void A320::init()
{
	GlobalState->InitializeColdAndDark();
	resetColdAndDark();
}


void A320::updateProbes()
{
	this->aoaProbeCapt->update();
	this->aoaProbeFO->update();
	this->aoaProbeStandby->update();

	this->tatProbeCapt->update();
	this->tatProbeFO->update();

	this->pitotProbeCapt->update();
	this->pitotProbeFO->update();
	this->pitotProbeStandby->update();

	this->staticProbeCapt1->update();
	this->staticProbeCapt2->update();
	this->staticProbeFO1->update();
	this->staticProbeFO2->update();
	this->staticProbeStandby1->update();
	this->staticProbeStandby2->update();

	this->ra1->update();
	this->ra2->update();
}

void A320::updateComputers()
{
	this->lgciu1->update();
	this->lgciu2->update();

	this->adiru1->update();
	this->adiru2->update();
	this->adiru3->update();

	this->elac1->update();
//	this->elac2->update();

}

void A320::updateDisplays()
{
	this->du1->update();
	this->du2->update();
	this->du3->update();
	this->du4->update();
	this->du5->update();
	this->du6->update();
}

void A320::reconfigureSystems()
{
	// Electric

	// Hydraulics

	// Bleed

	// Flight computers

	// ADIRU

	// FMGC

	// DMC

	// DU
}

void A320::update(float elapsedMe, float elapsedSim, int counter)
{
	// Check operation and reconfigure if required
	reconfigureSystems();

	// Probes and Sensors
	updateProbes();

	// Computers
	updateComputers();

	// Displays and Indicators
	updateDisplays();

	this->lastUpdateElapsedMe = elapsedMe;
	this->lastUpdateElapsedSimulator = elapsedSim;
	this->updateCounter = counter;

}

void A320::resetColdAndDark()
{
	//TODO: Until we have some buttons to turn the batteries on....
	electricNetwork->reconfigure(DEBUG_CONFIG_1);
}