#ifndef _PARENT_H_
#define _PARENT_H_


#include "Printer.h"
#include "Bank.h"


_Task Parent {

	const unsigned int numStudents;
	const unsigned int parentalDelay;
	Printer::Printer *printer;
	Bank::Bank *bank;
	RandomGenerator::RandomGenerator *random;

    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
	~Parent() {}
};


#endif
