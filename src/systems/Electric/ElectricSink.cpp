#include "Electric.h"


ElectricSink::ElectricSink()
{
}


ElectricSink::~ElectricSink()
{
}


ElectricSource* ElectricSink::getUpstreamSource() {
	return this->upstreamSource;
}

void ElectricSink::setUpstreamSource(ElectricSource* source)
{
	this->upstreamSource = source;
}