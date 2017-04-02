#include "GroupOff.h"

using namespace std;


	
    void main() 
	{
		for(; numCards < numStudents; ) _Accept(giftCard);

		while ( numCards > 0 ) 
		{
			_Accept(~Groupoff) 
			{
				vect< GiftCard *>::iterator it = cards.begin();
				for( ; it != vards.end(); it++) 
				{
					delete *it;
				} 
				break;
			}
			_Else
			{
				WATCard * watCard = new WATCard(sodaCost);
				int studentCard = random->generator(0, numCards-1);
				yield(GroupoffDelay);
				GiftCard * temp = cards[studentCard];
				temp->card.delivery(watCard);
				delete temp;
				cards.erase( cards.begin()+studentCard );
				numCards--;
				
			}
		}
	}


// intitialise GroupOff
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
	printer(&prt),
	numStudents(numStudents),
	sodaCost(sodaCost),
	goroupoffDelay(groupoffDelay),
	numCards(0)
	{
		random = RandomGenerator::getInstance();
	} // Groupoff


// return a groupoff future to student
    WATCard::FWATCard giftCard()
	{
		GiftCard * gc = new GiftCard();
		card.push_back(gc);
		numCards++;
		return gc->card;
	} // giftCard




