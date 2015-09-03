#pragma once
#include "systems/AirbusComponent.h"
#include "systems/ATA34\AOAProbe.h"
#include "systems/ATA34\PitotProbe.h"
#include "systems/ATA34\StaticProbe.h"
#include "systems/ATA34\TATProbe.h"

/*
 * ATA34 :: ADIRU
 */
class ADIRU : public AirbusComponent
{
protected:
	float aoaValue;
	float tatValue;
	float pitotPressureCapt;
	float staticPressureCapt;
	float staticPressureFO;

	AOAProbe * AOASrc;
	TATProbe * TATSrc;
	PitotProbe * PitotSrc;
	StaticProbe * StaticSrc;

public:
	ADIRU();
	~ADIRU();

	void setAOAsource(AOAProbe *);
	void setTATsource(TATProbe *);
	void setPitotSource(PitotProbe *);
	void setStaticSource(StaticProbe *);

	void update();
};

