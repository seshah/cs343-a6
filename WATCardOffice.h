#ifndef _WATCARDOFFICE_H_
#define _WATCARDOFFICE_H_

#include "Printer.h"
#include "Bank.h"
#include "Student.h"
#include "WATCard.h"
#include "RandomGenerator.h"
#include <queue>

using namespace std;

_Task WATCardOffice
{
    struct Job
    {                              // marshalled arguments and return future
        unsigned int sid;                       // call arguments (YOU DEFINE "Args")
		unsigned int amount;
		WATCard *card;
        WATCard::FWATCard result;             // return future
        Job( unsigned int sid, unsigned int amount, WATCard *card) :
				sid(sid),
				amount(amount),
				card(card)
        {}
    };
    _Task Courier 
	{ 
    	Printer* printer;
    	WATCardOffice* cardOffice;
    	Bank* bank;
    	unsigned int id;

		RandomGenerator *random;	
		Job * j;
		void main(); // call requestWork and block
	  public:
		Courier(Printer &prt, WATCardOffice &cardOffice, Bank &bank, unsigned int id):
			printer(&prt),cardOffice(&cardOffice),bank(&bank),id(id)
	  {
			random = &RandomGenerator::getInstance();
	  }
	};

	Printer *printer;
	Bank *bank;
	unsigned int numCouriers;
	Courier **listOfCouriers;  // may need to use different way to store courriers
	queue<Job *> jobs;
//	bool isShuttingDown;
//	_Event Shutdown {};

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
