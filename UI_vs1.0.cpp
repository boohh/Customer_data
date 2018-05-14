#include "stdafx.h"
#include "UI.h"


// Function make a * mask for password
string UI::HiddenPass(void)
{
	char c;
	string x = "";

	c = _getch();

	while (c != 13) //character 13 is enter
	{
		if ((c == 8 || c == 127) && !x.empty())
		{
			cout << "\b \b";
			x.erase(x.size() - 1);
			c = _getch();
		}
		else
		{
			x = x + c;
			cout << '*';
			c = _getch();
		}
	}
	return x;
}

// Login function for UI
int UI::LoginFunc(void)
{
	loginAttempt = 0;

	cout << endl;
	cout << "Enter login name: ";
	cin >> loginName;
	cout << "Enter password: ";
	loginPassword = HiddenPass();
	cout << endl;

	while (loginAttempt <= 3)
	{
		if (loginName == "Incoming" && loginPassword == "1")
		{
			cout << "\nWELCOME " << "INCOMING GROUP" << "\n" << endl;
			break;
		}

		else
		{
			cout << "\nInvalid login attempt. Please try again.\n" << '\n';
			loginAttempt++;
		}

		if (loginAttempt == 3)
		{
			cout << "TOO MANY LOGIN ATTEMPTS! LOGIN FAILED\n" << endl;
			return 0;
		}
		cout << "Enter login name: ";
		cin >> loginName; cin.ignore();
		cout << "Enter password: ";
		loginPassword = HiddenPass();
		cout << endl;
	}
	return 1;
}

// User interface
int UI::Interface(CusFile &CFile)
{
	int choice = 0;

	while (choice != 8)
	{
		cout << "----------------" << endl;
		cout << "Press 1 + Enter: Add a customer" << endl;
		cout << "Press 2 + Enter: Change the balance of customer" << endl;
		cout << "Press 3 + Enter: Change the email of customer" << endl;
		cout << "Press 4 + Enter: Change the last name of customer" << endl;
		cout << "Press 5 + Enter: Print the list of customer" << endl;
		cout << "Press 6 + Enter: Filter by last name" << endl;
		cout << "Press 7 + Enter: German language" << endl;
		cout << "Press 8 + Enter: Quit program" << endl;
		cout << "Your choice: ";
		cin >> choice; cin.ignore();

		while (!cin || (choice > 8) || (choice < 1))
		{
			choice = 0;
			cout << "Invalid!!! Please choose again!" << endl;
			cout << "Your choice: ";
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		switch (choice)
		{
		case 1:
			CFile.AddCustomer();
			break;
		case 2:
			CFile.ChangeBalance();
			break;
		case 3:
			CFile.ChangeEmail();
			break;
		case 4:
			CFile.ChangeLastName();
			break;
		case 5:
			CFile.PrintfList();
			break;
		case 6:
			FilterByFirstName();
			break;
		case 7:
			ofstream Lang("language.txt");
			Lang << 2;
			Lang.close();
			return 2;
		}
	}
	return 0;
}
