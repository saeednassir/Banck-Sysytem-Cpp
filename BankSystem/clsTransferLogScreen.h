#pragma once

#include <iostream>
#include "clsScreen.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{

private:

    static void _PrintTransferLoginRecordLine(clsBankClient::stTransferLog TransferLog)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLog.DateTime;
        cout << "| " << setw(10) << left << TransferLog.AccountNumberSourceClient;
        cout << "| " << setw(10) << left << TransferLog.AccountNumberDestinationClient;
        cout << "| " << setw(10) << left << TransferLog.Amount;
        cout << "| " << setw(10) << left << TransferLog.BalanceSourceClient;
        cout << "| " << setw(10) << left << TransferLog.BalanceDestinationClient;
        cout << "| " << setw(15) << left << TransferLog.UserName;

    }


public:

    static void  ShowTransferLogScreen()
    {
        vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransferLogList();

        string Title = "\t  Transfe rLog List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLog.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(15) << "User Name";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vTransferLog.size() == 0)
            cout << "\t\t\t\tNo LogIns Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : vTransferLog)
            {

                _PrintTransferLoginRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

    }

};

