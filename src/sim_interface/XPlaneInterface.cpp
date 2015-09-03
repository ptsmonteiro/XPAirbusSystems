#include "XPlaneInterface.h"

XPlaneInterface::XPlaneInterface()
{
}


XPlaneInterface::~XPlaneInterface()
{
}

XPLMDataRef findDataRefByName(char * datarefName)
{
	return XPLMFindDataRef(datarefName);
}


float XPlaneInterface::getAOADegrees()
{
	float value = XPLMGetDataf(findDataRefByName("sim/flightmodel2/misc/AoA_angle_degrees"));
	return value;
}

float XPlaneInterface::getTotalAirTemperatureKelvin()
{
	// Load Dataref sim/weather/temperature_le_c
	float value = XPLMGetDataf(findDataRefByName("sim/weather/temperature_le_c"));

	// Convert to kelvin
	return value + CELSIUS_TO_KELVIN_FACTOR;
}

int XPlaneInterface::getRadioAltitudeFt()
{
	// this should be improved
	float value = XPLMGetDataf(findDataRefByName("sim/cockpit2/gauges/indicators/radio_altimeter_height_ft_pilot"));
	return (int) value;
}

XPLMDataRef XPlaneInterface::findDataRefByName(char * datarefName)
{
	return XPLMDataRef();
}
