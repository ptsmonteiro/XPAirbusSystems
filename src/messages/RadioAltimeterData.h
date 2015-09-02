#pragma once
#include "BaseMessage.h"

class RadioAltimeterData : public BaseMessage
{
public:
	int altitude;
	RadioAltimeterData();
	~RadioAltimeterData();
};