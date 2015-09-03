#pragma once

#include "AirbusComponent.h"
#include "ADIRU.h"
#include "ATA32_LGCIU.h"
#include "systems\ATA34\RadioAlt.h"

class ATA22_ELAC : public AirbusComponent
{
private:
	int currentRadioAltimeterHeightFt;

public:
	ATA22_ELAC(int);
	~ATA22_ELAC();

	float getAileronPos();
	float getElevatorPos();
	float getRollOrder();
	float getYawRateOrder();

	void connect(ADIRU *);
	void connect(ATA32_LGCIU *);
	void connect(RadioAlt *);

	void update();

protected:

	ADIRU * myADIRU;
	RadioAlt * radioAlt;
	ATA32_LGCIU * LGCIU;


	void getFMGC();

	float getAccelX();
	float getAccelY();
	float getAccelZ();

	float getSideStickX();
	float getSideStickY();

	float getPedalsPos();
};

