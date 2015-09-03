#pragma once
#include "SimulatorInterface.h"

class XPlaneInterface :
	public SimulatorInterface
{
public:
	XPlaneInterface();
	~XPlaneInterface();

	float getAOADegrees();
	float getTotalAirTemperatureKelvin();
	int getRadioAltitudeFt();

protected:
	static XPLMDataRef findDataRefByName(char * datarefName);



};

