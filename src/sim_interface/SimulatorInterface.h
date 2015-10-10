#pragma once

class SimulatorInterface
{
public:
	SimulatorInterface();
	~SimulatorInterface();

	const float CELSIUS_TO_KELVIN_FACTOR = 273.15;

	virtual float getTotalAirTemperatureKelvin() = 0;
	virtual float getStaticAirTemperatureKelvin() = 0;
	virtual float getAOADegrees() = 0;
	virtual int getRadioAltitudeFt() = 0;
	virtual float getElapsedTimeDecimalSeconds() = 0;
	virtual float getCurrentPressureInHg() = 0;

	/* Speeds */
	virtual float getIASKn() = 0;

	virtual bool isMainGearCompressed() = 0;

	/* Attitude */
	virtual float getPitchAttitudeDegrees() = 0;
};

