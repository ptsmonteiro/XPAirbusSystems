#pragma once

#include "AirbusComponent.h"
#include "ADIRU.h"
#include "ATA32_LGCIU.h"
#include "ATA34_RadioAlt.h"

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
	void connect(ATA34_RadioAlt *);

	void update();

protected:

	ADIRU * myADIRU;
	ATA34_RadioAlt * radioAlt;
	ATA32_LGCIU * LGCIU;


	void getFMGC();

	float getAccelX();
	float getAccelY();
	float getAccelZ();

	float getSideStickX();
	float getSideStickY();

	float getPedalsPos();
};

