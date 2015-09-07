#include "XPlaneInterface.h"

XPlaneInterface::XPlaneInterface()
{
	DataRefMap[AOA_ANGLE] = findDataRefByName("sim/flightmodel2/misc/AoA_angle_degrees");
	DataRefMap[TEMPERATURE_LE] = findDataRefByName("sim/weather/temperature_le_c");
	DataRefMap[TEMPERATURE_AMBIENT] = findDataRefByName("sim/weather/temperature_le_c");
	DataRefMap[RADIO_ALTITUDE_CAPT] = findDataRefByName("sim/cockpit2/gauges/indicators/radio_altimeter_height_ft_pilot");


	// OH Panel
	DataRefMap[PB_BAT_1] = findDataRefByName("sim/custom/xap/elec/bat1_o");
	DataRefMap[PB_BAT_2] = findDataRefByName("sim/custom/xap/elec/bat1_o");
}


XPlaneInterface::~XPlaneInterface()
{
}

XPLMDataRef XPlaneInterface::findDataRefByName(char * datarefName)
{
	return XPLMFindDataRef(datarefName);
}

float XPlaneInterface::getAOADegrees()
{
	float value = XPLMGetDataf(findDataRefByCode(AOA_ANGLE));
	return value;
}

float XPlaneInterface::getTotalAirTemperatureKelvin()
{
	float value = XPLMGetDataf(findDataRefByCode(TEMPERATURE_LE));

	// Convert to kelvin
	return value + CELSIUS_TO_KELVIN_FACTOR;
}

float XPlaneInterface::getStaticAirTemperatureKelvin()
{
	float value = XPLMGetDataf(findDataRefByCode(TEMPERATURE_AMBIENT));

	// Convert to kelvin
	return value + CELSIUS_TO_KELVIN_FACTOR;
}

int XPlaneInterface::getRadioAltitudeFt()
{
	// this should be improved
	float value = XPLMGetDataf(findDataRefByCode(RADIO_ALTITUDE_CAPT));
	return (int) value;
}

float XPlaneInterface::getElapsedTimeDecimalSeconds()
{
	return XPLMGetElapsedTime();
}

XPLMDataRef XPlaneInterface::findDataRefByCode(DATAREF_LIST value) {
	return DataRefMap[value];
}