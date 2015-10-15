#pragma once
#include "systems/AirbusComponent.h"
#include "systems/ATA34/AOAProbe.h"
#include "systems/ATA34/PitotProbe.h"
#include "systems/ATA34/StaticProbe.h"
#include "systems/ATA34/TATProbe.h"
#include "core/AdiruData.h"

/*
 * ATA34 :: ADIRU
 */
class ADIRU : public AirbusComponent
{
private:
	AdiruData currentAdiruData;
	void updateAirData();
	void updateInertialData();
	

protected:
	AOAProbe * AOASrc;
	TATProbe * TATSrc;
	PitotProbe * PitotSrc;
	StaticProbe * StaticSrc1;
	StaticProbe * StaticSrc2;

public:
	ADIRU(int, StaticProbe* staticProbe1, StaticProbe* staticProbe2, AOAProbe* aoaProbe, PitotProbe* pitotProbe);
	~ADIRU();

	void update();

	AdiruData getCurrentAdiruData();
};

