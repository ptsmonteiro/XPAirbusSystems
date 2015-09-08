#include "ATA22_ELAC.h"
#include "systems/ATA34/ADIRU.h"

ATA22_ELAC::ATA22_ELAC(int number)
{
	this->number = number;
}


ATA22_ELAC::~ATA22_ELAC()
{
}

void ATA22_ELAC::connect(ADIRU * ADIRU)
{
	this->myADIRU = ADIRU;
}

void ATA22_ELAC::connect(ATA32_LGCIU *lgciu)
{
	this->LGCIU = lgciu;
}

void ATA22_ELAC::connect(RadioAlt *ra)
{
	this->radioAlt = ra;
}

void ATA22_ELAC::update()
{
	this->currentRadioAltimeterHeightFt = this->radioAlt->getAltitudeFt();

	this->processPitch();
	this->processRoll();
	this->processYaw();
}

void ATA22_ELAC::updatePitchControlMode()
{
	if (pitchControlMode == GROUND) {
		if (myADIRU->getPitchAttitudeDegrees() > MIN_PITCH_ATT_DEG_GROUND_TO_FLIGHT_MODE) {
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
			myADIRU->getPitchAttitudeDegrees() < MAX_PITCH_ATT_DEG_FLARE_TO_GROUND_MODE) {
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
	if (lateralControlMode == GROUND && myADIRU->getPitchAttitudeDegrees() > MIN_PITCH_ATT_DEG_GROUND_TO_FLIGHT_MODE) {
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
}

void ATA22_ELAC::processPitch()
{
	switch (this->pitchControlMode)
	{
		case GROUND:
			break;
		case GROUND_TO_FLIGHT:
			break;
		case FLIGHT:
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

void ATA22_ELAC::processRoll()
{
	switch (this->pitchControlMode)
	{
		case GROUND:
			break;
		case GROUND_TO_FLIGHT:
			break;
		case FLIGHT:
			break;
		case FLIGHT_TO_GROUND:
			break;
	}
}

void ATA22_ELAC::processYaw()
{

}