#include "A320.h"
#include "PitotProbe.h"

PitotProbe::PitotProbe(ProbeLocation probeLocation)
{
	this->probeLocation = probeLocation;
}

void PitotProbe::update()
{
	// TODO: Aircraft->EquipmentFailures->Pitot[probeLocation] -> Health.
	// TODO: icing conditions.
	this->indicatedAirspeedKn = SimInterface->getIASKn();

	// Simulate different readings for different probes.
	if (this->probeLocation == FO) {
		this->indicatedAirspeedKn *= PROBE_ACCURACY_RATIO;
	}
	else if (this->probeLocation == Standby) {
		this->indicatedAirspeedKn *= PROBE_ACCURACY_RATIO_INV;
	}
}

float PitotProbe::getIndicatedAirspeedKn()
{
	return this->indicatedAirspeedKn;
}
