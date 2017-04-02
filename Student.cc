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
	WATCard::FWATCard watCard = cardOffice->create(id, 5);
	WATCard::FWATCard giftCard = groupoff->giftCard();
	WATCard *pWATCard; // For destructing the last used WAT card given by the future

	printer->print(Printer::Kind::Student, id, 'S', favouriteFlavour, numPurchases);

	const unsigned int numPurchases = random->generator(1,maxPurchases);
	const unsigned int favouriteFlavour = random->generator(0, ((unsigned int)VendingMachine::Flavours::NoOfFlavours) - 2);


	VendingMachine *vendingMachine = nameServer->getMachine(id);

	printer->print(Printer::Kind::Student, id, 'V', vendingMachine->getId());

	for (unsigned int i = 0;i < numPurchase;i++)
	{
		yield(random->generator(1,10));

		// Determining what card is available to use
		WATCard *cardToUse;
		CardWait: while (true)
		{
			_Select(watCard.available())
			{
				try
				{
					_Activate
					{
						pWATCard = watCard();
						cardToUse = pWATCard;
						break CardWait;
					}
				}
				// WATCard was lost, so create a new one
				catch (WATCardOffice::Lost)
				{
					printer->print(Printer::Kind::Student, id, 'L');
					watCard = cardOffice->create(id, 5);
				}
			}
			or _Select(giftCard.available())
			{
				cardToUse = giftCard();
				break CardWait;
			}
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
			printer->print(Printer::Kind::Student, id, 'V', vendingMachine->getId());
		}
		_CatchResume(VendingMachine::Funds)
		{
			// Assumption: gift card should always be one soda and done
			cardOffice->transfer(id, vendingMachine->cost(), cardToUse)
		}

		if (giftCard.available() && cardToUse == giftCard)
		{
			printer->print(Printer::Kind::Student, id, 'G', flavourToBuy, cardToUse->getBalance());
			giftCard.reset();
		}
		else
			printer->print(Printer::Kind::Student, id, 'B', flavourToBuy, cardToUse->getBalance());

		// Drinking the soda
		yield();

	}

	// Making sure that the last WAT card that was being used is deleted
	if (pWATCard != NULL)
		delete watCard;

	printer->print(Printer::Kind::Student, id, 'F');

}
