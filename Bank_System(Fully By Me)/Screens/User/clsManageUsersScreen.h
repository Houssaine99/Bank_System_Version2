#pragma once

#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:

    enum enManageUsersMenuOption {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
    };

    static short _ReadManageUsersMenuChoice()
    {
        short Choice = 0;

        std::cout << "Choose what do you want to do " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "[1, 6]") << "? " << clsUtil::ColorText(clsUtil::LIGHTGREEN, "_");
        Choice = clsInputValidate::ReadIntNumberBetween(1, 6, clsUtil::ColorText(clsUtil::RED, "Invalid Choice! Enter a number between (1 and 6)? _"));

        return Choice;
    }

    static void _GoBackToManageUsersMenu()
    {
        std::cout << "\n\t" << clsUtil::ColorText(clsUtil::LIGHTGREEN, "Press any key to go back to manage users menu ...\n");

        system("pause>0");
        ShowManageUsersMenuScreen();
    }

    static void ListUsersScreen()
    {
        clsListUsersScreen::ShowListUsersScreen();
    }

    static void AddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void DeleteUserScreen()
    {
       clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void UpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void FindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerfromManageUsersMenuOptions(enManageUsersMenuOption Option)
    {
        switch (Option)
        {
        case enManageUsersMenuOption::eListUsers:
            system("cls");
            ListUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOption::eAddNewUser:
            system("cls");
            AddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOption::eDeleteUser:
            system("cls");
            DeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOption::eUpdateUser:
            system("cls");
            UpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOption::eFindUser:
            system("cls");
            FindUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOption::eMainMenu: {}
        }
    }

public:

	static void ShowManageUsersMenuScreen()
	{
        if (!_DoesCurrentUserHasPermission(clsUser::enPermissions::pManageUsers))
            return;

        system("cls");
		_DrawScreenHeader("Manage Users Screen");

        clsUtil::DrawLine('=', 98, 10);
        clsUtil::PrintTitle("Mange Users Menu", 100, 10);
        clsUtil::DrawLine('=');

        std::cout << "\n";
        clsUtil::PrintMenuOption("List Users", 1);
        clsUtil::PrintMenuOption("Add New User", 2);
        clsUtil::PrintMenuOption("Delete User", 3);
        clsUtil::PrintMenuOption("Update User Info", 4);
        clsUtil::PrintMenuOption("Find User", 5);
        clsUtil::PrintMenuOption("Main Menu", 6);
        std::cout << "\n";
        clsUtil::DrawLine('=');
        _PerfromManageUsersMenuOptions((enManageUsersMenuOption)_ReadManageUsersMenuChoice());
	}
};

