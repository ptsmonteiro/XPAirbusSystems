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

void AirbusComponent::update()
{
}

void AirbusComponent::setSimInterface(SimulatorInterface *)
{
}

void AirbusComponent::connect(ElectricSource* source)
{
	this->currentElectricSource = source;
}