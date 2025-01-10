#include "iostream"

int main()
{
	int account;
	float balance;
	float charges;
	float credits;
	float limit;

	// Program loop
	while (true)
	{
		std::cout << "Enter account number, or -1 to quit: ";
		std::cin >> account;

		// Exit condition
		if (account == -1)
			break;

		std::cout << "Enter starting balance: ";
		std::cin >> balance;

		std::cout << "Enter monthly charges: ";
		std::cin >> charges;

		std::cout << "Enter monthly credits: ";
		std::cin >> credits;

		std::cout << "Enter credit limit: ";
		std::cin >> limit;

		std::cout << std::endl;

		// Credit limit exceeded condition
		balance = balance + charges - credits;
		if (balance > limit)
		{
			std::cout << "Account number: " << account << std::endl;
			std::cout << "Credit limit: " << limit << std::endl;
			std::cout << "Balance: " << balance << std::endl;
			std::cout << "Credit Limit Exceeded" << std::endl;
		}
	}

	return 0;
}
