#include "SimulatorInterface.h"

const float CELSIUS_TO_KELVIN_FACTOR = 273.15;

float SimulatorInterface::getTotalAirTemperatureKelvin()
{
	// Load Dataref sim/weather/temperature_le_c
	float value = XPLMGetDataf(SimulatorInterface::findDataRefByName("sim/weather/temperature_le_c"));

	// Convert to kelvin
	return value + CELSIUS_TO_KELVIN_FACTOR;
}

XPLMDataRef SimulatorInterface::findDataRefByName(char * datarefName)
{
	return XPLMFindDataRef(datarefName);
}

SimulatorInterface::SimulatorInterface()
{
}


SimulatorInterface::~SimulatorInterface()
{
}
