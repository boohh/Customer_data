#pragma once
#ifndef UI_H_
#define UI_H_

#include<string>
#include<iostream>
#include<conio.h>
#include "CusFile.h"

using namespace std;

class UI : public CusFile
{
public:
	string HiddenPass(void);	// Function make a * mask for password
	int LoginFunc(CusFile &CFile);		// Login function for UI
	int Interface(CusFile &CFile);		// User interface
	void SignUp(CusFile &CFile);          // Function for signing up accounts

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

#endif // !UI_H_
