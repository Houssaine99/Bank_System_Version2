#pragma once

#include <iostream>

class clsPerson
{
private:

	std::string _FirstName;
	std::string _LastName;
	std::string _Email;
	std::string _Phone;

public:

	clsPerson(std::string FirstName, std::string LastName, std::string Email, std::string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(std::string FirstName)
	{
		_FirstName = FirstName;
	}

	std::string GetFirstName()
	{
		return _FirstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName)) std::string  FirstName;


	void SetLastName(std::string LastName)
	{
		_LastName = LastName;
	}

	std::string GetLastName()
	{
		return _LastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) std::string LastName;


	void SetEmail(std::string Email)
	{
		_Email = Email;
	}

	std::string GetEmail()
	{
		return _Email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) std::string Email;


	void SetPhone(std::string Phone)
	{
		_Phone = Phone;
	}

	std::string GetPhone()
	{
		return _Phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) std::string Phone;

	std::string FullName()
	{
		return _FirstName + " " + _LastName;
	}
};