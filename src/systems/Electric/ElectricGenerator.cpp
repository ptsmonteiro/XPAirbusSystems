#include "core\core.h"
#include "ElectricGenerator.h"
#include "ElectricSource.h"
#include "systems\AirbusComponent.h"


ElectricGenerator::ElectricGenerator(ElectricGeneratorType genType, ComponentHealth currentHealth) : AirbusComponent()
{
	this->genType = genType;
	this->currentHealth = Healthy;
}


ElectricGenerator::~ElectricGenerator()
{
}
