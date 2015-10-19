#include "core/core.h"
#include "systems/electric/electric.h"
#include "AirbusComponent.h"


AirbusComponent::AirbusComponent()
{
	this->currentElectricSource = NULL;
	this->currentHealth = Healthy;
	this->simulator = new XPlaneInterface();
}

AirbusComponent::AirbusComponent(int number)
{
	this->componentNumber = number;
	AirbusComponent::AirbusComponent();
}

AirbusComponent::~AirbusComponent()
{
}

void AirbusComponent::update()
{
}

ElectricBusType AirbusComponent::connectElectrical() {
	return Empty;
}

void AirbusComponent::setSource(ElectricSource *source)
{
	this->currentElectricSource = source;
}

void AirbusComponent::disconnectElectrical()
{
	this->currentElectricSource = NULL;
}

void AirbusComponent::updateHealth()
{
	// TODO: Check a global equipment failure list.

	if (this->currentElectricSource == NULL || !this->currentElectricSource->isAvailable()) {
		this->currentHealth = Failed;
	}
	else {
		this->currentHealth = Healthy;
	}
}