#pragma once

#include "clsScreen.h";
#include "../Lib/clsInputValidate.h"
#include "Client/clsListClientsScreen.h"
#include "Client/clsAddNewClientScreen.h"
#include "Client/clsDeleteClientScreen.h"
#include "Client/clsUpdateClientScreen.h"
#include "Client/clsFindClientScreen.h"
#include "User/clsManageUsersScreen.h"
#include "Client/clsLoginRegisterScreen.h"
#include "Client/clsTransactionsScreen.h"
#include "Currency/clsCurrencyExchangeScreen.h"


class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenuOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
    };

    static short _ReadMainMenuChoice()
    {
        short Choice = 0;

        std::cout << "Choose what do you want to do " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[1, 10]") << "? " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "_");
        Choice = clsInputValidate::ReadIntNumberBetween(1, 10, clsUtil::ColorText(clsUtil::RED, "Invalid Choice! Enter a number between (1 and 10)? _"));

        return Choice;
    }

    static void _GoBackToMainMenu()
    {
        std::cout << "\n\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Press any key to go back to main menu ...\n");

        system("pause>0");
        ShowMainScreen();
    }

    static void ClientsListScreen()
    {
        clsListClientsScreen::ShowListClientScreen();
    }

    static void AddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void DeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void UpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void FindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void TransactionsMenuScreen()
    {
        clsTransactionsScreen::ShowTransactionMenuScreen();
    }

    static void ManageUsersMenuScreen()
    {
        clsManageUsersScreen::ShowManageUsersMenuScreen();
    }

    static void LoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void CurrencyExchangeScreen()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeMenu();
    }

    static void Logout()
    {
        CurrentUser = clsUser::Find("");
    }

    static void _PerfromMainMenuOptions(enMainMenuOptions Option)
    {
        switch (Option)
        {
        case enMainMenuOptions::eListClients:
            system("cls");
            ClientsListScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eAddNewClient:
            system("cls");
            AddNewClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eDeleteClient:
            system("cls");
            DeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eUpdateClient:
            system("cls");
            UpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eFindClient:
            system("cls");
            FindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eShowTransactionsMenu:
            system("cls");
            TransactionsMenuScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eManageUsers:
            system("cls");
            ManageUsersMenuScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eLoginRegister:
            system("cls");
            LoginRegisterScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eCurrencyExchange:
            system("cls");
            CurrencyExchangeScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eExit:
            Logout();
            break;
        }
    }

public:

	static void ShowMainScreen()
	{
		system("cls");
		_DrawScreenHeader("Main Screen");

        clsUtil::DrawLine('=', 98, 10);
        clsUtil::PrintTitle("Main Menu", 100, 10);
        clsUtil::DrawLine('=');

        std::cout << "\n";
        clsUtil::PrintMenuOption("Show Client List", 1);
        clsUtil::PrintMenuOption("Add New Client", 2);
        clsUtil::PrintMenuOption("Delete Client", 3);
        clsUtil::PrintMenuOption("Update Client", 4);
        clsUtil::PrintMenuOption("Find Client", 5);
        clsUtil::PrintMenuOption("Transactions", 6);
        clsUtil::PrintMenuOption("Manage Users", 7);
        clsUtil::PrintMenuOption("Login Register", 8);
        clsUtil::PrintMenuOption("Currency Exchange", 9);
        clsUtil::PrintMenuOption("Logout", 10);
        std::cout << "\n";
        clsUtil::DrawLine('=');
        _PerfromMainMenuOptions((enMainMenuOptions)_ReadMainMenuChoice());
	}
   
};

