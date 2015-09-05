#pragma once

#include "systems\AirbusComponent.h"
#include "systems\ATA22_ELAC.h"
#include "systems\ATA31_DMC.h"
#include "systems\ATA31_DU.h"
#include "systems\ATA31_EWD.h"
#include "systems\ATA31_FWC.h"
#include "systems\ATA31_ND.h"
#include "systems\ATA31_PFD.h"
#include "systems\ATA31_SD.h"
#include "systems\ATA31_SDAC.h"
#include "systems\ATA32_LGCIU.h"
#include "systems\ATA34\ADIRU.h"
#include "systems\ATA34\RadioAlt.h"
#include "systems\ATA22_FMGC.h"
#include "systems\ATA34\AOAProbe.h"
#include "systems\ATA34\TATProbe.h"
#include "systems\ATA34\PitotProbe.h"
#include "systems\ATA34\StaticProbe.h"
#include "systems\Electric\ElectricNetwork.h"

class A320
{
public:
	A320();
	~A320();
	ElectricNetwork * electricNetwork;

	void update(float);

protected:

	// ATA 22 - Auto Flight
	ATA22_ELAC * elac1;
	ATA22_ELAC * elac2;

	ATA22_FMGC * fmgc1;
	ATA22_FMGC * fmgc2;

	// ATA 32 - Landing Gear
	ATA32_LGCIU * lgciu1;
	ATA32_LGCIU * lgciu2;

	// ATA 31 - Indicating / Recording Systems
	ATA31_DU * du1;
	ATA31_DU * du2;
	ATA31_DU * du3;
	ATA31_DU * du4;
	ATA31_DU * du5;
	ATA31_DU * du6;

	ATA31_FWC * fwc1;
	ATA31_FWC * fwc2;

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

	void updateSystemsHealth();
	void propagateSignals();

	void updateSystems();
	void reconfigureSystems();
	void updateProbes();
	void updateComputers();
	void updateDisplays();

};
