#pragma once
#include "systems/AirbusComponent.h"

class FAC : public AirbusComponent
{
private:
	const float RUDDER_TRAV_LIM_MAX_DEG =				25.0;
	const float RUDDER_TRAV_LIM_MIN_DEG =				3.4;
	const int	RUDDER_TRAV_LIM_EXP_TOP_BOUND_KN =		160;
	const int	RUDDER_TRAV_LIM_EXP_BTM_BOUND_KN =		380;
	const float RUDDER_TRAV_LIM_K =						1.0271;
	const float RUDDER_TRAV_LIM_L =						-275;

	double		elacYawOrder;
	double		calculateIas();

	float					computeRudderTravelLimit(int iasKn);

public:
	FAC(int componentNumber);
	~FAC();

	// Receives an yaw order fron the connected ELAC.
	void					setYawOrder(float yawOrderDegrees);

	ElectricBusType			connectElectrical();
	void					update();
	
};