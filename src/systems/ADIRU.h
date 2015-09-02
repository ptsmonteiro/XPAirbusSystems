#pragma once
#include "AirbusComponent.h"
#include "messages/AirDataProbesMessage.h"

/*
 * ATA34 :: ADIRU
 */
class ADIRU : public AirbusComponent
{
	float aoaValue;
	float tatValue;
	float pitotPressureCapt;
	float staticPressureCapt;
	float staticPressureFO;

public:
	ADIRU();
	~ADIRU();

	void inputMessage(AirDataProbesMessage *message);
	virtual BaseMessage* update();
};

