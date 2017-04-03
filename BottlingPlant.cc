#include "BottlingPlant.h"
#include "RandomGenerator.h" // RandomGenerator
#include "NameServer.h"
#include "Truck.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):
				 printer(&prt),nameServer(&nameServer),numVendingMachines(numVendingMachines),
				 maxShippedPerFlavour(maxShippedPerFlavour),maxStockPerFlavour(maxStockPerFlavour),
				 timeBetweenShipments(timeBetweenShipments)
{
	random = &RandomGenerator::getInstance();
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
}

void BottlingPlant::main()
{
	printer->print(Printer::Kind::BottlingPlant, 'S');

	Truck truck(*printer, *nameServer, *this, numVendingMachines, maxStockPerFlavour);
	// Priming to ensure that there is a production to start with
	runProduce();
	PlantProduction: while (true)
	{
		_Accept(~BottlingPlant)
		{
			isShuttingDown = true;

			// Tell truck of the shutdown and make sure they receive it.
		//	_Resume Shutdown() _At truck;
			try
			{
				_Accept(getShipment);
			}
			catch (uMutexFailure::RendezvousFailure)
			{
				break PlantProduction;
			}
		}
		// Wait for the truck to pick up current shipment
		or _Accept(getShipment)
		{
			printer->print(Printer::Kind::BottlingPlant, 'P');
			// Produce after truck has picked up shipment
			runProduce();
			yield(timeBetweenShipments);
		}
	}
	printer->print(Printer::Kind::BottlingPlant, 'F');
}

void BottlingPlant::getShipment( unsigned int cargo[] )
{
	if (isShuttingDown) throw Shutdown();
	for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
	{
		cargo[i] = produced[i];
		produced[i] = 0;
	}
}
