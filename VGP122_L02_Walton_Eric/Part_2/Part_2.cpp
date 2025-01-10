#include "iostream"

int main()
{
	int counter = 0;
	int number = 0;
	int largest = 0;

	while (counter < 10)
	{
		counter = counter + 1;

		std::cout << "Enter the number of units sold by salesperson " << counter << ": ";
		std::cin >> number;

		if (number > largest)
			largest = number;
	}

	std::cout << "The largest number of units sold is " << largest << ". ";

	return 0;
}
