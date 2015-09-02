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
	updateSystemsHealth();
	propagateSignals();
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

void A320::update()
{
}
