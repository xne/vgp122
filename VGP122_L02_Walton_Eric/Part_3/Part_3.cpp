#include "iostream"

int main()
{
	int total;
	int counter = 1;
	int smallest;
	int number;

	std::cout << "Enter the number of integers to compare: ";
	std::cin >> total;

	if (total < 1)
		return 0;

	std::cout << "Enter number " << counter << ": ";
	std::cin >> smallest;

	while (counter < total)
	{
		counter = counter + 1;

		std::cout << "Enter number " << counter << ": ";
		std::cin >> number;

		if (number < smallest)
			smallest = number;
	}

	std::cout << "The smallest number is " << smallest << ". ";

	return 0;
}
