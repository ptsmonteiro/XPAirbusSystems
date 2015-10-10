#pragma once

#include "AirbusComponent.h"
#include "systems/ATA34/ADIRU.h"
#include "ATA32_LGCIU.h"
#include "ATA34/RadioAlt.h"
#include "ATA22_FMGC.h"
#include "core/PID_v1.h"

class ATA22_ELAC : public AirbusComponent
{
private:
	int currentRadioAltimeterHeightFt = 0;

public:
	ATA22_ELAC(int, RadioAlt *, ATA32_LGCIU *, ADIRU *);
	~ATA22_ELAC();

	float getAileronPos();
	float getElevatorPos();
	float getRollOrder();
	float getYawRateOrder();

	void update();


//protected:

	// Ground -> Flight transition
	const int MIN_PITCH_ATT_DEG_GROUND_TO_FLIGHT_MODE = 8;
	const float TRANSITION_TIME_SEC_LATERAL_GROUND_TO_FLIGHT_MODE = 0.5;
	const int TRANSITION_TIME_SEC_PITCH_GROUND_TO_FLIGHT_MODE = 5;

	// Flight -> Ground transition
	const int MAX_RAD_ALT_FT_TO_FLARE_MODE = 50;
	const int TRANSITION_TIME_SEC_PITCH_FLIGHT_TO_FLARE_MODE = 1;
	const int TRANSITION_TIME_SEC_PITCH_FLARE_TO_GROUND_MODE = 5;
	const float MAX_PITCH_ATT_DEG_FLARE_TO_GROUND_MODE = 2.5;
	const float TRANSITION_TIME_SEC_LATERAL_FLIGHT_TO_GROUND_MODE = 0.5;

	float pitchControlModeTransitionStartTime = 0;
	float lateralControlModeTransitionStartTime = 0;

	enum MODE {
		GROUND,
		GROUND_TO_FLIGHT,
		FLIGHT,
		FLIGHT_TO_FLARE,
		FLARE,
		FLARE_TO_GROUND,
		FLIGHT_TO_GROUND
	};

	enum LAW {
		LAW_NORMAL,
		LAW_ALTERNATE_WITH_PROT,
		LAW_ALTERNATE_WITHOUT_PROT,
		LAW_DIRECT,
		LAW_MECHANICAL
	};

	MODE pitchControlMode = GROUND;
	MODE lateralControlMode = GROUND;

	float pitchControlModeTransitionProgress = 0;
	float lateralControlModeTransitionProgress = 0;

	LAW pitchLaw = LAW_NORMAL;
	LAW rollLaw = LAW_NORMAL;
	LAW yawLaw = LAW_NORMAL;

	// PID Controllers
	PID * pitchController;
	PID * rollController;

	// Flight control demands
	float pitchDemandG = 1.0f;
	float rollRateDemandDegreesSecond = 0.0f;

	ADIRU * myADIRU;
	RadioAlt * radioAlt;
	ATA32_LGCIU * LGCIU;
	ATA22_FMGC * FMGC;

	float accelX;
	float accelY;
	float accelZ;

	float sideStickX;
	float sideStickY;

	float pedalsPosition;

	// Surface deflection limits
	const int ELEVATOR_MAX_DEGREES = 30;
	const int ELEVATOR_MIN_DEGREES = -17;

	const float THS_MAX_DEGREES = 13.5;
	const int THS_MIN_DEGREES = -4;

	const int AILERON_MAX_DEGREES = 25;
	const int AILERON_MIN_DEGREES = -25;

	const int AILERON_DROOP_DEGREES = -5;

	const float SPEEDBRAKE_MAX_DEGREES_MANUAL[5] = {0, 20, 40, 40, 0};
	const float SPEEDBRAKE_MAX_DEGREES_AUTOPILOT[5] = {0, 12.5, 25, 25, 0};

	const int SPOILER_MAX_DEGREES = 35;

	// Modes
	void updatePitchControlMode();
	void updateLateralControlMode();
	MODE getConsistentControlMode(MODE);

	// Flight controls calculations
	void processPitch();
	void processRoll();
	void processYaw();

	void processPitchDirect();
	void processPitchLoadFactorDemand();

	void processRollDirect();
	void processRollRateDemand();

	// Protections
	void protectionHighAOA();
	void protectionHighSpeed();
	void protectionLoadFactor();
	void protectionPitchAttitude();
	void protectionBankAngle();

};

