#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	struct stLoginRegisterRecord; // declartion

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{

		stLoginRegisterRecord RegisterLogIn;

		vector<string> vRegisterLogInData = clsString::Split(Line, Seperator);

		RegisterLogIn.DateTime = vRegisterLogInData[0];
		RegisterLogIn.UserName = vRegisterLogInData[1];
		RegisterLogIn.Password = clsUtil::DecryptText(vRegisterLogInData[2], 35);
		RegisterLogIn.Permissions = stoi(vRegisterLogInData[3]);

		return RegisterLogIn;
	}


	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1],
			vUserData[2], vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5], 35), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string stUserRecord = "";
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Email + Seperator;
		stUserRecord += User.Phone + Seperator;
		stUserRecord += User._UserName + Seperator;
		stUserRecord += clsUtil::EncryptText(User._Password, 35) + Seperator;
		stUserRecord += to_string(User._Permissions);

		return stUserRecord;
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> _vUsers;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in); // Read Mode.


		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				_vUsers.push_back(User);
			}

			MyFile.close();
		}
		return _vUsers;
	}


	static void _SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out); //owerwrite mode

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsUser& U : vUsers)
			{
				if (U.MarkedForDelete() == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();
		}

	}

	void _Update()
	{
		vector<clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.GetUserName() == _UserName)
			{
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PerpareLogInRecord(string Seperator = "#//#")
	{

		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password, 35) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

public:



	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
		pManageUsers = 64, pRegisterLogin = 128, pCurrencyExchange = 256
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};


	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	string GetPassword()
	{
		return _Password;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	int GetPermissions()
	{
		return _Permissions;
	}

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	_declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{

		fstream MyFile;

		MyFile.open("Users.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.GetUserName() == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{

		clsUser User = Find(UserName);

		if (User.Password == Password)
			return User;
		else
			return _GetEmptyUserObject();

		/*vector<clsUser> vUsers;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile,Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);

				if (User.GetUserName() == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();*/



	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResults {
		svFaildEmptyObject = 0, svSucceeded = 1,
		svFaildUserExists = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;
		case clsUser::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case clsUser::AddNewMode:
			if (clsUser::IsUserExist(_UserName))
				return svFaildUserExists;
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

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;

		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.GetUserName() == _UserName)
			{
				U._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
		*this = _GetEmptyUserObject();

		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		if ((Permissions & this->Permissions) == Permissions)
			return true;
		else
			return false;

	}

	void RegisterLogIn()
	{

		fstream MyFile;

		string  stDataLine = _PerpareLogInRecord();

		MyFile.open("LogFile.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{

		vector<stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;

		MyFile.open("LogFile.txt", ios::in); // Read Mode.


		if (MyFile.is_open())
		{

			string Line;
			stLoginRegisterRecord LoginRegisterRecord;
			while (getline(MyFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}
		return vLoginRegisterRecord;

	}

	enSaveResults ResetPassword(string NewPassword)
	{
		this->Password = NewPassword;
		return Save();

	}

};

