#pragma once
#include "systems/AirbusComponent.h"

class FAC : public AirbusComponent
{
private:
	const float RUDDER_TRAV_LIM_MAX_DEG =				25.0;
	const float RUDDER_TRAV_LIM_MIN_DEG =				3.4;
	const int	RUDDER_TRAV_LIM_EXP_TOP_BOUND_KN =		160;
	const int	RUDDER_TRAV_LIM_EXP_BTM_BOUND_KN =		380;

	const float RUDDER_TRAV_LIM_K					= 1.0271;
	const float RUDDER_TRAV_LIM_L =						-275;

public:
	FAC(int componentNumber);
	~FAC();

	ElectricBusType			connectElectrical();
	void					update();
	float					computeRudderTravelLimit(int iasKn);
};