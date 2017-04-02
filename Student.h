#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "Printer.h"

_Task NameServer;
_Task WATCardOffice;
_Task Groupoff;
class RandomGenerator;

_Task Student
{
	const unsigned int id;

	Printer *printer;
	NameServer *nameServer;
	WATCardOffice *cardOffice;
	Groupoff *groupoff;
	RandomGenerator *random;

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif
