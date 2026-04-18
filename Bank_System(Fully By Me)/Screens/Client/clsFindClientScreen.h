#pragma once

#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{
private:

	static std::string _ReadAccountNumber()
	{
		std::string AccountNumber;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Account Number? _");
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "Client " << clsUtil::ColorText(clsUtil::RED, "not found :-(\n") << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter another account number? _");
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

public:

	static void ShowFindClientScreen()
	{
		if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pFindClient))
			return;

		_DrawScreenHeader("Find Client Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string AccountNumber = _ReadAccountNumber();
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		std::cout << "\nClient " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Found :-)\n");
		_PrintClientCard(Client);

		clsUtil::DrawLine('=', 110, 4);
	}
};

