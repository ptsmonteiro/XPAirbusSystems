#pragma once
#include "systems\AirbusComponent.h"

enum AoaProbeLocation {
	Captain,
	FO,
	Standby
};

class AOAProbe : public AirbusComponent
{
private:
	AoaProbeLocation probeLocation;
	float AOADegrees;

public:
	AOAProbe(AoaProbeLocation probeLocation);

	void update();
	float getAOADegrees();
};

