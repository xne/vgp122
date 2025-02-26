#include <iostream>

class SavingsAccount
{
public:
	SavingsAccount(float balance) : balance(balance) {}

	static void modifyInterestRate(float newInterestRate)
	{
		annualInterestRate = newInterestRate;
	}

	float calculateMonthlyInterest()
	{
		float monthlyInterest = balance * annualInterestRate / 12.f;
		balance += monthlyInterest;
		return monthlyInterest;
	}

private:
	static float annualInterestRate;
	float balance;
};

float SavingsAccount::annualInterestRate = 0.03f;

int main()
{
	SavingsAccount saver1{ 2000.f };
	SavingsAccount saver2{ 3000.f };

	std::cout << "Saver1 month 1 interest: $" << saver1.calculateMonthlyInterest() << std::endl;
	std::cout << "Saver2 month 1 interest: $" << saver2.calculateMonthlyInterest() << std::endl;

	SavingsAccount::modifyInterestRate(0.04f);

	std::cout << "Saver1 month 2 interest: $" << saver1.calculateMonthlyInterest() << std::endl;
	std::cout << "Saver2 month 2 interest: $" << saver2.calculateMonthlyInterest() << std::endl;

	return 0;
}
