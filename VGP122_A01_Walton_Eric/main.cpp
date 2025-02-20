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

bool canSplit = false;
bool canPass = true;
bool canDoubleDown = false;

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
	canPass = true;

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

	// reveal the second card if the first card is a ten-card or an ace
	if (dealer.getHandValue() >= 10)
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
		std::cout << "You collect " << bet * 1.5f << " credits. " << std::endl;
		credits += bet * 1.5f;
		return false;
	}
	else if (dealer.getHandValue() == 21)
	{
		if (!secondCardRevealed)
			std::cout << "Dealer has second card: " << secondCard << std::endl;
		std::cout << "Bust! You lose " << bet << " credits. " << std::endl;
		credits -= bet;
		return false;
	}

	return true;
}

bool gameLoop()
{
	std::cout << "The value of your hand is: " << player.getHandValue() << ". " << std::endl;
	std::cout << std::endl;

	std::cout << "You may Hit (H), Stand (S)";
	std::string options = "HS";

	if (canSplit)
	{
		std::cout << ", Split (P)";
		options += "P";
	}

	if (canDoubleDown)
	{
		std::cout << ", Double Down (D)";
		options += "D";
	}

	if (canPass)
	{
		std::cout << ", Pass (X)";
		options += "X";
	}

	std::cout << ": ";

	char choice = getOption(options.c_str());

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
		return false;
	}

	// handle blackjack and 21 stand-off
	if (player.getHandValue() == 21)
	{
		if (dealer.getHandValue() != 21)
		{
			std::cout << "Blackjack!" << std::endl;
			std::cout << "You collect " << bet << " credits. " << std::endl;
			credits += bet;
		}
		else
		{
			std::cout << "It's a stand-off!" << std::endl;
		}

		return false;
	}

	// handle bust
	if (player.getHandValue() > 21)
	{
		std::cout << "Bust! You lose " << bet << " credits. " << std::endl;
		credits -= bet;
		return false;
	}

	// reveal the dealer's second card, if we haven't already
	if (!secondCardRevealed)
	{
		std::cout << "Dealer has second card: " << secondCard << std::endl;
		secondCardRevealed = true;
	}

	// handle round loss
	if (choice == 'S' && dealer.getHandValue() > player.getHandValue())
	{
		std::cout << "You lost the round!" << std::endl;
		std::cout << "You lose " << bet << " credits. " << std::endl;
		credits -= bet;
		return false;
	}
	
	// dealer must hit
	if (dealer.getHandValue() < 17)
	{
		auto card = deck.draw();
		std::cout << "Dealer is dealt: " << card << ". " << std::endl;
		dealer.addCard(card);

		// handle dealer bust
		if (dealer.getHandValue() > 21)
		{
			std::cout << "You win the round!" << std::endl;
			std::cout << "You collect " << bet << " credits. " << std::endl;
			credits += bet;
			return false;
		}
	}
	// dealer must stand
	else
	{
		std::cout << "Dealer must stand. " << std::endl;

		// handle round win
		if (player.getHandValue() > dealer.getHandValue())
		{
			std::cout << "You win the round!" << std::endl;
			std::cout << "You collect " << bet << " credits. " << std::endl;
			credits += bet;
			return false;
		}
		
		// handle stand-off
		if (choice == 'S' && dealer.getHandValue() == player.getHandValue())
		{
			std::cout << "It's a stand-off!" << std::endl;
			return false;
		}
	}

	// can only pass on the first round
	canPass = false;

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
	std::cout << "You lose " << bet * 0.5f << " credits. " << std::endl;
	credits -= bet * 0.5f;
	std::cout << std::endl;
}
