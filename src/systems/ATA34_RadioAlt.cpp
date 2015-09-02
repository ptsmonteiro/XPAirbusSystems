#include "ATA34_RadioAlt.h"
#include "messages/RadioAltimeterData.h"


ATA34_RadioAlt::ATA34_RadioAlt(int number)
{
	this->currentHealth = Online;
	this->number = number;
}
 
BaseMessage* ATA34_RadioAlt::update()
{
	if (this->currentHealth == Online) {
		RadioAltimeterData* rad = new RadioAltimeterData();

		rad->altitude = 50;	// Get this from a dataref.
		return rad;
	}
	else {
		return nullptr;
	}
}

 

ATA34_RadioAlt::~ATA34_RadioAlt()
{
}

