#pragma once
#include "messages/BaseMessage.h"
#include "sim_interface/SimulatorInterface.h"

enum ComponentHealth : int {
	Online,
	Failed,
	Offline
};

class AirbusComponent
{

public:
	AirbusComponent();
	~AirbusComponent();

	ComponentHealth getHealth();
	virtual BaseMessage* update();

protected:
	int number;
	ComponentHealth currentHealth;

	SimulatorInterface *simInterface;
	void setSimInterface(SimulatorInterface *);

};

