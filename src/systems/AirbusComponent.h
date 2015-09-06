#pragma once
#include "core/core.h"
#include "sim_interface/SimulatorInterface.h"

class ElectricSource;

class AirbusComponent
{
protected:
	int number;

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

