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

Card dealerSecondCard; // dealer's second card dealt
bool dealerSecondCardRevealed = false;

bool canHit;
bool canSplit;
bool canPass;
bool canDoubleDown;

Card playerFirstCard; // player's first card dealt
Card playerSecondCard;

// functions
bool startGame();
bool gameLoop(Player &);
void endGame();

void getBet();

void hit(Player &);
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

		while (gameLoop(player)) {};
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
	dealerSecondCardRevealed = false;
	canHit = true;
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

	playerFirstCard = card;

	card = deck.draw();
	std::cout << "Dealer is dealt: " << card << ". " << std::endl;
	dealer.addCard(card);

	card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player.addCard(card);

	playerSecondCard = card;

	// reveal the second card if the first card is a ten-card or an ace
	if (dealer.getHandValue() >= 10)
	{
		card = deck.draw();
		std::cout << "Dealer is dealt: " << card << ". " << std::endl;
		dealerSecondCardRevealed = true;
		dealer.addCard(card);
	}
	else
	{
		dealerSecondCard = deck.draw();
		std::cout << "Dealer is dealt a card. " << std::endl;
		dealer.addCard(dealerSecondCard);
	}

	std::cout << std::endl;

	// handle naturals
	if (player.getHandValue() == 21 && dealer.getHandValue() == 21)
	{
		if (!dealerSecondCardRevealed)
			std::cout << "Dealer has second card: " << dealerSecondCard << std::endl;
		std::cout << std::endl;
		std::cout << "It's a stand-off!" << std::endl;
		return false;
	}

	if (player.getHandValue() == 21)
	{
		std::cout << std::endl;
		std::cout << "Wow, you're a natural!" << std::endl;
		std::cout << "You collect " << bet * 1.5f << " credits. " << std::endl;
		credits += (int)(bet * 1.5f);
		return false;
	}
	
	if (dealer.getHandValue() == 21)
	{
		if (!dealerSecondCardRevealed)
			std::cout << "Dealer has second card: " << dealerSecondCard << std::endl;
		std::cout << std::endl;
		std::cout << "Dealer got a natural!" << std::endl;
		std::cout << "You lose " << bet << " credits. " << std::endl;
		credits -= bet;
		return false;
	}

	// check if we can double down
	canDoubleDown = credits >= bet * 2 && player.getHandValue() >= 9 && player.getHandValue() <= 11;

	// check if we can split
	canSplit = credits >= bet * 2 && playerFirstCard.value == playerSecondCard.value;

	return true;
}

bool gameLoop(Player &player)
{
	std::cout << "The value of your hand is: " << player.getHandValue() << ". " << std::endl;

	char choice = 'S';
	if (canHit)
	{
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

		choice = getOption(options.c_str());
	}

	switch (choice)
	{
	case 'H':
		hit(player);
		break;
	case 'S':
		stand();
		break;
	case 'P':
		split();
		return false;
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
	if (!dealerSecondCardRevealed)
	{
		std::cout << "Dealer has second card: " << dealerSecondCard << std::endl;
		dealerSecondCardRevealed = true;
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

	// can only pass, double down, or split on the first round
	canPass = false;
	canDoubleDown = false;
	canSplit = false;

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

void hit(Player &player)
{
	std::cout << "You chose to Hit. " << std::endl;
	std::cout << std::endl;

	auto card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player.addCard(card);
}

void stand()
{
	if (canHit) std::cout << "You chose to Stand. " << std::endl;
	else std::cout << "You must Stand. " << std::endl;
	std::cout << std::endl;
}

void split()
{
	std::cout << "You chose to Split. " << std::endl;
	std::cout << std::endl;

	// can't do any of these if we split
	canPass = false;
	canDoubleDown = false;
	canSplit = false;

	// check if we can hit
	canHit = playerFirstCard.value != 1;

	Player leftHand = {};
	leftHand.addCard(playerFirstCard);

	Player rightHand = {};
	rightHand.addCard(playerSecondCard);

	std::cout << "Let's play your left hand first. " << std::endl;

	auto card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	leftHand.addCard(card);

	// handle naturals
	if (leftHand.getHandValue() == 21)
	{
		std::cout << "Wow, you're a natural!" << std::endl;
		if (canHit)
		{
			std::cout << "You collect " << bet * 1.5f << " credits. " << std::endl;
			credits += (int)(bet * 1.5f);
		}
		else
		{
			std::cout << "You collect " << bet << " credits. " << std::endl;
			credits += bet;
		}
	}
	else while (gameLoop(leftHand)) {}

	std::cout << std::endl;
	std::cout << "Now, let's play your right hand. " << std::endl;

	dealer = {};
	dealerSecondCardRevealed = false;

	card = deck.draw();
	std::cout << "Dealer is dealt: " << card << ". " << std::endl;
	dealer.addCard(card);

	card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	rightHand.addCard(card);

	// reveal the second card if the first card is a ten-card or an ace
	if (dealer.getHandValue() >= 10)
	{
		card = deck.draw();
		std::cout << "Dealer is dealt: " << card << ". " << std::endl;
		dealerSecondCardRevealed = true;
		dealer.addCard(card);
	}
	else
	{
		dealerSecondCard = deck.draw();
		std::cout << "Dealer is dealt a card. " << std::endl;
		dealer.addCard(dealerSecondCard);
	}

	// handle naturals
	if (rightHand.getHandValue() == 21 && dealer.getHandValue() == 21)
	{
		if (!dealerSecondCardRevealed)
			std::cout << "Dealer has second card: " << dealerSecondCard << std::endl;
		std::cout << "It's a stand-off!" << std::endl;
	}
	else if (rightHand.getHandValue() == 21)
	{
		std::cout << "Wow, you're a natural!" << std::endl;
		if (canHit)
		{
			std::cout << "You collect " << bet * 1.5f << " credits. " << std::endl;
			credits += (int)(bet * 1.5f);
		}
		else
		{
			std::cout << "You collect " << bet << " credits. " << std::endl;
			credits += bet;
		}
	}
	else if (dealer.getHandValue() == 21)
	{
		if (!dealerSecondCardRevealed)
			std::cout << "Dealer has second card: " << dealerSecondCard << std::endl;
		std::cout << "Dealer got a natural!" << std::endl;
		std::cout << "You lose " << bet << " credits. " << std::endl;
		credits -= bet;
	}
	else while (gameLoop(rightHand)) {}
}

void doubleDown()
{
	std::cout << "You chose to Double Down. " << std::endl;
	std::cout << std::endl;

	bet *= 2;

	auto card = deck.draw();
	std::cout << "You are dealt: " << card << ". " << std::endl;
	player.addCard(card);
}

void pass()
{
	std::cout << "You chose to Pass. " << std::endl;
	std::cout << "You lose " << bet * 0.5f << " credits. " << std::endl;
	credits -= (int)(bet * 0.5f);
}
