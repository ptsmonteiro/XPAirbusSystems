#include <math.h>
#include "A320.h"
#include "core/core.h"
#include "FAC.h"
#include "systems/electric/electric.h"

/*
	Flight Augmentation Computer

		Functions:
				// Yaw Damp
				// Rudder Trim
				// Rudder Limit
				// Flight Envelope
				// Speed computation
					� VSW (stall warning)
					� VLS
					� VFE and VFE for the next configuration
					� VLE
					� VMO/MMO
					� Green Dot Speed
					� S speed
					� F speed
					� Speed trend arrow for PFD
				// Low energy warning
				// Windshear detection

		Inputs:
			ADIRS
			L/G
			SLATS/FLAPS

		Outputs:
			Actuators: rudder trim, yaw damper, rudder travel limiter
			EFIS.
			CFDIU (centralized fault display interface unit)


*/



FAC::FAC(int componentNumber)
{
	this->componentNumber = componentNumber;
}

ElectricBusType FAC::connectElectrical()
{
	switch (this->componentNumber) {
	case 1:

		if (Aircraft->electricNetwork->busData[AcEssBus]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[AcEssBus]);
			return AcEssBus;
		} else if (Aircraft->electricNetwork->busData[DcEssShed]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[DcEssShed]);
			return HotBus1;
		} else {
			return Empty;
		}

		break;

	case 2:
		if (Aircraft->electricNetwork->busData[AcBus2]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[AcBus2]);
			return AcBus2;
		} else if (Aircraft->electricNetwork->busData[DcBus2]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[DcBus2]);
			return DcBus2;
		} else {
			return Empty;
		}
	}

	return Empty;
}

void FAC::setYawOrder(float yawOrderDegrees) {
	this->elacYawOrder = yawOrderDegrees;
}

void FAC::update()
{
	bool apEngaged;

	float targetIas = calculateIas();

	// check if this FAC is active or not.
	if (true) {

		// compute RTLU
		float rtLimitDeg = this->computeRudderTravelLimit(targetIas);

		// Limit the elac yaw order with rtLimitDeg.

		// Set limit.
	}
}

float FAC::computeRudderTravelLimit(int iasKn) {
	if (iasKn >= RUDDER_TRAV_LIM_EXP_BTM_BOUND_KN) {
		return RUDDER_TRAV_LIM_MIN_DEG;
	} else if (iasKn <= RUDDER_TRAV_LIM_EXP_TOP_BOUND_KN) {
		return RUDDER_TRAV_LIM_MAX_DEG;
	} else {
		// www.desmos.com/calculator
		// y\ =3.4\ +\ \ 1.0271\ ^{-\left(x-275\right)}

		// Simple function for exponential decay of RTL between 160 and 380Kn IAS, from 25 do 3.4 degrees.
		return RUDDER_TRAV_LIM_MIN_DEG + pow(RUDDER_TRAV_LIM_K, -(iasKn - RUDDER_TRAV_LIM_L));
	}
}

// https://criticaluncertainties.com/2009/06/20/airbus-voting-logic-and-qf72/
double FAC::calculateIas()
{
	float ias1 = Aircraft->adiru1->getCurrentAdiruData().airData.indicatedAirspeedKn;
	float ias2 = Aircraft->adiru2->getCurrentAdiruData().airData.indicatedAirspeedKn;
	float ias3 = Aircraft->adiru3->getCurrentAdiruData().airData.indicatedAirspeedKn;

	// For now, return the median value.
	if (ias1 > ias2) {
		if (ias2 > ias3) {
			return ias2;
		} else if (ias1 > ias3) {
			return ias3;
		} else {
			return ias1;
		}
	} else {
		if (ias1 > ias3) {
			return ias1;
		} else if (ias2 > ias3) {
			return ias3;
		} else {
			return ias2;
		}
	}
}

float computeYawDampingValue() {
	return 0.0f;
}

FAC::~FAC()
{
}