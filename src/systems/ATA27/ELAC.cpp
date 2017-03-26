#define _USE_MATH_DEFINES
#include <math.h>
#include "A320.h"
#include "core/core.h"
#include "systems/electric/electric.h"
//#include "systems/ATA34/ADIRU.h"
// #include "systems/ATA32/LGCIU.h"
#include "ELAC.h"

ELAC::ELAC(int number, RadioAlt *radioAlt, LGCIU *lgciu, ADIRU *adiru)
{
	this->componentNumber = number;
	this->radioAlt = radioAlt;
	this->myLGCIU = lgciu;
	this->myADIRU = adiru;

	initControllers();
}

ELAC::~ELAC()
{
	delete rollController;
	delete pitchController;
}

void ELAC::initControllers()
{
	// Roll controller
	rollController = new PID(simulator, &rollRateDegreesSecond, &rollOrder, &rollRateDemandDegreesSecond,
		0.3, 1.6, 0, DIRECT);
	rollController->SetOutputLimits(-1, 1);
	rollController->SetMode(AUTOMATIC);

	// Pitch controller
	pitchController = new PID(simulator, &pitchG, &pitchOrder, &pitchDemandG, .5, 0.6, 0.02, DIRECT);
	pitchController->SetOutputLimits(-1, 1);
	pitchController->SetMode(AUTOMATIC);
}

void ELAC::update()
{
	this->currentRadioAltimeterHeightFt = this->radioAlt->getAltitudeFt();

	this->updateLateralControlMode();
	this->updatePitchControlMode();

	this->processPitch();
	this->processRoll();
	this->processYaw();
}

ELAC::MODE ELAC::getConsistentControlMode(MODE m)
{
	if (m == GROUND && radioAlt->getAltitudeFt() > 1000) {
		return FLIGHT;
	}
	return m;
}

void ELAC::updatePitchControlMode()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	pitchControlMode = getConsistentControlMode(pitchControlMode);

	if (pitchControlMode == GROUND) {
		if (adiruData.inertialData.attitudeDegrees > MIN_PITCH_ATT_DEG_GROUND_TO_FLIGHT_MODE) {
			pitchControlModeTransitionStartTime = simulator->getElapsedTimeDecimalSeconds();
			pitchControlMode = GROUND_TO_FLIGHT;
		}
	}
	else if (pitchControlMode == GROUND_TO_FLIGHT &&
		(simulator->getElapsedTimeDecimalSeconds() - pitchControlModeTransitionStartTime)
		>= TRANSITION_TIME_SEC_PITCH_GROUND_TO_FLIGHT_MODE)
	{
		pitchControlMode = FLIGHT;
	}
	else if (pitchControlMode == FLIGHT && radioAlt->getAltitudeFt() <= MAX_RAD_ALT_FT_TO_FLARE_MODE)
	{
		pitchControlModeTransitionStartTime = simulator->getElapsedTimeDecimalSeconds();
		pitchControlMode = FLIGHT_TO_FLARE;
	}
	else if (pitchControlMode == FLIGHT_TO_FLARE &&
		simulator->getElapsedTimeDecimalSeconds() - pitchControlModeTransitionStartTime >= TRANSITION_TIME_SEC_PITCH_FLIGHT_TO_FLARE_MODE) {
		pitchControlMode = FLARE;
	}
	else if (pitchControlMode == FLARE &&
		myLGCIU->isGearCompressed() &&
		adiruData.inertialData.attitudeDegrees < MAX_PITCH_ATT_DEG_FLARE_TO_GROUND_MODE) {
		pitchControlModeTransitionStartTime = simulator->getElapsedTimeDecimalSeconds();
		pitchControlMode = FLARE_TO_GROUND;
	}
	else if (pitchControlMode == FLARE_TO_GROUND &&
		simulator->getElapsedTimeDecimalSeconds() - pitchControlModeTransitionStartTime >= TRANSITION_TIME_SEC_PITCH_FLARE_TO_GROUND_MODE) {
		pitchControlMode = GROUND;
	}
}

void ELAC::updateLateralControlMode()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	if (lateralControlMode == GROUND && adiruData.inertialData.attitudeDegrees > MIN_PITCH_ATT_DEG_GROUND_TO_FLIGHT_MODE) {
		lateralControlModeTransitionStartTime = simulator->getElapsedTimeDecimalSeconds();
		lateralControlMode = GROUND_TO_FLIGHT;
	}
	else if (lateralControlMode == GROUND_TO_FLIGHT &&
		simulator->getElapsedTimeDecimalSeconds() - lateralControlModeTransitionStartTime >= TRANSITION_TIME_SEC_LATERAL_GROUND_TO_FLIGHT_MODE)
	{
		lateralControlMode = FLIGHT;
	}
	else if (lateralControlMode == FLIGHT && myLGCIU->isGearCompressed()) {
		lateralControlModeTransitionStartTime = simulator->getElapsedTimeDecimalSeconds();
		lateralControlMode = FLIGHT_TO_GROUND;
	}
	else if (lateralControlMode == FLIGHT_TO_GROUND &&
		simulator->getElapsedTimeDecimalSeconds() - lateralControlModeTransitionStartTime >= TRANSITION_TIME_SEC_LATERAL_FLIGHT_TO_GROUND_MODE) {
		lateralControlMode = GROUND;
	}
	else {
		lateralControlMode = getConsistentControlMode(lateralControlMode);
	}
}

