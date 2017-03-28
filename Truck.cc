#include "Truck.h"
#include "BottlingPlant.h"
#include "RandomGenerator.h"
#include "VendingMachine.h" // VendingMachine::NoOfFlavours

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
				unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
				printer(&prt),nameServer(&nameServer),bottingPlant(&plant),
				numVendingMachines(numVendingMachines),maxStockPerFlavour(maxStockPerFlavour)
{
	for (unsigned int i = 0;i < VendingMachine::NoOfFlavours;i++)
		cargo[i] = 0;
}

void Truck::main()
{
	VendingMachine **vendingMachines = nameServer->getMachineList();
	RandomGenerator *random = RandomGenerator::getInstance();
	try
	{
		unsigned int currentMachine = 0;
		TruckDelivery: while (true)
		{
			bottlingPlant->getShipment(cargo);
			// Simulating getting coffee from Tim Hortons before beginning route
			yield(random->generator(1,10));
			unsigned int startMachine = currentMachine;
			// Going to each vending machine to restock
			TruckDeliveryRoute: while (true)
			{
				unsigned int machineInventory[VendingMachine::NoOfFlavours] = vendingMachines[currentMachine]->inventory();
				bool isCargoEmpty = true;
				// Restocking the vending machine
				TruckRestock: for (unsigned int i = 0;i < VendingMachine::NoOfFlavours;i++)
				{
					unsigned int restock = maxStockPerFlavour - machineInventory[i];
					if (restock > cargo[i])
						restock = cargo[i];
					cargo[i] -= restock;
					machineInventory[i] += restock;
					// Checking if there is cargo left while restocking machine
					if (cargo[i] > 0)
						isCargoEmpty = true;
				}
				// Let vending machine know that truck is finished restocking it
				vendingMachines[currentMachine]->restocked();
				currentMachine++;
				// If there is no cargo or we have restocked all machines, stop restocking cycle
				if (isCargoEmpty || startMachine == currentMachine)
					break TruckDeliveryRoute;
			}

		}
	}
	catch(BottlingPlant::Shutdown)
	{
		// TODO: Anything to do?
	}

}

