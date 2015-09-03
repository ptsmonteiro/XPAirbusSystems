#include "ADIRU.h"

ADIRU::ADIRU()
{
}

ADIRU::ADIRU(int number)
{
	this->number = number;
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

void ADIRU::update() 
{
}