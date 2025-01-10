#include "iostream"

int main()
{
	int counter = 0;
	int number = 0;
	int largest = 0;

	while (counter < 10)
	{
		std::cout << "Enter the number of units sold by salesperson " << counter + 1 << ": ";
		std::cin >> number;

		if (number > largest)
			largest = number;

		counter = counter + 1;
	}

	std::cout << "The largest number of units sold is " << largest << ". ";

	return 0;
}
