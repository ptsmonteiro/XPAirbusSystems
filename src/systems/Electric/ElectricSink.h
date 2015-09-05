#pragma once

class ElectricSink
{
public:
	ElectricSink();
	~ElectricSink();
	virtual float getUsedPowerAmps() = 0;
};
