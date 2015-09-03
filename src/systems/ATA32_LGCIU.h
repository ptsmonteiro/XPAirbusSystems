#pragma once

#include "AirbusComponent.h"

// Landing Gear Control Interface Unit
class ATA32_LGCIU : public AirbusComponent
{
public:
	ATA32_LGCIU(int);
	~ATA32_LGCIU();

	void update();

	bool isGearCompressed();

protected:
	int number;


};

