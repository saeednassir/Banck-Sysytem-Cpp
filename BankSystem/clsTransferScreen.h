#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "Global.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient card:\n";
		cout << "\n___________________________\n";
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________________\n";
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount;

		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadNumber<double>();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		return Amount;
	}

	static void _Transfer()
	{
		string AccountNumberSourceClient;

		cout << "\n\nPlease Enter Account Number to Transfer From : ";
		AccountNumberSourceClient = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumberSourceClient))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumberSourceClient = clsInputValidate::ReadString();

		}

		clsBankClient SourceClient = clsBankClient::Find(AccountNumberSourceClient);
		_PrintClientCard(SourceClient);

		string AccountNumberDestinationClient;

		cout << "\n\nPlease Enter Account Number to Transfer To : ";
		AccountNumberDestinationClient = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumberDestinationClient) || AccountNumberDestinationClient == AccountNumberSourceClient)
		{
			if (AccountNumberDestinationClient == AccountNumberSourceClient)
				cout << "\nIt is not possible to transfer to the same client, choose another one: ";
			else
				cout << "\nAccount number is not found, choose another one: ";

			AccountNumberDestinationClient = clsInputValidate::ReadString();

		}


		clsBankClient DestinationClient = clsBankClient::Find(AccountNumberDestinationClient);
		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'n';

		cout << "\nAre you sure you want to perform this operation? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully:-)";
			}
			else
			{
				cout << "\nFaild Transfer (-:";
			}

		}

		_PrintClientCard(SourceClient);
		_PrintClientCard(DestinationClient);

	}

public:

	static void _ShowTransferScreen()
	{

		_DrawScreenHeader("\t   Transfer Screen");
		_Transfer();

	}

};

