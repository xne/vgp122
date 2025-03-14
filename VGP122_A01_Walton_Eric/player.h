#ifndef XN_PLAYER
#define XN_PLAYER

#include "card.h"

class Player
{
public:
	void addCard(Card card)
	{
		mHand[mNextCard++] = card;
	}

	unsigned short getHandValue()
	{
		unsigned short result = 0;
		unsigned short aces = 0;

		// find hand total when aces have a value of 1
		for (Card card : mHand)
		{
			if (card.value == 1)
			{
				aces++;
				result++;
			}

			// handle face cards
			else if (card.value > 10)
				result += 10;
			else
				result += card.value;
		}

		// increase value of aces
		while (aces > 0 && result <= 11)
		{
			aces--;
			result += 10;
		}

		return result;
	}

private:
	// the maximum number of cards a player can hold without going over 21
	static const unsigned short maxHandSize = 11;
	unsigned short mNextCard = 0;

	Card mHand[maxHandSize] = { 0 };
};

#endif
