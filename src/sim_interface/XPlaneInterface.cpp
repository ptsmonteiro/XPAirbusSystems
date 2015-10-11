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

	// Sensores
	DataRefMap[BAROMETER_CURRENT_PRESSURE] = findDataRefByName("sim/weather/barometer_current_inhg");
	DataRefMap[SPEED_IAS] = findDataRefByName("sim/flightmodel/position/indicated_airspeed");
	DataRefMap[ONGROUND_ANY] = findDataRefByName("sim/flightmodel/failures/onground_all");

	// Attitude
	DataRefMap[PITCH_ATTITUDE] = findDataRefByName("sim/flightmodel/position/true_theta");
	DataRefMap[BANK_ANGLE] = findDataRefByName("sim/flightmodel/position/true_phi");

	// Yoke
	DataRefMap[JOYSTICK_AXIS_VALUES] = findDataRefByName("sim/joystick/joy_mapped_axis_value");
	DataRefMap[YOKE_ROLL_RATIO] = findDataRefByName("sim/joystick/yoke_roll_ratio");
	DataRefMap[YOKE_PITCH_RATIO] = findDataRefByName("sim/joystick/yoke_pitch_ratio");
	DataRefMap[OVERRIDE_JOYSTICK_ROLL] = findDataRefByName("sim/operation/override/override_joystick_roll");
	DataRefMap[OVERRIDE_JOYSTICK_PITCH] = findDataRefByName("sim/operation/override/override_joystick_pitch");


}

XPlaneInterface::~XPlaneInterface()
{
}

XPLMDataRef XPlaneInterface::findDataRefByName(char * datarefName)
{
	return XPLMFindDataRef(datarefName);
}

XPLMDataRef XPlaneInterface::findDataRefByCode(DATAREF_LIST value) {
	return DataRefMap[value];
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

float XPlaneInterface::getCurrentPressureInHg()
{
	return XPLMGetDataf(findDataRefByCode(BAROMETER_CURRENT_PRESSURE));
}

float XPlaneInterface::getIASKn() {
	return XPLMGetDataf(findDataRefByCode(SPEED_IAS));
}

bool XPlaneInterface::isMainGearCompressed() {
	int onGround = XPLMGetDatai(findDataRefByCode(ONGROUND_ANY));
	return onGround == 1;
}

float XPlaneInterface::getPitchAttitudeDegrees() {
	return XPLMGetDataf(findDataRefByCode(PITCH_ATTITUDE));
}

float XPlaneInterface::getBankAngleDegrees() {
	return XPLMGetDataf(findDataRefByCode(BANK_ANGLE));
}

float XPlaneInterface::getSideStickPitchRatio() {
	float values[100];
	XPLMGetDatavf(findDataRefByCode(JOYSTICK_AXIS_VALUES), values, 0, 4);
	return values[1];
}

float XPlaneInterface::getSideStickRollRatio() {
	float values[100];
	XPLMGetDatavf(findDataRefByCode(JOYSTICK_AXIS_VALUES), values, 0, 4);
	return values[2];
}

void XPlaneInterface::setSideStickRollRatio(float ratio)
{
	if (!isYokeRollOverriden) {
		XPLMSetDatai(findDataRefByCode(OVERRIDE_JOYSTICK_ROLL), true);
		isYokeRollOverriden = true;
	}
	XPLMSetDataf(findDataRefByCode(YOKE_ROLL_RATIO), ratio);
}

void XPlaneInterface::setSideStickPitchRatio(float ratio)
{
	if (!isYokePitchOverriden) {
		XPLMSetDatai(findDataRefByCode(OVERRIDE_JOYSTICK_PITCH), true);
		isYokePitchOverriden = true;
	}
	XPLMSetDataf(findDataRefByCode(YOKE_PITCH_RATIO), ratio);
}

