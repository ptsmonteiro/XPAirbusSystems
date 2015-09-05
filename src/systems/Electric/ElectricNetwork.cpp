#include "electric.h"
#include "A320.h"

ElectricNetwork::ElectricNetwork()
{
	mode = Normal_Flight;
}

ElectricNetwork::~ElectricNetwork()
{
	// Initialize generators.
	generatorData[Bat1] = new ElectricGenerator(Bat1, Healthy);
	generatorData[Bat2] = new ElectricGenerator(Bat2, Healthy);
	generatorData[EmergGen] = new ElectricGenerator(EmergGen, Healthy);
	generatorData[Gen1] = new ElectricGenerator(Gen1, Healthy);
	generatorData[Gen2] = new ElectricGenerator(Gen2, Healthy);
	generatorData[ExtPwr] = new ElectricGenerator(ExtPwr, Healthy);
	generatorData[ApuGen] = new ElectricGenerator(ApuGen, Healthy);

	// Initializes Buses.
	busData[HotBus1] = new ElectricBus(HotBus1);
	busData[HotBus2] = new ElectricBus(HotBus2);
	busData[DcBatBus] = new ElectricBus(DcBatBus);
	busData[DcBus1] = new ElectricBus(DcBus1);
	busData[DcBus2] = new ElectricBus(DcBus2);
	busData[DcEssBus] = new ElectricBus(DcEssBus);
	busData[DcEssShed] = new ElectricBus(DcEssShed);
	busData[AcEssBus] = new ElectricBus(AcEssBus);
	busData[AcEssShed] = new ElectricBus(AcEssShed);
	busData[AcBus1] = new ElectricBus(AcBus1);
	busData[AcBus2] = new ElectricBus(AcBus2);
}

void ElectricNetwork::reconfigure(ElectricNetworkMode mode)
{
	resetNetwork();

	this->mode = mode;

	switch (this->mode) {
	case Normal_Flight:
		prepareNormalFlightConfig();
		break;
	case Normal_Ground:
		prepareNormalGroundConfig();
		break;
	}
}

void ElectricNetwork::prepareNormalFlightConfig()
{
	//TODO: Read from user interface
	//TODO : Check IDG DISCONNECT P/B.

	bool gen1LineCont = true;
	bool gen2LineCont = true;

	// P/B now deprecated.
	// TODO: Auto-switching of AC ESS BUS on AC1 bus fault.
	bool ac_ess_feed_pb_pushed = true;

	// GEN 1.
	if (generatorData[Gen1]->currentHealth == Healthy && gen1LineCont)
	{
		couple(generatorData[Gen1], busData[AcBus1]);
		couple(busData[AcBus1], busData[DcBus1]);

		if (!ac_ess_feed_pb_pushed) {
			couple(busData[AcBus1], busData[AcEssBus]);
		}
	}

	// GEN 2.
	if (generatorData[Gen2]->currentHealth == Healthy && gen2LineCont)
	{

		couple(generatorData[Gen2], busData[AcBus2]);
		couple(busData[AcBus2], busData[DcBus2]);

		if (!ac_ess_feed_pb_pushed) {
			couple(busData[AcBus2], busData[AcEssBus]);
		}
	}

	// AC ESS SHED.
	couple(busData[AcEssBus], busData[AcEssShed]);

	//TODO: DC Buses.


	reconfigureEquipment();
}

void ElectricNetwork::prepareNormalGroundConfig()
{
	// Read from user interface
	bool ext_pwr_cont = true;
	bool bus_tie_cont = true;

	ElectricGenerator * rootGen = generatorData[ExtPwr];

	if (ext_pwr_cont && bus_tie_cont) {
		couple(rootGen, busData[AcBus1]);
		couple(rootGen, busData[AcBus2]);
	}
}

void ElectricNetwork::couple(ElectricSource* source, ElectricSink* sink)
{
	source->coupledSinks.push_back(sink);
	sink->setUpstreamSource(source);
}

void ElectricNetwork::resetNetwork()
{
	//TODO: Clear all arrays
}

void ElectricNetwork::reconfigureEquipment()
{
	// ATA34::Adiru1
	if (busData[AcEssBus]->isAvailable()) {
		Aircraft->adiru1->connect(busData[AcEssBus]);
	}
	else {
		Aircraft->adiru1->connect(busData[HotBus2]);
	}

	// ATA34::Adiru2
	if (busData[AcBus2]->isAvailable()) {
		Aircraft->adiru1->connect(busData[AcBus2]);
	}
	else {
		// This is time limited: 1.34.97-1
		Aircraft->adiru1->connect(busData[HotBus2]);
	}

	// ATA34::Adiru3
	if (busData[AcBus1]->isAvailable()) {
		Aircraft->adiru1->connect(busData[AcBus1]);
	}
	else {
		// This has multiple exceptions and pre-conditions 1.34.97-1
		// Rules: 
		// backup suply when: ATT HDG = CAPT 3 
		// backup suply for 5m when: ATT HDG = NORM || ATT HDG = FO3

		Aircraft->adiru1->connect(busData[HotBus1]);
	}
}