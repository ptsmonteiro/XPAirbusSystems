#include "ADIRU.h"



ADIRU::ADIRU()
{
}

ADIRU::~ADIRU()
{
}

void ADIRU::inputMessage(AirDataProbesMessage *message)
{
	this->tatValue = message->totalAirTemperatureKelvin;
}

BaseMessage* ADIRU::update() {

	// Dummy values....
	double machNumber = 0.333;
	double ratioSpecHeats = 1.444f;

	double factor = 1 + ((ratioSpecHeats - 1) / 2) * machNumber * machNumber;
	double staticAirTemp = this->tatValue / factor;



	// Return my calculated values.
	return nullptr;
}