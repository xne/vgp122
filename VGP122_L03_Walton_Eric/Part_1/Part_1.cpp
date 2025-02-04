#include <iostream>

int calculateCharges(float hoursParked);

int main()
{
	unsigned int numCars = 3;
	float *hoursParked = new float[numCars];

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Hours parked for car " << i + 1 << ": ";
		std::cin >> hoursParked[i];
	}
	std::cout << std::endl;

	float totalHours = 0.0f;
	float totalCharges = 0.0f;

	std::cout << "Car\tHours\tCharge" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		totalHours += hoursParked[i];
		totalCharges += calculateCharges(hoursParked[i]);
		std::cout << i + 1 << "\t" << hoursParked[i] << "\t" << calculateCharges(hoursParked[i]) << std::endl;
	}
	std::cout << "Total\t" << totalHours << "\t" << totalCharges << std::endl;

	delete[] hoursParked;
	return 0;
}

int calculateCharges(float hoursParked)
{
	// Minimum $20 charge for up to three hours
	int result = 20;

	// $5 charge for each additional hour, rounded up
	if (hoursParked > 3)
		result += 5 * std::ceil(hoursParked - 3);

	// Maximum $50 charge
	result = std::min(result, 50);

	return result;
}
