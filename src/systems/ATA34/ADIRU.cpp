#include "ADIRU.h"
#include "systems\electric\electric.h"

ADIRU::ADIRU(int number)
{
	this->number = number;
}

void ADIRU::update()
{
	updateHealth();

	// 
}

ADIRU::~ADIRU()
{
}

void ADIRU::setAOAsource(AOAProbe *src)
{
	this->AOASrc = src;
}

void ADIRU::setTATsource(TATProbe *src)
{
	this->TATSrc = src;
}

void ADIRU::setPitotSource(PitotProbe *src)
{
	this->PitotSrc = src;
}

void ADIRU::setStaticSource(StaticProbe *src)
{
	this->StaticSrc = src;
}