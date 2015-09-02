#include "AirbusComponent.h"



AirbusComponent::AirbusComponent()
{
}


AirbusComponent::~AirbusComponent()
{
}

ComponentHealth AirbusComponent::getHealth()
{
	return this->currentHealth;
}

BaseMessage* AirbusComponent:: update()
{
	return nullptr;
}
