#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

using namespace std;

class clsListCurrensiseScreen :protected clsScreen
{

private :

    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(7) << left << Currency.CurrencyCode();
        cout << "| " << setw(35) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();

    }


public:

    static void ShowListCurrensise()
    {
        vector <clsCurrency> vCurrensise = clsCurrency::GetCurrenciesList();

        string Title = "\t  Currensise List Screen";
        string SubTitle = "\t    (" + to_string(vCurrensise.size()) + ") Currency(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(7) << "Code";
        cout << "| " << left << setw(35) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vCurrensise.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsCurrency Currency : vCurrensise)
            {

                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

