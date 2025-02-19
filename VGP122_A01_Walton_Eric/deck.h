#ifndef XN_DECK
#define XN_DECK

#include <random>

const unsigned char mSuits[] = { 'C', 'D', 'H', 'S' };
const unsigned short mValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

class Deck
{
public:
	Deck()
	{
		unsigned short index = 0;
		for (unsigned char suit : mSuits)
			for (unsigned short value : mValues)
				mDeck[index++] = { suit, value };

		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(mDeck, mDeck + mSize, g);
	}

	Card draw()
	{
		return mDeck[mNextCard++];
	}

private:
	static const unsigned short mSize = 52;
	unsigned short mNextCard = 0;
	Card mDeck[mSize] = { 0 };
};

#endif