void ELAC::processPitch()
{
	switch (this->pitchControlMode)
	{
	case GROUND:
		processPitchDirect();
		break;
	case GROUND_TO_FLIGHT:
		// TODO do this right
		processPitchDirect();
		break;
	case FLIGHT:
		processPitchTrim();
		processPitchLoadFactorDemand();
		break;
	case FLIGHT_TO_FLARE:
		// TODO do this right
		processPitchDirect();
		break;
	case FLARE_TO_GROUND:
		// TODO do this right
		processPitchDirect();
		break;
	};
}

void ELAC::processPitchDirect()
{
	simulator->unsetSideStickPitchRatio();
}

void ELAC::processPitchLoadFactorDemand()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	// input = measure roll rate
	pitchG = adiruData.inertialData.acceleration.gNormal;

	// setpoint = get joystick values -> to roll rate demand
	processSideStickPitchDemand();

	// protections
	if (this->pitchLaw == LAW_NORMAL) {
		protectionHighAOA();
		protectionHighSpeed();
		protectionPitchAttitude();
	}

	// controller update
	pitchController->Compute();

	// output -> yoke_roll_ratio
	simulator->setSideStickPitchRatio(pitchOrder);
}

void ELAC::processSideStickPitchDemand()
{
	float sideStickPitch = simulator->getSideStickPitchRatio();
	if (sideStickPitch < 0) {
		pitchDemandG = 1 + (sideStickPitch * (1 - MIN_G_NORMAL_LAW));
	}
	else {
		pitchDemandG = 1 + (sideStickPitch * (MAX_G_NORMAL_LAW - 1));
	}

	// Correct G demand for bank
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	pitchDemandG *= 1 / cos(adiruData.inertialData.bankAngleDegrees / 180 * M_PI);
	if (pitchDemandG > MAX_G_NORMAL_LAW) {
		pitchDemandG = MAX_G_NORMAL_LAW;
	}
	else if (pitchDemandG < MIN_G_NORMAL_LAW) {
		pitchDemandG = MIN_G_NORMAL_LAW;
	}
}

void ELAC::processPitchTrim()
{
	if (this->pitchLaw != LAW_NORMAL) {
		this->simulator->releasePitchTrim();
		return;
	}

	if (this->pitchOrder > 0) {
		this->simulator->holdPitchTrimUp();
	}
	else {
		this->simulator->holdPitchTrimDown();
	}
}

void ELAC::protectionPitchAttitude()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	float pitchAttitude = adiruData.inertialData.attitudeDegrees;

	float minG = MIN_G_NORMAL_LAW;
	float maxG = MAX_G_NORMAL_LAW;

	float minPitch = MIN_PITCH_ATT_DEG;
	float maxPitch = MAX_PITCH_ATT_DEG_CONF_OTHER;

	bool upperLimit = true;

	if (pitchAttitude >= MAX_PITCH_ATT_DEG_CONF_OTHER)
	{
		upperLimit = true;
		minG = MIN_G_NORMAL_LAW;
		maxG = 1;
		minPitch = MAX_PITCH_ATT_DEG_CONF_OTHER;
		maxPitch = MAX_PITCH_ATT_DEG_CONF_OTHER + PITCH_ATT_SOFT_LIMIT_MARGIN;
	}
	else if (pitchAttitude >= MAX_PITCH_ATT_DEG_CONF_OTHER - PITCH_ATT_SOFT_LIMIT_MARGIN)
	{
		upperLimit = true;
		minG = 1;
		maxG = MAX_G_NORMAL_LAW;
		maxPitch = MAX_PITCH_ATT_DEG_CONF_OTHER;
		minPitch = MAX_PITCH_ATT_DEG_CONF_OTHER - PITCH_ATT_SOFT_LIMIT_MARGIN;
	}
	else if (pitchAttitude <= MIN_PITCH_ATT_DEG)
	{
		upperLimit = false;
		minG = 1;
		maxG = MAX_G_NORMAL_LAW;
		maxPitch = MIN_PITCH_ATT_DEG;
		minPitch = MIN_PITCH_ATT_DEG - PITCH_ATT_SOFT_LIMIT_MARGIN;
	}
	else if (pitchAttitude <= MIN_PITCH_ATT_DEG + PITCH_ATT_SOFT_LIMIT_MARGIN)
	{
		upperLimit = false;
		minG = MIN_PITCH_ATT_DEG;
		maxG = 1;
		maxPitch = MIN_PITCH_ATT_DEG + PITCH_ATT_SOFT_LIMIT_MARGIN;
		minPitch = MIN_PITCH_ATT_DEG;
	}
	else
	{
		return;
	}

	if (upperLimit)
	{
		float maxlimitG = (1 - (pitchAttitude - minPitch) / (maxPitch - minPitch)) * (maxG - minG) + minG;
		if (pitchDemandG > maxlimitG)
		{
			pitchDemandG = maxlimitG;
		}
	}
	else
	{
		float minlimitG = (1 - (pitchAttitude - minPitch) / (maxPitch - minPitch)) * (maxG - minG) + minG;
		if (pitchDemandG < minlimitG)
		{
			pitchDemandG = minlimitG;
		}
	}


	// enforce pitch envelope
	if (pitchDemandG < MIN_G_NORMAL_LAW)
	{
		pitchDemandG = MIN_G_NORMAL_LAW;
	}
	else if (pitchDemandG > MAX_G_NORMAL_LAW)
	{
		pitchDemandG = MAX_G_NORMAL_LAW;
	}

}

