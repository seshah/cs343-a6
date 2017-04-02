#ifndef _WATCARD_H_
#define _WATCARD_H_



class WATCard {
    WATCard( const WATCard & );               // prevent copying
    WATCard &operator=( const WATCard & );
	unsigned int balance;
	// define lock
  public:
    typedef Future_ISM<WATCard *> FWATCard;   // future watcard pointer
    WATCard() : balance(0) {}
	// called to increase  funds on WATCard
    void deposit( unsigned int amount )
    {
	// acquire lock
	balance += amount;
	// release lock
    }
	// called to withdraw funds. must call getBalance to ensure enough funds first
    void withdraw( unsigned int amount )
    {
	// acquire lock
	balance -= amount; // assume balance >= amount
	// release lock
    }
	// returns balance. must be called before withdraw to ensure enough funds
    unsigned int getBalance() 
    {
	return balance;
    }
	
};

#endif
