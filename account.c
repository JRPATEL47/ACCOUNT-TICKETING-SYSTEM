

#define _CRT_SECURE_NO_WARNINGS

  // SYSTEM LIBRARY
#include<stdio.h>
#include<ctype.h>

  //USER LIBRARY
#include "commonHelpers.h"
#include "account.h"


//Displays a title : "Account Data: New Record"
void getAccount(struct Account* accountData)
{

	printf("New Account Data (Account#:%d)\n", accountData->accountNumber);
	printf("----------------------------------------\n");

	printf("Enter the account type (A=Agent | C=Customer): ");
	accountData->accountType = getCharOption("AC");

	putchar('\n');

}

//Displays a title: "User Login Data Input"
void getUserLogin(struct Account* accountData)
{

	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	checkSpacesUserLogin(&accountData->login);

	printf("Enter the display name (%d chars max): ", CUSTOMER_NAME_LENGTH);
	getCString(accountData->login.customerName, MIN_CHARS, CUSTOMER_NAME_LENGTH);

	checkPasswordStrength(&accountData->login);

	putchar('\n');

}

//Displays a title: "Demographic Data Input"
void getDemographic(struct Account* accountData)
{

	int get_current_year;
	int minYear, maxYear;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");

	get_current_year = currentYear();
	minYear = get_current_year - 110;
	maxYear = get_current_year - 18;

	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	accountData->demo.birthYear = getIntFromRange(minYear, maxYear);

	printf("Enter the household Income: $");
	accountData->demo.houseIncome = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", COUNTRY_NAME_LENGTH);
	getCString(accountData->demo.country, MIN_CHARS, COUNTRY_NAME_LENGTH);

	uppercaseCountry(&accountData->demo);
	putchar('\n');


}

//Display's the update menu options for the account until the user wishes to exit.
void updateAccount(struct Account* accountData)
{
	int updateOption, min = 0, max = 3;
	int repeatLoop = 1;

	do
	{

		printf("Account: %d - Update Options\n", accountData->accountNumber);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", accountData->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		updateOption = getIntFromRange(min, max);
		putchar('\n');

		switch (updateOption)
		{
		case 1:

			printf("Enter the account type (A=Agent | C=Customer): ");
			accountData->accountType = getCharOption("AC");

			break;

		case 2:

			updateUserLogin(&accountData->login);

			break;

		case 3:

			updateDemographic(&accountData->demo);

			break;
		case 0:

			repeatLoop = 0;
			break;

		}

	} while (repeatLoop);

}

//Display's the update menu options for the user login until the user wishes to exit.
void updateUserLogin(struct UserLogin* user_login)
{
	int updateOption, min = 0, max = 2;
	int repeatLoop = 1;


	do
	{

		printf("User Login: %s - Update Options\n", user_login->userLogin);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", user_login->customerName);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		updateOption = getIntFromRange(min, max);
		putchar('\n');

		switch (updateOption)
		{
		case 1:

			printf("Enter the display name (%d chars max): ", CUSTOMER_NAME_LENGTH);
			getCString(user_login->customerName, MIN_CHARS, CUSTOMER_NAME_LENGTH);
			putchar('\n');
			break;

		case 2:

			checkPasswordStrength(user_login);

			printf("\n");;

			break;

		case 0:

			repeatLoop = 0;

			break;

		}

	} while (repeatLoop);

}

//a menu with options to modifying specific members of a Demographic:
void updateDemographic(struct Demographic* demo)
{
	int updateOption, min = 0, max = 2;
	int repeatLoop = 1;

	do
	{

		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demo->houseIncome);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\n");
		printf("Selection: ");
		updateOption = getIntFromRange(min, max);
		putchar('\n');

		switch (updateOption)
		{
		case 1:

			printf("Enter the household Income: $");
			demo->houseIncome = getPositiveDouble();

			putchar('\n');

			break;

		case 2:

			printf("Enter the country (%d chars max.): ", COUNTRY_NAME_LENGTH);
			getCString(demo->country, MIN_CHARS, COUNTRY_NAME_LENGTH);


			uppercaseCountry(demo);


			putchar('\n');

			break;

		case 0:

			repeatLoop = 0;

			break;

		}

	} while (repeatLoop);

}


//To Convert lowercase country name to uppercase country name
void uppercaseCountry(struct Demographic* demo)
{
	int i = 0;

	do
	{

		if (islower(demo->country[i]))
		{
			demo->country[i] = toupper(demo->country[i]);
		}
		i++;

	} while (demo->country[i] != '\0');


}

