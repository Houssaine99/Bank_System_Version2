#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../Lib/clsString.h"

class clsCurrency
{
private:

	enum enMode { eEmptyMode = 0, eUpdateMode = 1 };

	enMode _Mode;
	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate = 0;

	static clsCurrency _ConvertLineToCurrencyObject(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::eUpdateMode, vCurrencyData.at(0), vCurrencyData.at(1), vCurrencyData.at(2), std::stof(vCurrencyData.at(3)));
	}

	std::string _ConvertCurrencyObjectToLine(clsCurrency& Currency, std::string Seperator = "#//#")
	{
		std::string RecordLine;

		RecordLine += Currency.Country() + Seperator;
		RecordLine += Currency.CurrencyCode() + Seperator;
		RecordLine += Currency.CurrencyName() + Seperator;
		RecordLine += std::to_string(Currency.Rate());

		return RecordLine;

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}

	static std::vector <clsCurrency> _LoadCurrenciesListFromFile()
	{
		std::vector <clsCurrency> vCurrenciesData;
		std::fstream File;
		File.open("Data/Currencies.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrenciesData.push_back(Currency);
			}

			File.close();
		}

		return vCurrenciesData;
	}

	void _SaveCurrenciesDataToFile(std::vector <clsCurrency>& vCurrenciesData)
	{
		std::fstream File;
		File.open("Data/Currencies.txt", std::ios::out);

		if (File.is_open())
		{
			std::string Line;
			for (clsCurrency& Currency : vCurrenciesData)
			{
				Line = _ConvertCurrencyObjectToLine(Currency);
				File << Line << std::endl;
			}
			File.close();
		}
	}

	void _Update()
	{
		std::vector <clsCurrency> vCurrenciesData = _LoadCurrenciesListFromFile();

		for (clsCurrency& Currency : vCurrenciesData)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(vCurrenciesData);
	}

public:

	clsCurrency(enMode Mode, std::string Country, std::string CurrencyCode, std::string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::eEmptyMode);
	}

	std::string Country()
	{
		return _Country;
	}

	std::string CurrencyCode()
	{
		return _CurrencyCode;
	}

	std::string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCountry(std::string Country)
	{
		Country = clsString::UpperAllString(Country);
		std::fstream File;
		File.open("Data/Currencies.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					File.close();
					return Currency;
				}
			}

			File.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(std::string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		std::fstream File;
		File.open("Data/Currencies.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					File.close();
					return Currency;
				}
			}

			File.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(std::string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static std::vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesListFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / _Rate);
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency& OtherCurreny)
	{
		float AmountToUSD = ConvertToUSD(Amount);

		if (OtherCurreny.CurrencyCode() == "USD")
			return AmountToUSD;

		return (float)(AmountToUSD * OtherCurreny.Rate());
	}
};

