#pragma once

#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void _PrintTotalBalanceRecordLine(clsBankClient& Client)
	{
		std::cout << std::setw(10) << std::left << "";
		clsUtil::PrintTableBoxContent(Client.AccountNumber(), 25);
		clsUtil::PrintTableBoxContent(Client.FullName(), 41);
		clsUtil::PrintTableBoxContent(std::to_string(Client.AccountBalance), 25, true);
	}

public:

	static void ShowTotalBalancesScreen()
	{
		std::vector <clsBankClient> vClientsData = clsBankClient::GetClientsList();
		std::string Title = "Total Balances Screen";
		std::string SubTitle = "(" + std::to_string(vClientsData.size()) + ") Clients(s)";

		_DrawScreenHeader(Title, SubTitle);

		clsUtil::DrawLine('-', 96, 10);
		std::cout << std::setw(10) << std::left << "";
		clsUtil::PrintTableBoxTitle("Acc.Number", 25);
		clsUtil::PrintTableBoxTitle("Client Name", 41);
		clsUtil::PrintTableBoxTitle("Balance($)", 25, true);
		clsUtil::DrawLine('-', 96, 10);


		if (vClientsData.size() == 0)
		{
			std::cout << std::setw(10) << std::left << "";
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "| ") << std::string(4, '\t');
			std::cout << clsUtil::ColorText(clsUtil::RED, "No Clients Available In the System!") << std::right << std::setw(62) << clsUtil::ColorText(clsUtil::LIGHTGREEN, "|") << std::endl;
		}
		else
		{
			for (clsBankClient& Client : vClientsData)
				_PrintTotalBalanceRecordLine(Client);
		}
		clsUtil::DrawLine('-', 96, 10);

		std::cout << std::string(5, '\t') << "  Total Balances = " << clsUtil::ColorText(clsUtil::LIGHTGREEN, std::to_string(clsBankClient::GetTotalBalances()) + "$\n");
		std::cout << std::string(5, '\t') << "  ( " << clsUtil::NumberToText(clsBankClient::GetTotalBalances()) << ")" << std::endl;

	}
};

