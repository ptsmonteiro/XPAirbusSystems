#include "A320.h"
#include "LGCIU.h"



LGCIU::LGCIU(int number)
{
	this->number = number;
}


LGCIU::~LGCIU()
{
}

void LGCIU::update()
{
	this->gearCompressed = SimInterface->isMainGearCompressed();

}

bool LGCIU::isGearCompressed()
{
	return this->gearCompressed;
}
