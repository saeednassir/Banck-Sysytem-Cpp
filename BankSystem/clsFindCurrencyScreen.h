#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen
{

private :

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

	static void _ShowResult(clsCurrency Currency)
	{
		if (!(Currency.IsEmpty()))
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Not Found :-)\n";
		}
	}


public :

	

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t\tFind currency Screen");

		cout << "\n\nFind By: [1] Code or [2] Country ? ";

		short Answer = 1;

		Answer = clsInputValidate::ReadNumberBetween<short>(1, 2);

		if (Answer == 1)
		{
			string CurrentCode;
			cout << "\nPlease Currency Code : ";
			CurrentCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrentCode);
			_ShowResult(Currency);
		}
		else
		{
			string Country;
			cout << "\nPlease Country Name : ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
		
		

	}

};

