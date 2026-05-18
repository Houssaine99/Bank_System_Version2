#pragma once

#include <fstream>

#include "../Lib/clsDate.h"
#include "clsBankClient.h"

class clsReceipt
{
private:
	
	enum enOperationType;
	enum enStatus;

	enOperationType _Operation;
	enStatus _Status;
	std::string TransactionID;

	static std::string ReceiptFilePath;

	struct stReceiptRecord;

	static void _PrintField(std::string Label, std::string Value)
	{
		int Spaces = 26 - Label.size();
		clsUtil::LeadingSpaces(30);
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "-> ") << Label << std::string(Spaces, ' ') << ": ";
		

		if (Value == "Succeed")
			std::cout << clsUtil::ColorTextBackGround(clsUtil::LIGHTGREEN, clsUtil::ColorText(clsUtil::BLACK, Value));

		else if (Value == "Failed")
			std::cout << clsUtil::ColorTextBackGround(clsUtil::RED, clsUtil::ColorText(clsUtil::BLACK, Value));

		else if(Value == "Cancelled")
			std::cout << clsUtil::ColorTextBackGround(clsUtil::CYAN, clsUtil::ColorText(clsUtil::BLACK, Value));

		else if (Label == "Balance (After Operation)" || Label == "Amount" || Label == "Balance (Before Operation)")
			std::cout << clsUtil::ColorTextBackGround(clsUtil::LIGHTGREEN, clsUtil::ColorText(clsUtil::RED, Value + " $"));

		else
			std::cout << Value;

		std::cout << "\n";

	}

	stReceiptRecord _PrepareReceiptRecord(clsBankClient& Client, float Amount, float BalanceBeforeOperation)
	{
		stReceiptRecord Record;

		Record.AccountNumber = Client.AccountNumber();
		Record.Client = Client.FullName();
		Record.DateTime = clsDate::GetSystemDateTimeString();
		Record.Amount = std::to_string(Amount);
		Record.BalanceBeforeOperation = std::to_string(BalanceBeforeOperation);
		Record.BalanceAfterOperation = std::to_string(Client.AccountBalance);
		Record.Operation = GetOperationType();
		Record.Status = GetStatus();
		Record.TransactionID = _GenerateTransactionID();

		return Record;
	}

	std::string _ConvertReceiptRecordToLine(stReceiptRecord& Record, std::string Seperator = "#//#")
	{
		std::string Line = "";
		
		Line += Record.AccountNumber + Seperator;
		Line += Record.Client + Seperator;
		Line += Record.DateTime + Seperator;
		Line += Record.Amount + Seperator;
		Line += Record.BalanceBeforeOperation + Seperator;
		Line += Record.BalanceAfterOperation + Seperator;
		Line += Record.Operation + Seperator;
		Line += Record.Status + Seperator;
		Line += Record.TransactionID;

		return Line;
	}

	static stReceiptRecord _ConvertLineToReceiptRecord(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vRececiptData = clsString::Split(Line, Seperator);
		stReceiptRecord Record;

		Record.AccountNumber = vRececiptData.at(0);
		Record.Client = vRececiptData.at(1);
		Record.DateTime = vRececiptData.at(2);
		Record.Amount = vRececiptData.at(3);
		Record.BalanceBeforeOperation = vRececiptData.at(4);
		Record.BalanceAfterOperation = vRececiptData.at(5);
		Record.Operation = vRececiptData.at(6);
		Record.Status = vRececiptData.at(7);
		Record.TransactionID = vRececiptData.at(8);

		return Record;
	}

	void _SaveReceiptHistory(std::string Line)
	{
		std::fstream File;
		File.open(ReceiptFilePath, std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << Line << std::endl;
			File.close();
		}
	}

	void _SaveTransactionIDToFile(std::string TransactionID)
	{
		std::fstream File;
		File.open("Data/ReciptIDs.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << TransactionID << std::endl;
			File.close();
		}
	}

	bool _IsTransactionIDAlreadyGenerated(std::string TransactionID)
	{
		std::fstream File;
		File.open("Data/ReciptIDs.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				if (Line == TransactionID)
				{
					File.close();
					return true;
				}
			}
			File.close();
		}
		return false;
	}

	std::string _GenerateTransactionID()
	{
		std::string TransactionID;

		do
		{
			TransactionID = "R" + std::to_string(clsUtil::RandomNumber(1000, 9999)) + std::to_string(clsUtil::RandomNumber(1000, 9999));

		} while (_IsTransactionIDAlreadyGenerated(TransactionID));

		_SaveTransactionIDToFile(TransactionID);
		return TransactionID;
	}

