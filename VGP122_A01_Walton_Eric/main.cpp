#include <algorithm>
#include <iostream>
#include <random>

#include "util.h"
#include "card.h"

// constants
const unsigned short minBet = 2;
const unsigned short maxBet = 500;
const unsigned short startingCredits = 1000;

const unsigned char cardSuits[] = { 'C', 'D', 'H', 'S' };
const unsigned short cardValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

const unsigned short deckSize = 52;

// the maximum number of cards a player can hold without going over 21
const unsigned short maxHandSize = 11;

// variables
unsigned short credits;
unsigned short bet;
Card deck[deckSize] = { 0 };
Card dealer[maxHandSize] = { 0 };
Card hand[maxHandSize] = { 0 };

// functions
void startGame();
void gameLoop();
void initDeck();
Card draw();
void addToHand(Card);
void addToDealer(Card);
unsigned short getHandValue();

void hit();
void stand();
void split();
void doubleDown();
void pass();

int main()
{
	startGame();
	gameLoop();

	return 0;
}

void startGame()
{
	// setup
	initDeck();
	credits = startingCredits;
	std::cout << "You have " << credits << " credits. " << std::endl;
	std::cout << std::endl;

	// starting bet
	std::cout << "Place your starting bet: ";
	if (credits < maxBet)
		bet = getInt(minBet, credits);
	else
		bet = getInt(minBet, maxBet);
	std::cout << "You bet " << bet << " credits. " << std::endl;
	std::cout << std::endl;

	// starting deal
	Card card = draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	addToHand(card);

	card = draw();
	std::cout << "Dealer is dealt: " << card << ". " << std::endl;
	addToDealer(card);

	card = draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	addToHand(card);

	card = draw();
	std::cout << "Dealer is dealt a card. " << std::endl;
	addToDealer(card);

	std::cout << std::endl;
}

void gameLoop()
{
	std::cout << "The value of your hand is: " << getHandValue() << ". " << std::endl;
	std::cout << "You may Hit (H), Stand (S), Split (P), Double Down (D), or Pass (X): ";
}

void initDeck()
{
	// init deck array
	unsigned short index = 0;
	for (unsigned char suit : cardSuits)
		for (unsigned short value : cardValues)
			deck[index++] = { suit, value };

	// shuffle
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(deck, deck + deckSize, g);
}

Card draw()
{
	static unsigned short index = 0;
	return deck[index++];
}

void addToHand(Card card)
{
	static unsigned short index = 0;
	hand[index++] = card;
}

void addToDealer(Card card)
{
	static unsigned short index = 0;
	dealer[index++] = card;
}

unsigned short getHandValue()
{
	unsigned short result = 0;
	unsigned short aces = 0;

	// find hand total when aces have a value of 1
	for (Card card : hand)
	{
		if (card.value == 1)
			aces++;

		if (card.value > 10)
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

void hit()
{

}

void stand()
{

}

void split()
{

}

void doubleDown()
{

}

void pass()
{

}
