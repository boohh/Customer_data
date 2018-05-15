#include "FileGerman.h"

FileGerman::FileGerman()
{
	ofstream CF("customer.csv", std::ios_base::app);
	CF.close();
}


FileGerman::~FileGerman()
{
}

//Function to check email is valid or not
int FileGerman::checkEmail(string input)
{
	for (int i = 0, n = input.length(); i < n; i++)
	{
		if (input[i] < 33 || input[i] > 126)
		{
			cout << "Kann nur Buchstaben (a-z, A-Z), Ziffern (0-9), Punkte (.) Und bestimmte Sonderzeichen (! # $% & '* + - / =? ^ _ `{|} ~) Enthalten" << endl;
			return 9;
		}
	}

	size_t at = input.find('@');
	if (at == string::npos)
	{
		cout << "Fehlendes @ Symbol \n";
		return 1;
	}

	if (input.find("@") <1 || input[(input.find("@") - 1)] == '.' || input[(input.find("@") + 1)] == '.')
	{
		cout << "Ungültige E-Mail, es muss mindestens einen Chatacter vor und nach @ geben und es sollte nicht '.' \n" << endl;
		return 6;
	}

	if (input[0] == '.')
	{
		cout << "ngültige E-Mail, sollte nicht mit '.' Beginnen \n";
		return 7;
	}

	int t = 0;
	for (int i = 0, n = input.length(); i<n; i++)
	{
		if (input[i] == '@') t++;
	}

	if (t >= 2)
	{
		cout << "Es gibt mehr als eine @" << endl;
		return 2;
	}

	size_t dot = input.find('.', at + 1);
	if (dot == string::npos)
	{
		cout << "Vermisst. Symbol nach @ \n";
		return 3;
	}


	if ((input.length() - (input.rfind(".") + 1)) < 5 && (input.length() - (input.rfind(".") + 1)) > 1)
	{
		string str = input.substr((input.rfind(".") + 1), (input.length() - (input.rfind(".") + 1)));

		for (int i = 0, n = str.length(); i<n; i++)
		{
			if (!isalpha(str[i]))
			{
				cerr << "Ungültige E-Mail, alle Zeichen müssen Buchstaben sein" << endl;
				return 5;
			}
		}
	}
	else
	{
		cout << "Ungültige E-Mail Cuz nach dem letzten Punkt u kann nur 2-4 digitals haben" << endl;
		return 4;
	}

	cout << "E-Mail akzeptiert.\n";
	return 0;
}

// Encrypted information in file
string FileGerman::encrypted(string s)
{
	int m = s.length();
	string k = "softwareengineering";
	int n = k.length();
	for (int i = 0; i<n; i++)
	{
		k[i] = k[i] - 97;
	}

	string c = s;

	for (int i = 0, j = 0; i < m; i++)
	{
		if (isalpha(s[i]))
		{
			if (islower(s[i]))
			{
				c[i] = (s[i] + k[j] - 97) % 26 + 97;
			}
			else if (isupper(s[i]))
			{
				c[i] = (s[i] + k[j] - 65) % 26 + 65;
			}

			j++;
			if (j >= n) j = 0;
		}
	}
	return c;
}

// Decrypted information in file
string FileGerman::decrypted(string s)
{
	int m = s.length();
	string k = "softwareengineering";
	int n = k.length();
	for (int i = 0; i<n; i++)
	{
		k[i] = k[i] - 97;
	}

	string c = s;

	for (int i = 0, j = 0; i < m; i++)
	{
		if (isalpha(s[i]))
		{

			if (islower(s[i]))
			{
				if ((s[i] - k[j]) < 97) c[i] = s[i] - k[j] + 26;
				else c[i] = s[i] - k[j];
			}
			else if (isupper(s[i]))
			{
				if ((s[i] - k[j]) < 65) c[i] = s[i] - k[j] + 26;
				else c[i] = s[i] - k[j];
			}

			j++;
			if (j >= n) j = 0;
		}
	}
	return c;
}

// Fuctions to compare name of customer
bool FileGerman::acompare(CUSTOMER &lhs, CUSTOMER &rhs) { return (lhs.Name.compare(rhs.Name) < 0); }
bool FileGerman::zcompare(CUSTOMER &lhs, CUSTOMER &rhs) { return (lhs.Name.compare(rhs.Name) > 0); }

// Function convert float to string
string FileGerman::convertFloatToStr(double d)
{
	stringstream ss;
	ss << d;
	string str = ss.str();
	return str;
}

// Function convert int to string
string FileGerman::convertIntToStr(int x)
{
	stringstream ss;
	ss << x;
	string str = ss.str();
	return str;
}

