#pragma once
#include <vector>
#include "core\core.h"
#include "ElectricSink.h"
#include "electricSource.h"

class ElectricBus : public ElectricSource, public ElectricSink
{
	ElectricBusType					busType;
	std::vector<ElectricSink>		coupledSystems;

public:
	ElectricBus(ElectricBusType busType);
	~ElectricBus();
};


