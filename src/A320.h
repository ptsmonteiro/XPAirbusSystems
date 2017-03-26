#pragma once

#include "systems/AirbusComponent.h"
#include "systems/ATA22/FAC.h"
#include "systems/ATA27/ELAC.h"
#include "systems/ATA27/FCDC.h"
#include "systems/ATA31/DMC.h"
#include "systems/ATA31/DU.h"
#include "systems/ATA31/EWD.h"
#include "systems/ATA31/FWC.h"
#include "systems/ATA31/ND.h"
#include "systems/ATA31/PFD.h"
#include "systems/ATA31/SD.h"
#include "systems/ATA31/SDAC.h"
#include "systems/ATA32/LGCIU.h"
#include "systems/ATA34/ADIRU.h"
#include "systems/ATA34/RadioAlt.h"
#include "systems/ATA22/FMGC.h"
#include "systems/ATA34/AOAProbe.h"
#include "systems/ATA34/TATProbe.h"
#include "systems/ATA34/PitotProbe.h"
#include "systems/ATA34/StaticProbe.h"
#include "systems/Electric/Electric.h"
#include "core/AircraftState.h"

class A320
{

public:
	A320();
	~A320();

	float lastUpdateElapsedMe;
	float lastUpdateElapsedSimulator;
	float updateCounter;

	AircraftState * GlobalState;
	ElectricNetwork * electricNetwork;

	// ATA 22 - Auto Flight
	ELAC * elac1;
	ELAC * elac2;

	FAC * fac1;
	FAC * fac2;

	// ATA 27 - Flight Controls
	FCDC * fcdc1;
	FCDC * fcdc2;

	FMGC * fmgc1;
	FMGC * fmgc2;

	// ATA 32 - Landing Gear
	LGCIU * lgciu1;
	LGCIU * lgciu2;

	// ATA 31 - Indicating / Recording Systems
	DU * du1;
	DU * du2;
	DU * du3;
	DU * du4;
	DU * du5;
	DU * du6;

	FWC * fwc1;
	FWC * fwc2;

	// ATA 34 - Navigation Sensors

	TATProbe * tatProbeCapt;
	TATProbe * tatProbeFO;

	AOAProbe * aoaProbeCapt;
	AOAProbe * aoaProbeFO;
	AOAProbe * aoaProbeStandby;

	StaticProbe * staticProbeCapt1;
	StaticProbe * staticProbeCapt2;
	StaticProbe * staticProbeFO1;
	StaticProbe * staticProbeFO2;
	StaticProbe * staticProbeStandby1;
	StaticProbe * staticProbeStandby2;

	PitotProbe * pitotProbeCapt;
	PitotProbe * pitotProbeFO;
	PitotProbe * pitotProbeStandby;

	RadioAlt * ra1;
	RadioAlt * ra2;

	ADIRU * adiru1;
	ADIRU * adiru2;
	ADIRU * adiru3;

	void update(float elapsedMe, float elapsedSim, int counter);
	void init();

protected:
	void resetColdAndDark();
//	void propagateSignals();
//	void updateSystems();
	void reconfigureSystems();
	void updateProbes();
	void updateComputers();
	void updateDisplays();
};

// Global variables
extern A320* Aircraft;
extern SimulatorInterface* SimInterface;
extern MessageLogger* Logger;