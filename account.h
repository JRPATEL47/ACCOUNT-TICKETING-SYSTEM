#pragma once



#ifndef ACCOUNT_H_
#define ACCOUNT_H_


#define ACCOUNTSFILE "accounts.txt"
#define ACCOUNTSARCFILE "accounts_arc.txt"



// MACROS

#define COUNTRY_NAME_LENGTH 30
#define CUSTOMER_NAME_LENGTH 30
#define USERLOGIN_NAME_LENGTH 10
#define PASSWORD_LENGTH 8
#define MIN_CHARS 1
#define MIN_AGE 18
#define MAX_AGE 110
#define SYMBOLS 8

// STRUCTURES

struct Demographic
{
	int birthYear;
	double houseIncome;
	char country[COUNTRY_NAME_LENGTH + 1];
};

struct UserLogin
{
	char customerName[CUSTOMER_NAME_LENGTH + 1];
	char userLogin[USERLOGIN_NAME_LENGTH + 1];
	char password[PASSWORD_LENGTH + 1];
};

struct Account
{
	int accountNumber;
	char accountType;
	struct UserLogin login;
	struct Demographic demo;

};

#endif 

//FUNCTIONS DECLARATIONS

//Displays a title : "Account Data: New Record"
void getAccount(struct Account* accountData);

//Displays a title: "User Login Data Input"
void getUserLogin(struct Account* accountData);

//Displays a title: "Demographic Data Input"
void getDemographic(struct Account* accountData);

//Display's the update menu options for the account until the user wishes to exit.
void updateAccount(struct Account* accountData);

//Display's the update menu options for the user login until the user wishes to exit.
void updateUserLogin(struct UserLogin* user_login);

//A menu with options to modifying specific members of a Demographic:
void updateDemographic(struct Demographic* demo);

//To Convert lowercase country name to uppercase country name
void uppercaseCountry(struct Demographic* demo);

//To validate password strength
void checkPasswordStrength(struct UserLogin* user_login);

//To check for whitespaces in user login name
void checkSpacesUserLogin(struct UserLogin* user_login);

// To load accounts data from the accounts.txt file
int loadAccounts(struct Account accountData[], int maxElements);

// To archive removed accounts in accounts_arc.txt
int archiveRemovedAccount(const struct Account* accountData);

// To save the current updated accounts in accounts.txt
int saveCurrentAccounts(const struct Account accountData[], int maxElements);