//To validate password strength
void checkPasswordStrength(struct UserLogin* user_login)
{
	int countDigit, countUpper, countLower, countSymbol;
	int i = 0, j = 0;
	int keepRepeating = 1;
	char symbols[SYMBOLS + 1] = "!@#$%^&*";

	do
	{
		countDigit = 0;
		countUpper = 0;
		countLower = 0;
		countSymbol = 0;

		printf("Enter the password (must be %d chars in length): ", PASSWORD_LENGTH);
		getCString(user_login->password, PASSWORD_LENGTH, PASSWORD_LENGTH);


		i = 0;
		do
		{
			if (isdigit(user_login->password[i]))
			{
				countDigit++;
			}

			if (isupper(user_login->password[i]))
			{
				countUpper++;
			}

			if (islower(user_login->password[i]))
			{
				countLower++;
			}

			if (!islower(user_login->password[i]) && !isupper(user_login->password[i]) && !isdigit(user_login->password[i]))
			{
				for (j = 0; j < SYMBOLS; j++)
				{
					if (user_login->password[i] == symbols[j])
					{

						countSymbol++;

					}

				}

			}

			i++;

		} while (user_login->password[i] != '\0');

		if (countDigit == 2 && countLower == 2 && countUpper == 2 && countSymbol == 2)
		{

			keepRepeating = 0;

		}
		else
		{

			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");

		}

	} while (keepRepeating);

}


//To check for whitespaces in user login name
void checkSpacesUserLogin(struct UserLogin* user_login)
{
	int count = 0;
	int repeatLoop = 1;
	int i = 0;

	do
	{
		count = 0;

		printf("Enter user login (%d chars max): ", USERLOGIN_NAME_LENGTH);
		getCString(user_login->userLogin, MIN_CHARS, USERLOGIN_NAME_LENGTH);

		do
		{
			if (isspace(user_login->userLogin[i]))
			{
				count++;
			}

			i++;
		} while (user_login->userLogin[i] != '\0');

		if (count > 0)
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
		}
		else
		{
			repeatLoop = 0;
		}

	} while (repeatLoop);

}

// To load accounts data from the accounts.txt file
int loadAccounts(struct Account accountData[], int maxElements)
{
	int countAccounts = 0;
	char ch;
	FILE* fp = fopen(ACCOUNTSFILE, "r");

	if (fp != NULL)
	{

		while (countAccounts < maxElements && fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]%c",
			&accountData[countAccounts].accountNumber,
			&accountData[countAccounts].accountType,
			accountData[countAccounts].login.customerName,
			accountData[countAccounts].login.userLogin,
			accountData[countAccounts].login.password,
			&accountData[countAccounts].demo.birthYear,
			&accountData[countAccounts].demo.houseIncome,
			accountData[countAccounts].demo.country, &ch) == 9)
		{

			if (ch != '\n')
			{
				while (fgetc(fp) != '\n');
			}

			countAccounts++;
		}

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}

	return countAccounts;
}

// To archive removed accounts in accounts_arc.txt
int archiveRemovedAccount(const struct Account* accountData)
{
	int result = 0;

	FILE* fp = fopen(ACCOUNTSARCFILE, "a");

	if (fp != NULL)
	{

		result = fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accountData->accountNumber,
			accountData->accountType,
			accountData->login.customerName,
			accountData->login.userLogin,
			accountData->login.password,
			accountData->demo.birthYear,
			accountData->demo.houseIncome,
			accountData->demo.country);

		fflush(fp);
		fclose(fp);
		fp = NULL;

	}
	else
	{
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

	}

	return result > 0 ? 1 : 0;

}

// To save the current updated accounts in accounts.txt
int saveCurrentAccounts(const struct Account accountData[], int maxElements)
{
	int i = 0, countAccounts = 0;

	FILE* fp = fopen(ACCOUNTSFILE, "w");

	if (fp != NULL)
	{

		for (i = 0; i < maxElements; i++)
		{
			if (accountData[i].accountNumber > 0)
			{

				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accountData[i].accountNumber,
					accountData[i].accountType,
					accountData[i].login.customerName,
					accountData[i].login.userLogin,
					accountData[i].login.password,
					accountData[i].demo.birthYear,
					accountData[i].demo.houseIncome,
					accountData[i].demo.country);

				countAccounts++;
			}

		}

		fflush(fp);
		fclose(fp);
		fp = NULL;

	}
	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

	}
	return countAccounts;
}
