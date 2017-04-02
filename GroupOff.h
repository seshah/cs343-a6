#ifndef _GROUPOFF_H_
#define _GROUPOFF_H_

#include "Printer.h"

_Task Groupoff {
	Printer *printer;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupOffDelay;
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif

