#pragma once
#include <vector>
#include "ElectricGenerator.h"
#include "ElectricSource.h"
#include "ElectricBus.h"
#include "systems\AirbusComponent.h"
#include "core\core.h"



class ElectricGenerator : public ElectricSource, public AirbusComponent
{
public:
	ElectricGeneratorType		genType;
	bool						online;
	std::vector<ElectricSink *>	coupledBuses;

	ElectricGenerator(ElectricGeneratorType genType, ComponentHealth currentHealth);
	~ElectricGenerator();
};

