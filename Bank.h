#ifndef _BANK_H_
#define _BANK_H_



_Monitor Bank
{
	unsigned int numStudents
	unsigned int *accounts;
	uCondition *moneyWait;
	unsigned int *moneyNeeded;
	
  public:
	~Bank() 
	{ 
		delete [] accounts;  // may not be needed if stack is used
	}
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};


#endif
