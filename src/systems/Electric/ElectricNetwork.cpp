#include "ElectricNetwork.h"
#include "ElectricBus.h"
#include "A320.h"
#include "core\core.h"

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
		generatorData[Gen1]->coupledBuses.push_back(busData[AcBus1]);
		busData[AcBus1]->coupledSystems.push_back(busData[DcBus1]);

		if (!ac_ess_feed_pb_pushed) {
			busData[AcBus1]->coupledSystems.push_back(busData[AcEssBus]);
		}
	}

	// GEN 2.
	if (generatorData[Gen2]->currentHealth == Healthy && gen2LineCont)
	{
		generatorData[Gen2]->coupledBuses.push_back(busData[AcBus2]);
		busData[AcBus2]->coupledSystems.push_back(busData[DcBus2]);

		if (ac_ess_feed_pb_pushed) {
			busData[AcBus2]->coupledSystems.push_back(busData[AcEssBus]);
		}
	}

	// AC ESS SHED.
	busData[AcEssBus]->coupledSystems.push_back(busData[AcEssShed]);

	//TODO: DC Buses.
}

void ElectricNetwork::prepareNormalGroundConfig()
{
	// Read from user interface
	bool ext_pwr_cont = true;
	bool bus_tie_cont = true;

	ElectricGenerator * rootGen = generatorData[ExtPwr];

	if (ext_pwr_cont && bus_tie_cont) {
		rootGen->coupledBuses.push_back(busData[AcBus1]);
		rootGen->coupledBuses.push_back(busData[AcBus2]); 
	}
}

void ElectricNetwork::resetNetwork()
{
	//TODO: Clear all arrays
}