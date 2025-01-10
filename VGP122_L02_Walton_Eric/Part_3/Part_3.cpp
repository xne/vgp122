#include "iostream"

int main()
{
	int total;
	int counter = 0;
	int smallest;
	int number;

	std::cout << "Enter the number of integers to compare: ";
	std::cin >> total;

	if (total < 1)
		return 0;


	std::cout << "Enter number " << counter + 1 << ": ";
	std::cin >> smallest;
	counter = counter + 1;

	while (counter < total)
	{
		std::cout << "Enter number " << counter + 1 << ": ";
		std::cin >> number;

		if (number < smallest)
			smallest = number;

		counter = counter + 1;
	}

	std::cout << "The smallest number is " << smallest << ". ";

	return 0;
}
