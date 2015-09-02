#pragma once
#include "messages/BaseMessage.h"

enum ComponentHealth : int {
	Online,
	Failed,
	Offline
};

class AirbusComponent
{

protected:
	ComponentHealth currentHealth;


public:
	AirbusComponent();
	~AirbusComponent();


	ComponentHealth getHealth();
	virtual BaseMessage* update();

protected:
	int number;
};

