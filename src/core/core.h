#pragma once

#include "XPLM/XPLMUtilities.h"

//TODO: INOP status might be redundant.
enum ComponentHealth {
	Healthy,		// System is healthy
	Failed,			// System has failled but is recoverable (ie: Power loss)
	Inop			// System is inoperable and not recoverable.
};

enum ElectricGeneratorType {
	Bat1,
	Bat2,
	EmergGen,
	Gen1,
	Gen2,
	ExtPwr,
	ApuGen
};

enum ElectricBusType {
	Empty,			// Virtual Bus to represent an unconnected component.	
	HotBus1,
	HotBus2,
	DcBatBus,
	DcBus1,
	DcBus2,
	DcEssBus,
	DcEssShed,
	AcEssBus,
	AcEssShed,
	AcBus1,
	AcBus2
};

enum ElectricNetworkMode {
	ColdAndDark,
	Normal_Flight,
	Normal_Ground,
	Emerg_Elec,
	DEBUG_CONFIG_1			/* Batteries only. */
};

typedef struct _stCoordinates {
	float latitude;
	float longitude;
} Coordinates;

typedef struct _stAccel {
	float gNormal;
	float gAxil;
	float gSide;
} AccelerometerData;

typedef struct _stGyroData {
	float yaw;
	float roll;
	float pitch;
} GyroData;

class MessageLogger
{
public:
	MessageLogger();
	~MessageLogger();
	void LogMessage(const char* msg);
};

class Calculator
{
public:
	static float pressureAltitudeFt(float pressureInHg, float qnhInHg);
};

