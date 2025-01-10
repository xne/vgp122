#include "iostream"

int main()
{
	int counter = 0;
	int total = 20;

	long long factorial = 1;

	while (counter < total)
	{
		counter = counter + 1;

		factorial = factorial * counter;

		std::cout << counter << "! \t = " << factorial << std::endl;
	}

	return 0;
}
