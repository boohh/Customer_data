#include "UI.h"
#include "CusFile.h"
#include "UIgerman.h"
#include "FileGerman.h"

using namespace std;


int main()
{
	UI U;
	CusFile C;
	UIgerman U2;
	FileGerman C2;

	int Check1, Check2, Check3=3, CheckStart = 0;
	int choice;
	string language;

	ifstream Langua("language.txt");
	getline(Langua, language);
	Langua.close();

	Check2 = atoi(language.c_str());

	while (Check3 != 0)
	{
		// English UI
		if (Check2 == 1 || Check3 == 1 || language.empty())
		{
			if (CheckStart == 0)                        		// if user has just started the program
            {
                cout << "Press 1 to sign-up, press 2 to login" << endl;
                cout << "Your choice: ";
                cin >> choice; cin.ignore();

                while (!cin || (choice > 2) || (choice < 1))
                {
                    choice = 0;
                    cout << "Invalid!!! Please choose again!" << endl;
                    cout << "Your choice: ";
                    cin >> choice;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (choice == 1) {U.SignUp(C); Check1 = U.LoginFunc(C);}
                else if(choice == 2) Check1 = U.LoginFunc(C);
            }

			if (Check1 == 1)									// if login success
			{
				Check3 = U.Interface(C);
				CheckStart = 1;
				if (Check3 == 0) break;
			}
			else												// if login failed
			{
				system("pause");
				return 1;
			}
		}
		// German UI
		if (Check2 == 2 || Check3 == 2)
		{
			if(CheckStart == 0)                         		// if user has just started the program
			{
                cout << "Drücken Sie 1 um sich anzumelden, drücken Sie 2 um sich anzumelden" << endl;
                cout << "Deine Entscheidung: ";
                cin >> choice; cin.ignore();

                while (!cin || (choice > 2) || (choice < 1))
                {
                    choice = 0;
                    cout << "Ungültig!!! Bitte wählen Sie erneut!" << endl;
                    cout << "Deine Entscheidung: ";
                    cin >> choice;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (choice == 1) {U2.SignUp(C2); Check1 = U2.LoginFunc(C2);}
                else if(choice == 2) Check1 = U2.LoginFunc(C2);
			}

			if (Check1 == 1)									// if login success
			{
				Check3 = U2.Interface(C2);
				CheckStart = 1;
			}
			else												// if login failed
			{
				system("pause");
				return 1;
			}
		}
	}

	system("pause");
	return 0;

}
