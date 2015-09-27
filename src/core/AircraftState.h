#pragma once
class AircraftState
{
public:
	float CaptQNHInHg;
	float FOQNHInHg;



	void InitializeColdAndDark();


	AircraftState();
	~AircraftState();
};