void ELAC::protectionHighAOA()
{

}

void ELAC::protectionHighSpeed()
{

}

void ELAC::processRoll()
{
	switch (this->pitchControlMode)
	{
	case GROUND:
		processRollDirect();
		break;
	case GROUND_TO_FLIGHT:
		// TODO do this right
		processRollDirect();
		break;
	case FLIGHT:
		processRollRateDemand();
		break;
	case FLIGHT_TO_GROUND:
		// TODO do this right
		processRollDirect();
		break;
	}
}

void ELAC::processRollDirect()
{
	simulator->unsetSideStickRollRatio();
}

void ELAC::processRollRateDemand()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	// input = measure roll rate
	rollRateDegreesSecond = adiruData.inertialData.angularRate.roll;

	// setpoint = get joystick values -> to roll rate demand
	processSideStickRollRateDemand();

	// protections
	if (this->rollLaw == LAW_NORMAL) {
		protectionBankAngle();
	}

	// controller update
	rollController->Compute();

	// output -> yoke_roll_ratio
	simulator->setSideStickRollRatio(rollOrder);
}

void ELAC::processSideStickRollRateDemand()
{
	float sideStickRoll = simulator->getSideStickRollRatio();
	rollRateDemandDegreesSecond = sideStickRoll * MAX_ROLL_RATE_NORMAL_LAW_DEG_SEC;
}

void ELAC::protectionBankAngle()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();
	float bankAngle = adiruData.inertialData.bankAngleDegrees;

	float neutralLimit = BANK_ANGLE_NEUTRAL_STICK_NORMAL_LIMIT_DEG;
	float fullLimit = BAKN_ANGLE_FULL_STICK_NORMAL_LIMIT_DEG;

	if (isHighAOAProtectionActive || isHighSpeedProtectionActive) {
		neutralLimit = BANK_ANGLE_NEUTRAL_STICK_AOA_HS_PROT_ON_LIMIT_DEG;
		fullLimit = BAKN_ANGLE_FULL_STICK_AOA_HS_PROT_ON_LIMIT_DEG;
	}

	float rollRateCorrection = 0;

	float absBankAngle = abs((int)bankAngle);

	if (absBankAngle >= neutralLimit) {
		rollRateCorrection = (absBankAngle - neutralLimit) * MAX_ROLL_RATE_NORMAL_LAW_DEG_SEC /
			(fullLimit - neutralLimit);
		float signal = bankAngle > 0 ? 1 : -1;
		rollRateDemandDegreesSecond = rollRateDemandDegreesSecond - (rollRateCorrection * signal);
	}
}

void ELAC::processYaw()
{
	processRudderDemand();

	// send this value to the facs.
	Aircraft->fac1->setYawOrder(yawDemandDegrees);
	Aircraft->fac2->setYawOrder(yawDemandDegrees);
}

void ELAC::processRudderDemand() {
	yawDemandDegrees = simulator->getRudderRatio() * RUDDER_MAX_DEFLECTION_DEG;
}

ElectricBusType ELAC::connectElectrical()
{
	switch (this->componentNumber) {
	case 1:

		if (Aircraft->electricNetwork->busData[DcEssBus]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[DcEssBus]);
			return DcEssBus;
		}
		else if (Aircraft->electricNetwork->busData[HotBus1]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[HotBus1]);
			return HotBus1;
		}
		else {
			return Empty;
		}

		break;

	case 2:
		if (Aircraft->electricNetwork->busData[DcBus2]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[DcBus2]);
			return DcBus2;
		}
		else if (Aircraft->electricNetwork->busData[HotBus2]->isAvailable()) {
			setSource(Aircraft->electricNetwork->busData[HotBus2]);
			return HotBus2;
		}
		else {
			return Empty;
		}
	}

	return Empty;
}