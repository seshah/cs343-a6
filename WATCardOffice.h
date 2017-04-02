#ifndef _WATCARDOFFICE_H_
#define _WATCARDOFFICE_H_

#include "Printer.h"
#include "Bank.h"
#include "Student.h"
#include "WATCard.h"
#include "RandomGenerator.h"
#include <queue>

_Task WATCardOffice {
	
	Printer *printer;
	Bank *bank;
	unsigned int numCouriers;
	Courier *listOfCouriers;  // may need to use different way to store courriers
	queue<Job *> jobs;
    struct Job
    {                              // marshalled arguments and return future
        unsigned int sid;                       // call arguments (YOU DEFINE "Args")
	WATCard *card;
	unsigned int amount;
        WATCard::FWATCard result;             // return future
        Job( unsigned int sid, unsigned int amount, WATCard *card) :
		sid(sid),
		amount(amount),
		card(card) {}
    };
    _Task Courier 
	{ 
		RandomGenerator *random;	
		Job * j;
		void main(); // call requestWork and block
	    public:
		Courier() { random = RandomGenerator::getInstance();}
	}       

    void main();
  public:
    _Event Lost {};                           // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork(); // check if queue is empty, wait if it is, pop first element if it isn't
	~WATCardOffice();
};


#endif
