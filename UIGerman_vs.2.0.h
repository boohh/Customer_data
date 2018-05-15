#ifndef UIGERMAN_H
#define UIGERMAN_H

#include<string>
#include<iostream>
#include<conio.h>
#include "FileGerman.h"

using namespace std;

class UIgerman : public FileGerman
{
public:
	string HiddenPass(void);	// Function make a * mask for password
	void SignUp(FileGerman &CFile);          // Function for signing up accounts
	int LoginFunc(FileGerman &CFile);		// Login function for UI
	int Interface(FileGerman &CFile);		// User interface

private:
	string loginName;
	string loginPassword;

	typedef struct user
	{
		string Username;
		string Password;
	} USER;

	USER User[50];
};

#endif // UIGERMAN_H
