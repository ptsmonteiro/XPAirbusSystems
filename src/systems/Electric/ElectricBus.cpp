#include "electric.h"

ElectricBus::ElectricBus(ElectricBusType busType)
{
	this->busType = busType;
}

ElectricBus::~ElectricBus()
{
}

bool ElectricBus::isAvailable()
{
	ElectricSource *upstream = this->getUpstreamSource();

	if (upstream == nullptr) {
		return false;
	}
	else {
		return upstream->isAvailable();
	}
}

