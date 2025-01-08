#include <iostream>

int main()
{
	// Part 1.
	std::cout << "Part 1." << std::endl;

	// Print with one stream insertion operator
	std::cout << "\t1 2 3 4";
	std::cout << std::endl;

	// Print with four stream insertion operators
	std::cout << "\t1" << " 2" << " 3" << " 4";
	std::cout << std::endl;

	// Print with four statements
	std::cout << "\t1";
	std::cout << " 2";
	std::cout << " 3";
	std::cout << " 4";
	std::cout << std::endl;

	return 0;
}