// Function check if string is float
bool FileGerman::isFloat(string& s)
{
	istringstream iss(s);
	double dummy;
	iss >> noskipws >> dummy;
	return iss && iss.eof();	// Result converted to bool
}

int FileGerman::isName(string& s)			// Function check if name is valid
{
	int n = s.length();
	for (i = 0, n; i < n; i++)
	{
		if ((isalpha(s[i]) == 0) && (s[i] != ' '))
		{
			return 0;
		}
	}
	return 1;
}

// Function to generate unique ID
string FileGerman::GenerateID()
{
	int x;
	string s;
	bool b;

	ifstream CusF("customer.csv", std::ios_base::app);

	while (CusF.good())
	{
		getline(CusF, id, ',');
		getline(CusF, NAME, ',');
		getline(CusF, EMAIL, ',');
		getline(CusF, BALANCE, ',');
		getline(CusF, timelc);
	}

	b = id.empty();					// Check if file is empty

	if (b) id = "C0001";
	else
	{
		s = id.substr(1, 4);
		x = atoi(s.c_str());
		x = x + 1;
		s = convertIntToStr(x);
		x = id.length() - s.length();
		id = id.substr(0, x) + s;
	}

	CusF.close();

	return id;
}

// Function to show the date last change
string FileGerman::TLastChanged()
{
	time_t tim;  //create variable of time_t
	time(&tim); //pass variable tim to time function

	string s = ctime(&tim);
	string str = s.erase(s.size() - 1);

	return str;
}

// Function to add customer to the file
void FileGerman::AddCustomer()
{
	char c;
	int x;
	string s;

	id = GenerateID();

	ofstream CF("customer.csv", std::ios_base::app);
	if (id != "C0001") CF << '\n';
	do
	{
		cout << "----------------" << endl;
		cout << "Information des Kunden:" << endl;
		cout << "ID dieses Kunden ist: " << id << endl;
		cout << "Vorname: "; getline(cin, FNAME);

		while (isName(FNAME) == 0)	// Check if first name is valid
		{
			cout << "Ihr eingegebener Vorname ist ungültig, bitte geben Sie Ihren Vornamen erneut ein" << endl;
			cout << "Vorname: "; getline(cin, FNAME);
		}

		cout << "Nachname: "; getline(cin, LNAME);

		while (isName(LNAME) == 0)	// Check if first name is valid
		{
			cout << "Ihr eingegebener Nachname ist ungültig, bitte geben Sie Ihren Nachnamen erneut ein" << endl;
			cout << "Nachname: "; getline(cin, LNAME);
		}

		cout << "Email: "; cin >> EMAIL; cin.ignore();
		while (checkEmail(EMAIL) != 0)
		{
			cout << "Reinige deine E-Mail: ";
			cin >> EMAIL; cin.ignore();
		}
		cout << "Kontostand: "; getline(cin, BALANCE);

		while (!isFloat(BALANCE))
		{
			cout << "Ihr eingegebener Kontostand ist ungültig, bitte geben Sie Ihren Kontostand erneut ein" << endl;
			cout << "Kontostand: "; getline(cin, BALANCE);
		}

		NAME = FNAME + " " + LNAME;

		NAME = encrypted(NAME);
		EMAIL = encrypted(EMAIL);
		timelc = encrypted(TLastChanged());

		CF << id << ',' << NAME << ',' << EMAIL << ',' << BALANCE << "," << timelc;
		cout << "Drücken Sie die ESC-Taste, um zu beenden, irgendwelche anderen Knöpfe, um fortzufahren" << endl;
		c = _getch();
		if (c != 27)
		{
			CF << '\n';
			cout << "\nBitte fügen Sie weitere Kunden hinzu!\n" << endl;
			s = id.substr(1, 4);
			x = atoi(s.c_str());
			x = x + 1;
			s = convertIntToStr(x);
			x = id.length() - s.length();
			id = id.substr(0, x) + s;
		}
	} while (c != 27);
	CF.close();
}

