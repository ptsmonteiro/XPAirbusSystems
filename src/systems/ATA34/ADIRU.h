#pragma once
#include "systems/AirbusComponent.h"
#include "systems/ATA34\AOAProbe.h"
#include "systems/ATA34\PitotProbe.h"
#include "systems/ATA34\StaticProbe.h"
#include "systems/ATA34\TATProbe.h"

/*
 * ATA34 :: ADIRU
 */
class ADIRU : public AirbusComponent
{
protected:
	float aoaValue;
	float tatValue;
	float pitotPressureCapt;
	float staticPressureCapt;
	float staticPressureFO;

	AOAProbe * AOASrc;
	TATProbe * TATSrc;
	PitotProbe * PitotSrc;
	StaticProbe * StaticSrc;

public:
	ADIRU(int);
	~ADIRU();

	void setAOAsource(AOAProbe *);
	void setTATsource(TATProbe *);
	void setPitotSource(PitotProbe *);
	void setStaticSource(StaticProbe *);

	// Air Data Reference
	int getBarometricAltitudeFeet();
	float getIndicatedAirspeedKnots();
	float getMach();
	float getAngleOfAtackDegrees();
	float getTotalAirTempDegreesCelsius();
	float getSaturatedAirTempDegreesCelsius();
	bool overspeed();

	// Inertial Reference
	float getPitchAttitudeDegrees();
	float getBankAngleDegrees();
	float getFlightPathVectorDegreesX();
	float getFlightPathVectorDegreesY();
	int getTrackDegrees();
	int getHeadingDegrees();
	int getAccelerationNewtonX();
	int getAccelerationNewtonY();
	int getAccelerationNewtonZ();
	float getPitchRateDegreesSecond();
	float getRollRateDegreesSecond();
	float getYawRateDegreesSecond();
	float getGroundSpeedKnots();
	float getPositionLatitudeDegrees();
	float getPositionLongitudeDegrees();

	void update();
};

