#include "A320.h"
#include <vector>

A320::A320()
{
	// Probes and sensors
	this->aoaProbeCapt = new AOAProbe;
	this->aoaProbeFO = new AOAProbe;
	this->aoaProbeStandby = new AOAProbe;

	this->tatProbeCapt = new TATProbe;
	this->tatProbeFO = new TATProbe;

	this->pitotProbeCapt = new PitotProbe;
	this->pitotProbeFO = new PitotProbe;
	this->pitotProbeStandby = new PitotProbe;

	this->staticProbeCapt1 = new StaticProbe;
	this->staticProbeCapt2 = new StaticProbe;
	this->staticProbeFO1 = new StaticProbe;
	this->staticProbeFO2 = new StaticProbe;
	this->staticProbeStandby1 = new StaticProbe;
	this->staticProbeStandby2 = new StaticProbe;

	this->ra1 = new RadioAlt(1);
	this->ra2 = new RadioAlt(2);

	// Computers

	this->lgciu1 = new ATA32_LGCIU(1);
	this->lgciu2 = new ATA32_LGCIU(2);

	this->adiru1 = new ADIRU(1);
	this->adiru2 = new ADIRU(2);
	this->adiru3 = new ADIRU(3);

	this->elac1 = new ATA22_ELAC(1);
	this->elac2 = new ATA22_ELAC(2);

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

void A320::updateSystemsHealth()
{

	// Update an array/table/vector os systems health.
	return;
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
	this->elac2->update();

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

/*
	Reconfigures system connections:
		1. Failover connections
		2. Control Law changes
		3. Elec emergency configuration
*/
void A320::reconfigureSystems()
{
	// Electrics

	// Hydraulics

	// Bleed

	// Flight computers

	// ADIRU

	// FMGC

	// DMC

	// DU
}

void A320::update()
{
	// Probes and Sensors
	updateProbes();

	// Computers
	updateComputers();

	// Displays and Indicators
	updateDisplays();

	// Check operation and reconfigure if required
	reconfigureSystems();

	updateSystemsHealth();
}
