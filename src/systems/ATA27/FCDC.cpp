#include "FCDC.h"
#include "A320.h"

FCDC::FCDC(int number)
{
	this->componentNumber = number;
}

FCDC::~FCDC()
{
}

void FCDC::update()
{
	this->pitchTrimPosition = SimInterface->getPitchTrimPosition();
}
