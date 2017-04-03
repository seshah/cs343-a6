#include "GroupOff.h"
#include <vector>

using namespace std;


	
void Groupoff::main()
{
	for(;numCards < numStudents;) _Accept(giftCard);

	while ( numCards > 0 )
	{
		_Accept(~Groupoff)
		{
			vector< GiftCard *>::iterator it = cards.begin();
			for( ; it != cards.end(); it++)
			{
				delete *it;
			}
			break;
		}
		_Else
		{
			WATCard * watCard = new WATCard();
			watCard->deposit(sodaCost);
			int studentCard = random->generator(0, numCards-1);
			yield(groupOffDelay);
			GiftCard * temp = cards[studentCard];
			temp->card.delivery(watCard);
			delete temp;
			cards.erase( cards.begin()+studentCard );
			numCards--;

		}
	}
}


// intitialise GroupOff
Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
	printer(&prt),
	numStudents(numStudents),
	sodaCost(sodaCost),
	groupOffDelay(groupoffDelay),
	numCards(0)
{
	random = &RandomGenerator::getInstance();
} // Groupoff


// return a groupoff future to student
WATCard::FWATCard Groupoff::giftCard()
{
	GiftCard * gc = new GiftCard();
	cards.push_back(gc);
	numCards++;
	return gc->card;
} // giftCard




