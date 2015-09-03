#pragma once
#include "systems\AirbusComponent.h"
class StaticProbe :
	public AirbusComponent
{
public:
	StaticProbe();
	~StaticProbe();

	void update();
};

