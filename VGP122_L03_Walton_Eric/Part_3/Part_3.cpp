#include <cmath>
#include <iostream>

double hypotenuse(double, double);

int main()
{
	std::cout << "Tri\tSide 1\tSide 2\tHyp" << std::endl;
	std::cout << 1 << "\t" << 3.0f << "\t" << 4.0f << "\t" << hypotenuse(3.0f, 4.0f) << std::endl;
	std::cout << 2 << "\t" << 5.0f << "\t" << 12.0f << "\t" << hypotenuse(5.0f, 12.0f) << std::endl;
	std::cout << 3 << "\t" << 8.0f << "\t" << 15.0f << "\t" << hypotenuse(8.0f, 15.0f) << std::endl;
}

double hypotenuse(double a, double b)
{
	return std::sqrt(a * a + b * b);
}
