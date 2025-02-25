#include <iostream>

class Date
{
public:
	Date(int month, int day, int year)
	{
		setMonth(month);
		setDay(day);
		setYear(year);
	}

	int getYear() const
	{
		return year;
	}

	void setYear(int year)
	{
		this->year = year;
	}

	int getMonth() const
	{
		return month;
	}

	void setMonth(int month)
	{
		this->month = (month < 1 || month > 12) ? 1 : month;
	}

	int getDay() const
	{
		return day;
	}

	void setDay(int day)
	{
		this->day = day;
	}

	static friend std::ostream &operator<<(std::ostream& os, const Date& d)
	{
		os << d.month << '/' << d.day << '/' << d.year;
		return os;
	}

private:
	int year;
	int month;
	int day;
};

int main()
{
	Date d = { 1, 1, 2000 };

	std::cout << "Date created: " << d << std::endl;

	d.setMonth(12);
	d.setDay(31);
	d.setYear(1999);

	std::cout << "Date set: " << d << std::endl;

	return 0;
}
