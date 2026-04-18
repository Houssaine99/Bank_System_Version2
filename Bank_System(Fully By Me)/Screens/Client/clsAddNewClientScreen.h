#pragma once

#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"

class clsAddNewClientScreen : protected clsScreen
{
private:

	static std::string _ReadAccountNumber()
	{
		std::string AccountNumber;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Account Number? _");
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << clsUtil::ColorText(clsUtil::RED, "This account number is already exist! Enter another one? _");
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
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

public:

	static void ShowAddNewClientScreen()
	{
		if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pAddNewClient))
			return;

		_DrawScreenHeader("Add New Client Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string AccountNumber = _ReadAccountNumber();
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
		_ReadClientInfo(NewClient);
		NewClient.Save();

		std::cout << "\nClient Saved " << clsUtil::ColorText(clsUtil::LIGHTGREEN, " Successfully :-)\n");
		_PrintClientCard(NewClient);

		clsUtil::DrawLine('=', 110, 4);
	}
};

