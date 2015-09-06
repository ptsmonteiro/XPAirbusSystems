#pragma once

#include "XPLM\XPLMUtilities.h"

enum ComponentHealth : int {
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

class MessageLogger
{
public:
	MessageLogger();
	~MessageLogger();
	void LogMessage(const char* msg);
};
