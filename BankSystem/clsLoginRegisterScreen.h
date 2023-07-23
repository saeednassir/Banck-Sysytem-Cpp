#pragma once

#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsDate.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{

private:

    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord RegisterLogIn)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << RegisterLogIn.DateTime;
        cout << "| " << setw(20) << left << RegisterLogIn.UserName;
        cout << "| " << setw(20) << left << RegisterLogIn.Password;
        cout << "| " << setw(10) << left << RegisterLogIn.Permissions;

    }

public:

    static void ShowLoginRegisterList()
    {

        if (!CheckAccessRights(clsUser::pRegisterLogin))
        {
            return;
        }

        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "\t  RegisterLogIn List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(5) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo LogIns Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
            {

                _PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }


};

