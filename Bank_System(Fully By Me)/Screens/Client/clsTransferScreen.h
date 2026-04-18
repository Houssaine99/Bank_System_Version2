#pragma once

#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

	static std::string _ReadAccountNumber()
	{
		std::string AccountNumber;
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
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Full Name   : " << Client.FullName() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Acc. Number : " << Client.AccountNumber() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Balance     : " << clsUtil::ColorText(clsUtil::LIGHTGREEN, std::to_string(Client.AccountBalance) + " $\n");
		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

	static float _ReadAmount(float S_AccBalance)
	{
		float Amount;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Transfer Amount($)? _");
		Amount = clsInputValidate::ReadFltPostiveNumber();

		while (S_AccBalance < Amount)
		{
			std::cout << clsUtil::ColorText(clsUtil::RED, "Amount Exceeds Available Balance! Enter Another Amount? _");
			Amount = clsInputValidate::ReadFltPostiveNumber();
		}

		return Amount;
	}

	static clsBankClient _GetClient(std::string Message)
	{
		std::string AccountNumber;

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, Message);
		AccountNumber = _ReadAccountNumber();

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientCard(Client);

		return Client;
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

	static void ShowTransferLogScreen()
	{
		float Amount = 0;

		_DrawScreenHeader("Transfer Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		clsBankClient SourceClient = _GetClient("\nPlease Enter Account Number To Transfer From: _");
		clsBankClient DestinationClient = _GetClient("\nPlease Enter Account Number To Transfer To: _");

		Amount = _ReadAmount(SourceClient.AccountBalance);

		if (_ConfirmationMessage())
		{
			SourceClient.Transfer(Amount, DestinationClient, CurrentUser.Username);
			std::cout << "\nTransfer Done " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)") << ".\n";
			_PrintClientCard(SourceClient);
			_PrintClientCard(DestinationClient);
		}
		else
			std::cout << "\nOperation Was " << clsUtil::ColorText(clsUtil::RED, "Cancelled!\n");

		std::cout << "\n";
		clsUtil::DrawLine('=', 110, 4);
		
	}
};

