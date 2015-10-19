#include <math.h>
#include "A320.h"
#include "core/core.h"
#include "systems/electric/electric.h"
#include "systems/ATA34/ADIRU.h"
#include "ATA22_ELAC.h"

ATA22_ELAC::ATA22_ELAC(int number, RadioAlt *radioAlt, ATA32_LGCIU *lgciu, ADIRU *adiru)
{
	this->componentNumber = number;
	this->radioAlt = radioAlt;
	this->LGCIU = lgciu;
	this->myADIRU = adiru;

	initControllers();
}

ATA22_ELAC::~ATA22_ELAC()
{
	delete rollController;
	delete pitchController;
}

void ATA22_ELAC::initControllers()
{
	// Roll controller
	rollController = new PID(simulator, &rollRateDegreesSecond, &rollOrder, &rollRateDemandDegreesSecond, 
		0.1, 0.1, 0, DIRECT);
	rollController->SetOutputLimits(-1, 1);
	rollController->SetMode(AUTOMATIC);

	// Pitch controller
	pitchController = new PID(simulator, &pitchG, &pitchOrder, &pitchDemandG, 0.4, 0, 0, DIRECT);
	pitchController->SetOutputLimits(-1, 1);
	pitchController->SetMode(AUTOMATIC);
}

void ATA22_ELAC::update()
{
	this->currentRadioAltimeterHeightFt = this->radioAlt->getAltitudeFt();

	this->updateLateralControlMode();
	this->updatePitchControlMode();

	this->processPitch();
	this->processRoll();
	this->processYaw();
}

ATA22_ELAC::MODE ATA22_ELAC::getConsistentControlMode(MODE m)
{
	if (m == GROUND && radioAlt->getAltitudeFt() > 1000) {
		return FLIGHT;
	}
	return m;
}

void ATA22_ELAC::updatePitchControlMode()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();

	pitchControlMode = getConsistentControlMode(pitchControlMode);

	if (pitchControlMode == GROUND) {
		if (adiruData.inertialData.attitudeDegrees  > MIN_PITCH_ATT_DEG_GROUND_TO_FLIGHT_MODE) {
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
			LGCIU->isGearCompressed() &&
		adiruData.inertialData.attitudeDegrees < MAX_PITCH_ATT_DEG_FLARE_TO_GROUND_MODE) {
		pitchControlModeTransitionStartTime = simulator->getElapsedTimeDecimalSeconds();
		pitchControlMode = FLARE_TO_GROUND;
	}
	else if (pitchControlMode == FLARE_TO_GROUND &&
			simulator->getElapsedTimeDecimalSeconds() - pitchControlModeTransitionStartTime >= TRANSITION_TIME_SEC_PITCH_FLARE_TO_GROUND_MODE) {
		pitchControlMode = GROUND;
	}
}

void ATA22_ELAC::updateLateralControlMode()
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
	else if (lateralControlMode == FLIGHT && LGCIU->isGearCompressed()) {
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

void ATA22_ELAC::processPitch()
{
	switch (this->pitchControlMode)
	{
		case GROUND:
			processPitchDirect();
			break;
		case GROUND_TO_FLIGHT:
			break;
		case FLIGHT:
			processPitchLoadFactorDemand();
			break;
		case FLIGHT_TO_FLARE:
			break;
		case FLARE_TO_GROUND:
			break;
	};
}

void ATA22_ELAC::processPitchDirect()
{
	
}

void ATA22_ELAC::processPitchLoadFactorDemand()
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
	}

	// controller update
	pitchController->Compute();

	// output -> yoke_roll_ratio
	simulator->setSideStickPitchRatio(pitchOrder);
}

void ATA22_ELAC::processSideStickPitchDemand()
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

void ATA22_ELAC::protectionHighAOA() 
{

}

void ATA22_ELAC::protectionHighSpeed()
{

}

void ATA22_ELAC::processRoll()
{
	switch (this->pitchControlMode)
	{
		case GROUND:
			processRollDirect();
			break;
		case GROUND_TO_FLIGHT:
			break;
		case FLIGHT:
			processRollRateDemand();
			break;
		case FLIGHT_TO_GROUND:
			break;
	}
}

void ATA22_ELAC::processRollDirect()
{
	// This is normal simulator behaviour
}

void ATA22_ELAC::processRollRateDemand()
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

void ATA22_ELAC::processSideStickRollRateDemand()
{
	float sideStickRoll = simulator->getSideStickRollRatio();
	rollRateDemandDegreesSecond = sideStickRoll * MAX_ROLL_RATE_NORMAL_LAW_DEG_SEC;
}

void ATA22_ELAC::protectionBankAngle()
{
	AdiruData adiruData = myADIRU->getCurrentAdiruData();
	float bankAngle = adiruData.inertialData.bankAngleDegrees;

	int neutralLimit = BANK_ANGLE_NEUTRAL_STICK_NORMAL_LIMIT_DEG;
	int fullLimit = BAKN_ANGLE_FULL_STICK_NORMAL_LIMIT_DEG;

	if (isHighAOAProtectionActive || isHighSpeedProtectionActive) {
		neutralLimit = BANK_ANGLE_NEUTRAL_STICK_AOA_HS_PROT_ON_LIMIT_DEG;
		fullLimit = BAKN_ANGLE_FULL_STICK_AOA_HS_PROT_ON_LIMIT_DEG;
	}

	float rollRateCorrection = 0;

	if (abs((int) bankAngle) >= neutralLimit) {
		rollRateCorrection = (abs((int) bankAngle) - neutralLimit) / (fullLimit - neutralLimit) * MAX_ROLL_RATE_NORMAL_LAW_DEG_SEC;
		int signal = bankAngle > 0 ? 1 : -1;
		rollRateDemandDegreesSecond =  rollRateDemandDegreesSecond - (rollRateCorrection * signal);
	}
}

void ATA22_ELAC::processYaw()
{

}

ElectricBusType ATA22_ELAC::connectElectrical()
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