#include "Parent.h"
#include "RandomGenerator.h"

using namespace std;


void Parent::main()
{
	printer->print(Printer::Kind::Parent, 'S'); //Starting
	Deposit: while(true) 
	{
	
		_Accept(~Parent)
		{
			break Deposit;
		}
		_Else
		{
			unsigned int student = random->generator(0, numStudents);
			unsigned int amount = random->generator(1,3); 
			yield(parentalDelay);
			printer->print(Printer::Kind::Parent, 'D', student, amount); // deposit gift
			bank->deposit(student, amount);
		}

	}

} // main


Parent::~Parent()
{
	printer->print(Printer::Kind::Parent, 'F'); //Finished
}


Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
	printer(&prt),
	bank(&bank),
	numStudents(numStudents),
	parentalDelay(parentalDelay)
{
	random = &RandomGenerator::getInstance();
}  // Parent




