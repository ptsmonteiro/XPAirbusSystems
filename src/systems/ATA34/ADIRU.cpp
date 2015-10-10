#include "ADIRU.h"
#include "A320.h"
#include "core\core.h"
#include "systems\electric\electric.h"

ADIRU::ADIRU(int, StaticProbe* staticProbe1, StaticProbe* staticProbe2, AOAProbe* aoaProbe, PitotProbe* pitotProbe)
{
	this->number = number;
	this->StaticSrc1 = staticProbe1;
	this->StaticSrc2 = staticProbe2;
	this->AOASrc = aoaProbe;
	this->PitotSrc = pitotProbe;
}

void ADIRU::update()
{
	updateHealth();

	if (this->currentHealth == Failed) {
		return;
	}

	updateAirData();
	updateInertialData();
}

void ADIRU::updateAirData()
{
	// Baro height:
	if (this->StaticSrc1->currentHealth == Healthy)
	{
		this->currentAdiruData.airData.staticPressureHg = this->StaticSrc1->getCurrentStaticPressureInHg();

		this->currentAdiruData.airData.baroHeightFeet =
			Calculator::pressureAltitudeFt(this->currentAdiruData.airData.staticPressureHg, Aircraft->GlobalState->CaptQNHInHg);
	}
	else if (this->StaticSrc2->currentHealth == Healthy)
	{
		this->currentAdiruData.airData.staticPressureHg = this->StaticSrc2->getCurrentStaticPressureInHg();

		this->currentAdiruData.airData.baroHeightFeet =
			Calculator::pressureAltitudeFt(this->currentAdiruData.airData.staticPressureHg, Aircraft->GlobalState->FOQNHInHg);
	}

	// Speed (IAS)
	if (this->PitotSrc->currentHealth == Healthy) {
		this->currentAdiruData.airData.indicatedAirspeedKn = this->PitotSrc->getIndicatedAirspeedKn();
	}
	else {
		// TODO: airData.speedValid = false.
		this->currentAdiruData.airData.indicatedAirspeedKn = 0.0f;
	}


	// Speed Mach

	// Angle of Attack
	if (this->AOASrc->currentHealth == Healthy) {
		this->currentAdiruData.airData.angleOfAttack =
			SimInterface->getAOADegrees();
	}

	// Temperature (TAT, SAT?)

}

void ADIRU::updateInertialData() {
	this->currentAdiruData.inertialData.attitudeDegrees = SimInterface->getPitchAttitudeDegrees();
}

AdiruData ADIRU::getCurrentAdiruData()
{
	return this->currentAdiruData;
}


ADIRU::~ADIRU()
{
}