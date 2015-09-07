#pragma once
#include "core/core.h"
#include "sim_interface/XPlaneInterface.h"

class ElectricSource;

class AirbusComponent
{
protected:
	int number;
	SimulatorInterface* simulator;

	void updateHealth();

public:
	AirbusComponent();
	AirbusComponent(int);
	~AirbusComponent();

	ElectricSource* currentElectricSource;
	ComponentHealth currentHealth;

	virtual void update();
	virtual void connectElectrical(ElectricSource* source);
	virtual void disconnectElectrical();
};

