#pragma once
#include "systems\AirbusComponent.h"
class PitotProbe :
	public AirbusComponent
{
public:
	PitotProbe();
	~PitotProbe();

	void update();
};

