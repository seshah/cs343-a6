#include "Truck.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "RandomGenerator.h"
#include "VendingMachine.h" // VendingMachine::NoOfFlavours

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
				unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
				printer(&prt),nameServer(&nameServer),bottingPlant(&plant),
				numVendingMachines(numVendingMachines),maxStockPerFlavour(maxStockPerFlavour)
{}

void Truck::main()
{
	printer->print(Printer::Kind::Truck, 'S');
	VendingMachine **vendingMachines = nameServer->getMachineList();
	RandomGenerator *random = RandomGenerator::getInstance();
	try
	{
		unsigned int currentMachine = 0;
		TruckDelivery: while (true)
		{
			_Enable
			{
				// Initializing cargo for first time, or forcing contents of cargo to 'expire'
				for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
						cargo[i] = 0;

				// Simulating getting coffee from Tim Hortons before beginning route
				yield(random->generator(1,10));

				bottlingPlant->getShipment(cargo);

				// Counting the total shipment
				unsigned int totalSodasInCargo = 0;
				for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
					totalSodasInCargo += cargo[i];
				printer->print(Printer::Kind::Truck, 'P', totalSodasInCargo);

				unsigned int startMachine = currentMachine;

				// Going to each vending machine to restock
				TruckDeliveryRoute: while (true)
				{
					unsigned int *machineInventory = vendingMachines[currentMachine]->inventory();
					printer->print(Printer::Kind::Truck, currentMachine, 'P', totalSodasInCargo);

					unsigned int machineMissingStock = VendingMachine::Flavours::NoOfFlavours * maxStockPerFlavour;

					// Restocking the vending machine
					TruckRestock: for (unsigned int i = 0;i < VendingMachine::Flavours::NoOfFlavours;i++)
					{
						unsigned int restock = maxStockPerFlavour - machineInventory[i];
						if (restock > cargo[i])
							restock = cargo[i];

						cargo[i] -= restock;
						machineInventory[i] += restock;
						machineMissingStock -= machineInventory[i];
						totalSodasInCargo -= restock;
					}

					// Printing before restocked, in case of pre-emption after restocked
					if (machineMissingStock > 0)
						printer->print(Printer::Kind::Truck, currentMachine, 'U', machineMissingStock);
					printer->print(Printer::Kind::Truck, currentMachine, 'D', totalSodasInCargo);

					// Let vending machine know that truck is finished restocking it
					vendingMachines[currentMachine]->restocked();

					currentMachine++;
					// If there is no cargo or we have restocked all machines, stop restocking cycle
					if (totalSodasInCargo == 0 || startMachine == currentMachine)
						break TruckDeliveryRoute;
				}
			}
		}
	}
	catch(BottlingPlant::Shutdown)
	{
		printer->print(Printer::Kind::Truck, 'F');
	}

}

