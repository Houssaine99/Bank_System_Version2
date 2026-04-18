#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/clsDate.h"

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptpyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	std::string _AccountNumber;
	std::string _PINCode;
	float _AccountBalance;

	bool _MarkForDelete = false;

	struct stTransferLogRecord;


	static clsBankClient _ConvertLineToClientObject(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vRecordLine = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vRecordLine.at(0), vRecordLine.at(1), vRecordLine.at(2),
			vRecordLine.at(3), vRecordLine.at(4), clsUtil::DecryptText(vRecordLine.at(5)), std::stof(vRecordLine.at(6)));
	}

	static std::string _ConvertClientObjectToLine(clsBankClient& Client, std::string Seperator = "#//#")
	{
		std::string Line;

		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.AccountNumber() + Seperator;
		Line += clsUtil::EncryptText(Client.PINCode) + Seperator;
		Line += std::to_string(Client.AccountBalance);

		return Line;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptpyMode, "", "", "", "", "", "", 0);
	}

	static std::vector <clsBankClient> _LoadClientsDataFromFile()
	{
		std::vector <clsBankClient> vClientsData;
		std::fstream File;
		File.open("Data/Clients.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClientsData.push_back(Client);
			}
			File.close();
		}

		return vClientsData;
	}

	void _SaveClientsDataToFile(std::vector <clsBankClient>& vClientsData)
	{
		std::fstream File;
		File.open("Data/Clients.txt", std::ios::out);

		if (File.is_open())
		{
			std::string Line;

			for (clsBankClient& Client : vClientsData)
			{
				if (!Client._MarkForDelete)
				{
					Line = _ConvertClientObjectToLine(Client);
					File << Line << std::endl;
				}
			}

			File.close();
		}
	}

	static void _AddDataLineToFile(std::string DataLine)
	{
		std::fstream File;
		File.open("Data/Clients.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << DataLine << std::endl;
			File.close();
		}

	}

	void _Update()
	{
		std::vector <clsBankClient> vClientsData = _LoadClientsDataFromFile();

		for (clsBankClient& Client : vClientsData)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClientsData);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static stTransferLogRecord _ConvertLineToTransferLogRecord(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vTransferLog = clsString::Split(Line, Seperator);
		stTransferLogRecord Record;

		Record.DateTime = vTransferLog.at(0);
		Record.S_AccNumber = vTransferLog.at(1);
		Record.D_AccNumber = vTransferLog.at(2);
		Record.Amount = std::stof(vTransferLog.at(3));
		Record.S_Balance = std::stof(vTransferLog.at(4));
		Record.D_Balance = std::stof(vTransferLog.at(5));
		Record.Username = vTransferLog.at(6);

		return Record;

	}

	std::string _ConvertTransferLogRecordToLine(stTransferLogRecord& Record, std::string Seperator = "#//#")
	{
		std::string Line;

		Line += Record.DateTime + Seperator;
		Line += Record.S_AccNumber + Seperator;
		Line += Record.D_AccNumber + Seperator;
		Line += std::to_string(Record.Amount) + Seperator;
		Line += std::to_string(Record.S_Balance) + Seperator;
		Line += std::to_string(Record.D_Balance) + Seperator;
		Line += Record.Username;

		return Line;
	}

	stTransferLogRecord _PrepareTransferLogRecord(float Amount, clsBankClient& DestinationClient, std::string Username)
	{
		stTransferLogRecord Record;

		Record.DateTime = clsDate::GetSystemDateTimeString();
		Record.S_AccNumber = AccountNumber();
		Record.D_AccNumber = DestinationClient.AccountNumber();
		Record.Amount = Amount;
		Record.S_Balance = AccountBalance;
		Record.D_Balance = DestinationClient.AccountBalance;
		Record.Username = Username;

		return Record;
	}

	void _RegisterTransferLog(float Amount, clsBankClient& DestinationClient, std::string Username)
	{
		stTransferLogRecord Record = _PrepareTransferLogRecord(Amount, DestinationClient, Username);
		std::fstream File;
		File.open("Data/TransferLog.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			std::string RecordLine = _ConvertTransferLogRecordToLine(Record);
			File << RecordLine << std::endl;
			File.close();
		}
	}

public:

	clsBankClient(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone,
		std::string AccountNumber, std::string PINCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PINCode = PINCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{
		std::string DateTime;
		std::string S_AccNumber;
		std::string D_AccNumber;
		float Amount = 0;
		float S_Balance = 0;
		float D_Balance = 0;
		std::string Username;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptpyMode);
	}

	std::string AccountNumber()
	{
		return _AccountNumber;
	}


	void SetPINCode(std::string PINCode)
	{
		_PINCode = PINCode;
	}

	std::string GetPINCode()
	{
		return _PINCode;
	}

	__declspec(property(get = GetPINCode, put = SetPINCode)) std::string PINCode;


	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBlance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBlance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(std::string AccountNumber)
	{
		std::fstream File;
		File.open("Data/Clients.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					File.close();
					return Client;
				}
			}
			File.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(std::string AccountNumber, std::string PINCode)
	{
		std::fstream File;
		File.open("Data/Clients.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PINCode == PINCode)
				{
					File.close();
					return Client;
				}
			}
			File.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(std::string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(std::string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	void Save()
	{
		switch (_Mode)
		{
		case enMode::UpdateMode:
			_Update();
			break;

		case enMode::AddNewMode:
			_AddNew();
			_Mode = enMode::AddNewMode;
			break;
		}
	}

	void Delete()
	{
		std::vector <clsBankClient> vClientsData = _LoadClientsDataFromFile();

		for (clsBankClient& Client : vClientsData)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClientsData);

		*this = _GetEmptyClientObject();

	}

	static std::vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposit(float Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(float Amount)
	{
		if (Amount > _AccountBalance)
			return false;

		_AccountBalance -= Amount;
		Save();
	}

	void Transfer(float Amount, clsBankClient& DistinationClient, std::string Username)
	{
		Withdraw(Amount);
		DistinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DistinationClient, Username);
	}

	static float GetTotalBalances()
	{
		std::vector <clsBankClient> vClientsData = _LoadClientsDataFromFile();
		float TotalBalance = 0;

		for (clsBankClient& Client : vClientsData)
		{
			TotalBalance += Client.AccountBalance;
		}

		return TotalBalance;
	}

	static std::vector <stTransferLogRecord> GetTransferLogList()
	{
		std::vector <stTransferLogRecord> vTransferLog;
		std::fstream File;
		File.open("Data/TransferLog.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			stTransferLogRecord Record;
			while (std::getline(File, Line))
			{
				Record = _ConvertLineToTransferLogRecord(Line);
				vTransferLog.push_back(Record);
			}

			File.close();
		}

		return vTransferLog;
	}


};

