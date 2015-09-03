#pragma once
#include "XPLM/XPLMDataAccess.h"

class SimulatorInterface
{
public:
	SimulatorInterface();
	~SimulatorInterface();

	const float CELSIUS_TO_KELVIN_FACTOR = 273.15;

	virtual float getTotalAirTemperatureKelvin() = 0;
	virtual float getAOADegrees() = 0;
	virtual int getRadioAltitudeFt() = 0;

};
