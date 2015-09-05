#include "AOAProbe.h"
#include "A320.h"


AOAProbe::AOAProbe()
{
}

float AOAProbe::getAOADegrees()
{
	return this->AOADegrees;
}


AOAProbe::~AOAProbe()
{
}

void AOAProbe::update()
{
	this->AOADegrees = SimInterface->getAOADegrees();
}