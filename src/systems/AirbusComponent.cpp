#include "core\core.h"
#include "systems\electric\electric.h"
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
	if (this->currentHealth != Healthy) {
		return;
	}

	if (this->currentElectricSource == nullptr) {
		this->currentHealth = Failed;
		return;
	}

	if (this->currentElectricSource->isAvailable()) {
		this->currentHealth = Failed;
		return;
	}

}