#include "ADIRU.h"
#include "A320.h"
#include "core\core.h"
#include "systems\electric\electric.h"

ADIRU::ADIRU(int, StaticProbe* staticProbe1, StaticProbe* staticProbe2, AOAProbe* aoaProbe)
{
	this->number = number;
	this->StaticSrc1 = staticProbe1;
	this->StaticSrc2 = staticProbe2;
	this->AOASrc = aoaProbe;
}

void ADIRU::update()
{
	updateHealth();

	if (this->currentHealth == Failed){
		return;
	}

	updateAirData();
}

void ADIRU::updateAirData()
{
	// Baro height:
	if (this->StaticSrc1->currentHealth == Healthy)
	{
		this->currentAdiruData.airData.baroHeightFeet =
			Calculator::pressureAltitudeFt(this->StaticSrc1->getCurrentStaticPressureInHg(), Aircraft->GlobalState->CaptQNHInHg);
	}
	else if (this->StaticSrc2->currentHealth == Healthy)
	{
		this->currentAdiruData.airData.baroHeightFeet =
			Calculator::pressureAltitudeFt(this->StaticSrc2->getCurrentStaticPressureInHg(), Aircraft->GlobalState->FOQNHInHg);
	}

	// Speed


	// Speed Mach

	// Angle of Attack
	if (this->AOASrc->currentHealth == Healthy) {
		this->currentAdiruData.airData.angleOfAttack =
			SimInterface->getAOADegrees();
	}

	// Temperature (TAT, SAT?)

}

AdiruData ADIRU::getCurrentAdiruData()
{
	return this->currentAdiruData;
}


ADIRU::~ADIRU()
{
}