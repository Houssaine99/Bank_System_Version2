#pragma once

#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{
private:

	static std::string _ReadAccountNumber()
	{
		std::string AccountNumber;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Account Number? _");
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << clsUtil::ColorText(clsUtil::RED, "This account number is not found! Enter another one? _");
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static void _PrintClientCard(clsBankClient& Client)
	{
		std::cout << "\n";
		clsUtil::DrawCardLine();
		std::cout << "\n" << std::left << std::setw(9) << "" << "Client Card\n";
		clsUtil::DrawCardLine();
		std::cout << "\n";
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "FirstName   : " << Client.FirstName << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "LastName    : " << Client.LastName << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Full Name   : " << Client.FullName() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Email       : " << Client.Email << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Phone       : " << Client.Phone << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Password    : " << Client.PINCode << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Balance     : " << clsUtil::ColorText(clsUtil::LIGHTGREEN, std::to_string(Client.AccountBalance) + " $\n");
		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

	static float _ReadAmount()
	{
		float Amount;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Withdraw Amount($)? _");
		Amount = clsInputValidate::ReadFltPostiveNumber();

		return Amount;
	}

	static bool _ConfirmationMessage()
	{
		char Answer = 'n';

		std::cout << "\nAre you sure you want to perform this operation " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[y/n]") << "? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return true;
		else
			return false;
	}

public:

	static void ShowWithdrawScreen()
	{
		std::string AccountNumber;
		float Amount = 0;

		_DrawScreenHeader("Withdraw Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		AccountNumber = _ReadAccountNumber();
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientCard(Client);

		Amount = _ReadAmount();

		if (_ConfirmationMessage())
		{
			if (Client.Withdraw(Amount))
			{
				std::cout << "\nOperation Done " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)\n");
			}
			else
			{
				std::cout << clsUtil::ColorText(clsUtil::RED, "\nCannot withdraw! Insuffecient Balance!\n");
				std::cout << "\nAmount to withdraw = " << clsUtil::ColorText(clsUtil::RED, std::to_string(Amount) + "$\n");
				std::cout << "Client Balance = " << clsUtil::ColorText(clsUtil::LIGHTGREEN, std::to_string(Client.AccountBalance) + "$\n");
			}
		}
		else
			std::cout << "\nOperation Was " << clsUtil::ColorText(clsUtil::RED, "Cancelled!\n");

		std::cout << "\n";
		clsUtil::DrawLine('=', 110, 4);
	}
};

