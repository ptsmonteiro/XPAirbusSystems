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

	if (upstream == NULL) {
		return false;
	}
	else {
		return upstream->isAvailable();
	}
}

