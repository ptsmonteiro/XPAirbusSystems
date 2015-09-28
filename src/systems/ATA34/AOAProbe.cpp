#include "AOAProbe.h"
#include "A320.h"


AOAProbe::AOAProbe(ProbeLocation probeLocation)
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

	// Simulate different readings for different probes.
	if (this->probeLocation == FO) {
		this->AOADegrees += PROBE_ACCURACY_DEG;
	}
	else if (this->probeLocation == Standby) {
		this->AOADegrees -= PROBE_ACCURACY_DEG;
	}
}