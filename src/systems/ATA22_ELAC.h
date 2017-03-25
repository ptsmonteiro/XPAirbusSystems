#pragma once

#include "AirbusComponent.h"
#include "systems/ATA34/ADIRU.h"
#include "ATA32_LGCIU.h"
#include "ATA34/RadioAlt.h"
#include "ATA22_FMGC.h"
#include "ATA22/FAC.h"
#include "core/PID_v1.h"

class ATA22_ELAC : public AirbusComponent
{
private:
	int currentRadioAltimeterHeightFt = 0;

public:
	ATA22_ELAC(int, RadioAlt *, ATA32_LGCIU *, ADIRU *);
	~ATA22_ELAC();

	ElectricBusType connectElectrical();

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
	double pitchDemandG = 1.0f;
	double rollRateDemandDegreesSecond = 0.0f;
	double yawDemandDegrees = 0.0f;

	// Flight control readings
	double pitchG = 1.0f;
	double rollRateDegreesSecond = 0.0f;

	// Flight control controller orders
	double pitchOrder = 0.0f;
	double rollOrder = 0.0f;

	ADIRU * myADIRU;
	RadioAlt * radioAlt;
	ATA32_LGCIU * LGCIU;
	ATA22_FMGC * FMGC;
	FAC * fac1;
	FAC * fac2;

	float accelX;
	float accelY;
	float accelZ;

	float sideStickRoll = 0;
	float sideStickPitch = 0;

	float pedalPosition;

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

	// Other limits
	const int MAX_ROLL_RATE_NORMAL_LAW_DEG_SEC = 15;
	const int BANK_ANGLE_NEUTRAL_STICK_NORMAL_LIMIT_DEG = 33;
	const int BAKN_ANGLE_FULL_STICK_NORMAL_LIMIT_DEG = 67;
	const int RUDDER_MAX_DEFLECTION_DEG = 25;

	const int BANK_ANGLE_NEUTRAL_STICK_AOA_HS_PROT_ON_LIMIT_DEG = 0;
	const int BAKN_ANGLE_FULL_STICK_AOA_HS_PROT_ON_LIMIT_DEG = 45;
    
    const float MAX_PITCH_ATT_DEG_CONF_OTHER = 30.0;
    const float MAX_PITCH_ATT_DEG_CONF_FULL = 25.0;
    const float MIN_PITCH_ATT_DEG = -15.0;
    const float PITCH_ATT_SOFT_LIMIT_MARGIN = 10;

	const float MIN_G_NORMAL_LAW = -1.0;
	const float MAX_G_NORMAL_LAW = 2.5;

	// Modes
	void updatePitchControlMode();
	void updateLateralControlMode();
	MODE getConsistentControlMode(MODE);

	// Flight controls calculations
	void initControllers();

	void processPitch();
	void processRoll();
	void processYaw();

	void processPitchDirect();
	void processPitchLoadFactorDemand();
	void processPitchTrim();

	void processRollDirect();
	void processRollRateDemand();

	void processSideStickRollRateDemand();
	void processSideStickPitchDemand();

	void processRudderDemand();


	// Protections
	void protectionHighAOA();
	void protectionHighSpeed();
	void protectionLoadFactor();
	void protectionPitchAttitude();
	void protectionBankAngle();

	bool isHighAOAProtectionActive = false;
	bool isHighSpeedProtectionActive = false;

};

