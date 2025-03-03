#include <concepts>
#include <iostream>
#include <numeric>
#include <string>
#include <stdexcept>

// type can be any integral type (C++20)
template <std::integral T>
class Rational
{
public:
	constexpr Rational(T numerator = 1, T denominator = 1)
	{
		// prevent zero numerator
		if (numerator == 0)
			throw std::invalid_argument("Numerator can not be zero. ");

		// prevent zero denominator
		if (denominator == 0)
			throw std::invalid_argument("Denominator can not be zero. ");

		// avoid negative denominator
		if (denominator < 0)
		{
			numerator = -numerator;
			denominator = -denominator;
		}

		// find greatest common denominator (C++17)
		T gcd = std::gcd(numerator, denominator);

		this->numerator = numerator / gcd;
		this->denominator = denominator / gcd;
	}

	constexpr Rational operator+(const Rational& rhs) const noexcept
	{
		// shortcut if denominators are equal
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
		// shortcut if denominators are equal
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

	// type can be any floating point type (C++20)
	template<std::floating_point T>
	explicit constexpr operator T() const noexcept
	{
		return static_cast<T>(numerator) / static_cast<T>(denominator);
	}

	// three-way comparison (spaceship) operator (C++20)
	constexpr auto operator<=>(const Rational& rhs) const noexcept
	{
		return static_cast<double>(*this) <=> static_cast<double>(rhs);
	}

	// == operator automatically provides != as well
	constexpr bool operator==(const Rational& rhs) const noexcept
	{
		return (*this <=> rhs) == 0;
	}

	friend std::ostream& operator<<(std::ostream& os, const Rational& r)
	{
		os << r.to_string();
		return os;
	}

	std::string to_string() const
	{
		if (numerator > denominator)
			return std::to_string(numerator % denominator) + ' ' + std::to_string(numerator / denominator) + '/' + std::to_string(denominator);
		return std::to_string(numerator) + '/' + std::to_string(denominator);
	}

	Rational reciprocal() const
	{
		return Rational{ denominator, numerator };
	}

private:
	T numerator;
	T denominator;
};

const char* boolToStr(bool b)
{
	return b ? "True" : "False";
}

int main()
{
	std::cout << "Rational(4, 8): ";
	std::cout << Rational{ 4, 8 } << std::endl;
	
	std::cout << "Rational(0, 1): ";
	try
	{
		std::cout << Rational{ 0, 1 } << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << "Caught exception: " << ex.what() << std::endl;
	}

	std::cout << "Rational(1, 0): ";
	try
	{
		std::cout << Rational{ 1, 0 } << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << "Caught exception: " << ex.what() << std::endl;
	}

	std::cout << "Rational(1, -2): ";
	std::cout << Rational{ 1, -2 } << std::endl;

	Rational r1{ 1, 2 };
	Rational r2{ 3, 4 };

	std::cout << "1/2 + 3/4: ";
	std::cout << r1 + r2 << std::endl;

	std::cout << "1/2 - 3/4: ";
	std::cout << r1 - r2 << std::endl;

	std::cout << "1/2 * 3/4: ";
	std::cout << r1 * r2 << std::endl;

	std::cout << "1/2 / 3/4: ";
	std::cout << r1 / r2 << std::endl;

	std::cout << "static_cast<double>(1/2): ";
	std::cout << static_cast<double>(r1) << std::endl;

	std::cout << "1/2 > 3/4: ";
	std::cout << boolToStr(r1 > r2) << std::endl;

	std::cout << "1/2 >= 3/4: ";
	std::cout << boolToStr(r1 >= r2) << std::endl;

	std::cout << "1/2 < 3/4: ";
	std::cout << boolToStr(r1 < r2) << std::endl;

	std::cout << "1/2 <= 3/4: ";
	std::cout << boolToStr(r1 <= r2) << std::endl;

	std::cout << "1/2 == 3/4: ";
	std::cout << boolToStr(r1 == r2) << std::endl;

	std::cout << "1/2 != 3/4: ";
	std::cout << boolToStr(r1 != r2) << std::endl;

	return 0;
}
