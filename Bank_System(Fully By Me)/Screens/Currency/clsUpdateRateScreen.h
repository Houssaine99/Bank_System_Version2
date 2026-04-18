#pragma once

#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"

class clsUpdateRateScreen : protected clsScreen
{
private:

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

	static std::string _ReadCurrencyCode()
	{
		std::string CurrencyCode;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Currency Code? _");
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			std::cout << "\nCurrency " << clsUtil::ColorText(clsUtil::RED, "not found :-(\n") << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nEnter another currency code? _");
			CurrencyCode = clsInputValidate::ReadString();
		}

		return CurrencyCode;
	}

	static bool _ConfirmationMessage()
	{
		char Answer = 'n';

		std::cout << "\nAre you sure you want to update this currency's rate " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[y/n]") << "? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return true;
		else
			return false;
	}

	static float _ReadNewCurrencyRate()
	{
		float Input;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease enter new rate? _");
		Input = clsInputValidate::ReadFltPostiveNumber();

		return Input;
	}

public:

	static void showUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("Update Rate Screen");

		std::cout << "\n\n";
		clsUtil::DrawLine('=', 110, 4);

		clsCurrency Currency = clsCurrency::FindByCode(_ReadCurrencyCode());

		std::cout << "\nCurrency Found " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)\n");
		_PrintCurrencyCard(Currency);

		if (_ConfirmationMessage())
		{
			std::cout << clsUtil::ColorText(clsUtil::BLUE, "\n>") << "Update Currency Rate\n";
			clsUtil::DrawLine('-', 25);

			Currency.UpdateRate(_ReadNewCurrencyRate());

			std::cout << "\nRate Updated " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Successfully :-)\n");

			_PrintCurrencyCard(Currency);
		}
		else
			std::cout << "\nThis Operation Was " << clsUtil::ColorText(clsUtil::RED, "Canclled!\n\n");

		clsUtil::DrawLine('=', 110, 4);
	}
};

