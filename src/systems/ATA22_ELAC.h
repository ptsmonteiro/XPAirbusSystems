#pragma once

#include "AirbusComponent.h"
#include "systems/ATA34/ADIRU.h"
#include "ATA32_LGCIU.h"
#include "ATA34/RadioAlt.h"
#include "ATA22_FMGC.h"

class ATA22_ELAC : public AirbusComponent
{
private:
	int currentRadioAltimeterHeightFt;

public:
	ATA22_ELAC(int);
	~ATA22_ELAC();

	float getAileronPos();
	float getElevatorPos();
	float getRollOrder();
	float getYawRateOrder();

	void connect(ADIRU *);
	void connect(ATA32_LGCIU *);
	void connect(RadioAlt *);

	void update();


protected:

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

	unsigned long pitchControlModeGroundToFlightStartTime = 0;
	unsigned long lateralControlModeGroundToFlightStartTime = 0;

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
		NORMAL,
		ALTERNATE_WITH_PROT,
		ALTERNATE_WITHOUT_PROT,
		DIRECT,
		MECHANICAL
	};

	MODE pitchControlMode = GROUND;
	MODE lateralControlMode = GROUND;

	float pitchControlModeTransitionProgress = 0;
	float lateralControlModeTransitionProgress = 0;

	LAW pitchLaw = NORMAL;
	LAW rollLaw = NORMAL;
	LAW yawLaw = NORMAL;

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

	// Modes
	void updatePitchControlMode();
	void updateLateralControlMode();

	// Flight controls calculations
	void processPitch();
	void processRoll();
	void processYaw();

	// Protections
	void protectionHighAOA();
	void protectionHighSpeed();
	void protectionLoadFactor();
	void protectionPitchAttituce();
	void protectionBankAngle();

};

