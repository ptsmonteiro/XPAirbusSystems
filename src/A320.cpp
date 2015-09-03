#include "A320.h"
#include <vector>

A320::A320()
{
	this->elac1 = new ATA22_ELAC(1);
	this->elac2 = new ATA22_ELAC(2);

	this->lgciu1 = new ATA32_LGCIU(1);
	this->lgciu2 = new ATA32_LGCIU(2);

	this->du1 = new ATA31_DU(1);
	this->du2 = new ATA31_DU(2);
	this->du3 = new ATA31_DU(3);
	this->du4 = new ATA31_DU(4);
	this->du5 = new ATA31_DU(5);
	this->du6 = new ATA31_DU(6);

	this->ra1 = new ATA34_RadioAlt(1);
	this->ra2 = new ATA34_RadioAlt(2);

	this->fwc1 = new ATA31_FWC(1);
	this->fwc2 = new ATA31_FWC(2);
}


A320::~A320()
{
}

void A320::updateSystemsHealth()
{

	// Update an array/table/vector os systems health.
	return;
}


/*
	Updates each component:
		1. Probes and Sensors
		2. Computers
		3. Displays and Indicators
*/
void A320::updateSystems()
{
	// Probes and Sensors
	updateProbes();

	// Computers
	updateComputers();

	// Displays and Indicators
	updateDisplays();
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
}

/*
	Reconfigures system connections:
		1. Failover connections
		2. Control Law changes
		3. Elec emergency configuration
*/
void A320::reconfigureSystems()
{

}

void A320::update()
{
	updateSystems();
	reconfigureSystems();

	//updateSystemsHealth();
	//propagateSignals();
}
