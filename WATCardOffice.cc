#include "WATCardOffice.h"


using namespace std;



	void Courier::main() 
	{
			printer->print(Printer::Courier, 'S'); 
		while(true) 
		{
			int lost = random->generator(1, 6);
			j = requestWob;
			printer->print(Printer::Courier,j->sid, 't', j->amount); 
			bank->withdraw(j->sid, j->amount);
			if (lost == 3) 
			{
				printer->print(Printer::Courier,j->sid, 'L');  
				j->result = WATCardOffice::Lost;
				delete j->card;
			}
			else
			{
				j->card->deposit(amount);
				printer->print(Printer::WATCardOffice, j->sid, 'T', j->amount);
			}
		}	
		printer->print(Printer::Courier, 'F');
	} // Courrier::main

// 
	void WATCardOffice::main()
	{
		printer->print(Printer::WATCardOffice, 'S');
		for(int i = 0; i < numCouriers; i++) listOfCouriers[i] = new Courier;
		while(true) 
		{
			// only allow destructor when queue is empty. i.e no jobs left to do
			_When(jobs.empty()) _Accept(~WATCardOffice)
			{
				for(int i = 0; i < numCouriers; i++) delete listOfCouriers[i];
			}
			or _Accept(create) 
			{ 
				// signal requestJob
			}
			or _Accept(tranfer)
			{
				// signal requestJob
			}
			or _Accept(requestWork)
			{
				printer->print(Printer::WATCardOffice, 'W');
			}
		}

		printer->print(Printer::WATCardOffice, 'F');
		
	} // WATCardOffice


// initialise WATCardOffice
	WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ): 
	printer(&prt),
	bank(&bank),
	numCouriers(numCouriers)
	{} // WATCardOffice


// delete couriers before ending
	~WATCardOffice() 
	{} // ~WATCardOffice

// Student calls create, new Job is created and pushed on jobs, returns FWATcard
	WATCard::FWATCard create( unsigned int sid, unsigned int amount )
	{
		WATCard::FWATCard card = new WATCard;
		Job * newJob = new Job(sid, amount, card);
		jobs.push(newJob);
		printer->print(Printer::WATCardOffice, sid, 'C', amount);
		return newJob->result;
        } // create

// Student calls transfer, new Job is created and pushed on jobs, returns FWATcard
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card ) 
	{
		Job *newJob = new Job(sid, amount, card);
		jobs.push(newJob);
		printer->print(Printer::WATCardOffice, sid,'T',  amount);
		return newJob->result;
	} // transfer
	

// Courier calls requestWork, waits if jobs is empty, returns Job otherwise
	Job *requestWork() 
	{
		Job * ret;
		// get lock for queue
		if (jobs.empty() ) 
		{
			// wait for queue to have job
		}
		ret = jobs.front();
		jobs.pop(); 

		// release lock for queue
		return ret;
	} // requestWork



