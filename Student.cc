#include "Student.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "WATCard.h"
#include "GroupOff.h"
#include "VendingMachine.h"
#include "RandomGenerator.h" // RandomGenerator

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ):
			 printer(&prt),nameServer(&nameServer),cardOffice(&cardOffice),groupoff(&groupoff),
			 id(id),maxPurchases(maxPurchases)
{
	random = &RandomGenerator::getInstance();
}

Student::~Student()
{}

void Student::main()
{
	WATCard::FWATCard watCard = cardOffice->create(id, 5);
	WATCard::FWATCard giftCard = groupoff->giftCard();
	WATCard *pWATCard = NULL; // For destructing the last used WAT card given by the future

	const unsigned int numPurchases = random->generator(1,maxPurchases);
	const unsigned int favouriteFlavour = random->generator(0, ((unsigned int)VendingMachine::Flavours::NoOfFlavours) - 2);

	printer->print(Printer::Kind::Student, id, 'S', favouriteFlavour, numPurchases);

	VendingMachine *vendingMachine = nameServer->getMachine(id);

	printer->print(Printer::Kind::Student, id, 'V', vendingMachine->getId());

	for (unsigned int i = 0;i < numPurchases;i++)
	{
		yield(random->generator(1,10));

		// Determining what card is available to use
		WATCard *cardToUse;
		CardWait: while (true)
		{
			_Select(watCard)
			{
				try
				{
					_Enable
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
			or _Select(giftCard)
			{
				cardToUse = giftCard();
				break CardWait;
			}
		}

		// Determining whether to buy favourite flavour or the new one
		VendingMachine::Flavours flavourToBuy = (random->generator(1,4) == 1) ? VendingMachine::Flavours::DrSalt : static_cast<VendingMachine::Flavours>(favouriteFlavour);

/*
<<<<<<< HEAD
					// Attempting to buy the chosen soda
					vendingMachine->buy(flavourToBuy, *(cardToUse));
					yield(); // In case an exception is thrown
					break BuyAttempts;
				}
			
			}
			_CatchResume(VendingMachine::Stock)
			{
				// Chosen soda was out of stock, so look for another machine
				vendingMachine = nameServer->getMachine(id);
				printer->print(Printer::Kind::Student, id, 'V', vendingMachine->getId());
				throw BuyRetry();
			}
			_CatchResume(VendingMachine::Funds)	
			{
				// Assumption: gift card should always be one soda and done
				watCard = cardOffice->transfer(id, vendingMachine->cost(), cardToUse);
				throw BuyRetry();
			}		
			catch (BuyRetry)
=======*/
		try
		{
			_Enable
//>>>>>>> 72a9d3b13a2bb27ff495cc14c95c4cd6fc01557d
			{

				// Attempting to buy the chosen soda
				vendingMachine->buy(flavourToBuy, *(cardToUse));
				yield(); // In case an exception is thrown
			}

		}
		_CatchResume(VendingMachine::Stock)
		{
			// Chosen soda was out of stock, so look for another machine
			vendingMachine = nameServer->getMachine(id);
			printer->print(Printer::Kind::Student, id, 'V', vendingMachine->getId());
			// Attempting to buy the chosen soda
			vendingMachine->buy(flavourToBuy, *(cardToUse));
			yield(); // In case an exception is thrown
		}
		_CatchResume(VendingMachine::Funds)
		{
			// Assumption: gift card should always be one soda and done
			cardOffice->transfer(id, vendingMachine->cost(), cardToUse);
			// Attempting to buy the chosen soda
			vendingMachine->buy(flavourToBuy, *(cardToUse));
			yield(); // In case an exception is thrown
		}

		if (giftCard.available() && cardToUse == giftCard)
		{
			printer->print(Printer::Kind::Student, id, 'G', flavourToBuy, cardToUse->getBalance());
			delete cardToUse;
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
