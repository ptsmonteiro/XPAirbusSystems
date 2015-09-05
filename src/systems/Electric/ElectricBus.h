#pragma once
#include <vector>
#include "core\core.h"
#include "ElectricSink.h"
#include "electricSource.h"

class ElectricBus : public ElectricSource, public ElectricSink
{
public:
	ElectricBusType					busType;
	std::vector<ElectricSink *>		coupledSystems;

	ElectricBus(ElectricBusType busType);
	~ElectricBus();
};


