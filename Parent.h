#ifndef _PARENT_H_
#define _PARENT_H_


#include "RandomGenerator.h"
#include "Printer.h"
#include "Bank.h"


_Task Parent
{

	Printer *printer;
	Bank *bank;
	const unsigned int numStudents;
	const unsigned int parentalDelay;
	RandomGenerator *random;

    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
	~Parent(); 
};


#endif