public:

	enum enOperationType { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCardlessTransfer = 4 };
	enum enStatus {eSucceed = 1, eFailed = 2, eCancelled = 3};

	struct stReceiptRecord
	{
		std::string AccountNumber;
		std::string Client;
		std::string DateTime;
		std::string Amount;
		std::string BalanceBeforeOperation;
		std::string BalanceAfterOperation;
		std::string Operation;
		std::string Status;
		std::string TransactionID;
	};
	
	clsReceipt(enOperationType Operation, enStatus Status)
	{
		_Operation = Operation;
		_Status = Status;
	}

	std::string GetStatus()
	{
		switch (_Status) {

		case enStatus::eSucceed:
			return "Succeed";

		case enStatus::eFailed:
			return "Failed";

		case enStatus::eCancelled:
			return "Cancelled";
		}
	
	}

	std::string GetOperationType()
	{
		switch (_Operation) {
		
		case enOperationType::eQuickWithdraw:
			return "Quick Withdraw";

		case enOperationType::eNormalWithdraw:
			return "Normal Withdraw";

		case enOperationType::eDeposit:
			return "Depoist";

		case enOperationType::eCardlessTransfer:
			return "Cardless Transfer";

		}
		
	}

	static stReceiptRecord GetEmptyRecord()
	{
		stReceiptRecord Record;

		Record.AccountNumber = "";
		Record.Client = "";
		Record.DateTime = "";
		Record.Amount = "";
		Record.BalanceBeforeOperation = "";
		Record.BalanceBeforeOperation = "";
		Record.Operation = "";
		Record.Status = "";
		Record.TransactionID = "";

		return Record;
	}

	static stReceiptRecord LoadReceiptRecordByTransactionID(std::string TransactionID)
	{
		std::fstream File;
		File.open(ReceiptFilePath, std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				stReceiptRecord Record = _ConvertLineToReceiptRecord(Line);

				if (Record.TransactionID == TransactionID)
				{
					File.close();
					return Record;
				}
			}
			File.close();
		}

		return GetEmptyRecord();
	}

	static std::vector <stReceiptRecord> LoadReceiptRecordByAccountNumber(std::string AccountNumber)
	{
		std::vector <stReceiptRecord> vRecords;
		std::fstream File;
		File.open(ReceiptFilePath, std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				stReceiptRecord Record = _ConvertLineToReceiptRecord(Line);

				if (Record.AccountNumber == AccountNumber)
				{
					vRecords.push_back(Record);
				}
			}
			File.close();
		}

		return vRecords;
	}

	void GenerateReceipt(clsBankClient& Client, float Amount, float BalanceBeforeOperation)
	{
		stReceiptRecord Record = _PrepareReceiptRecord(Client, Amount, BalanceBeforeOperation);

		std::cout << "\n\n";

		clsUtil::DrawLine('-', 18, 50);
		clsUtil::PrintTitle("Receipt", 20, 50);
		clsUtil::DrawLine('-', 58, 30);
		_PrintField("Acc.Number", Record.AccountNumber);
		_PrintField("Client", Record.Client);
		_PrintField("Date/Time", Record.DateTime);
		_PrintField("Amount", Record.Amount);
		_PrintField("Balance (Before Operation)", Record.BalanceBeforeOperation);
		_PrintField("Balance (After Operation)", Record.BalanceAfterOperation);
		_PrintField("Operation", Record.Operation);
		_PrintField("Status", Record.Status);
		_PrintField("Transaction ID", Record.TransactionID);
		clsUtil::DrawLine('-', 58, 30);

		_SaveReceiptHistory(_ConvertReceiptRecordToLine(Record));
	}

	static void PrintReceipt(stReceiptRecord Receipt)
	{
		clsUtil::DrawLine('=');

		std::cout << "\n\n";
		clsUtil::DrawLine('-', 18, 50);
		clsUtil::PrintTitle(Receipt.TransactionID, 20, 50);
		clsUtil::DrawLine('-', 58, 30);
		_PrintField("Acc.Number", Receipt.AccountNumber);
		_PrintField("Client", Receipt.Client);
		_PrintField("Date/Time", Receipt.DateTime);
		_PrintField("Amount", Receipt.Amount);
		_PrintField("Balance (Before Operation)", Receipt.BalanceBeforeOperation);
		_PrintField("Balance (After Operation)", Receipt.BalanceAfterOperation);
		_PrintField("Operation", Receipt.Operation);
		_PrintField("Status", Receipt.Status);
		clsUtil::DrawLine('-', 58, 30);
		std::cout << "\n\n";
	}

};

