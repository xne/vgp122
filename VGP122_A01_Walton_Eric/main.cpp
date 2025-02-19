#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>

#include "util.h"
#include "card.h"
#include "deck.h"
#include "player.h"

// constants
const unsigned short minBet = 2;
const unsigned short maxBet = 500;
const unsigned short startingCredits = 1000;

// variables
unsigned short credits;
unsigned short bet;
Deck deck;
Player player;
Player dealer;

// functions
void startGame();
void gameLoop();
void endGame();

void getBet();

void hit();
void stand();
void split();
void doubleDown();
void pass();

int main()
{
	char playAgain;
	do
	{
		startGame();
		gameLoop();
		endGame();

		std::cout << std::endl;
		std::cout << "Would you like to play again? (Y/N): ";
		std::cin >> playAgain;
	} while (std::toupper(playAgain) == 'Y');

	return 0;
}

void startGame()
{
	// setup
	deck = {};
	player = {};
	dealer = {};

	credits = startingCredits;
	std::cout << "You have " << credits << " credits. " << std::endl;
	std::cout << std::endl;

	// starting bet
	std::cout << "Place your starting bet: ";
	getBet();
	std::cout << "You bet " << bet << " credits. " << std::endl;
	std::cout << std::endl;

	// starting deal
	auto card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player.addCard(card);

	card = deck.draw();
	std::cout << "Dealer is dealt: " << card << ". " << std::endl;
	dealer.addCard(card);

	card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player.addCard(card);

	card = deck.draw();
	std::cout << "Dealer is dealt a card. " << std::endl;
	dealer.addCard(card);

	std::cout << std::endl;
}

void gameLoop()
{
	std::cout << "The value of your hand is: " << player.getHandValue() << ". " << std::endl;
	std::cout << std::endl;
	std::cout << "You may Hit (H), Stand (S), Split (P), Double Down (D), or Pass (X): ";

	char choice;
	std::cin >> choice;

	switch (std::toupper(choice))
	{
	case 'H':
		hit();
		break;
	case 'S':
		stand();
		break;
	case 'P':
		split();
		break;
	case 'D':
		doubleDown();
		break;
	case 'X':
		pass();
		break;
	default:
		break;
	}
}

void endGame()
{

}

void getBet()
{
	if (credits < maxBet)
		bet = getInt(minBet, credits);
	else
		bet = getInt(minBet, maxBet);

	credits -= bet;
}

void hit()
{
	std::cout << "You chose to Hit. " << std::endl;
	std::cout << std::endl;

	auto card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player.addCard(card);
}

void stand()
{
	std::cout << "You chose to Stand. " << std::endl;
	std::cout << std::endl;
}

void split()
{
	std::cout << "You chose to Split. " << std::endl;
	std::cout << std::endl;
}

void doubleDown()
{
	std::cout << "You chose to Double Down. " << std::endl;
	std::cout << std::endl;
}

void pass()
{
	std::cout << "You chose to Pass. " << std::endl;
	std::cout << std::endl;
}
