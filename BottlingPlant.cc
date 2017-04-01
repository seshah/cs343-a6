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
	unsigned int totalProduced = 0;
	for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
	{
		produced[i] = random->generator(0,maxShippedPerFlavour);
		totalProduced += produced[i];
	}
	printer->print(Printer::Kind::BottlingPlant, 'G', totalProduced);
	yield(timeBetweenShipments);
}

void BottlingPlant::main()
{
	printer->print(Printer::Kind::BottlingPlant, 'S');

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
			printer->print(Printer::Kind::BottlingPlant, 'P');
			// Produce after truck has picked up shipment
			runProduce();
		}
	}
	printer->print(Printer::Kind::BottlingPlant, 'F');
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
