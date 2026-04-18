#pragma once

#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsUtil.h"

class clsListClientsScreen : protected clsScreen
{
private:

	static void _PrintClientRecordLine(clsBankClient& Client)
	{
		//std::cout << std::setw(2) << std::left << "";
		clsUtil::PrintTableBoxContent(Client.AccountNumber(), 11);
		clsUtil::PrintTableBoxContent(Client.FullName(), 25);
		clsUtil::PrintTableBoxContent(Client.Phone, 12);
		clsUtil::PrintTableBoxContent(Client.Email, 30);
		clsUtil::PrintTableBoxContent(Client.PINCode, 10);
		clsUtil::PrintTableBoxContent(std::to_string(Client.AccountBalance), 19, true);
	}

public:
	
	static void ShowListClientScreen()
	{
		if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pListClient))
			return;
		
		std::vector <clsBankClient> vClientsData = clsBankClient::GetClientsList();
		std::string Title = "Clients List Screen";
		std::string SubTitle = "(" + std::to_string(vClientsData.size()) + ") Clients(s)";

		_DrawScreenHeader(Title, SubTitle);

		//std::cout << std::setw(2) << std::left << "";
		clsUtil::DrawLine('-', 118);
		clsUtil::PrintTableBoxTitle("Acc.Number", 11);
		clsUtil::PrintTableBoxTitle("Client Name", 25);
		clsUtil::PrintTableBoxTitle("Phone", 12);
		clsUtil::PrintTableBoxTitle("Email", 30);
		clsUtil::PrintTableBoxTitle("PIN Code", 10);
		clsUtil::PrintTableBoxTitle("Balance($)", 19, true);
		clsUtil::DrawLine('-', 118);
		

		if (vClientsData.size() == 0)
		{
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "| ") << std::string(4, '\t');
			std::cout << clsUtil::ColorText(clsUtil::RED, "No Clients Available In the System!") << std::right << std::setw(62) << clsUtil::ColorText(clsUtil::LIGHTGREEN, "|") << std::endl;
		}
		else
		{
			for (clsBankClient& Client : vClientsData)
				_PrintClientRecordLine(Client);
		}
		clsUtil::DrawLine('-', 118);
	}
};

