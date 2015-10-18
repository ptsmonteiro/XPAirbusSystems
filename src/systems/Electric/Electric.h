#pragma once
#include <vector>
#include <map>
#include "core/core.h"
#include "systems/airbuscomponent.h"

class ElectricSource;


class ElectricSink
{
private:
	ElectricSource *upstreamSource;
public:

	// Returns the upstream source that provides power to this one, if any.
	virtual ElectricSource* getUpstreamSource();

	// Sets the upstream source to provide power to this one.
	virtual void setUpstreamSource(ElectricSource* source);

	ElectricSink();
	~ElectricSink();
};

/*
Represents an electrical source.
*/
class ElectricSource
{
public:

	ElectricSource();
	~ElectricSource();

	std::vector<ElectricSink *>			coupledSinks;

	// Current source power usage, in Amps
	virtual float getSourceLoad();

	// Indicates if this source is online and delivering power.
	virtual bool isAvailable() = 0;
};

class ElectricBus : public ElectricSource, public ElectricSink
{
public:
	ElectricBusType					busType;
	std::vector<ElectricSink *>		coupledSystems;

	ElectricBus(ElectricBusType busType);
	~ElectricBus();

	virtual bool isAvailable();
};

class ElectricGenerator : public ElectricSource, public AirbusComponent
{
public:
	ElectricGeneratorType		genType;
	bool						online;

	ElectricGenerator(ElectricGeneratorType genType, ComponentHealth currentHealth);
	~ElectricGenerator();

	virtual bool isAvailable();
};

class ElectricNetwork
{
	ElectricNetworkMode									mode;
	std::map<ElectricGeneratorType, ElectricGenerator*> generatorData;
	std::map<ElectricBusType, ElectricBus *>			busData;

public:
	void reconfigure(ElectricNetworkMode mode);
	void reconfigureEquipment();
	void resetNetwork();
	void prepareNormalFlightConfig();
	void prepareNormalGroundConfig();
	void prepareDebugConfigOne();
    void prepareEmerElecConfig();
	void couple(ElectricSource* source, ElectricSink* sink);

	ElectricNetwork();
};
