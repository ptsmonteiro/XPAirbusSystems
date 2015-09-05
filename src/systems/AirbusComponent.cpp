#include "core\core.h"
#include "AirbusComponent.h"


AirbusComponent::AirbusComponent()
{
	this->currentElectricSource = nullptr;
	this->currentHealth = Healthy;
}

AirbusComponent::AirbusComponent(int number) : AirbusComponent()
{
	this->number = number;
}

AirbusComponent::~AirbusComponent()
{
}

void AirbusComponent::update()
{
}

void AirbusComponent::connect(ElectricSource* source)
{
	this->currentElectricSource = source;
}

void AirbusComponent::disconnectElectrical()
{
	this->currentElectricSource = nullptr;
}