#pragma once
#include "XPLM/XPLMDataAccess.h"

class SimulatorInterface
{
public:
	static float getTotalAirTemperatureKelvin();



	static XPLMDataRef SimulatorInterface::findDataRefByName(char * datarefName);

	SimulatorInterface();
	~SimulatorInterface();

};

