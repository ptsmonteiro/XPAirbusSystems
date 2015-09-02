#pragma once
#include "BaseMessage.h"


class AirDataProbesMessage : public BaseMessage
{
public:
	float totalAirTemperatureKelvin;

	AirDataProbesMessage();
	~AirDataProbesMessage();
};

