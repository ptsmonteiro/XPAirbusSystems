#pragma once
#include "core/core.h"

typedef struct  _adiruInertialData {
	float attitudeDegrees = 0;
	float bankAngleDegrees = 0;

	int groundSpeedKnots;
	float flightPathAngleDegrees;
	float trackDegrees;
	float headingDegrees;

	// Acceleration
	AccelerometerData acceleration;

	// Inertial Position
	Coordinates position;

	// Angular Rate
	GyroData angularRate;

} AdiruInertialData;

typedef struct _adiruAirData {
	float staticPressureHg;
	int baroHeightFeet;
	int indicatedAirspeedKn;
	float speedMach;
	float angleOfAttack;
	float temperatureKelvin;
} AdiruAirData;

typedef struct _AdiruData {
	AdiruAirData		airData;
	AdiruInertialData	inertialData;
	float				lastUpdateTimeSeconds = 0;
} AdiruData;




/*
flight path vector, 
angular rates,
*/

/*

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


*/