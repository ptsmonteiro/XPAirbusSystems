#pragma once
#include "core/core.h"
#include "sim_interface/XPlaneInterface.h"

enum ProbeLocation {
	Captain,
	FO,
	Standby
};

class ElectricSource;

class AirbusComponent
{
protected:
	int componentNumber;
	SimulatorInterface* simulator;
	
	void				updateHealth();
	virtual void		setSource(ElectricSource *source);

public:
	AirbusComponent();
	AirbusComponent(int);
	~AirbusComponent();

	ElectricSource* currentElectricSource;
	ComponentHealth currentHealth;

	virtual void				update();
	virtual ElectricBusType		connectElectrical();
	virtual void				disconnectElectrical();
};