#pragma once

#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
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

	static std::string _ReadCurrencyCode(std::string Message)
	{
		std::string CurrencyCode;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, Message);
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

		std::cout << "\nDo you want to perform another calculation " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[y/n]") << "? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return true;
		else
			return false;
	}

	static float _ReadAmount()
	{
		float Amount;
		std::cout << clsUtil::ColorText(clsUtil::LIGHTGREEN, "\nPlease Enter Exchange Amount? _");
		Amount = clsInputValidate::ReadFltPostiveNumber();

		return Amount;
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		bool PerformAnotherCalculation = true;

		while (PerformAnotherCalculation)
		{
			system("cls");
			_DrawScreenHeader("Currency Calculator");

			std::cout << "\n\n";
			clsUtil::DrawLine('=', 110, 4);

			clsCurrency FirstCurrency = clsCurrency::FindByCode(_ReadCurrencyCode("\nPlease enter first currency? _"));
			clsCurrency SecondCurrency = clsCurrency::FindByCode(_ReadCurrencyCode("\nPlease enter second currency? _"));
			float ExchangeAmount = _ReadAmount();

			std::cout << clsUtil::ColorText(clsUtil::BLUE, "\n>") << "Convert From\n";
			clsUtil::DrawLine('-', 20);
			_PrintCurrencyCard(FirstCurrency);

			std::cout << ExchangeAmount << " " << clsUtil::ColorText(clsUtil::LIGHTGREEN, FirstCurrency.CurrencyCode());
			std::cout << " = " << FirstCurrency.ConvertToUSD(ExchangeAmount) << clsUtil::ColorText(clsUtil::LIGHTGREEN, " USD\n\n");

			
			if (SecondCurrency.CurrencyCode() != "USD")
			{
				std::cout << clsUtil::ColorText(clsUtil::BLUE, "\n>") << "Convert From USD To\n";
				clsUtil::DrawLine('-', 20);
				_PrintCurrencyCard(SecondCurrency);

				std::cout << ExchangeAmount << " " << clsUtil::ColorText(clsUtil::LIGHTGREEN, FirstCurrency.CurrencyCode());
				std::cout << " = " << FirstCurrency.ConvertToOtherCurrency(ExchangeAmount, SecondCurrency) << " " 
					<< clsUtil::ColorText(clsUtil::LIGHTGREEN, SecondCurrency.CurrencyCode()) << std::endl;
			}
			
			PerformAnotherCalculation = _ConfirmationMessage();
		}

		std::cout << "\n";
		clsUtil::DrawLine('=', 110, 4);
	}

};

