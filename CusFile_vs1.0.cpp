#include "stdafx.h"
#include "CusFile.h"

// Open the "customer.csv" file, if there isn't that file, create one.
CusFile::CusFile()
{
	ofstream CF("customer.csv", std::ios_base::app);
	CF.close();
}

CusFile::~CusFile() {}

// Function check valid email
int CusFile::checkEmail(string input)
{
	for (int i = 0, n = input.length(); i < n; i++)
	{
		if (input[i] < 33 || input[i] > 126)
		{
			cout << "Can include only letter (a-z, A-Z), digits (0-9), dot (.) and certain special symbols (!#$%&'*+-/=?^_`{|}~)" << endl;
			return 9;
		}
	}

	size_t at = input.find('@');
	if (at == string::npos)
	{
		cout << "Missing @ symbol\n";
		return 1;
	}

	if (input.find("@") <1 || input[(input.find("@") - 1)] == '.' || input[(input.find("@") + 1)] == '.')
	{
		cout << "invalid email, there must be at least one chatacter before and after @ and it shouldn't be '.' \n";
		return 6;
	}

	if (input[0] == '.')
	{
		cout << "invalid email, shouldn't start with '.' \n";
		return 7;
	}

	int t = 0;
	for (int i = 0, n = input.length(); i<n; i++)
	{
		if (input[i] == '@') t++;
	}

	if (t >= 2)
	{
		cout << "There are more than one @" << endl;
		return 2;
	}

	size_t dot = input.find('.', at + 1);
	if (dot == string::npos)
	{
		cout << "Missing . symbol after @\n";
		return 3;
	}


	if ((input.length() - (input.rfind(".") + 1)) < 5 && (input.length() - (input.rfind(".") + 1)) > 1)
	{
		string str = input.substr((input.rfind(".") + 1), (input.length() - (input.rfind(".") + 1)));

		for (int i = 0, n = str.length(); i<n; i++)
		{
			if (!isalpha(str[i]))
			{
				cerr << "Invalid email, all characters must be letter" << endl;
				return 5;
			}
		}
	}
	else
	{
		cout << "Invalid email cuz after the final dot u can just have 2-4 digitals" << endl;
		return 4;
	}

	cout << "Email accepted.\n";
	return 0;
}

// Encrypted information in file
string CusFile::encrypted(string s)
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
string CusFile::decrypted(string s)
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
bool CusFile::acompare(CUSTOMER &lhs, CUSTOMER &rhs) { return (lhs.Name.compare(rhs.Name) < 0); }
bool CusFile::zcompare(CUSTOMER &lhs, CUSTOMER &rhs) { return (lhs.Name.compare(rhs.Name) > 0); }

// Function convert float to string
string CusFile::convertFloatToStr(double d)
{
	stringstream ss;
	ss << d;
	string str = ss.str();
	return str;
}

// Function convert int to string
string CusFile::convertIntToStr(int x)
{
	stringstream ss;
	ss << x;
	string str = ss.str();
	return str;
}

// Function check if string is float
bool CusFile::isFloat(string& s)
{
	istringstream iss(s);
	double dummy;
	iss >> noskipws >> dummy;
	return iss && iss.eof();	// Result converted to bool
}

