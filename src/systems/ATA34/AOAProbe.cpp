#include "AOAProbe.h"
#include "A320.h"


AOAProbe::AOAProbe(AoaProbeLocation probeLocation)
{
	this->probeLocation = probeLocation;
}

float AOAProbe::getAOADegrees()
{
	return this->AOADegrees;
}

void AOAProbe::update()
{
	// No electric supply.
	// TODO: Aircraft->EquipmentFailures[probeLocation] -> Health.
	// TODO: icing conditions.

	this->AOADegrees = SimInterface->getAOADegrees();
}