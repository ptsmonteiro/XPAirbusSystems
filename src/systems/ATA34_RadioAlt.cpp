#include "ATA34_RadioAlt.h"


ATA34_RadioAlt::ATA34_RadioAlt(int number)
{
	this->currentHealth = Online;
	this->number = number;
}
 
void ATA34_RadioAlt::update()
{
	this->altitudeFt = this->simInterface->getRadioAltitudeFt();
}

int ATA34_RadioAlt::getAltitudeFt()
{
	return 0;
}

 

ATA34_RadioAlt::~ATA34_RadioAlt()
{
}

