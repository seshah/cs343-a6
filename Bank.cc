
#include "Bank.h"

using namespace std;



Bank::Bank( unsigned int numStudents ) :
	numSudents(numStudents)
{
	accounts = new unsigned int [numStudents];
	// comment out the dynamic allocation? 
	for (int i = 0; i < numStudents; i++) 
	{
		accounts[i] = 0;  // assert each account starts with 0. probably unnecessary
	} // for

} // Bank



void Bank::deposit( unsigned int id, unsigned int amount ) 
{
	accounts[id] = accounts[id] + amount;

} //deposit



void Bank::withdraw( unsigned int id, unsigned int amount )
{
	while (accounts[id] < amount) // wait for enough funds
	{
		_Accept(deposit) 
	}// while

	accounts[id] = accounts[id] - amount;

} // withdraw


