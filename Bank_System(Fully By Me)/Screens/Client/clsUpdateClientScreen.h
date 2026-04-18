#pragma once

#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
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

	static void _PrintClientCard(clsBankClient& Client, bool IsUpdated = false)
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
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Status      : ";

		if (IsUpdated)
			std::cout << clsUtil::ColorText(clsUtil::RED, "Updated!") << std::endl;
		else
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Ready To Update") << std::endl;

		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

	static void _ReadClientInfo(clsBankClient& Client)
	{
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nEnter Client First Name: ");
		Client.FirstName = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Client Last Name: ");
		Client.LastName = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Client Email: ");
		Client.Email = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Client Phone: ");
		Client.Phone = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Client PIN Code: ");
		Client.PINCode = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Client Account Balance ($): ");
		Client.AccountBalance = clsInputValidate::ReadFltNumber();
	}


public:

	static void ShowUpdateClientScreen()
	{
		if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pUpdateClient))
			return;

		_DrawScreenHeader("Update Client Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string AccountNumber = _ReadAccountNumber();
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientCard(Client);

		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Update The Client Info\n";
		clsUtil::DrawLine('-', 25);
		_ReadClientInfo(Client);

		Client.Save();
		std::cout << "\nClient Updated " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)\n");

		_PrintClientCard(Client, true);

		clsUtil::DrawLine('=', 110, 4);
	}


};

