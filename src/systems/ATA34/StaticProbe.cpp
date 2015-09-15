#include "a320.h"
#include "StaticProbe.h"

float StaticProbe::getCurrentStaticPressureInHg()
{
	return this->currentPressureInHg;
}

StaticProbe::StaticProbe(StaticProbeLocation probeLocation)
{
	this->probeLocation = probeLocation;
}

void StaticProbe::update()
{
	// No electric supply.

	// TODO: Aircraft->EquipmentFailures[probeLocation] -> Health.

	if (currentHealth == Healthy) {
		currentPressureInHg = SimInterface->getCurrentPressureInHg();
	}
}

StaticProbe::~StaticProbe()
{
}