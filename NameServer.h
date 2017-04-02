#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "Printer.h"

// Forward declarations
_Task VendingMachine;

_Task NameServer
{
	const unsigned int numVendingMachines, numStudents;
	unsigned int recentStudentIdRequest;
	VendingMachine *recentlyRegisteredVM;

	Printer *printer;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};


#endif
