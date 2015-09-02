#include "A320.h"
#include "messages/AirDataProbesMessage.h"
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

void A320::propagateSignals()
{
	BaseMessage* message;
	
	/// ATA34 Information (Nav Data)
	// RA 1
	if (this->ra1->getHealth() == Online)
	{
		this->elac1->inputMessage((RadioAltimeterData*) this->ra1->update());
		this->elac2->inputMessage((RadioAltimeterData*) this->ra1->update());
	}
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
	AirDataProbesMessage* adpm = (AirDataProbesMessage*) this->airDataProbes->update();

	this->adiru1->inputMessage(adpm);
	this->adiru2->inputMessage(adpm);
	this->adiru3->inputMessage(adpm);
}

void A320::updateComputers()
{
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
