#pragma once

#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:

	static std::string _ReadUsername()
	{
		std::string Username;

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nEnter username: _");
		Username = clsInputValidate::ReadString();

		return Username;
	}

	static std::string _ReadPassword()
	{
		std::string Password;

		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Enter password: _");
		Password = clsInputValidate::ReadString();

		return Password;
	}

	static bool _Login()
	{
		std::string Username;
		std::string Password;
		short Trials = 0;
		bool LoginFaild = false;

		do
		{
			if (LoginFaild)
			{
				Trials++;
				std::cout << clsUtil::ColorText(clsUtil::RED, "\nInvalid Username/Password!\n");
				std::cout << clsUtil::ColorText(clsUtil::RED, "You have " + std::to_string(3 - Trials) + " trial(s) to login!\n");
			}

			if (Trials == 3)
			{
				std::cout << clsUtil::ColorText(clsUtil::RED, "\n\n\t>>You are blocked after 3 faild trials!!!!<<\n\n");
				return false;
			}
			
			Username = _ReadUsername();
			Password = _ReadPassword();

			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.LoginRegister();
		clsMainScreen::ShowMainScreen();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("Login Screen");
		clsUtil::DrawLine('=', 110, 4);

		return _Login();
	}
};

