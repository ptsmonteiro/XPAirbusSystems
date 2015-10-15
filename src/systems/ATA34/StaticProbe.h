#pragma once
#include "systems/AirbusComponent.h"

enum StaticProbeLocation {
	Captain1,
	Captain2,
	FO1,
	FO2,
	StandBy1,
	StandBy2
};

class StaticProbe :	public AirbusComponent
{
private:
	StaticProbeLocation probeLocation;
	float currentPressureInHg;

	
public:
	float getCurrentStaticPressureInHg();

	StaticProbe(StaticProbeLocation probeLocation);

	void update();
};