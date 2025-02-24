#include <iostream>

void factorial(int*, unsigned long long*);

int main()
{
	int num;
	unsigned long long result;

	std::cout << "Enter a positive integer: ";
	std::cin >> num;

	if (num < 0) return 1;

	factorial(&num, &result);

	std::cout << "Factorial of " << num << " is " << result;

	return 0;
}

void factorial(int* num, unsigned long long* result)
{
	*result = 1;

	for (int i = 1; i <= *num; i++) *result *= i;
}
