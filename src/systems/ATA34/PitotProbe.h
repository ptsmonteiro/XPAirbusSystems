#pragma once
#include "systems/AirbusComponent.h"


class PitotProbe : public AirbusComponent
{
private:
	const float PROBE_ACCURACY_RATIO = 1.005;
	const float PROBE_ACCURACY_RATIO_INV = 0.995;
	ProbeLocation probeLocation;
	float indicatedAirspeedKn;

public:
	PitotProbe(ProbeLocation probeLocation);
	void update();
	float getIndicatedAirspeedKn();
};