#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsUser.h"

using namespace std;

class clsResetPasswordUserScreen : protected clsScreen
{


public:

    static void ShowResetPasswordScreen()
    {
        _DrawScreenHeader("\t    Reset Password");

        string OldPassword;
        cout << "\n\nPlease Enter Old Password : ";
        OldPassword = clsInputValidate::ReadString();

        while (OldPassword != CurrentUser.Password)
        {
            cout << "\nWrong Password, Please Enter Old Password : ";
            OldPassword = clsInputValidate::ReadString();
        }

        string NewPassword,RestNewPassword;
        cout << "\nPlease Enter New Password : ";
        NewPassword = clsInputValidate::ReadString();

        cout << "\nPlease Enter Rest New Password : ";
        RestNewPassword = clsInputValidate::ReadString();

        while (NewPassword == OldPassword || NewPassword != RestNewPassword)
        {
            if (NewPassword == OldPassword)
                cout << "\nEnter a new password, not the old password : ";
            else
                cout << "\nThe two passwords are the same, enter a passowrd : ";

            cout << "\nPlease Enter New Password : ";
            NewPassword = clsInputValidate::ReadString();

            cout << "\nPlease Enter Rest New Password : ";
            RestNewPassword = clsInputValidate::ReadString();
        }


        if (CurrentUser.ResetPassword(NewPassword) == clsUser::svSucceeded)
            cout << "\nPassword reset successfully -:)";
        else
            cout << "\nPassword reset Faild (:-";

 
            
    }

};

