#include "electric.h"

ElectricGenerator::ElectricGenerator(ElectricGeneratorType genType, ComponentHealth currentHealth) : AirbusComponent()
{
	this->genType = genType;
	this->currentHealth = Healthy;
}

ElectricGenerator::~ElectricGenerator()
{
}

bool ElectricGenerator::isAvailable()
{
	return online && currentHealth == Healthy;
}