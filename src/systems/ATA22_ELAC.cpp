#include "ATA22_ELAC.h"
#include "ATA34_ADIRU.h"




ATA22_ELAC::ATA22_ELAC(int number)
{
	this->number = number;
}


ATA22_ELAC::~ATA22_ELAC()
{
}

void ATA22_ELAC::connect(ATA34_ADIRU * ADIRU)
{

}

void update()
{
	
}

void ATA22_ELAC::inputMessage(RadioAltimeterData *message)
{
	this->currentRadioAltimeterHeightFt = message->altitude;
}
