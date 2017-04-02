
#include "Bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ) :
	numStudents(numStudents)
{
	accounts = new unsigned int[numStudents];
	moneyNeeded = new unsigned int[numStudents];
	moneyWait = new uCondition[numStudents];

	for (int i = 0; i < numStudents; i++) 
	{
		accounts[i] = 0;  // assert each account starts with 0. probably unnecessary
		moneyNeeded[i] = 0;
	} // for

} // Bank



void Bank::deposit( unsigned int id, unsigned int amount ) 
{
	accounts[id] = accounts[id] + amount;
	// Let the waiting withdrawer know that there is enough money now
	if (moneyNeeded[id] != 0 && accounts[id] >= moneyNeeded[id])
		moneyWait.signal();
} //deposit



void Bank::withdraw( unsigned int id, unsigned int amount )
{
	// Wait for a big enough deposit, so that withdraw can complete
	if (accounts[id] < amount)
	{
		moneyNeeded[id] = amount;
		moneyWait.wait();
		moneyNeeded[id] = 0;
	} // if

	accounts[id] = accounts[id] - amount;

} // withdraw


