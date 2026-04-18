#pragma once

#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"

class clsDeleteUserScreen : protected clsScreen
{
private:

	static std::string _ReadUsername()
	{
		std::string Username;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Username? _");
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			std::cout << clsUtil::ColorText(clsUtil::RED, "This username is not found! Enter another one? _");
			Username = clsInputValidate::ReadString();
		}

		return Username;
	}

	static bool _ConfirmationMessage()
	{
		char Answer = 'n';

		std::cout << "\nAre you sure you want to delete this user " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[y/n]") << "? _";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return true;
		else
			return false;
	}

	static void _PrintUserCard(clsUser& User, bool IsDeleted = false)
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
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Status : ";

		if (IsDeleted)
			std::cout << clsUtil::ColorText(clsUtil::RED, "Deleted!") << std::endl;
		else
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Selected") << std::endl;

		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("Delete User Screen");


		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string Username = _ReadUsername();
		clsUser User = clsUser::Find(Username);

		_PrintUserCard(User);

		if (_ConfirmationMessage())
		{
			User.Delete();
			std::cout << "\nUser Was Deleted " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)\n");
			_PrintUserCard(User, true);
		}
		else
			std::cout << "\nThis Operation Was " << clsUtil::ColorText(clsUtil::RED, "Canclled!\n");

		clsUtil::DrawLine('=', 110, 4);
	}
};

