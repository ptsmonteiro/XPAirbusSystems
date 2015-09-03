#include "AOAProbe.h"



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
	this->AOADegrees = this->simInterface->getAOADegrees();
}