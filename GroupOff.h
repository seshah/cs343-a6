#ifndef _GROUPOFF_H_
#define _GROUPOFF_H_

#include "Printer.h"
#include "WATCard.h"
#include "RandomGenerator.h"
#include <vector>

using namespace std;

_Task Groupoff
{
	Printer *printer;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupOffDelay;
	RandomGenerator *random;
	unsigned int numCards;
	struct GiftCard 
	{
		WATCard::FWATCard card;
		GiftCard() {};
	};
	vector<GiftCard*> cards;
	
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
	~Groupoff();
};


#endif

