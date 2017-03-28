#include "VendingMachine.h"


VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
					unsigned int maxStockPerFlavour ):
					printer(&prt),nameServer(&nameServer),id(id),sodaCost(sodaCost),
					maxStockPerFlavour(maxStockPerFlavour)
{
	for (unsigned int i = 0;i < Flavours::NoOfFlavour;i++)
		stockPerFlavour[i] = 0;
}

void VendingMachine::main()
{
	bool isRestocking = false;
	while (true)
	{
		// Only allow deconstruction when its not restocking, since the stock array is given to restocker for direct manipulation
		_When(~isRestocking) _Accept(~VendingMachine)
		{}
		or _Accept(inventory)
		{
			isRestocking = true;
		}
		or _When(isRestocking) _Accept(restocked)
		{
			isRestocking = false;
		}
		// Cannot allow people to buy while machine is restocking
		or _When(~isRestocking) _Accept(buy)
		{
		}
	}
}

void VendingMachine::buy( Flavours flavour, WATCard &card )
{
	// Check if desired flavour is in stock
	if (stockPerFlavour[(unsigned int)flavour] == 0)
		_Resume Stock(); // TODO: Check if _Resume or _Throw is needed (and check if this is correct task stack)

	// Check if there is enough funds in the card
	if (card.getBalance() < sodaCost)
		_Resume Stock(); // TODO: Check if _Resume or _Throw is needed (and check if this is correct task stack)

	card.withdraw(sodaCost);
	stockPerFlavour[(unsigned int)flavour]--;
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
