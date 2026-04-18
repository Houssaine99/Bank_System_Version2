#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "../Lib/clsUtil.h"

#include "../Global.h"


class clsScreen
{

protected:

	
	static void _DrawScreenHeader(std::string Title, std::string SubTitle = "")
	{
		clsUtil::DrawLine();
		clsUtil::PrintTitle(Title);

		if (SubTitle != "")
			clsUtil::PrintTitle(SubTitle);

		clsUtil::DrawLine();

		std::cout << "\n" << "\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, ">>") << "User: ";

		if(CurrentUser.IsEmpty())
			std::cout << "No user loged in" << clsUtil::ColorText(clsUtil::LIGHTGREEN, "<<") << std::endl;
		else
			std::cout << CurrentUser.Username << clsUtil::ColorText(clsUtil::LIGHTGREEN, "<<") << std::endl;
		
		std::cout << "\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, ">>") << "Date: " << clsDate::GetSystemDateString() << clsUtil::ColorText(clsUtil::LIGHTGREEN, "<<") << std::endl;
		std::cout << "\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, ">>") << clsUtil::ColorText(clsUtil::BLUE, "Bank_System_Version_2") << clsUtil::ColorText(clsUtil::LIGHTGREEN, "<<") << "\n\n";
	
	}

	static bool _DoesCurrentUserHasPermission(clsUser::enPermissions Permission)
	{
		if (CurrentUser.CheckPermissionsRights(Permission))
			return true;
		else
		{
			std::cout << "\n\n\n\n";
			//_DrawScreenHeader(" Access Denied! Contact Your Admin.");

			clsUtil::DrawLine(clsUtil::enColor::RED);
			clsUtil::PrintTitle("Access Denied! Contact Your Admin.", clsUtil::enColor::RED);
			clsUtil::DrawLine(clsUtil::enColor::RED);
			return false;
		}
	}

};

