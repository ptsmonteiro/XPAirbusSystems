#include "ADIRU.h"

ADIRU::ADIRU()
{
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

	// Dummy values....
	double machNumber = 0.333;
	double ratioSpecHeats = 1.444f;

	double factor = 1 + ((ratioSpecHeats - 1) / 2) * machNumber * machNumber;
	double staticAirTemp = this->tatValue / factor;

}