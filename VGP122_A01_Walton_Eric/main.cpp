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
Deck* deck;
Player* player;
Player* dealer;

// functions
void startGame();
void gameLoop();
void endGame();

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
	deck = new Deck();
	player = new Player();
	dealer = new Player();

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
	auto card = deck->draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player->addCard(card);

	card = deck->draw();
	std::cout << "Dealer is dealt: " << card << ". " << std::endl;
	dealer->addCard(card);

	card = deck->draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player->addCard(card);

	card = deck->draw();
	std::cout << "Dealer is dealt a card. " << std::endl;
	dealer->addCard(card);

	std::cout << std::endl;
}

void gameLoop()
{
	std::cout << "The value of your hand is: " << player->getHandValue() << ". " << std::endl;
	std::cout << "You may Hit (H), Stand (S), Split (P), Double Down (D), or Pass (X): ";

	char choice;
	std::cin >> choice;
	switch (std::toupper(choice))
	{
	case 'H':
		std::cout << "You chose to Hit. " << std::endl;
		break;
	case 'S':
		std::cout << "You chose to Stand. " << std::endl;
		break;
	case 'P':
		std::cout << "You chose to Split. " << std::endl;
		break;
	case 'D':
		std::cout << "You chose to Double Down. " << std::endl;
		break;
	case 'X':
		std::cout << "You chose to Pass. " << std::endl;
		break;
	default:
		break;
	}
}

void endGame()
{
	delete deck;
	delete player;
	delete dealer;
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
