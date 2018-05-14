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
	int LoginFunc(void);		// Login function for UI
	int Interface(CusFile &CFile);		// User interface

private:
	string loginName;
	string loginPassword;
	int loginAttempt = 0;

	int i;
};

#endif // !UI_H_
