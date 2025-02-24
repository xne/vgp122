#include <cctype>
#include <cstring>
#include <iostream>

const char* consonants = "bcdfghjklmnpqrstvwxz";
const char* vowels = "aeiouy";

const char* str = "The quick brown fox";

int main()
{
	int numc = 0;
	int numv = 0;

	for (int i = 0; i < std::strlen(str); i++)
	{
		for (int j = 0; j < std::strlen(vowels); j++)
			if (std::tolower(str[i]) == vowels[j]) numv++;

		for (int j = 0; j < std::strlen(consonants); j++)
			if (std::tolower(str[j]) == consonants[j]) numc++;
	}

	std::cout << "Number of consonants in \"" << str << "\": " << numc << std::endl;
	std::cout << "Number of vowels: " << numv;

	return 0;
}
