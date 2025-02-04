#include <iostream>

bool isEven(int);

int main()
{
	std::cout << 1 << " is " << (isEven(1) ? "even" : "odd") << std::endl;
	std::cout << 2 << " is " << (isEven(2) ? "even" : "odd") << std::endl;
	std::cout << 3 << " is " << (isEven(3) ? "even" : "odd") << std::endl;
	std::cout << 4 << " is " << (isEven(4) ? "even" : "odd") << std::endl;
	std::cout << 5 << " is " << (isEven(5) ? "even" : "odd") << std::endl;

	return 0;
}

bool isEven(int n)
{
	return n % 2 == 0;
}
