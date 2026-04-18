#pragma once

#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"

class clsFindUserScreen : protected clsScreen
{
private:

	static std::string _ReadUsername()
	{
		std::string Username;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Username? _");
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			std::cout << "User " << clsUtil::ColorText(clsUtil::RED, "not found :-(\n") << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter another username? _");
			Username = clsInputValidate::ReadString();
		}

		return Username;
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

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("Find User Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		std::string Username = _ReadUsername();
		clsUser User = clsUser::Find(Username);

		std::cout << "\nClient " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Found :-)\n");
		_PrintUserCard(User);

		clsUtil::DrawLine('=', 110, 4);
	}
};