#ifndef XN_CARD
#define XN_CARD

#include <iostream>

struct Card
{
public:
	unsigned char suit;
	unsigned short value;
};

// implement operator <<
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	switch (card.value)
	{
	case 1:
		os << "Ace";
		break;
	case 11:
		os << "Jack";
		break;
	case 12:
		os << "Queen";
		break;
	case 13:
		os << "King";
		break;
	default:
		os << card.value;
	}

	os << " of ";

	switch (card.suit)
	{
	case 'C':
		os << "Clubs";
		break;
	case 'D':
		os << "Diamonds";
		break;
	case 'H':
		os << "Hearts";
		break;
	case 'S':
		os << "Spades";
		break;
	}

	return os;
}

#endif
