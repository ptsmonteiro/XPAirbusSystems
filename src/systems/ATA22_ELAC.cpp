#include "ATA22_ELAC.h"
#include "systems/ATA34/ADIRU.h"




ATA22_ELAC::ATA22_ELAC(int number)
{
	this->number = number;
}


ATA22_ELAC::~ATA22_ELAC()
{
}

void ATA22_ELAC::connect(ADIRU * ADIRU)
{
	this->myADIRU = ADIRU;
}

void ATA22_ELAC::connect(ATA32_LGCIU *lgciu)
{
	this->LGCIU = lgciu;
}

void ATA22_ELAC::connect(RadioAlt *ra)
{
	this->radioAlt = ra;
}

void ATA22_ELAC::update()
{
	this->currentRadioAltimeterHeightFt = this->radioAlt->getAltitudeFt();
}
