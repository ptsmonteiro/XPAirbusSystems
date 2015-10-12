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

	if (currentHealth == Failed) {
		return;
	}

	updateAirData();
	updateInertialData();

	currentAdiruData.lastUpdateTimeSeconds = simulator->getElapsedTimeDecimalSeconds();
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
	float now = simulator->getElapsedTimeDecimalSeconds();
	float timeDelta = now - currentAdiruData.lastUpdateTimeSeconds;

	float pitchAttitude = SimInterface->getPitchAttitudeDegrees();
	float bankAngle = SimInterface->getBankAngleDegrees();

	// rates
	currentAdiruData.inertialData.angularRate.pitch = 
		(pitchAttitude - currentAdiruData.inertialData.attitudeDegrees) / timeDelta;

	currentAdiruData.inertialData.angularRate.roll =
		(bankAngle - currentAdiruData.inertialData.bankAngleDegrees) / timeDelta;

	currentAdiruData.inertialData.attitudeDegrees = SimInterface->getPitchAttitudeDegrees();
	currentAdiruData.inertialData.bankAngleDegrees = SimInterface->getBankAngleDegrees();

	// forces
	currentAdiruData.inertialData.acceleration.gNormal = SimInterface->getGNormal();
}

AdiruData ADIRU::getCurrentAdiruData()
{
	return this->currentAdiruData;
}


ADIRU::~ADIRU()
{
}