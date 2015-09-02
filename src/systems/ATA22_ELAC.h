#pragma once

#include "AirbusComponent.h"
#include "ATA34_ADIRU.h"
#include "ATA32_LGCIU.h"
#include "messages\RadioAltimeterData.h"

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

	void connect(ATA34_ADIRU *);
	void connect(ATA32_LGCIU *);

	void inputMessage(RadioAltimeterData *);

protected:

	ATA34_ADIRU * m_ADIRU;
	ATA34_ADIRU *getADIRU();

	void getFMGC();

	float getAccelX();
	float getAccelY();
	float getAccelZ();

	void getLGCIU();

	void getRadioAlt();

	float getSideStickX();
	float getSideStickY();

	float getPedalsPos();
};

