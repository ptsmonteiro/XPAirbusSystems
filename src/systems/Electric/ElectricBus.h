#pragma once
#include <vector>
#include "core\core.h"
#include "ElectricSink.h"
#include "electricSource.h"

class ElectricBus : public ElectricSource, public ElectricSink
{
	ElectricBusType				busType;
	ElectricSource				source;
	std::vector<ElectricSink>		coupledSystems;

public:
	ElectricBus();
	~ElectricBus();
};


