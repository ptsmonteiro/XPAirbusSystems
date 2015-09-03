#include "AirbusComponent.h"


AirbusComponent::AirbusComponent()
{
}

AirbusComponent::AirbusComponent(int number)
{
	this->number = number;
}


AirbusComponent::~AirbusComponent()
{
}

ComponentHealth AirbusComponent::getHealth()
{
	return this->currentHealth;
}

void AirbusComponent::update()
{
}

void AirbusComponent::setSimInterface(SimulatorInterface *)
{
}
