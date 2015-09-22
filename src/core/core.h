#pragma once

#include "XPLM\XPLMUtilities.h"

enum ComponentHealth {
	Healthy,
	Failed,
	Inop
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
	Emerg_Elec
};

typedef struct _stCoordinates {
	float latitude;
	float longitude;
} Coordinates;

typedef struct _stAccel {
	float x;
	float y;
	float z;
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

