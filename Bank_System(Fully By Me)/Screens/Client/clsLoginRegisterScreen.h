#pragma once

#include "../clsScreen.h";

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord& Record)
	{
		std::cout << std::setw(10) << std::left << "";
		clsUtil::PrintTableBoxContent(Record.DateTime, 30);
		clsUtil::PrintTableBoxContent(Record.Username, 21);
		clsUtil::PrintTableBoxContent(Record.Password, 20);
		clsUtil::PrintTableBoxContent(std::to_string(Record.Permissions), 20, true);
	}

public:
	
	static void ShowLoginRegisterScreen()
	{
		if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pLoginRegister))
			return;

		std::vector <clsUser::stLoginRegisterRecord> vRecords = clsUser::GetLoginRegisterRecords();

		std::string Title = "Login Register Screen";
		std::string SubTitle = "(" + std::to_string(vRecords.size()) + ") Login(s)";

		_DrawScreenHeader(Title, SubTitle);

		clsUtil::DrawLine('-', 98, 10);
		std::cout << std::setw(10) << std::left << "";
		clsUtil::PrintTableBoxTitle("Date/Time", 30);
		clsUtil::PrintTableBoxTitle("Username", 21);
		clsUtil::PrintTableBoxTitle("Password", 20);
		clsUtil::PrintTableBoxTitle("Permissions", 20, true);
		clsUtil::DrawLine('-', 98, 10);

		for (clsUser::stLoginRegisterRecord Record : vRecords)
			_PrintLoginRegisterRecordLine(Record);

		clsUtil::DrawLine('-', 98, 10);
	}
};

