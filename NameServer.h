#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "Printer.h"

// Forward declarations
_Task VendingMachine;

_Task NameServer
{
	Printer *printer;
	const unsigned int numVendingMachines, numStudents;
	VendingMachine **vendingMachines;
	unsigned int *getIndexStudent;

	unsigned int recentStudentIdRequest;
	VendingMachine *recentlyRegisteredVM;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};


#endif
