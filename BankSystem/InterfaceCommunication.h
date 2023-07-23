#pragma once

#include <iostream>
#include <string>

using namespace std;

class InterfaceCommunication
{

	virtual void SendEmail(string Title, string Body) = 0;
	virtual void SendFax(string Title, string Body) = 0;
	virtual void SendPhone(string Title, string Body) = 0;

};

