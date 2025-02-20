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
unsigned short credits = startingCredits;
unsigned short bet;
Deck deck;
Player player;
Player dealer;
char playAgain;

Card secondCard;
bool secondCardRevealed = false;

// functions
bool startGame();
bool gameLoop();
void endGame();

void getBet();

void hit();
void stand();
void split();
void doubleDown();
void pass();

int main()
{
	std::cout << "Welcome to Blackjack!" << std::endl;
	do
	{
		if (!startGame())
		{
			endGame();
			continue;
		}

		while (gameLoop()) {};
		endGame();
	} while (playAgain == 'Y');

	return 0;
}

bool startGame()
{
	// setup
	deck = {};
	player = {};
	dealer = {};
	secondCardRevealed = false;

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

	if (dealer.getHandValue() == 1 || dealer.getHandValue() == 10)
	{
		card = deck.draw();
		std::cout << "Dealer is dealt: " << card << ". " << std::endl;
		secondCardRevealed = true;
		dealer.addCard(card);
	}
	else
	{
		secondCard = deck.draw();
		std::cout << "Dealer is dealt a card. " << std::endl;
		dealer.addCard(secondCard);
	}

	std::cout << std::endl;

	// handle naturals
	if (player.getHandValue() == 21 && dealer.getHandValue() == 21)
	{
		if (!secondCardRevealed)
			std::cout << "Dealer has second card: " << secondCard << std::endl;
		std::cout << "It's a stand-off!" << std::endl;
		return false;
	}
	else if (player.getHandValue() == 21)
	{
		std::cout << "Wow, you're a natural!" << std::endl;
		return false;
	}
	else if (dealer.getHandValue() == 21)
	{
		if (!secondCardRevealed)
			std::cout << "Dealer has second card: " << secondCard << std::endl;
		std::cout << "Bust!" << std::endl;
		return false;
	}

	return true;
}

bool gameLoop()
{
	std::cout << "The value of your hand is: " << player.getHandValue() << ". " << std::endl;
	std::cout << std::endl;

	std::cout << "You may Hit (H), Stand (S), Split (P), Double Down (D), or Pass (X): ";

	char choice = getOption("HSPDX");

	switch (choice)
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
	}

	if (player.getHandValue() == 21)
	{
		if (dealer.getHandValue() != 21)
		{
			std::cout << "Blackjack!" << std::endl;
		}
		else
		{
			std::cout << "It's a stand-off!" << std::endl;
		}

		return false;
	}

	if (player.getHandValue() > 21)
	{
		std::cout << "Bust!" << std::endl;
		return false;
	}

	if (!secondCardRevealed)
	{
		std::cout << "Dealer has second card: " << secondCard << std::endl;
		secondCardRevealed = true;
	}

	return true;
}

void endGame()
{
	if (credits > minBet)
	{
		std::cout << std::endl;
		std::cout << "Would you like to play again? (Y/N): ";
		playAgain = getOption("YN");
	}
	else
	{
		std::cout << "Out of credits!" << std::endl;
		playAgain = 'N';
	}
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
