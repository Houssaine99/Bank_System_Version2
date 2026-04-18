#pragma once

#include <iostream>
#include <string>

#include "Lib/clsDate.h"
#include "Lib/clsUtil.h"

class clsInputValidate
{
public:

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		if (clsDate::isDate1AfterDate2(DateFrom, DateTo))
			clsDate::SwapDates(DateFrom, DateTo);

		return (clsDate::isDate1AfterDate2(Date, DateFrom) || clsDate::isDate1EqualDate2(DateFrom, Date))
			&& (clsDate::isDate1BeforeDate2(Date, DateTo) || clsDate::isDate1EqualDate2(Date, DateTo));
	}

	static int ReadIntNumber(std::string ErrorMessage = "Invalid Number! Try Again: ")
	{
		ErrorMessage = clsUtil::ColorText(clsUtil::RED, ErrorMessage);
		int InputNumber = 0;

		std::cin >> InputNumber;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			std::cout << ErrorMessage;

			std::cin >> InputNumber;
		}

		return InputNumber;
	}

	static double ReadDblNumber(std::string ErrorMessage = "Invalid Number! Try Again: ")
	{
		double InputNumber = 0;

		std::cin >> InputNumber;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			std::cout << ErrorMessage;

			std::cin >> InputNumber;
		}

		return InputNumber;
	}

	static float ReadFltNumber(std::string ErrorMessage = "Invalid Number! Try Again: ")
	{
		float InputNumber = 0;

		std::cin >> InputNumber;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			std::cout << ErrorMessage;

			std::cin >> InputNumber;
		}

		return InputNumber;
	}

	static float ReadFltPostiveNumber(std::string ErrorMessage = "Invalid Number! Try Again: ")
	{
		float InputNumber = ReadFltNumber();

		while (InputNumber < 0)
		{
			std::cout << "Enter a positive number! ";
			InputNumber = ReadFltNumber();
		}

		return InputNumber;
	}

	static int ReadIntNumberBetween(int From, int To, std::string ErrorMessage)
	{
		int InputNumber = ReadIntNumber();

		while (!IsNumberBetween(InputNumber, From, To))
		{
			std::cout << ErrorMessage;
			InputNumber = ReadIntNumber();
		}

		return InputNumber;
	}

	static double ReadDblNumberBetween(double From, double To, std::string ErrorMessage)
	{
		double InputNumber = ReadDblNumber();

		while (!IsNumberBetween(InputNumber, From, To))
		{
			std::cout << ErrorMessage;
			InputNumber = ReadDblNumber("Invalid Input! Try Again: ");
		}

		return InputNumber;
	}

	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValideDate(Date);
	}

	static std::string ReadString()
	{
		std::string InputString;

		std::getline(std::cin >> std::ws, InputString);

		return InputString;
	}
};

