#pragma once
#include "systems/AirbusComponent.h"



class AOAProbe : public AirbusComponent
{
	
private:
	//Source: thales AOA sensor accuracy: 0.25º 
	const float PROBE_ACCURACY_DEG = 0.125;
	ProbeLocation probeLocation;
	float AOADegrees;

public:
	AOAProbe(ProbeLocation probeLocation);

	void update();
	float getAOADegrees();
};

