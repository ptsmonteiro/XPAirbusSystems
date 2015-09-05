#include "ElectricNetwork.h"

ElectricNetwork::ElectricNetwork()
{
	mode = Normal_Flight;
}

ElectricNetwork::~ElectricNetwork()
{
	// Initialize generators.
	generatorData[Bat1] = new ElectricGenerator(Bat1, Healthy);
}

void ElectricNetwork::reconfigure()
{
	this->mode = Normal_Flight;

	switch (this->mode) {
		case Normal_Flight:
			prepareNormalFlightConfig();
			break;
		case Normal_Ground:
			prepareNormalGroundConfig();
			break;
	}
}

void ElectricNetwork::prepareNormalFlightConfig()
{

}

void ElectricNetwork::prepareNormalGroundConfig()
{

}
