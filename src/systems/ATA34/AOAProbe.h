#pragma once
#include "systems\AirbusComponent.h"
class AOAProbe : AirbusComponent
{
public:
	AOAProbe();
	~AOAProbe();

	void update();
	float getAOADegrees();

protected:
	float AOADegrees;
};

