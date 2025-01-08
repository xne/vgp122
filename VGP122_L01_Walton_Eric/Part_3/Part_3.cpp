#include <iostream>

int main()
{
	// Part 3.
	std::cout << "Part 3." << std::endl;

	float a = 0.0f;
	float b = 0.0f;
	float sum, product, difference, quotient;

	// Ask for both numbers
	std::cout << "\tEnter the first number: ";
	std::cin >> a;

	std::cout << "\tEnter the second number: ";
	std::cin >> b;

	std::cout << std::endl;

	// Calculate and print the sum, product, difference, and quotient
	sum = a + b;
	std::cout << "\tSum: " << sum << std::endl;

	product = a * b;
	std::cout << "\tProduct: " << product << std::endl;

	difference = a - b;
	std::cout << "\tDifference: " << difference << std::endl;

	quotient = a / b;
	std::cout << "\tQuotient: " << quotient << std::endl;

	return 0;
}
