#ifndef _GROUPOFF_H_
#define _GROUPOFF_H_

#include "Printer.h"
#include "RamdomGenerator.h"

_Task Groupoff {
	Printer *printer;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupOffDelay;
	RandomGenerator *random
	int numCards;
	struct GiftCard 
	{
		WATCard::FWATCard card;
		GiftCards() {};
	}
	vector< GiftCards * > cards;
	
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif

