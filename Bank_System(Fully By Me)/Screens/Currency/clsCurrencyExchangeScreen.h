#pragma once

#include "../clsScreen.h" 
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:

    enum enCurrencyExchangeMenuOptions {
        eListCurrency = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5 };


    static short _ReadCurrencyExchangeMenuOption()
    {
        short Choice = 0;

        std::cout << "Choose what do you want to do " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[1, 5]") << "? " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "_");
        Choice = clsInputValidate::ReadIntNumberBetween(1, 5, clsUtil::ColorText(clsUtil::RED, "Invalid Choice! Enter a number between (1 and 5)? _"));

        return Choice;
    }

    static void _GoBackToCurrencyExchangeMenu()
    {
        std::cout << "\n\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Press any key to go back to currency exchange menu ...\n");

        system("pause>0");
        ShowCurrencyExchangeMenu();
    }

    static void _ListCurrenciesScreen()
    {
        clsListCurrenciesScreen::ShowListClientScreen();
    }

    static void _FindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _UpdateRateScreen()
    {
        clsUpdateRateScreen::showUpdateCurrencyRateScreen();
    }

    static void _CurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenuOptions(enCurrencyExchangeMenuOptions Option)
    {
        switch (Option)
        {
        case enCurrencyExchangeMenuOptions::eListCurrency:
            system("cls");
            _ListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eFindCurrency:
            system("cls");
            _FindCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eUpdateRate:
            system("cls");
            _UpdateRateScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eCurrencyCalculator:
            system("cls");
            _CurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eMainMenu:{}
        }
    }

public:

	static void ShowCurrencyExchangeMenu()
	{
        if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pCurrencyExchange))
            return;

        system("cls");
        _DrawScreenHeader("Currency Exchange Screen");

        clsUtil::DrawLine('=', 98, 10);
        clsUtil::PrintTitle("Currency Exchange Menu", 100, 10);
        clsUtil::DrawLine('=');

        std::cout << "\n";
        clsUtil::PrintMenuOption("List Currencies", 1);
        clsUtil::PrintMenuOption("Find Currency", 2);
        clsUtil::PrintMenuOption("Update Rate", 3);
        clsUtil::PrintMenuOption("Currency Calculator", 4);
        clsUtil::PrintMenuOption("Main Menu", 5);
        std::cout << "\n";
        clsUtil::DrawLine('=');
        _PerformCurrencyExchangeMenuOptions((enCurrencyExchangeMenuOptions)_ReadCurrencyExchangeMenuOption());
	}
};

