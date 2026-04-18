#pragma once

#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:

	enum enFindBy {eByCode = 1, eByCountry = 2};

	static enFindBy _ReadFindByChoice()
	{
		short Choice;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nFind By: [1] Code or [2] Country? _");
		Choice = clsInputValidate::ReadIntNumberBetween(1, 2, clsUtil::ColorText(clsUtil::RED, "Invalid choice! Enter 1 or 2? _"));

		return (enFindBy)Choice;
	}

	static std::string _ReadStringFromUser(std::string Message)
	{
		std::string Input;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, Message);
		Input = clsInputValidate::ReadString();

		return Input;
	}

	static clsCurrency _FindCurreny(enFindBy FindByChoice)
	{
		switch (FindByChoice)
		{
		case enFindBy::eByCode:
			return clsCurrency::FindByCode(_ReadStringFromUser("\nPlease enter currency code? _"));

		case enFindBy::eByCountry:
			return clsCurrency::FindByCountry(_ReadStringFromUser("\nPlease enter currency country? _"));
		}
	}

	static void _PrintCurrencyCard(clsCurrency& Currency)
	{
		std::cout << "\n";
		clsUtil::DrawCardLine();
		std::cout << "\n" << std::left << std::setw(9) << "" << "Currency Card\n";
		clsUtil::DrawCardLine();
		std::cout << "\n";
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Country : " << Currency.Country() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Code    : " << Currency.CurrencyCode() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Name    : " << Currency.CurrencyName() << std::endl;
		std::cout << clsUtil::ColorText(clsUtil::BLUE, ">") << "Rate(1$): " << Currency.Rate() << std::endl;
		clsUtil::DrawCardLine();
		std::cout << "\n\n";
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("Find Currency Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		clsCurrency Currency = _FindCurreny(_ReadFindByChoice());

		if (Currency.IsEmpty())
			std::cout << "\nCurrency is " << clsUtil::ColorText(clsUtil::RED, "NOT Found :-(\n");
		else
		{
			std::cout << "\nCurrency is " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Found :-)\n");
			_PrintCurrencyCard(Currency);
		}

		clsUtil::DrawLine('=', 110, 4);
	}

};

