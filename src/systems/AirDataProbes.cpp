#include "AirDataProbes.h"
#include "messages/AirDataProbesMessage.h"


AirDataProbes::AirDataProbes()
{
}


AirDataProbes::~AirDataProbes()
{
}

BaseMessage* AirDataProbes::update()
{
	if (this->currentHealth == Online) {
		AirDataProbesMessage* msg = new AirDataProbesMessage();

		msg->totalAirTemperatureKelvin = SimulatorInterface::getTotalAirTemperatureKelvin();
		return msg;
	}
	else {
		return nullptr;
	}
}