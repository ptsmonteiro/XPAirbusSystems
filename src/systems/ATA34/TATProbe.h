#pragma once
#include "systems/AirbusComponent.h"
class TATProbe :
	public AirbusComponent
{
public:
	TATProbe();
	~TATProbe();

	float totalAirTemperatureKelvin;

	void update();
};

