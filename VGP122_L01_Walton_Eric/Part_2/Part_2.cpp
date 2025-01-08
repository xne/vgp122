#include <iostream>

int main()
{
	// Part 2.
	std::cout << "Part 2." << std::endl;

	int a = 0;
	int b = 0;
	int product;

	// Ask for both integers
	std::cout << "\tEnter the first integer: ";
	std::cin >> a;

	std::cout << "\tEnter the second integer: ";
	std::cin >> b;

	std::cout << std::endl;

	// Calculate and print the sum
	product = a * b;
	std::cout << "\tProduct: " << product << std::endl;

	return 0;
}
