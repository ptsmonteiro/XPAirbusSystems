#pragma once
#include <iostream>
#include <map>
#include "SimulatorInterface.h"
#include "XPLM/XPLMDataAccess.h"
#include "XPLM/XPLMProcessing.h"

enum DATAREF_LIST {
	AOA_ANGLE,
	TEMPERATURE_LE,
	TEMPERATURE_AMBIENT,
	RADIO_ALTITUDE_CAPT,
	PB_BAT_1,
	PB_BAT_2,

	BAROMETER_CURRENT_PRESSURE,

	SPEED_IAS,

	G_NORMAL,

	ONGROUND_ANY,

	PITCH_ATTITUDE,
	BANK_ANGLE,

	JOYSTICK_AXIS_VALUES,

	YOKE_PITCH_RATIO,
	YOKE_ROLL_RATIO,
	YOKE_HEADING_RATIO,

	OVERRIDE_JOYSTICK_ROLL,
	OVERRIDE_JOYSTICK_PITCH,
	OVERRIDE_JOYSTICK_HEADING
};

class XPlaneInterface :
	public SimulatorInterface
{
	std::map<DATAREF_LIST, XPLMDataRef> DataRefMap;

private:
	float joystickAxisValueBuffer[100];

public:
	XPlaneInterface();
	~XPlaneInterface();

	float getAOADegrees();
	float getStaticAirTemperatureKelvin();
	float getTotalAirTemperatureKelvin();
	int getRadioAltitudeFt();
	float getElapsedTimeDecimalSeconds();
	float getCurrentPressureInHg();

	/* Speeds */
	float getIASKn();

	/* Gear */
	bool isMainGearCompressed();

	/* Attitude */
	float getPitchAttitudeDegrees();
	float getBankAngleDegrees();

	/* Yoke */
	float getSideStickRollRatio();
	float getSideStickPitchRatio();

	void setSideStickRollRatio(float);
	void setSideStickPitchRatio(float);
    
    void unsetSideStickRollRatio();
    void unsetSideStickPitchRatio();

	/* Rudder Pedals*/
	float getRudderRatio();

	void setRudderRatio(float);

	void unsetRudderRatio();

	/* Forces */
	float getGNormal();
	

protected:
	bool isYokeRollOverriden = false;
	bool isYokePitchOverriden = false;
	bool isRudderOverriden = false;

	XPLMDataRef findDataRefByName(char * datarefName);
	XPLMDataRef findDataRefByCode(DATAREF_LIST value);
};


