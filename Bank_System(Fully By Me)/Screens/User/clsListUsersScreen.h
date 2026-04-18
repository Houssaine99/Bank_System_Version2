#pragma once

#include <vector>

#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"

class clsListUsersScreen : protected clsScreen
{

private:

	static void _PrintUserRecordLine(clsUser& User)
	{
		
		clsUtil::PrintTableBoxContent(User.Username, 15);
		clsUtil::PrintTableBoxContent(User.FullName(), 25);
		clsUtil::PrintTableBoxContent(User.Phone, 12);
		clsUtil::PrintTableBoxContent(User.Email, 30);
		clsUtil::PrintTableBoxContent(User.Password, 11);
		clsUtil::PrintTableBoxContent(std::to_string(User.Permissions), 14, true);
	}

public:

	static void ShowListUsersScreen()
	{
		std::vector <clsUser> vUsers = clsUser::GetUsersList();

		std::string Title = "Manage Users Screen";
		std::string SubTitle = "(" + std::to_string(vUsers.size()) + ") User(s)";

		_DrawScreenHeader(Title, SubTitle);

		clsUtil::DrawLine('-', 118);
		clsUtil::PrintTableBoxTitle("Username", 15);
		clsUtil::PrintTableBoxTitle("Full Name", 25);
		clsUtil::PrintTableBoxTitle("Phone", 12);
		clsUtil::PrintTableBoxTitle("Email", 30);
		clsUtil::PrintTableBoxTitle("Password", 11);
		clsUtil::PrintTableBoxTitle("Permissions", 14, true);
		clsUtil::DrawLine('-', 118);

		if (vUsers.size() == 0)
		{
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "| ") << std::string(4, '\t');
			std::cout << clsUtil::ColorText(clsUtil::RED, "No Clients Available In the System!") << std::right << std::setw(62) << clsUtil::ColorText(clsUtil::LIGHTGREEN, "|") << std::endl;
		}
		else
		{
			for (clsUser& User : vUsers)
				_PrintUserRecordLine(User);
		}
		clsUtil::DrawLine('-', 118);

	}
};

