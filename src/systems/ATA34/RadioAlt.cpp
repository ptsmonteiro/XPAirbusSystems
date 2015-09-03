#include "systems\ATA34\RadioAlt.h"


RadioAlt::RadioAlt(int number)
{
	this->currentHealth = Online;
	this->number = number;
}
 
void RadioAlt::update()
{
	this->altitudeFt = this->simInterface->getRadioAltitudeFt();
}

int RadioAlt::getAltitudeFt()
{
	return 0;
}

 

RadioAlt::~RadioAlt()
{
}

