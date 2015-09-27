#include "core\core.h"
#include "systems\electric\electric.h"
#include "AirbusComponent.h"


AirbusComponent::AirbusComponent()
{
	this->currentElectricSource = nullptr;
	this->currentHealth = Healthy;
	this->simulator = new XPlaneInterface();
}

AirbusComponent::AirbusComponent(int number) : AirbusComponent()
{
	this->number = number;
	AirbusComponent::AirbusComponent();
}

AirbusComponent::~AirbusComponent()
{
}

void AirbusComponent::update()
{
}

void AirbusComponent::connectElectrical(ElectricSource* source)
{
	this->currentElectricSource = source;
}

void AirbusComponent::disconnectElectrical()
{
	this->currentElectricSource = nullptr;
}

void AirbusComponent::updateHealth()
{
	// TODO: Check a global equipment failure list.

	if (this->currentElectricSource == nullptr || !this->currentElectricSource->isAvailable()) {
		this->currentHealth = Failed;
	}
	else {
		this->currentHealth = Healthy;
	}
}