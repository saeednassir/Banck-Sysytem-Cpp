#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double  _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
			vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> _vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // Read Mode.


		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				_vClients.push_back(Client);
			}

			MyFile.close();
		}
		return _vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out); //owerwrite mode

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();
		}

	}

	void _Update()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PerpareTransferLogRecord(double Amount, clsBankClient  DestinationClient, string UserName, string Seperator = "#//#")
	{

		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient  DestinationClient, string UserName)
	{

		fstream MyFile;

		string  stDataLine = _PerpareTransferLogRecord(Amount, DestinationClient, UserName);

		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	struct stTransferLog;
	static stTransferLog _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{

		stTransferLog TransferLog;

		vector<string> vTransferLog = clsString::Split(Line, Seperator);

		TransferLog.DateTime = vTransferLog[0];
		TransferLog.AccountNumberSourceClient = vTransferLog[1];
		TransferLog.AccountNumberDestinationClient = vTransferLog[2];
		TransferLog.Amount = stod(vTransferLog[3]);
		TransferLog.BalanceSourceClient = stod(vTransferLog[4]);
		TransferLog.BalanceDestinationClient = stod(vTransferLog[5]);
		TransferLog.UserName = vTransferLog[6];

		return TransferLog;
	}


public:

	struct stTransferLog
	{
		string DateTime;
		string AccountNumberSourceClient;
		string AccountNumberDestinationClient;
		double Amount;
		double BalanceSourceClient;
		double BalanceDestinationClient;
		string UserName;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PinCode, double  AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	//readonly propraty 
	string AccountNumber()
	{
		return _AccountNumber;
	}

	//propraty Set & Get
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	_declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	_declspec(property(get = GetAccountBalance, put = SetAccountBalance))double AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{

		clsBankClient Client = Find(AccountNumber);

		if (Client.PinCode == PinCode)return Client;
		else return _GetEmptyClientObject();

		/*vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile,Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();*/



	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResults {
		svFaildEmptyObject = 0, svSucceeded = 1,
		svFaildAccountNumberExists = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;
		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case clsBankClient::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
				return svFaildAccountNumberExists;
			else
			{
				_AddNew();

				//We need to set the mode to update after and new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;

		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients;

		vClients = _LoadClientsDataFromFile();

		double TotalBalances = 0;

		for (clsBankClient& C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;

	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
		}

	}


	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
			return false;

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);

		return true;
	}


	static vector<stTransferLog> GetTransferLogList()
	{

		vector<stTransferLog> vTransferLog;

		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in); // Read Mode.


		if (MyFile.is_open())
		{

			string Line;
			stTransferLog TransferLog;
			while (getline(MyFile, Line))
			{
				TransferLog = _ConvertTransferLogLineToRecord(Line);
				vTransferLog.push_back(TransferLog);
			}

			MyFile.close();
		}
		return vTransferLog;

	}


};

