#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateRateScreen : protected clsScreen
{

private :

	static float _ReadRate()
	{
		cout << "\nEnter New Rate : ";

		double NewRate;
		NewRate = clsInputValidate::ReadNumber<double>();

		return NewRate;

	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n___________________";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n___________________\n";

	}

	

public :

	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = "";

		cout << "\n\nPlease Enter Currency Code : ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one : ";
			CurrencyCode = clsInputValidate::ReadString();
		}


		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);


		cout << "\nAre you sure you want to update the rate of this currency y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Currency Rate : ";
			cout << "\n___________________";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate updated succssuflly :-)";
			_PrintCurrency(Currency);

		}


	}


};

