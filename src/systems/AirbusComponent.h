#pragma once
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
	AirbusComponent(int);
	~AirbusComponent();

	ComponentHealth getHealth();
	virtual void update();

protected:
	int number;
	ComponentHealth currentHealth;

	SimulatorInterface *simInterface;
	void setSimInterface(SimulatorInterface *);

};

