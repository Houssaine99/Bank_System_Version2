#pragma once

#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord& Record)
	{
		//std::cout << std::setw(2) << std::left << "";
		clsUtil::PrintTableBoxContent(Record.DateTime, 25);
		clsUtil::PrintTableBoxContent(Record.S_AccNumber, 10);
		clsUtil::PrintTableBoxContent(Record.D_AccNumber, 10);
		clsUtil::PrintTableBoxContent(std::to_string(Record.Amount), 15);
		clsUtil::PrintTableBoxContent(std::to_string(Record.S_Balance), 15);
		clsUtil::PrintTableBoxContent(std::to_string(Record.D_Balance), 15);
		clsUtil::PrintTableBoxContent(Record.Username, 15, true);
	}

public:

	static void ShowTransferLogScreen()
	{
		std::vector <clsBankClient::stTransferLogRecord> vTransferLog = clsBankClient::GetTransferLogList();
		std::string Title = "Transfer Log Screen";
		std::string SubTitle = "(" + std::to_string(vTransferLog.size()) + ") Transfer Log(s)";

		_DrawScreenHeader(Title, SubTitle);

		//std::cout << std::setw(2) << std::left << "";
		clsUtil::DrawLine('-', 118);
		clsUtil::PrintTableBoxTitle("Date/Time", 25);
		clsUtil::PrintTableBoxTitle("S.Acc", 10);
		clsUtil::PrintTableBoxTitle("D.Acc", 10);
		clsUtil::PrintTableBoxTitle("Amount($)", 15);
		clsUtil::PrintTableBoxTitle("S.Balance($)", 15);
		clsUtil::PrintTableBoxTitle("D.Balance($)", 15);
		clsUtil::PrintTableBoxTitle("Username", 15, true);
		clsUtil::DrawLine('-', 118);


		if (vTransferLog.size() == 0)
		{
			std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "| ") << std::string(4, '\t');
			std::cout << clsUtil::ColorText(clsUtil::RED, "No Transfer Logs Available In the System!") << std::right << std::setw(62) << clsUtil::ColorText(clsUtil::LIGHTGREEN, "|") << std::endl;
		}
		else
		{
			for (clsBankClient::stTransferLogRecord& Record : vTransferLog)
				_PrintTransferLogRecordLine(Record);
		}
		clsUtil::DrawLine('-', 118);
	}
};

