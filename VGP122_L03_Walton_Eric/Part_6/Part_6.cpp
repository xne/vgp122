#include <iostream>

bool checkNumber(int);
bool checkArray(int);

const unsigned int arraySize = 20;
int array[20] = { 0 };

int main()
{
	int temp;

	for (int i = 0; i < arraySize; i++)
	{
		std::cout << "Enter integer number " << i + 1 << ": ";
		std::cin >> temp;
		if (checkNumber(temp))
			if (!checkArray(temp))
				array[i] = temp;
	}

	std::cout << "The unique numbers between 10 and 100 inclusive you entered were: " << std::endl;
	for (int i = 0; i < arraySize; i++)
		if (array[i] != 0)
			std::cout << array[i] << ", ";
	std::cout << std::endl;

	return 0;
}

bool checkNumber(int n)
{
	return n >= 10 && n <= 100;
}

bool checkArray(int n)
{
	for (int i = 0; i < arraySize; i++)
		if (array[i] == n) return true;

	return false;
}
