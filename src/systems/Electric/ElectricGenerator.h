#pragma once
#include "ElectricGenerator.h"
#include "ElectricSource.h"
#include "systems\AirbusComponent.h"
#include "core\core.h"



class ElectricGenerator : public ElectricSource, public AirbusComponent
{
public:
	ElectricGeneratorType genType;
	bool					online;

	ElectricGenerator(ElectricGeneratorType genType, ComponentHealth currentHealth);
	~ElectricGenerator();
};

