#pragma once
#include <iostream>
#include <map>
#include "SimulatorInterface.h"

enum DATAREF_LIST {
	AOA_ANGLE,
	TEMPERATURE_LE,
	TEMPERATURE_AMBIENT,
	RADIO_ALTITUDE_CAPT,
	PB_BAT_1,
	PB_BAT_2
};

class XPlaneInterface :
	public SimulatorInterface
{
	std::map<DATAREF_LIST, XPLMDataRef> DataRefMap;

public:
	XPlaneInterface();
	~XPlaneInterface();

	float getAOADegrees();
	float getStaticAirTemperatureKelvin();
	float getTotalAirTemperatureKelvin();
	int getRadioAltitudeFt();
	

protected:
	XPLMDataRef findDataRefByName(char * datarefName);
	XPLMDataRef findDataRefByCode(DATAREF_LIST value);
};


