#pragma once

#include "../clsScreen.h"
#include "../../Core/clsReceipt.h"

class clsClientATMTransferHistoryScreen : protected clsScreen
{
private:

	static short _ReadFindByChoice()
	{
		short Choice;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nFind By: [1] TransactionID or [2] AccountNumber? _");
		Choice = clsInputValidate::ReadIntNumberBetween(1, 2, clsUtil::ColorText(clsUtil::RED, "Invalid choice! Enter 1 or 2? _"));

		return Choice;
	}

	static std::string _ReadTransactionID()
	{
		std::string TransactionID;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter TransactionID? _");
		TransactionID = clsInputValidate::ReadString();

		return TransactionID;
	}

	static std::string _ReadAccountNumber()
	{
		std::string AccountNumber;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter AccountNumber? _");
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

	static bool _ConfirmationMessage()
	{
		char Answer = 'n';

		std::cout << "\nDo You Want To Perfrom Another Search? " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[y/n]") << "? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return true;
		else
			return false;
	}

public:

	static void ShowClientATMTransferHistoryScreen()
	{
		do
		{
			system("cls");
			_DrawScreenHeader("Clinet ATM Transactions History Screen");

			short choice = _ReadFindByChoice();
			switch (choice)
			{
			case 1:
			{
				clsReceipt::stReceiptRecord Receipt = clsReceipt::LoadReceiptRecordByTransactionID(_ReadTransactionID());

				if (Receipt.AccountNumber == "" && Receipt.Amount == "" && Receipt.BalanceAfterOperation == "")
					std::cout << clsUtil::ColorText(clsUtil::RED, "Receipt Not Found!");
				else
					clsReceipt::PrintReceipt(Receipt);
				break;
			}
			case 2:
				std::string AccountNumber = _ReadAccountNumber();

				if (!clsBankClient::IsClientExist(AccountNumber))
				{
					std::cout << clsUtil::ColorText(clsUtil::RED, "Account Number Not Found!");
					break;
				}

				std::vector <clsReceipt::stReceiptRecord> vReceipts = clsReceipt::LoadReceiptRecordByAccountNumber(AccountNumber);
				int ReceiptsNumber = vReceipts.size();

				std::cout << "\n" << clsUtil::ColorTextBackGround(clsUtil::LIGHTGREEN, clsUtil::ColorText(clsUtil::BLACK, std::to_string(ReceiptsNumber) + " Result(s) found"));
				std::cout << "\n\n";

				if (vReceipts.size() == 0)
					std::cout << clsUtil::ColorText(clsUtil::RED, "Client has no history!");
				else
				{
					for (clsReceipt::stReceiptRecord& Record : vReceipts)
						clsReceipt::PrintReceipt(Record);
				}

				break;
			}
		} while (_ConfirmationMessage());
	} 
};

