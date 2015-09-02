#pragma once
#include "AirbusComponent.h"

/*
	System to hold all air data sensors and probes:
		AOA
		TAT
		Pitot Pressure
		Static Pressure
*/
class AirDataProbes : AirbusComponent
{
public:
	AirDataProbes();
	~AirDataProbes();

	virtual BaseMessage* update();
};

