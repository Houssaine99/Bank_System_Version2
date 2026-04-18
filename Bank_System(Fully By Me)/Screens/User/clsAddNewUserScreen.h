#pragma once

#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"

class clsAddNewUserScreen : protected clsScreen
{
private:

	static std::string _ReadUsername()
	{
		std::string Username;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Username? _");
		Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			std::cout << clsUtil::ColorText(clsUtil::RED, "This username is already exist! Enter another one? _");
			Username = clsInputValidate::ReadString();
		}

		return Username;
	}

	static char _GetUserAnswer(std::string Question)
	{
		char Answer = 'Y';
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, Question) << " ";
		std::cout << clsUtil::ColorText(clsUtil::BLUE, "[y/n]") << clsUtil::ColorText(clsUtil::LIGHTGREEN, "? _");
		std::cin >> Answer;

		return Answer;
	}

	static int _ReadPermissionsToSet()
	{
		short Permissions = 0;
		

		if (toupper(_GetUserAnswer("\nDo you want to give full access")) == 'Y')
			return clsUser::enPermissions::eAll;

		std::cout << "\nDo you want to give access to:\n";

		if (toupper(_GetUserAnswer("\nShow Client List")) == 'Y')
			Permissions += clsUser::enPermissions::pListClient;

		if (toupper(_GetUserAnswer("Add New Client")) == 'Y')
			Permissions += clsUser::enPermissions::pAddNewClient;

		if (toupper(_GetUserAnswer("Delete Client")) == 'Y')
			Permissions += clsUser::enPermissions::pDeleteClient;

		if (toupper(_GetUserAnswer("Update Client")) == 'Y')
			Permissions += clsUser::enPermissions::pUpdateClient;

		if (toupper(_GetUserAnswer("Find Client")) == 'Y')
			Permissions += clsUser::enPermissions::pFindClient;

		if (toupper(_GetUserAnswer("Transactions")) == 'Y')
			Permissions += clsUser::enPermissions::pTransactions;

		if (toupper(_GetUserAnswer("Manage Users")) == 'Y')
			Permissions += clsUser::enPermissions::pManageUsers;

		if (toupper(_GetUserAnswer("Login Register")) == 'Y')
			Permissions += clsUser::enPermissions::pLoginRegister;

		if (toupper(_GetUserAnswer("Currency Calculator")) == 'Y')
			Permissions += clsUser::enPermissions::pCurrencyExchange;

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nEnter First Name: ");
		User.FirstName = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Last Name: ");
		User.LastName = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Email: ");
		User.Email = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Phone: ");
		User.Phone = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter Password: ");
		User.Password = clsInputValidate::ReadString();

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nEnter Permissions: ");
		User.Permissions = _ReadPermissionsToSet();
		
	}

	static void _PrintUserCard(clsUser& User)
	{
		std::cout << "\n";
		clsUtil::DrawCardLine();
		std::cout << "\n" << std::left << std::setw(9) << "" << "User Card\n";
		clsUtil::DrawCardLine();
		std::cout << "\n";
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "FirstName   : " << User.FirstName << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "LastName    : " << User.LastName << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Full Name   : " << User.FullName() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Email       : " << User.Email << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Phone       : " << User.Phone << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Password    : " << User.Password << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Permissions : " << User.Permissions << std::endl;
		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("Add New User Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string Username = _ReadUsername();
		clsUser NewUser = clsUser::GetAddNewUserObject(Username);
		_ReadUserInfo(NewUser);
		NewUser.Save();

		std::cout << "\nUser Saved " << clsUtil::ColorText(clsUtil::LIGHTGREEN, " Successfully :-)\n");
		_PrintUserCard(NewUser);

		clsUtil::DrawLine('=', 110, 4);
	}
};

