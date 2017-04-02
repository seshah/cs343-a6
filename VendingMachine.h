#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "Printer.h"
#include "NameServer.h"

_Task VendingMachine
{
  public:
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
	const unsigned int id;
	const unsigned int sodaCost;
	const unsigned int maxStockPerFlavour;
	unsigned int stockPerFlavour[Flavours::NoOfFlavours];
    unsigned int mostRecentlyBoughtFlavour;
    bool buyOutOfFunds, buyOutOfStock;
    uBaseTask *lastBuyer;

	Printer *printer;
	NameServer *nameServer;

    void main();
};

#endif
