#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "Printer.h"
#include "RandomGenerator.h"
#include "VendingMachine.h" // VendingMachine::Flavours::NoOfFlavours

// Forward Declarations
_Task NameServer;
_Task Truck;

_Task BottlingPlant
{
	Printer *printer;
	NameServer *nameServer;
	const unsigned int numVendingMachines;
	const unsigned int maxShippedPerFlavour;
	const unsigned int maxStockPerFlavour;
	const unsigned int timeBetweenShipments;

	bool isShuttingDown = false;

	unsigned int produced[VendingMachine::Flavours::NoOfFlavours];
	RandomGenerator *random;

	void runProduce(); // The production run for the bottling plant
    void main();
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif
