#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "Printer.h"

_Task NameServer;
_Task WATCardOffice;
_Task Groupoff;
_Task VendingMachine;
class RandomGenerator;

_Task Student
{
	Printer *printer;
	NameServer *nameServer;
	WATCardOffice *cardOffice;
	Groupoff *groupoff;
	const unsigned int id;
	const unsigned int maxPurchases;

	RandomGenerator *random;

	VendingMachine* getNewVendingMachine();
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif
