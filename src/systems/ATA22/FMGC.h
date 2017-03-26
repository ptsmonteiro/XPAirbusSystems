#pragma once
#include "systems/AirbusComponent.h"
class FMGC : public AirbusComponent
{
public:
	FMGC(int);
	~FMGC();

	void update();
};

