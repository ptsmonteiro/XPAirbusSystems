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

	ComponentHealth currentHealth;
	virtual void update();

protected:
	int number;
	

	SimulatorInterface *simInterface;
	void setSimInterface(SimulatorInterface *);

};

