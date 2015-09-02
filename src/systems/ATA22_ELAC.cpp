#include "ATA22_ELAC.h"
#include "ADIRU.h"




ATA22_ELAC::ATA22_ELAC(int number)
{
	this->number = number;
}


ATA22_ELAC::~ATA22_ELAC()
{
}

void ATA22_ELAC::connect(ADIRU * ADIRU)
{

}

void update()
{
	
}

void ATA22_ELAC::inputMessage(RadioAltimeterData *message)
{
	this->currentRadioAltimeterHeightFt = message->altitude;
}
