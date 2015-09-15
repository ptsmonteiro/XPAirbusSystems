#include "ADIRU.h"
#include "A320.h"
#include "core\core.h"
#include "systems\electric\electric.h"

ADIRU::ADIRU(int, StaticProbe* staticProbe1, StaticProbe* staticProbe2)
{
	this->number = number;
	this->StaticSrc1 = staticProbe1;
	this->StaticSrc2 = staticProbe2;
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
			Calculator::pressureAltitudeFt(this->StaticSrc1->getCurrentStaticPressureInHg(), 29.92126);	//TODO: FIX
	}
	else if (this->StaticSrc2->currentHealth == Healthy)
	{
		this->currentAdiruData.airData.baroHeightFeet =
			Calculator::pressureAltitudeFt(this->StaticSrc2->getCurrentStaticPressureInHg(), 29.92126); //TODO: FIX
	}

}

AdiruData ADIRU::getCurrentAdiruData()
{
	return this->currentAdiruData;
}

ADIRU::~ADIRU()
{
}