// Function to change the balance of customer
void FileGerman::ChangeBalance()
{
	double moneyChange;
	string Id;

	ifstream CF("customer.csv", std::ios_base::app);

	i = 0;
	while (CF.good())
	{
		getline(CF, Customer[i].ID, ',');
		getline(CF, Customer[i].Name, ',');
		getline(CF, Customer[i].Email, ',');
		getline(CF, Customer[i].Balance, ',');
		getline(CF, Customer[i].TimeLastChange);
		i++;
	}

	int count = i;

	cout << "----------------" << endl;
	cout << "Geben Sie die Kundennummer ein, um den Kontostand zu ändern." << endl;
	cout << "Bitte geben Sie die richtige ID-Syntax ein, die mit C beginnt, dann 4 Ziffern und nicht mehr als " << Customer[count - 1].ID << endl;
	cout << "ID = ";
	cin >> Id;

	while (std::cout << "Geben Sie die Geldbetragsänderung ein: " && !(std::cin >> moneyChange))
	{
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Ungültige Eingabe; Bitte erneut eingeben!\n";
	}

	for (i = 0; i < count; i++)
	{
		if (Customer[i].ID == Id)
		{
			Customer[i].Balance = convertFloatToStr(atof(Customer[i].Balance.c_str()) + moneyChange);
			cout << "\nName des Kunden, der Kontostand ändert: " << decrypted(Customer[i].Name) << endl;
			cout << "\nDer Kontostand ist jetzt: " << Customer[i].Balance << endl;
			Customer[i].TimeLastChange = TLastChanged();
			Customer[i].TimeLastChange = encrypted(Customer[i].TimeLastChange);
			break;
		}
	}

	CF.close();

	remove("customer.csv");

	ofstream CF1("customer.csv", std::ios_base::app);

	for (i = 0; i < count; i++)
	{
		CF1 << Customer[i].ID << "," << Customer[i].Name << "," << Customer[i].Email << "," << Customer[i].Balance << "," << Customer[i].TimeLastChange;
		if (i < (count - 1)) CF1 << '\n';
	}
	CF1.close();
}

// Function to change email of customer
void FileGerman::ChangeEmail()
{
	string newEmail;
	string Id;

	ifstream CF("customer.csv", std::ios_base::app);

	i = 0;
	while (CF.good())
	{
		getline(CF, Customer[i].ID, ',');
		getline(CF, Customer[i].Name, ',');
		getline(CF, Customer[i].Email, ',');
		getline(CF, Customer[i].Balance, ',');
		getline(CF, Customer[i].TimeLastChange);
		i++;
	}

	int count = i;

	cout << "----------------" << endl;
	cout << "Geben Sie die ID des Kunden ein, dessen E-Mail Sie ändern möchten." << endl;
	cout << "Bitte geben Sie die richtige ID-Syntax ein, die mit C beginnt, dann 4 Ziffern und nicht mehr als " << Customer[count - 1].ID << endl;
	cout << "ID = ";
	cin >> Id;
	cout << "Geben Sie die neue E-Mail ein: ";
	cin >> newEmail;

	for (i = 0; i < count; i++)
	{
		if (Customer[i].ID == Id)
		{
			Customer[i].Email = newEmail;
			cout << "\nName des Kunden, der die E-Mail geändert hat: " << decrypted(Customer[i].Name) << endl;
			cout << "\nDie E-Mail ist jetzt: " << Customer[i].Email << endl;
			Customer[i].Email = encrypted(Customer[i].Email);
			Customer[i].TimeLastChange = TLastChanged();
			Customer[i].TimeLastChange = encrypted(Customer[i].TimeLastChange);
			break;
		}
	}

	CF.close();

	remove("customer.csv");

	ofstream CF1("customer.csv", std::ios_base::app);

	for (i = 0; i < count; i++)
	{
		CF1 << Customer[i].ID << "," << Customer[i].Name << "," << Customer[i].Email << "," << Customer[i].Balance << "," << Customer[i].TimeLastChange;
		if (i < (count - 1)) CF1 << '\n';
	}
	CF1.close();
}

