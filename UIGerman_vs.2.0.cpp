#include "UIgerman.h"


// Function make a * mask for password
string UIgerman::HiddenPass(void)
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
void UIgerman::SignUp(FileGerman &CFile)
{
    ofstream account("abcxyz.csv", std::ios_base::app);
    cout << "\nRegistrieren Sie Ihr Konto!!!\n" << endl;
	cout << "Benutzername: ";
	cin >> loginName;
	cout << "Passwort: ";
	loginPassword = HiddenPass();
	cout << "\nEinloggen erfolgreich" << endl;
	account << CFile.encrypted(loginName) << "," << CFile.encrypted(loginPassword) << "\n";
    account.close();
}

// Login function for UI
int UIgerman::LoginFunc(FileGerman &CFile)
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

	cout << "\nAnmelden in Ihrem Konto \n" << endl;
	cout << "Geben Sie den Anmeldenamen ein: ";
	cin >> loginName;
	cout << "Passwort eingeben: ";
	loginPassword = HiddenPass();
	cout << endl;

	while (loginAttempt <= 3)
	{
	    for(i=0; i < NumberUser; i++)
        {
            if (loginName == User[i].Username && loginPassword == User[i].Password)
            {
                cout << "\nWILLKOMMEN " << User[i].Username << "\n" << endl;
                return 1;
            }
        }

        cout << "\nUngültiger Anmeldeversuch. Bitte versuche es erneut!\n" << '\n';
        loginAttempt++;

		if (loginAttempt == 3)
		{
			cout << "ZU VIELEN LOGIN VERSUCHT! ANMELDUNG FEHLGESCHLAGEN\n" << endl;
			return 0;
		}
		cout << "Geben Sie den Anmeldenamen ein: ";
		cin >> loginName; cin.ignore();
		cout << "Passwort eingeben: ";
		loginPassword = HiddenPass();
		cout << endl;
	}
	account.close();
	return 1;
}

// User interface
int UIgerman::Interface(FileGerman &CFile)
{
	int choice = 0;

	while (choice != 8)
	{
		cout << "----------------" << endl;
		cout << "Drücken Sie 1 + Enter: Fügen Sie einen Kunden hinzu" << endl;
		cout << "Drücken Sie 2 + Enter: Ändern Sie den Kontostand des Kunden" << endl;
		cout << "Drücken Sie 3 + Enter: Ändern Sie die E-Mail des Kunden" << endl;
		cout << "Drücken Sie 4 + Enter: Ändern Sie den Nachnamen des Kunden" << endl;
		cout << "Drücken Sie 5 + Enter: Drucken Sie die Kundenliste" << endl;
		cout << "Drücken Sie 6 + Enter: Filtern nach Nachnamen" << endl;
		cout << "Drücken Sie 7 + Enter: Englische Sprache" << endl;
		cout << "Drücken Sie 8 + Enter: Beenden Sie das Programm" << endl;
		cout << "Deine Entscheidung: ";
		cin >> choice; cin.ignore();

		while (!cin || (choice > 8) || (choice < 1))
		{
			choice = 0;
			cout << "Ungültig!!! Bitte wählen Sie erneut!" << endl;
			cout << "Deine Entscheidung: ";
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
			Lang << 1;
			Lang.close();
			return 1;
		}
	}
	return 0;
}
