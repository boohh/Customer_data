#pragma once
#ifndef CusFile_H_
#define CusFile_H_

#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<stdlib.h>
#include <sstream>
#include <ctype.h>
#include <limits>
#include <algorithm>
#include <utility>
#include <time.h>

using namespace std;

class CusFile
{
private:
	typedef struct customer
	{
		string Name;
		string LastName;
		string FirstName;
		string Email;
		string ID;
		string Balance;
		string TimeLastChange;
	} CUSTOMER;

	CUSTOMER Customer[1000];

	string NAME;
	string LNAME;
	string FNAME;
	string BALANCE;
	string EMAIL;
	string id;
	string timelc;

	int i;

public:
	CusFile();	// Open the "customer.csv" file, if there isn't that file, create one.
	~CusFile();
	static bool acompare(CUSTOMER &lhs, CUSTOMER &rhs);	// Function compare name of customer a->z
	static bool zcompare(CUSTOMER &lhs, CUSTOMER &rhs);	// Function compare name of customer z->a
	string convertFloatToStr(double);			// Function convert float to string
	string convertIntToStr(int);				// Function convert int to string
	bool isFloat(string& s);					// Function check if string is float
	int isName(string& s);						// Function check if name is valid

	int checkEmail(string);						// Function to check email is valid or not
	string GenerateID();						// Function to generate unique ID
	void AddCustomer();							// Function to add customer to the file
	void ChangeBalance();						// Function to change the balance of customer
	void PrintfList();							// Function to print out all list of customer
	void ChangeEmail();							// Function to change email of customer
	void ChangeLastName();						// Function to change last name of customer
	void FilterByFirstName();						// Function to filter by name
	inline string TLastChanged();						// Function to show the date last change
	inline string encrypted(string);					// Encrypted information in file
	inline string decrypted(string);					// Decrypted information in file

};

#endif // CUSFILE_H
