#include <cmath>
#include <iostream>

int roundToInteger(float);
float roundToTenths(float);
float roundToHundredths(float);
float roundToThousandths(float);

int main()
{
	float n;
	while (true)
	{
		std::cout << "Enter a number to round, or 0 to exit: ";
		std::cin >> n;

		if (n == 0)
			return 0;

		std::cout << "You entered " << n << ", which rounds to ";
		std::cout << roundToInteger(n) << ", ";
		std::cout << roundToTenths(n) << ", ";
		std::cout << roundToHundredths(n) << ", or ";
		std::cout << roundToThousandths(n) << std::endl;
		std::cout << std::endl;
	}

	return 0;
}

int roundToInteger(float n)
{
	return int(n + 0.5);
}

float roundToTenths(float n)
{
	return std::floor(n * 10 + 0.5) / 10;
}

float roundToHundredths(float n)
{
	return std::floor(n * 100 + 0.5) / 100;
}

float roundToThousandths(float n)
{
	return std::floor(n * 1000 + 0.5) / 1000;
}
