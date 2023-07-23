#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsListCurrensiseScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{

private :

    static enum enCurrencyMenueOption {
        eListCurrensise = 1, eFindCurrency = 2,
        eUpdateRate = 3, eCurrencyCalculator = 4, eShowMainMenue = 5
    };

    static short _ReadCurrencyMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _ShowListCurrensiseScreen()
    {
        //cout << "\nList Currencies Screen Will Be Here.\n\n";
        clsListCurrensiseScreen::ShowListCurrensise();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "\nFind Currency Screen Will Be Here.\n\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();

    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\nUpdate Rate Screen Will Be Here.\n\n";
        clsUpdateRateScreen::ShowUpdateRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        //cout << "\nCurrency Calculator Screen Will Be Here.\n\n";

        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();

    }

    static void _GoBackToCurrencyMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowCurrencyExchangeScreen();

    }

    static void _PerformCurrencyMenueOption(enCurrencyMenueOption CurrencyMenueOption)
    {
       
        switch (CurrencyMenueOption)
        {
        case clsCurrencyExchangeScreen::eListCurrensise:
            system("cls");
            _ShowListCurrensiseScreen();
            _GoBackToCurrencyMenue();
            break;
        case clsCurrencyExchangeScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;
        case clsCurrencyExchangeScreen::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyMenue();
            break;
        case clsCurrencyExchangeScreen::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyMenue();
            break;
        case clsCurrencyExchangeScreen::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
           
        }
    }


public :

	static void ShowCurrencyExchangeScreen()
	{

        if (!CheckAccessRights(clsUser::pCurrencyExchange))
        {
            return;
        }

        system("cls");

        _DrawScreenHeader("\tCurrency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currensise.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyMenueOption((enCurrencyMenueOption)_ReadCurrencyMenueOption());

	}


};

