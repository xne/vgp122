#include <concepts>
#include <iostream>
#include <numeric>
#include <string>

class Rational
{
public:
	constexpr Rational(int numerator = 1, int denominator = 1)
	{
		int gcd = std::gcd(numerator, denominator);

		this->numerator = numerator / gcd;
		this->denominator = denominator / gcd;
	}

	constexpr Rational operator+(const Rational& rhs) const noexcept
	{
		if (denominator == rhs.denominator)
			return Rational{ numerator + rhs.numerator, denominator };

		return Rational
		{
			numerator * rhs.denominator + rhs.numerator * denominator,
			denominator * rhs.denominator
		};
	}

	constexpr Rational operator-(const Rational& rhs) const noexcept
	{
		if (denominator == rhs.denominator)
			return Rational{ numerator - rhs.numerator, denominator };

		return Rational
		{
			numerator * rhs.denominator - rhs.numerator * denominator,
			denominator * rhs.denominator
		};
	}

	constexpr Rational operator*(const Rational& rhs) const noexcept
	{
		return Rational
		{
			numerator * rhs.numerator,
			denominator * rhs.denominator
		};
	}

	constexpr Rational operator/(const Rational& rhs) const noexcept
	{
		return *this * rhs.reciprocal();
	}

	template<std::floating_point T>
	explicit constexpr operator T() const noexcept
	{
		return static_cast<T>(numerator) / static_cast<T>(denominator);
	}

	friend std::ostream& operator<<(std::ostream& os, const Rational& r)
	{
		os << r.to_string();
		return os;
	}

	std::string to_string() const
	{
		return std::to_string(numerator) + '/' + std::to_string(denominator);
	}

	Rational reciprocal() const
	{
		return Rational{ denominator, numerator };
	}

private:
	int numerator;
	int denominator;
};

int main()
{
	Rational r{ 2, 4 };
	std::cout << "Creating rational number from 2/4: " << r << std::endl;

	r = r + Rational{ 2, 5 };
	std::cout << "Adding 2/5: " << r << std::endl;

	r = r - Rational{ 10, 100 };
	std::cout << "Subtracting 10/100: " << r << std::endl;

	r = r * Rational{ 2, 1 };
	std::cout << "Multiplying by 2/1: " << r << std::endl;

	r = r / Rational{ 4, 1 };
	std::cout << "Dividing by 4/1: " << r << std::endl;

	std::cout << "As double: " << static_cast<double>(r) << std::endl;

	return 0;
}
