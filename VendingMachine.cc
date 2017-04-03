#include "VendingMachine.h"
#include "NameServer.h"
#include "WATCard.h"


VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
					unsigned int maxStockPerFlavour ):
					printer(&prt),nameServer(&nameServer),id(id),sodaCost(sodaCost),
					maxStockPerFlavour(maxStockPerFlavour)
{
	for (unsigned int i = 0;i < Flavours::NoOfFlavours;i++)
		stockPerFlavour[i] = 0;
	buyOutOfFunds = false;
	buyOutOfStock = false;
}

void VendingMachine::main()
{
	printer->print(Printer::Kind::Vending, id, 'S', sodaCost);

	nameServer->VMregister(this);

	bool isRestocking = false;
	while (true)
	{
		// Only allow deconstruction when its not restocking, since the stock array is given to restocker for direct manipulation
		_When(!isRestocking) _Accept(~VendingMachine)
		{}
		or _Accept(inventory)
		{
			printer->print(Printer::Kind::Vending, id, 'r');
			isRestocking = true;
		}
		or _When(isRestocking) _Accept(restocked)
		{
			printer->print(Printer::Kind::Vending, id, 'R');
			isRestocking = false;
		}
		// Cannot allow people to buy while machine is restocking
		or _When(!isRestocking) _Accept(buy)
		{
			if (buyOutOfFunds)
			{
				_Resume Funds() _At *lastBuyer;
			}
			if (buyOutOfStock)
			{
				_Resume Stock() _At *lastBuyer;
			}
			else
			{
				stockPerFlavour[mostRecentlyBoughtFlavour]--;
				printer->print(Printer::Kind::Vending, id, 'B', mostRecentlyBoughtFlavour);
			}

			// Reset the flags for next usage
			buyOutOfFunds = false;
			buyOutOfStock = false;
		}
	}
}

void VendingMachine::buy( Flavours flavour, WATCard &card )
{
	// Saves the student task in case an exception needs to be raised on it
	lastBuyer = &uThisTask();

	// Check if desired flavour is in stock
	if (stockPerFlavour[(unsigned int)flavour] == 0)
	{
		buyOutOfStock = true;
		return;
	}

	// Check if there is enough funds in the card
	if (card.getBalance() < sodaCost)
	{
		buyOutOfFunds = true;
		return;
	}

	card.withdraw(sodaCost);
	mostRecentlyBoughtFlavour = (unsigned int)flavour;

}

unsigned int *VendingMachine::inventory()
{
	return stockPerFlavour;
}

void VendingMachine::restocked()
{

}

_Nomutex unsigned int VendingMachine::cost()
{
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
	return id;
}
