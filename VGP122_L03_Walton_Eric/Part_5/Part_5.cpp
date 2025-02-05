#include <cmath>
#include <iostream>

int toCelsius(int);
int toFahrenheit(int);

int main()
{
	std::cout << "C\tF" << std::endl;
	for (int i = 0; i <= 100; i++)
	{
		std::cout << i << "\t" << toFahrenheit(i) << std::endl;
	}
	std::cout << std::endl;

	std::cout << "F\tC" << std::endl;
	for (int i = 32; i <= 212; i++)
	{
		std::cout << i << "\t" << toCelsius(i) << std::endl;
	}

	return 0;
}

int toFahrenheit(int c)
{
	return std::round(c * (9.0f / 5) + 32);
}

int toCelsius(int f)
{
	return std::round((f - 32) * (5.0f / 9));
}
