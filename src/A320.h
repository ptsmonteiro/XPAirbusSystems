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
#include "systems\ATA34_ADIRU.h"
#include "systems\ATA34_RadioAlt.h"
#include "systems\ATA34_PitotProbe.h"
#include "systems\ATA34_StaticProbe.h"
#include "systems\ATA34_AOAProbe.h"
#include "systems\ATA34_PitotProbe.h"
#include "systems\ATA34_TATProbe.h"

class A320
{
public:
	A320();
	~A320();

	void update();
	void updateSystemsHealth();
	void propagateSignals();

protected:

	// ATA 22 - Auto Flight
	ATA22_ELAC * elac1;
	ATA22_ELAC * elac2;

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

	// ATA 34 - Navigation
	ATA34_StaticProbe * capt_static_probe1;
	ATA34_StaticProbe * capt_static_probe2;
	ATA34_StaticProbe * fo_static_probe1;
	ATA34_StaticProbe * fo_static_probe2;
	ATA34_StaticProbe * standby_static_probe1;
	ATA34_StaticProbe * standby_static_probe2;

	ATA34_AOAProbe * capt_aoa_probe;
	ATA34_AOAProbe * fo_aoa_probe;
	ATA34_AOAProbe * standby_aoa_probe;

	ATA34_TATProbe * capt_tat_probe;
	ATA34_TATProbe * fo_tat_probe;

	ATA34_RadioAlt * ra1;
	ATA34_RadioAlt * ra2;





};
