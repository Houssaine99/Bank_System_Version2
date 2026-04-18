#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "clsPerson.h"
#include "../Lib/clsDate.h"
#include "../Lib/clsString.h"
#include "../Lib/clsUtil.h"

class clsUser : public clsPerson
{
private:

	enum enMode { EmptpyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	std::string _Username;
	std::string _Password;
	int _Permissions = 0;
	
	bool _MarkForDelete = false;
	struct stLoginRegisterRecord;


	std::string _ConvertLoginRegisterRecordToLine(stLoginRegisterRecord Record, std::string Seperator = "#//#")
	{
		std::string DataLine;

		DataLine += Record.DateTime + Seperator;
		DataLine += Record.Username + Seperator;
		DataLine += clsUtil::EncryptText(Record.Password) + Seperator;
		DataLine += std::to_string(Record.Permissions);

		return DataLine;
	}

	static stLoginRegisterRecord _ConvertLineToLoginRegisterRecord(std::string Line, std::string Sepertor = "#//#")
	{
		std::vector <std::string> vLoginRegister = clsString::Split(Line, Sepertor);
		stLoginRegisterRecord Record;

		Record.DateTime = vLoginRegister.at(0);
		Record.Username = vLoginRegister.at(1);
		Record.Password = clsUtil::DecryptText(vLoginRegister.at(2));
		Record.Permissions = std::stoi(vLoginRegister.at(3));

		return Record;

	}

	static std::vector <stLoginRegisterRecord> _LoadLoginRegisterFromFile()
	{
		std::vector <stLoginRegisterRecord> vLoginRegisterRecords;
		std::fstream File;
		File.open("Data/LoginRegister.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				stLoginRegisterRecord Record = _ConvertLineToLoginRegisterRecord(Line);
				vLoginRegisterRecords.push_back(Record);
			}

			File.close();
		}

		return vLoginRegisterRecords;
	}

	 stLoginRegisterRecord _PrepareLoginRegisterRecord()
	{
		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.DateTime = clsDate::GetSystemDateTimeString();
		LoginRegisterRecord.Username = Username;
		LoginRegisterRecord.Password = Password;
		LoginRegisterRecord.Permissions = Permissions;

		return LoginRegisterRecord;
	}

	static clsUser _ConvertLineToUserObject(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vRecordLine = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vRecordLine.at(0), vRecordLine.at(1), vRecordLine.at(2),
			vRecordLine.at(3), vRecordLine.at(4), clsUtil::DecryptText(vRecordLine.at(5)), std::stof(vRecordLine.at(6)));
	}

	static std::string _ConvertUserObjectToLine(clsUser& Client, std::string Seperator = "#//#")
	{
		std::string Line;

		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.Username + Seperator;
		Line += clsUtil::EncryptText(Client.Password) + Seperator;
		Line += std::to_string(Client.Permissions);

		return Line;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptpyMode, "", "", "", "", "", "", 0);
	}

	static std::vector <clsUser> _LoadUsersDataFromFile()
	{
		std::vector <clsUser> vUsersData;
		std::fstream File;
		File.open("Data/Users.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsersData.push_back(User);
			}
			File.close();
		}

		return vUsersData;
	}

	void _SaveUsersDataToFile(std::vector <clsUser>& vUsersData)
	{
		std::fstream File;
		File.open("Data/Users.txt", std::ios::out);

		if (File.is_open())
		{
			std::string Line;

			for (clsUser& User : vUsersData)
			{
				if (!User.MarkedForDelete())
				{
					Line = _ConvertUserObjectToLine(User);
					File << Line << std::endl;
				}
			}

			File.close();
		}
	}

	static void _AddDataLineToFile(std::string DataLine)
	{
		std::fstream File;
		File.open("Data/Users.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << DataLine << std::endl;
			File.close();
		}

	}

	void _Update()
	{
		std::vector <clsUser> vUsersData = _LoadUsersDataFromFile();

		for (clsUser& User : vUsersData)
		{
			if (User.Username == Username)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsersData);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

public:

	clsUser(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone,
		std::string Username, std::string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions {
		eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128, pCurrencyExchange = 256
	};

	struct stLoginRegisterRecord
	{
		std::string Username;
		std::string Password;
		std::string DateTime;
		int Permissions;
	};


	bool IsEmpty()
	{
		return (_Mode == enMode::EmptpyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkForDelete;
	}

	void SetUsername(std::string Username)
	{
		_Username = Username;
	}

	std::string GetUsername()
	{
		return _Username;
	}

	__declspec(property(get = GetUsername, put = SetUsername)) std::string Username;


	void SetPassword(std::string Password)
	{
		_Password = Password;
	}

	std::string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) std::string Password;


	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(std::string Username)
	{
		std::fstream File;
		File.open("Data/Users.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username)
				{
					File.close();
					return User;
				}
			}
			File.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(std::string Username, std::string Password)
	{
		std::fstream File;
		File.open("Data/Users.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username && User.Password == Password)
				{
					File.close();
					return User;
				}
			}
			File.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(std::string Username)
	{
		clsUser User = clsUser::Find(Username);
		return (!User.IsEmpty());
	}

	static clsUser GetAddNewUserObject(std::string Username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
	}

	enum enSaveResults { svSucceded = 1, svFaildEmptyObject = 2, svFaildAccountUsernameExist = 3 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptpyMode:
			return svFaildEmptyObject;

		case enMode::UpdateMode:
			_Update();
			return svSucceded;

		case enMode::AddNewMode:
			if (IsUserExist(Username))
				return svFaildAccountUsernameExist;

			_AddNew();
			_Mode = enMode::AddNewMode;
			return svSucceded;
		}
	}

	bool Delete()
	{
		std::vector <clsUser> vUsersData = _LoadUsersDataFromFile();

		for (clsUser& User : vUsersData)
		{
			if (User.Username == Username)
			{
				User._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsersData);

		*this = _GetEmptyUserObject();

		return true;
	}

	static std::vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	void LoginRegister()
	{
		stLoginRegisterRecord LoginRecord = _PrepareLoginRegisterRecord();
		std::fstream File;
		File.open("Data/LoginRegister.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			std::string Line = _ConvertLoginRegisterRecordToLine(LoginRecord);
			File << Line << std::endl;
			File.close();
		}
	}

	static std::vector <stLoginRegisterRecord> GetLoginRegisterRecords()
	{
		return _LoadLoginRegisterFromFile();
	}

	 bool CheckPermissionsRights(enPermissions Permission)
	{
		 if (_Permissions == enPermissions::eAll)
			 return true;

		 return ((_Permissions & Permission) == Permission);
	}

};

