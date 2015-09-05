#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "systems\AirbusComponent.h"
#include "core\core.h"
#include "electricSource.h"
#include "electricSink.h"
#include "electricGenerator.h"

class ElectricNetwork
{
	ElectricNetworkMode								mode;
	std::map<ElectricGeneratorType, ElectricGenerator*> generatorData;

public:
	void reconfigure();
	void prepareNormalFlightConfig();
	void prepareNormalGroundConfig();
	ElectricNetwork();
	~ElectricNetwork();
};
