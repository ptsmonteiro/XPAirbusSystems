#include "systems\ATA34\RadioAlt.h"

RadioAlt::RadioAlt(int number)
{
	this->currentHealth = Healthy;
	this->number = number;
}
 
void RadioAlt::update()
{
	if (this->currentHealth != Healthy) {
		return;
	}

	this->altitudeFt = this->simInterface->getRadioAltitudeFt();
}

int RadioAlt::getAltitudeFt()
{
	return this->altitudeFt;
}

RadioAlt::~RadioAlt()
{
}