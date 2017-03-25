#pragma once
#include "systems\AirbusComponent.h"

class FCDC : public AirbusComponent
{
public:
	FCDC(int);
	~FCDC();

	void update();

	float pitchTrimPosition = 0;

};

