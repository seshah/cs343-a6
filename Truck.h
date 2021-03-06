#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "Printer.h"
#include "VendingMachine.h" // VendingMachine::NoOfFlavours

_Task NameServer;
_Task BottlingPlant;

_Task Truck
{
	Printer *printer;
	NameServer *nameServer;
	BottlingPlant *bottlingPlant;
	const unsigned int numVendingMachines;
	const unsigned int maxStockPerFlavour;

	unsigned int cargo[VendingMachine::Flavours::NoOfFlavours];

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
