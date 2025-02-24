#include <cstdlib>
#include <iostream>
#include <memory>

int main()
{
	int size;
	std::cout << "Enter an array size greater than 1: ";
	std::cin >> size;

	if (size < 2) return 1;

	int* arr = (int*)std::malloc(size * sizeof(int));

	if (arr == NULL) return 1;

	for (int i = 0; i < size; i++)
	{
		std::cout << "Number " << i + 1 << ": ";
		std::cin >> arr[i];
	}

	int max = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[max] < arr[i])
			max = i;
	}

	std::cout << "Max is " << arr[max] << " at address " << std::addressof(arr[max]);

	std::free(arr);

	return 0;
}
