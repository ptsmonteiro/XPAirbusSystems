#pragma once

// Landing Gear Control Interface Unit
class ATA32_LGCIU
{
public:
	ATA32_LGCIU(int);
	~ATA32_LGCIU();

	bool isGearCompressed();

protected:
	int number;


};

