#include "Student.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "WATCard.h"
#include "Groupoff.h"
#include "VendingMachine.h"
#include "RandomGenerator.h" // RandomGenerator

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ):
			 printer(&prt),nameServer(nameServer),cardOffice(&cardOffice),groupoff(&groupoff),
			 id(id)
{
	random = RandomGenerator::getInstance();
}

void Student::main()
{
	const unsigned int numPurchases = random->generator(1,maxPurchases);
	const unsigned int favouriteFlavour = random->generator(0, ((unsigned int)VendingMachine::Flavours::NoOfFlavours) - 2);

	printer->print(Printer::Kind::Student, 'S', favouriteFlavour, numPurchases);

	WATCard::FWATCard watCard = cardOffice->create(id, 5);
	WATCard::FWATCard giftCard = groupoff->giftCard();
	VendingMachine *vendingMachine = nameServer->getMachine(id);

	printer->print(Printer::Kind::Student, 'V', vendingMachine->getId());
	bool isUsingGiftCard;

	// TODO: Make a local function Student::buy, so that watCard and giftCard can use that repeated code with their own try/catch handlers
	for (unsigned int i = 0;i < numPurchase;i++)
	{
		yield(random->generator(1,10));

		WATCard *cardToUse;
		// Determining what card is available to use
		_Select(watCard.available())
		{
			try
			{
				_Activate
				{
					cardToUse = watCard();
					isUsingGiftCard = false;
				}
			}
			// WATCard was lost, so create a new one and wait for it again
			_CatchResume(WATCardOffice::Lost)
			{
				printer->print(Printer::Kind::Student, 'L');
				watCard = cardOffice->create(id, 5);
			}
		}
		or _Select(giftCard.available())
		{
			cardToUse = giftCard();
			isUsingGiftCard = true;
		}
		// Determining whether to buy favourite flavour or the new one
		VendingMachine::Flavours flavourToBuy = (random->generator(1,4) == 1) ? VendingMachine::Flavours::DrSalt : static_cast<VendingMachine::Flavours>(favouriteFlavour);

		try
		{
			// Attempting to buy the chosen soda
			_Activate
			{
				vendingMachine->buy(flavourToBuy, *(cardToUse));
			}
		}
		_CatchResume(VendingMachine::Stock)
		{
			// Chosen soda was out of stock, so look for another machine
			vendingMachine = nameServer->getMachine(id);
			printer->print(Printer::Kind::Student, 'V', vendingMachine->getId());
		}
		_CatchResume(VendingMachine::Funds)
		{
			if (!isUsingGiftCard)
			{
				cardOffice->transfer(id, vendingMachine->cost(), cardToUse)
			}
			// TODO : What if it is a giftcard?
		}

		// Drinking the soda
		yield();

	}

	printer->print(Printer::Kind::Student, 'F', vendingMachine->getId());

}