// Function to change last name of customer
void FileGerman::ChangeLastName()
{
	string newLastName;
	string Id;

	ifstream CF("customer.csv", std::ios_base::app);

	i = 0;
	while (CF.good())
	{
		getline(CF, Customer[i].ID, ',');
		getline(CF, Customer[i].Name, ',');
		Customer[i].Name = decrypted(Customer[i].Name);
		getline(CF, Customer[i].Email, ',');
		getline(CF, Customer[i].Balance, ',');
		getline(CF, Customer[i].TimeLastChange);
		i++;
	}

	int count = i;

	cout << "----------------" << endl;
	cout << "Geben Sie die ID des Kunden ein, für den Sie den Nachnamen ändern möchten." << endl;
	cout << "Bitte geben Sie die richtige ID-Syntax ein, die mit C beginnt, dann 4 Ziffern und nicht mehr als " << Customer[count - 1].ID << endl;
	cout << "ID = ";
	cin >> Id;
	cout << "Geben Sie den neuen Nachnamen ein: ";
	cin >> newLastName;

	for (i = 0; i < count; i++)
	{
		if (Customer[i].ID == Id)
		{
			Customer[i].FirstName = Customer[i].Name.substr(0, Customer[i].Name.rfind(" "));
			Customer[i].Name = Customer[i].FirstName + " " + newLastName;
			cout << "\nName des Kunden ist jetzt: " << Customer[i].Name << endl;
			Customer[i].TimeLastChange = TLastChanged();
			Customer[i].TimeLastChange = encrypted(Customer[i].TimeLastChange);
			break;
		}
	}

	CF.close();

	remove("customer.csv");

	ofstream CF1("customer.csv", std::ios_base::app);

	for (i = 0; i < count; i++)
	{
		Customer[i].Name = encrypted(Customer[i].Name);
		CF1 << Customer[i].ID << "," << Customer[i].Name << "," << Customer[i].Email << "," << Customer[i].Balance << "," << Customer[i].TimeLastChange;
		if (i < (count - 1)) CF1 << '\n';
	}
	CF1.close();
}

void FileGerman::FilterByFirstName()
{
	string FilterName;
	ifstream CF("customer.csv", std::ios_base::app);

	i = 0;
	while (CF.good())
	{
		getline(CF, Customer[i].ID, ',');
		getline(CF, Customer[i].Name, ',');
		Customer[i].Name = decrypted(Customer[i].Name);
		getline(CF, Customer[i].Email, ',');
		getline(CF, Customer[i].Balance, ',');
		getline(CF, Customer[i].TimeLastChange);
		i++;
	}

	int count = i;

	cout << "Geben Sie den Vornamen ein, den Sie filtern möchten: ";
	cin >> FilterName;

	int n = 0;

	for (i = 0; i < count; i++)
	{
		Customer[i].FirstName = Customer[i].Name.substr(0, Customer[i].Name.find(" "));
		if (FilterName.compare(Customer[i].FirstName) == 0)
		{
			Customer[i].Email = decrypted(Customer[i].Email);
			Customer[i].TimeLastChange = decrypted(Customer[i].TimeLastChange);
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "KONTOSTAND: " << Customer[i].Balance << " - Letzte Änderung der Zeit: " << Customer[i].TimeLastChange << endl;
			n++;
		}

	}
	if (n == 0) cout << "Es gibt keinen Kunden, der diesen Vornamen hat." << endl;

	CF.close();
}

// Function to print out all list of customer
void FileGerman::PrintfList()
{
	ifstream CF("customer.csv");

	cout << "----------------" << endl;

	i = 0;

	while (CF.good())
	{
		getline(CF, Customer[i].ID, ',');
		getline(CF, Customer[i].Name, ',');
		Customer[i].Name = decrypted(Customer[i].Name);
		getline(CF, Customer[i].Email, ',');
		Customer[i].Email = decrypted(Customer[i].Email);
		getline(CF, Customer[i].Balance, ',');
		getline(CF, Customer[i].TimeLastChange);
		Customer[i].TimeLastChange = decrypted(Customer[i].TimeLastChange);
		i++;
	}

	int count = i;
	int choices;

	cout << "Wählen Sie die Art, wie Sie die Liste drucken möchten!!!" << endl;
	cout << "Drücken Sie 1 + Eingabe: Drucken Sie die ursprüngliche Liste" << endl;
	cout << "Drücken Sie 2 + Enter: Drucken Sie die sortierte Liste von A -> Z nach Namen" << endl;
	cout << "Drücken Sie 3 + Enter: Drucken Sie die sortierte Liste von Z -> A nach Namen" << endl;
	cout << "\nDeine Entscheidung: ";
	cin >> choices; cin.ignore();

	if (choices == 1)
	{
		for (i = 0; i < count; i++)
		{
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "KONTOSTAND: " << Customer[i].Balance << " - " << "Letzte Änderung der Zeit: " << Customer[i].TimeLastChange << endl;
		}
	}

	if (choices == 2)
	{
		sort(Customer, Customer + count, acompare);
		for (i = 0; i < count; i++)
		{
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "KONTOSTAND: " << Customer[i].Balance << " - " << "Letzte Änderung der Zeit: " << Customer[i].TimeLastChange << endl;
		}
	}

	if (choices == 3)
	{
		sort(Customer, Customer + count, zcompare);
		for (i = 0; i < count; i++)
		{
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "KONTOSTAND: " << Customer[i].Balance << " - " << "Letzte Änderung der Zeit: " << Customer[i].TimeLastChange << endl;
		}
	}

	CF.close();
}