int CusFile::isName(string& s)			// Function check if name is valid
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
string CusFile::GenerateID()
{
	int x;
	string s;

	ifstream CusF("customer.csv", std::ios_base::app);

	while (CusF.good())
	{
		getline(CusF, id, ',');
		getline(CusF, NAME, ',');
		getline(CusF, EMAIL, ',');
		getline(CusF, BALANCE,',');
		getline(CusF, timelc);
	}

	bool b = id.empty();					// Check if file is empty

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
string CusFile::TLastChanged()
{
	time_t tim;  //create variable of time_t
	time(&tim); //pass variable tim to time function

	string s = ctime(&tim);
	string str = s.erase(s.size() - 1);

	return str;
}

// Function to add customer to the file
void CusFile::AddCustomer()
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
		cout << "Information of customer:" << endl;
		cout << "ID of this customer is: " << id << endl;
		cout << "First name: "; getline(cin, FNAME);

		while (isName(FNAME) == 0)	// Check if first name is valid
		{
			cout << "Your inputed first name is invalid, please input your first name again" << endl;
			cout << "First name: "; getline(cin, FNAME);
		}

		cout << "Last name: "; getline(cin, LNAME);

		while (isName(LNAME) == 0)	// Check if first name is valid
		{
			cout << "Your inputed last name is invalid, please input your last name again" << endl;
			cout << "Last name: "; getline(cin, LNAME);
		}

		cout << "Email: "; cin >> EMAIL; cin.ignore();
		while (checkEmail(EMAIL) != 0)
		{
			cout << "Reinput your email: ";
			cin >> EMAIL; cin.ignore();
		}
		cout << "Balance: "; getline(cin, BALANCE);

		while (!isFloat(BALANCE))
		{
			cout << "Your inputed balance is invalid, please input your balance again" << endl;
			cout << "Balance: "; getline(cin, BALANCE);
		}

		NAME = FNAME + " " + LNAME;

		NAME = encrypted(NAME);
		EMAIL = encrypted(EMAIL);
		timelc = encrypted(TLastChanged());

		CF << id << ',' << NAME << ',' << EMAIL << ',' << BALANCE << "," << timelc;
		cout << "Press Esc button to finish, any other buttons to continue" << endl;
		c = _getch();
		if (c != 27)
		{
			CF << '\n';
			cout << "\nPlease keep adding customer!\n" << endl;
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
void CusFile::ChangeBalance()
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
	cout << "Enter the ID of customer you want to change the balance." << endl;
	cout << "Please enter the right ID syntax which begin with C, then 4 digits and no more than " << Customer[count - 1].ID << endl;
	cout << "ID = ";
	cin >> Id;

	while (std::cout << "Enter the amount of money change: " && !(std::cin >> moneyChange))
	{
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Invalid input; please re-enter.\n";
	}

	for (i = 0; i < count; i++)
	{
		if (Customer[i].ID == Id)
		{
			Customer[i].Balance = convertFloatToStr(atof(Customer[i].Balance.c_str()) + moneyChange);
			cout << "\nName of customer who has balance change: " << decrypted(Customer[i].Name) << endl;
			cout << "\nThe balance now is: " << Customer[i].Balance << endl;
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

// Function to print out all list of customer
void CusFile::PrintfList()
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

	cout << "Choose the way you want to print list!!!" << endl;
	cout << "Press 1 + Enter: Print the original list" << endl;
	cout << "Press 2 + Enter: Print the sorted list from A -> Z by name" << endl;
	cout << "Press 3 + Enter: Print the sorted list from Z -> A by name" << endl;
	cout << "\nYour choice: ";
	cin >> choices; cin.ignore();

	if (choices == 1)
	{
		for (i = 0; i < count; i++)
		{
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "BALANCE: " << Customer[i].Balance << " - " << "TIME LAST CHANGED: " << Customer[i].TimeLastChange << endl;	
		}
	}

	if (choices == 2)
	{
		sort(Customer, Customer + count, acompare);
		for (i = 0; i < count; i++)
		{
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "BALANCE: " << Customer[i].Balance << " - " << "TIME LAST CHANGED: " << Customer[i].TimeLastChange << endl;
		}
	}

	if (choices == 3)
	{
		sort(Customer, Customer + count, zcompare);
		for (i = 0; i < count; i++)
		{
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "BALANCE: " << Customer[i].Balance << " - " << "TIME LAST CHANGED: " << Customer[i].TimeLastChange << endl;
		}
	}

	CF.close();
}

// Function to change email of customer
void CusFile::ChangeEmail()
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
	cout << "Enter the ID of customer you want to change email." << endl;
	cout << "Please enter the right ID syntax which begin with C, then 4 digits and no more than " << Customer[count - 1].ID << endl;
	cout << "ID = ";
	cin >> Id;
	cout << "Enter the new email: ";
	cin >> newEmail;

	for (i = 0; i < count; i++)
	{
		if (Customer[i].ID == Id)
		{
			Customer[i].Email = newEmail;
			cout << "\nName of customer who has email changed: " << decrypted(Customer[i].Name) << endl;
			cout << "\nThe email now is: " << Customer[i].Email << endl;
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
void CusFile::ChangeLastName()
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
	cout << "Enter the ID of customer you want to change last name." << endl;
	cout << "Please enter the right ID syntax which begin with C, then 4 digits and no more than " << Customer[count - 1].ID << endl;
	cout << "ID = ";
	cin >> Id;
	cout << "Enter the new last name: ";
	cin >> newLastName;

	for (i = 0; i < count; i++)
	{
		if (Customer[i].ID == Id)
		{
			Customer[i].FirstName = Customer[i].Name.substr(0, Customer[i].Name.rfind(" "));
			Customer[i].Name = Customer[i].FirstName + " " + newLastName;
			cout << "\nName of customer now is: " << Customer[i].Name << endl;
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

void CusFile::FilterByFirstName()
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

	cout << "Input the first name you want to filter: ";
	cin >> FilterName;

	int n = 0;

	for (i = 0; i < count; i++)
	{
		Customer[i].FirstName = Customer[i].Name.substr(0, Customer[i].Name.find(" "));
		if (FilterName.compare(Customer[i].FirstName) == 0)
		{
			Customer[i].Email = decrypted(Customer[i].Email);
			Customer[i].TimeLastChange = decrypted(Customer[i].TimeLastChange);
			cout << "ID: " << Customer[i].ID << " - " << "NAME: " << Customer[i].Name << " - " << "EMAIL: " << Customer[i].Email << " - " << "BALANCE: " << Customer[i].Balance << " - Time Last Changed: "<< Customer[i].TimeLastChange << endl;
			n++;
		}

	}
	if (n == 0) cout << "There is no customer who has that first name" << endl;

	CF.close();
}
