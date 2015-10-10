#include "A320.h"
#include "ATA32_LGCIU.h"



ATA32_LGCIU::ATA32_LGCIU(int number)
{
	this->number = number;
}


ATA32_LGCIU::~ATA32_LGCIU()
{
}

void ATA32_LGCIU::update()
{
	this->gearCompressed = SimInterface->isMainGearCompressed();

}

bool ATA32_LGCIU::isGearCompressed()
{
	return this->gearCompressed;
}
