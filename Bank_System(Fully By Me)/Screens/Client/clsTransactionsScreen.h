#pragma once

#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


class clsTransactionsScreen : protected clsScreen
{
private:

    enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eMainMenu = 6 };

    static short _ReadTransactionsMenuOption()
    {
        short Choice = 0;

        std::cout << "Choose what do you want to do " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[1, 6]") << "? " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "_");
        Choice = clsInputValidate::ReadIntNumberBetween(1, 6, clsUtil::ColorText(clsUtil::RED, "Invalid Choice! Enter a number between (1 and 6)? _"));

        return Choice;
    }

    static void _DepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _WithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _TotalbalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _TransferScreen()
    {
       clsTransferScreen::ShowTransferLogScreen();
    }

    static void _TransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _GoBackToTransactionsMenu()
    {
        std::cout << "\n\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Press any key to go back to transactions menu ...\n");

        system("pause>0");
        ShowTransactionMenuScreen();
    }

    static void _PerformTransactionMenuOptions(enTransactionsMenuOptions Option)
    {
        switch (Option)
        {
        case enTransactionsMenuOptions::eDeposit:
            system("cls");
           _DepositScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eWithdraw:
            system("cls");
            _WithdrawScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eTotalBalances:
            system("cls");
           _TotalbalancesScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eTransfer:
            system("cls");
            _TransferScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eTransferLog:
            system("cls");
            _TransferLogScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eMainMenu:{}
        }
    }

public:

    static void ShowTransactionMenuScreen()
    {
        if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pTransactions))
            return;

        system("cls");
        _DrawScreenHeader("Transactions Screen");

        clsUtil::DrawLine('=', 98, 10);
        clsUtil::PrintTitle("Transactions Menu", 100, 10);
        clsUtil::DrawLine('=');

        std::cout << "\n";
        clsUtil::PrintMenuOption("Deposit", 1);
        clsUtil::PrintMenuOption("Withdraw", 2);
        clsUtil::PrintMenuOption("Total Balances", 3);
        clsUtil::PrintMenuOption("Transfer", 4);
        clsUtil::PrintMenuOption("Transfer Log", 5);
        clsUtil::PrintMenuOption("Main Menu", 6);
        std::cout << "\n";
        clsUtil::DrawLine('=');
        _PerformTransactionMenuOptions((enTransactionsMenuOptions)_ReadTransactionsMenuOption());
    }
};

