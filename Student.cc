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

VendingMachine* Student::getNewVendingMachine()
{
	VendingMachine *vendingMachine = nameServer->getMachine(id);
	printer->print(Printer::Kind::Student, id, 'V', vendingMachine->getId());
	return vendingMachine;
}

void Student::main()
{
	WATCard::FWATCard watCard = cardOffice->create(id, 5);
	WATCard::FWATCard giftCard = groupoff->giftCard();

	const unsigned int numPurchases = random->generator(1,maxPurchases);
	const unsigned int favouriteFlavour = random->generator(0, ((unsigned int)VendingMachine::Flavours::NoOfFlavours) - 2);

	printer->print(Printer::Kind::Student, id, 'S', favouriteFlavour, numPurchases);

	VendingMachine *vendingMachine = getNewVendingMachine();

	BuyProcess: for (unsigned int i = 0;i < numPurchases;i++)
	{
		yield(random->generator(1,10));
		// Determining whether to buy favourite flavour or the new one

		VendingMachine::Flavours flavourToBuy = (random->generator(1,4) == 1) ? VendingMachine::Flavours::DrSalt : static_cast<VendingMachine::Flavours>(favouriteFlavour);

		_Select(giftCard)
		{
			GiftBuyAttempt: while (true)
			{
				try
				{
					_Enable
					{
						// Attempting to buy the chosen soda
						vendingMachine->buy(flavourToBuy, *(giftCard()));
						break GiftBuyAttempt;
					}
				}
				catch(VendingMachine::Stock)
				{
					// Chosen soda was out of stock, so look for another machine
					vendingMachine = getNewVendingMachine();
				}
			}
			printer->print(Printer::Kind::Student, id, 'G', flavourToBuy, (*giftCard).getBalance());
			giftCard.reset();
		}
		or
		_Select(watCard)
		{
			WATBuyAttempt: while (true)
			{
				try
				{
					_Enable
					{
						// Attempting to buy the chosen soda
						vendingMachine->buy(flavourToBuy, *watCard());
						break WATBuyAttempt;
					}
				}
				catch(VendingMachine::Stock)
				{
					// Chosen soda was out of stock, so look for another machine
					vendingMachine = getNewVendingMachine();
				}
				catch(VendingMachine::Funds)
				{
					// Attempt to transfer funds to the card
					watCard = cardOffice->transfer(id, vendingMachine->cost(), watCard);
				}
				catch (WATCardOffice::Lost)
				{
					// WATCard was lost, so create a new one
					printer->print(Printer::Kind::Student, id, 'L');
					watCard = cardOffice->create(id, 5);
				}
			}

			printer->print(Printer::Kind::Student, id, 'B', flavourToBuy, (*watCard).getBalance());
		}

		// Drinking the soda
		yield();
	}

	// Making sure that the remaining WAT cards that was being used are deleted
	try
	{
		_Enable
		{
			delete watCard();
		}
	}
	catch (WATCardOffice::Lost) {}

	printer->print(Printer::Kind::Student, id, 'F');
}
