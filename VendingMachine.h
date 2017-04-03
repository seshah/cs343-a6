#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "Printer.h"

// Forward declarations
_Task NameServer;
class WATCard;

_Task VendingMachine
{
  public:
	// Assumption: DrSalt is the last soda in the enum and is not the only soda in the enum
    enum Flavours
	{
    	Blues,
		BlackCherry,
		CreamSoda,
		RootBeer,
		Lime,
		DrSalt,
		NoOfFlavours
	};                    					  // flavours of soda (YOU DEFINE)
    _Event Funds {};                          // insufficient funds
    _Event Stock {};                          // out of stock for particular flavour

    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
  private:
	Printer *printer;
	NameServer *nameServer;
	const unsigned int id;
	const unsigned int sodaCost;
	const unsigned int maxStockPerFlavour;

	unsigned int stockPerFlavour[Flavours::NoOfFlavours];
    unsigned int mostRecentlyBoughtFlavour;
    bool buyOutOfFunds, buyOutOfStock;
    uBaseTask *lastBuyer;


    void main();
};

#endif
