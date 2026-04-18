#pragma once

#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
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

	static void _PrintClientCard(clsBankClient& Client, bool IsDeleted = false)
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

		if (IsDeleted)
			std::cout << clsUtil::ColorText(clsUtil::RED, "Deleted!") << std::endl;
		else
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Selected") << std::endl;

		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

	static bool _ConfirmationMessage()
	{
		char Answer = 'n';

		std::cout << "\nAre you sure you want to delete this client " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[y/n]") << "? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return true;
		else
			return false;
	}

public:

	static void ShowDeleteClientScreen()
	{
		if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pDeleteClient))
			return;
		
		_DrawScreenHeader("Delete Client Screen");
		
		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string AccountNumber = _ReadAccountNumber();
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		
		_PrintClientCard(Client);

		if (_ConfirmationMessage())
		{
			Client.Delete();
			std::cout << "\nClient Was Deleted " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)\n");
			_PrintClientCard(Client, true);
		}
		else
			std::cout << "\nThis Operation Was " << clsUtil::ColorText(clsUtil::RED, "Canclled!\n");

		clsUtil::DrawLine('=', 110, 4);
	}
};

