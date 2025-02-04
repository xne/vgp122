#ifndef XN_UTIL
#define XN_UTIL

#include <iostream>
#include <string>

// get a valid integer between min and max from cin
int getInt(int min, int max)
{
	std::string tempStr;
	int tempInt;

	// loop until we return a valid integer
	while (true)
	{
		std::cin >> tempStr;

		try
		{
			tempInt = std::stoi(tempStr);

			// minimum and maximum value validation
			if (tempInt < min)
			{
				std::cout << "\tThe minimum is " << min << ": ";
				continue;
			}

			if (tempInt > max)
			{
				std::cout << "\tThe maximum is " << max << ": ";
				continue;
			}

			// integer validation
			if (tempStr.find('.') != std::string::npos)
			{
				std::cout << "\tMust be a whole number: ";
				continue;
			}

			return tempInt;
		}
		// std::stoi error handling
		catch (std::invalid_argument)
		{
			std::cout << "\tMust be a number: ";
		}
		catch (std::out_of_range)
		{
			std::cout << "\tThe maximum is " << max << ": ";
		}
	}
}

#endif