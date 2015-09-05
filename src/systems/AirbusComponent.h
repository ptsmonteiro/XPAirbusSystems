#pragma once
#include "core/core.h"
#include "sim_interface/SimulatorInterface.h"

class ElectricSource;

class AirbusComponent
{
protected:
	int number;

	SimulatorInterface *simInterface;

	void setSimInterface(SimulatorInterface *);
	

public:
	AirbusComponent();
	AirbusComponent(int);
	~AirbusComponent();

	ElectricSource* currentElectricSource;
	ComponentHealth currentHealth;

	virtual void update();
	virtual void connect(ElectricSource* source);

};

