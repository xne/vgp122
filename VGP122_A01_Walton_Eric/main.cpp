#include <iostream>
#include <string>

void startGame();
void gameLoop();

int getInt(int, int);

const int minBet = 2;
const int maxBet = 500;
const int startingCredits = 1000;

int credits;
int bet;

int main()
{
	startGame();
	gameLoop();

	return 0;
}

void startGame()
{
	// setup
	credits = startingCredits;
	std::cout << "You have " << credits << " credits. " << std::endl;

	// starting bet
	std::cout << "Place your starting bet: ";
	if (credits < maxBet)
	{
		bet = getInt(minBet, credits);
	}
	else
	{
		bet = getInt(minBet, maxBet);
	}
}

void gameLoop()
{
}

// gets a valid integer between min and max from cin
int getInt(int min, int max)
{
	std::string tempStr;
	int tempInt;

	// loop until we return a valid integer
	while (true)
	{
		std::cin >> tempStr;

		try
		{
			tempInt = std::stoi(tempStr);

			// min-max validation
			if (tempInt < min)
			{
				std::cout << "\tThe minimum is " << min << ": ";
				continue;
			}
			
			if (tempInt > max)
			{
				std::cout << "\tThe maximum is " << max << ": ";
				continue;
			}
			
			// integer validation
			// find returns string::npos if the char is not found
			if (tempStr.find('.') != std::string::npos)
			{
				std::cout << "\tMust be a whole number: ";
				continue;
			}

			return tempInt;
		}
		// std::stoi error handling
		catch (std::invalid_argument)
		{
			std::cout << "\tMust be a number: ";
		}
		catch (std::out_of_range)
		{
			std::cout << "\tThe maximum is " << max << ": ";
		}
	}
}
