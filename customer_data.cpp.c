#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
template <typename Customer>
Customer get_input(const std::string &strQuery);

std::string get_username();
std::string get_password();
void save_user(const std::string &username, const std::string &password);

void login();
void register_user();
void main_menu();


int main()
{
    main_menu();
}

template <typename Customer>
Customer get_input(const std::string &strQuery)
{
    std::cout << strQuery << "\n> ";
    Customer out = Customer();

    while (!(std::cin >> out)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
        std::cout << "Error!" "\n";
        std::cout << strQuery << "\n> ";
    }

    return out;
}

std::string get_password()
{
    std::string password1 = get_input <std::string> ("Please enter your password.");
    std::string password2 = get_input <std::string> ("Please re-enter your password.");

    while (password1 != password2) {
        std::cout << "Error! Passwords do not match." "\n";
        password1 = get_input <std::string>("Please enter your password.");
        password2 = get_input <std::string>("Please re-enter your password.");
    }

    return password1;
}

std::string get_username()
{
    std::string username = get_input <std::string>("Please enter a username.");
    std::cout << "Username: \"" << username << "\"\n";

    while (get_input <int>("Confirm? [0|1]") != 1) {
        username = get_input <std::string>("Please enter a username.");
        std::cout << "Username: \"" << username << "\"\n";
    }

    return username;
}

void login()
{
    std::cout << "You are being logged in!" "\n";
}

void main_menu()
{
    int choice = get_input <int>(
        "Hello, Would you like to log in or register?" "\n"
        "[1] Login" "\n"
        "[2] Register" "\n"
        "[3] Exit");

    switch (choice)
	 {
    case 1:
        login();
        break;
    case 2:
        register_user();
        break;
    }
}

void register_user()
{
    std::string username = get_username();
    std::string password = get_password();
    save_user(username, password);
}


struct Email
{
  char s;
  char e;
  char c;
  char hasDot;
  string fileInput;
  string fileOutput;
};


{
    string input;
    cout << "Enter your email address\n";
    getline(cin, input);

    size_t at = input.find('@');
    if (at == string::npos)
    {
        cout << "Missing @ symbol\n";
        return 1;
    }

    size_t dot = input.find('.', at + 1);
    if (dot == string::npos)
    {
        cout << "Missing . symbol after @\n";
        return 2;
    }

    cout << "Email accepted.\n";
    return 0;
}


void save_user(const std::string &username, const std::string &password)
{
    std::string filename = username + ".csv";
    std::ofstream file(filename);
    file << password << "\n";
}


void lastDateModified()
{
struct stat date1;
struct stat date2;

   //File on workstation
   if (stat("c:\\program files\\nav\\navup.exe", &date1) == 0)
   {
	printf("Last modified: %s\n", ctime(&date1.st_mtime));
   }

   //File on server
   if (stat("f:\\navup.exe", &date2) == 0)
   {
	printf("Last modified: %s\n", ctime(&date2.st_mtime));
   }

   if (&date2.st_mtime > &date1.st_mtime)
   {
   	chdir("c:\\progra~1\\nav");
   	system("copy f:\\navup.exe C:\\Progra~1\\NAV\\navup.exe");
   	system("c:\\progra~1\\nav\\navup.exe");
   }

   return 0;
}






