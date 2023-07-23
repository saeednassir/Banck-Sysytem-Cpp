#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "clsString.h"

using namespace std;

class clsCurrency
{

private :
	
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(Line,Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0],
			vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector<clsCurrency> vCurrencyData;

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			
			while (getline(MyFile, Line))
			{
					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
					vCurrencyData.push_back(Currency);
			}
				
			

			MyFile.close();
		}

		return vCurrencyData;
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string RecordLine;

		RecordLine += Currency.Country() + Seperator;
		RecordLine += Currency.CurrencyCode() + Seperator;
		RecordLine += Currency.CurrencyName() + Seperator;
		RecordLine += to_string(Currency.Rate()) + Seperator;

		return RecordLine;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencys)
	{
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsCurrency& Currency : vCurrencys)
			{
				DataLine = _ConvertCurrencyObjectToLine(Currency);
				MyFile << DataLine << endl;
			}
			
			MyFile.close();
		}

	}

	void _Update()
	{
		vector<clsCurrency> vCurrencys = _LoadCurrencyDataFromFile();

		for (clsCurrency& Currency : vCurrencys)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public :

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	double Rate()
	{
		return _Rate;
	}

	void UpdateRate(double Rate)
	{
		_Rate = Rate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile,Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}

		return _GetEmptyCurrencyObject();

	}

	static clsCurrency FindByCountry(string Country)
	{

		Country = clsString::UpperAllString(Country);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	double ConvertToUSD(double Amount)
	{
		return (double)(Amount / Rate());
	}

	double ConvertToOtherCurrency(double Amount, clsCurrency Currency2)
	{
		double AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (double)(AmountInUSD * Currency2.Rate());

	}


};

