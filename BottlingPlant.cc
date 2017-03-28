#include "BottlingPlant.h"
#include "RandomGenerator.h" // RandomGenerator
#include "Truck.h" // Truck

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):
				 printer(&prt),nameServer(&nameServer),numVendingMachines(numVendingMachines),
				 maxShippedPerFlavour(maxShippedPerFlavour),maxStockPerFlavour(maxStockPerFlavour),
				 timeBetweenShipments(timeBetweenShipments)
{
	random = RandomGenerator::getInstance();
	for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
	{
		produced[i] = 0;
	}
}

// The production run for the bottling plant
void BottlingPlant::runProduce()
{
	for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
	{
		produced[i] = random->generator(0,maxShippedPerFlavour);
	}
	yield(timeBetweenShipments);
}

void BottlingPlant::main()
{
	Truck truck(*printer, *nameServer, this, numVendingMachines, maxStockPerFlavour);
	// Priming to ensure that there is a production to start with
	runProduce();
	PlantProduction: while (true)
	{
		_Accept(~BottlingPlant)
		{
			isShuttingDown = true;
			// Wait for the truck to come back to tell them to stop
			_Accept (getShipment){}
			break PlantProduction;
		}
		// Wait for the truck to pick up current shipment
		_Accept(getShipment)
		{
			// Produce after truck has picked up shipment
			runProduce();
		}
	}
}

void BottlingPlant::getShipment( unsigned int cargo[] )
{
	if (isShuttingDown)
		_Resume Shutdown();

	for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
	{
		cargo[i] = produced[i];
		produced[i] = 0;
	}
}