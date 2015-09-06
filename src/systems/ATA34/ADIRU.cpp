#include "ADIRU.h"
#include "systems\electric\electric.h"

ADIRU::ADIRU(int number)
{
	this->number = number;
}

void ADIRU::update()
{
	updateHealth();



	/*
	The ADR part(Air Data Reference) which supplies barometric altitude, airspeed, mach, angle of
		attack, temperature and overspeed warnings.
	
	
	The IR part(Inertial Reference) which supplies attitude, flight path vector, track, heading,
		accelerations, angular rates, ground speed and aircraft position.
		Note: Above 73 ° North and above 60 ° South, the ADIRU gives true heading instead of
		magnetic heading.
		-
		*/
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