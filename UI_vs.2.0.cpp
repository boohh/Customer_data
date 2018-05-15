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

// Function for signing up account
void UI::SignUp(CusFile &CFile)
{
    ofstream account("abcxyz.csv", std::ios_base::app);
    cout << "\nSigning up your account!!!" << endl;
	cout << "Login name: ";
	cin >> loginName;
	cout << "Password: ";
	loginPassword = HiddenPass();
	cout << "\nLogin success" << endl;
	account << CFile.encrypted(loginName) << "," << CFile.encrypted(loginPassword) << "\n";
    account.close();
}

// Login function for UI
int UI::LoginFunc(CusFile &CFile)
{
    int i = 0;
    ifstream account("abcxyz.csv");
    while (account.good())
	{
		getline(account, User[i].Username, ',');
		User[i].Username = CFile.decrypted(User[i].Username);
		getline(account, User[i].Password);
		User[i].Password = CFile.decrypted(User[i].Password);
		i++;
	}

	int NumberUser = i;

	int loginAttempt = 0;

	cout << "\nLoginng in your account\n" << endl;
	cout << "Enter your login name: ";
	cin >> loginName;
	cout << "Enter password: ";
	loginPassword = HiddenPass();
	cout << endl;

	while (loginAttempt <= 3)
	{
	    for(i=0; i < NumberUser; i++)
        {
            if (loginName == User[i].Username && loginPassword == User[i].Password)
            {
                cout << "\nWELCOME " << User[i].Username << "\n" << endl;
                return 1;
            }
        }

        cout << "\nInvalid login attempt. Please try again.\n" << '\n';
        loginAttempt++;

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
	account.close();
	return 0;
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
