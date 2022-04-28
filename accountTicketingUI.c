

#define _CRT_SECURE_NO_WARNINGS

  //SYSTEM LIBRARIES
#include<stdio.h>
#include<string.h>

//USER LIBRARIES
#include "account.h"
#include"commonHelpers.h"
#include"accountTicketingUI.h"


  //FUNCTIONS DEFINITIONS

//Displays a formatted table header with three (3) column
void displayAccountSummaryHeader()
{

	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");

}

//Displays a formatted table header with seven (7) column
void displayAccountDetailHeader()
{

	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");

}

//Displays a formatted record that aligns to the respective header as defined in function "displayAccountSummaryHeader" described earlier
void displayAccountSummaryRecord(const struct Account* accountData)
{

	printf("%05d %-9s %5d", accountData->accountNumber, accountData->accountType == 'A' ? "AGENT" : "CUSTOMER", accountData->demo.birthYear);
	putchar('\n');

}

//Displays a formatted record that aligns to the respective header as defined in function "displayAccountDetailHeader" described earlier
void displayAccountDetailRecord(struct Account* accountData)
{
	int i;
	int count = 0;

	count = strlen(accountData->login.password);

	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s ", accountData->accountNumber, accountData->accountType == 'A' ? "AGENT" : "CUSTOMER", accountData->demo.birthYear, accountData->demo.houseIncome, accountData->demo.country, accountData->login.customerName, accountData->login.userLogin);

	for (i = 0; i < count; i++)
	{

		if ((i + 1) % 2 == 0)
		{

			printf("*");

		}
		else
		{

			printf("%c", accountData->login.password[i]);

		}

	}

	putchar('\n');

}

//Display's the customer's main menu options until the user wishes to logout
void  menuCustomer(struct Ticket* ticketData, struct Account* accountInfo, int maxElements)
{

	int customerOption = 0;
	int min = 0, max = 4;
	int repeatLoop = 1;
	int count = 0;

	do
	{

		printf("CUSTOMER: %s (%d)\n", accountInfo->login.customerName, accountInfo->accountNumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		customerOption = getIntFromRange(min, max);
		putchar('\n');

		switch (customerOption)
		{
		case 1:

			displayAccountDetailHeader();
			displayAccountDetailRecord(accountInfo);
			putchar('\n');
			pauseExecution();

			break;

		case 2:

			createNewTicket(ticketData, accountInfo, maxElements);

			break;

		case 3:

			modifyCustomerTicket(ticketData, accountInfo, maxElements);

			break;

		case 4:

			displayCustomerTicketMessage(ticketData, accountInfo, maxElements);

			break;

		case 0:

			count = saveCurrentTickets(ticketData, maxElements);

			printf("Saving session modifications...\n");
			printf("   %d tickets saved.\n", count);
			printf("### LOGGED OUT ###\n\n");
			repeatLoop = 0;

			break;

		}

	} while (repeatLoop);

}

//Displays Ticket's Header
void displayTicketHeader(void)
{

	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");

}

//Display's New Tickets
void displayNewTicketMessage(const struct AccountTicketingData* newTicket)
{

	int i = 0, j = 0;
	int keepRepeating = 1, keepLoop = 1, ticketNo;
	int count = 0;

	do
	{

		keepLoop = 1;
		displayTicketHeader();

		for (i = 0; i < newTicket->TICKET_MAX_SIZE; i++)
		{

			if (newTicket->tickets[i].countMessage == NEW_MESSAGE_COUNT && newTicket->tickets[i].uniqueNum != 0)
			{

				printf("%06d %5d %-15s %-6s %-30s %5d\n", newTicket->tickets[i].uniqueNum, newTicket->tickets[i].customer_account_number, newTicket->tickets[i].messageInfo->displayName, newTicket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", newTicket->tickets[i].subjectLine, newTicket->tickets[i].countMessage);

			}

		}

		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");

		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		do
		{

			ticketNo = getInteger();

			if (ticketNo < 0)
			{

				printf("ERROR: Value must be positive or zero: ");

			}
			else if (ticketNo == 0)
			{

				putchar('\n');
				keepRepeating = 0;
				keepLoop = 0;

			}
			else
			{

				putchar('\n');
				keepLoop = 0;

			}

		} while (keepLoop);

		keepLoop = 1;

		if (ticketNo != 0)
		{

			count = 0;
			for (i = 0; i < newTicket->TICKET_MAX_SIZE && keepLoop; i++)
			{

				if (newTicket->tickets[i].uniqueNum == ticketNo && newTicket->tickets[i].uniqueNum != 0)
				{

					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", newTicket->tickets[i].uniqueNum, newTicket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", newTicket->tickets[i].subjectLine);
					printf("================================================================================\n");

					for (j = 0; j < newTicket->tickets[i].countMessage; j++)
					{

						printf("%s (%s):\n", newTicket->tickets[i].messageInfo[j].account_type_author == 'A' ? "AGENT" : "CUSTOMER", newTicket->tickets[i].messageInfo[j].displayName);
						printf("   %s\n\n", newTicket->tickets[i].messageInfo[j].messageDetail);

						count++;

						if (count % 5 == 0)
						{

							pauseExecution();

						}

					}

					if (count % 5 != 0)
					{

						pauseExecution();

					}

					keepLoop = 0;

				}

			}

		}

		if (ticketNo != 0)
		{

			if (keepLoop)
			{

				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			}
		}

	} while (keepRepeating);

}

//Display's Active Tickets
void displayActiveTicketMessage(const struct AccountTicketingData* newTicket)
{
	int i = 0, j = 0;
	int keepRepeating = 1, keepLoop = 1, ticketNo;
	int count = 0;

	do
	{

		keepLoop = 1;
		displayTicketHeader();

		for (i = 0; i < newTicket->TICKET_MAX_SIZE; i++)
		{

			if (newTicket->tickets[i].ticketStatus == ACTIVE_TICKET_INDICATOR && newTicket->tickets[i].uniqueNum != 0)
			{

				printf("%06d %5d %-15s %-6s %-30s %5d\n", newTicket->tickets[i].uniqueNum, newTicket->tickets[i].customer_account_number, newTicket->tickets[i].messageInfo->displayName, newTicket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", newTicket->tickets[i].subjectLine, newTicket->tickets[i].countMessage);

			}

		}

		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");

		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		do
		{
			ticketNo = getInteger();

			if (ticketNo < 0)
			{

				printf("ERROR: Value must be positive or zero: ");

			}
			else if (ticketNo == 0)
			{

				putchar('\n');
				keepRepeating = 0;
				keepLoop = 0;

			}
			else
			{

				putchar('\n');
				keepLoop = 0;

			}

		} while (keepLoop);

		keepLoop = 1;

		if (ticketNo != 0)
		{

			count = 0;
			for (i = 0; i < newTicket->TICKET_MAX_SIZE && keepLoop; i++)
			{

				if (newTicket->tickets[i].uniqueNum == ticketNo && newTicket->tickets[i].uniqueNum != 0)
				{

					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", newTicket->tickets[i].uniqueNum, newTicket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", newTicket->tickets[i].subjectLine);
					printf("================================================================================\n");

					for (j = 0; j < newTicket->tickets[i].countMessage; j++)
					{

						printf("%s (%s):\n", newTicket->tickets[i].messageInfo[j].account_type_author == 'A' ? "AGENT" : "CUSTOMER", newTicket->tickets[i].messageInfo[j].displayName);
						printf("   %s\n\n", newTicket->tickets[i].messageInfo[j].messageDetail);

						count++;

						if (count % 5 == 0)
						{

							pauseExecution();

						}

					}

					if (count % 5 != 0)
					{

						pauseExecution();

					}

					keepLoop = 0;

				}

			}

		}
		if (ticketNo != 0)
		{

			if (keepLoop)
			{

				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			}

		}

	} while (keepRepeating);

}

//Displays Customer Ticket's Header
void displayCustomerTicketHeader(void)
{

	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");

}

//Display's Customer Tickets
void displayCustomerTicketMessage(const struct Ticket* displayTicket, const struct Account* accountInfo, int maxElements)
{
	int i = 0, j = 0;
	int keepRepeating = 1, keepLoop = 1, ticketNo, indexNo = 0;
	int count = 0;

	do
	{

		keepLoop = 1;
		displayCustomerTicketHeader();

		for (i = 0; i < maxElements; i++)
		{

			if (displayTicket[i].customer_account_number == accountInfo->accountNumber && displayTicket[i].uniqueNum != 0)
			{

				printf("%06d %-6s %-30s %5d\n", displayTicket[i].uniqueNum, displayTicket[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", displayTicket[i].subjectLine, displayTicket[i].countMessage);

			}

		}

		printf("------ ------ ------------------------------ --------");
		printf("\n\n");


		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		do
		{
			ticketNo = getInteger();

			if (ticketNo < 0)
			{

				printf("ERROR: Value must be positive or zero: ");

			}
			else if (ticketNo == 0)
			{

				putchar('\n');
				keepRepeating = 0;
				keepLoop = 0;

			}
			else
			{

				putchar('\n');
				keepLoop = 0;

			}

		} while (keepLoop);

		keepLoop = 1;

		if (ticketNo != 0)
		{

			indexNo = findTicketIndexByTickNum(ticketNo, displayTicket, maxElements, DONOT_PROMPT);

			if (displayTicket[indexNo].customer_account_number != accountInfo->accountNumber && indexNo != -1)
			{

				printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
				pauseExecution();
				keepLoop = 0;

			}

			if (displayTicket[indexNo].customer_account_number == accountInfo->accountNumber && indexNo != -1)
			{

				count = 0;
				for (i = 0; i < maxElements && keepLoop; i++)
				{

					if (displayTicket[i].uniqueNum == ticketNo && displayTicket[i].uniqueNum != 0)
					{

						printf("================================================================================\n");
						printf("%06d (%s) Re: %s\n", displayTicket[i].uniqueNum, displayTicket[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", displayTicket[i].subjectLine);
						printf("================================================================================\n");

						for (j = 0; j < displayTicket[i].countMessage; j++)
						{

							printf("%s (%s):\n", displayTicket[i].messageInfo[j].account_type_author == 'A' ? "AGENT" : "CUSTOMER", displayTicket[i].messageInfo[j].displayName);
							printf("   %s\n\n", displayTicket[i].messageInfo[j].messageDetail);

							count++;

							if (count % 5 == 0)
							{

								pauseExecution();

							}

						}

						if (count % 5 != 0)
						{

							pauseExecution();

						}

						keepLoop = 0;

					}

				}

			}

			if (keepLoop)
			{

				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			}
		}

	} while (keepRepeating);

}

// Pause execution until user enters the enter key 
void pauseExecution(void)
{

	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');

}

//This function's purpose is to search the array received in argument 2 for a match on a desired account number.
int findAccountIndexByAcctNum(int accountNum, const struct Account accountData[], int maxElements, int prompt_account_num)
{

	int i, indexFound;

	if (prompt_account_num)
	{

		printf("Enter the account#: ");
		accountNum = getPositiveInteger();
		putchar('\n');

	}

	for (i = 0, indexFound = -1; indexFound < 0 && i < maxElements; i++)
	{

		if (accountNum == accountData[i].accountNumber)
		{

			indexFound = i;

		}

	}

	return indexFound;
}

//entry point to the application logic.
void  applicationStartup(struct AccountTicketingData* accountTicket)
{
	int index;

	do
	{
		index = menuLogin(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);

		if (index != -1)
		{

			if (accountTicket->accounts[index].accountType == 'C')
			{

				menuCustomer(accountTicket->tickets, &accountTicket->accounts[index], accountTicket->TICKET_MAX_SIZE);

			}
			else if (accountTicket->accounts[index].accountType == 'A')
			{

				menuAgent(accountTicket, &accountTicket->accounts[index]);

			}

		}
		else
		{

			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");

		}

	} while (index != -1);

}


//Displays a login menu:
int menuLogin(const struct Account accountData[], int maxElements)
{
	int option, min = 0, max = 1;
	int indexNo = 0;
	int  keepRepeating = 1;
	char character = 0;

	do
	{

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");

		option = getIntFromRange(min, max);
		putchar('\n');

		switch (option)
		{
		case 0:

			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			character = getCharOption("yYnN");

			if (character == 'y' || character == 'Y')
			{

				indexNo = -1;
				keepRepeating = 0;

			}
			else
			{

				keepRepeating = 1;

			}

			putchar('\n');
			break;

		case 1:

			indexNo = validatePasswordAndUserLogin(accountData, maxElements);

			if (indexNo > 0)
			{

				keepRepeating = 0;

			}

			break;

		}

	} while (keepRepeating);

	return indexNo;
}


//Display's the agent's main menu options until the user wishes to logout
void  menuAgent(struct AccountTicketingData* accountTicket, struct Account* accountInfo)
{

	int option, min = 0, max = 12;
	int i;
	int accountNo = 0, maxAccount = 0;
	int repeatLoop = 1;
	int indexNo;
	int countTickets1 = 0, count_removed_messages = 0, count_closed_messages = 0, count_removed_account = 0, total_removed_messages = 0;
	int total_removed_tickets = 0, total_closed_tickets = 0, countTickets2 = 0, totalTickets = 0, totalAccounts = 0;
	char yesNo = 0, character = 0;

	do
	{

		printf("AGENT: %s (%d)\n", accountInfo->login.customerName, accountInfo->accountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		option = getIntFromRange(min, max);

		switch (option)
		{

		case 1:
			putchar('\n');

			indexNo = findAccountIndexByAcctNum(0, accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, DONOT_PROMPT);

			if (indexNo < 0)
			{

				printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();

			}
			else
			{

				for (i = 0; i < accountTicket->ACCOUNT_MAX_SIZE; i++)
				{

					if (accountTicket->accounts[i].accountNumber > maxAccount)
					{

						maxAccount = accountTicket->accounts[i].accountNumber;

					}

				}

				accountTicket->accounts[indexNo].accountNumber = maxAccount + 1;

				getAccount(&accountTicket->accounts[indexNo]);
				getUserLogin(&accountTicket->accounts[indexNo]);
				getDemographic(&accountTicket->accounts[indexNo]);

				printf("*** New account added! ***\n\n");
				pauseExecution();

			}

			break;

		case 2:

			putchar('\n');
			do
			{

				indexNo = findAccountIndexByAcctNum(accountNo, accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, PROMPT);

			} while (indexNo == -1);

			updateAccount(&accountTicket->accounts[indexNo]);

			break;

		case 3:

			putchar('\n');
			printf("Enter the account#: ");
			accountNo = getPositiveInteger();

			if (accountNo == accountInfo->accountNumber)
			{

				putchar('\n');
				printf("ERROR: You can't remove your own account!\n\n");
				clearStandardInputBuffer();
				pauseExecution();

			}
			else
			{

				indexNo = findAccountIndexByAcctNum(accountNo, accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, DONOT_PROMPT);

				displayAccountDetailHeader();
				displayAccountDetailRecord(&accountTicket->accounts[indexNo]);

				putchar('\n');

				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				character = getCharOption("YN");
				putchar('\n');

				countTickets1 = 0;
				count_removed_messages = 0;

				if (character == 'Y')
				{

					countTickets1 = removeTickets(accountTicket, &accountTicket->accounts[indexNo], &count_removed_messages);
					total_removed_tickets = total_removed_tickets + countTickets1;
					total_removed_messages = total_removed_messages + count_removed_messages;
					archiveRemovedAccount(&accountTicket->accounts[indexNo]);
					accountTicket->accounts[indexNo].accountNumber = 0;

					count_removed_account++;
					printf("*** Account Removed! ***\n\n");

					pauseExecution();

				}
				else
				{

					printf("*** No changes made! ***\n\n");
					pauseExecution();

				}

			}

			break;

		case 4:

			putchar('\n');
			displayAllAccountSummaryRecords(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;

		case 5:

			putchar('\n');
			displayAllAccountDetailRecords(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;

		case 6:

			putchar('\n');
			displayNewTicketMessage(accountTicket);
			break;

		case 7:

			putchar('\n');
			displayActiveTicketMessage(accountTicket);
			break;

		case 8:

			putchar('\n');
			displayAgentTicketMessage(accountTicket);
			break;

		case 9:

			putchar('\n');
			modifyAgentTicket(accountTicket, accountInfo);

			break;

		case 10:

			putchar('\n');

			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			yesNo = getCharOption("YN");
			printf("\n");

			if (yesNo == 'Y')
			{
				countTickets2 = 0;

				for (i = 0; i < accountTicket->TICKET_MAX_SIZE; i++)
				{

					if (accountTicket->tickets[i].ticketStatus == CLOSED_TICKET_INDICATOR && accountTicket->tickets[i].uniqueNum != 0)
					{

						countTickets2++;
						archiveClosedTickets(&accountTicket->tickets[i]);
						total_closed_tickets = total_closed_tickets + countTickets2;

						count_closed_messages = count_closed_messages + accountTicket->tickets[i].countMessage;

						accountTicket->tickets[i].uniqueNum = 0;
						accountTicket->tickets[i].customer_account_number = 0;

					}

				}

				printf("*** %d tickets archived ***\n\n", countTickets2);
				pauseExecution();

			}

			break;
		case 11:

			putchar('\n');

			printf("There are %d account(s) currently archived.\n\n", count_removed_account);
			pauseExecution();

			break;
		case 12:

			putchar('\n');

			printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", total_removed_tickets + countTickets2, count_closed_messages + total_removed_messages);

			pauseExecution();

			break;
		case 0:

			putchar('\n');
			printf("Saving session modifications...\n");
			totalAccounts = saveCurrentAccounts(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			printf("   %d account saved.\n", totalAccounts);
			totalTickets = saveCurrentTickets(accountTicket->tickets, accountTicket->TICKET_MAX_SIZE);
			printf("   %d tickets saved.\n", totalTickets);

			printf("### LOGGED OUT ###\n\n");
			repeatLoop = 0;

			break;

		}

	} while (repeatLoop);

}

//This function displays a summary view of all the valid account records (where the account number is greater than zero (0)
void displayAllAccountSummaryRecords(struct Account accountData[], int maxElements)
{
	int i;

	displayAccountSummaryHeader();

	for (i = 0; i < maxElements; i++)
	{

		if (accountData[i].accountNumber != 0)
		{
			displayAccountSummaryRecord(&accountData[i]);
		}


	}

	putchar('\n');

}

//This function displays a detailed view of all the valid account records(where the account number is greater than zero(0)
void displayAllAccountDetailRecords(struct Account accountData[], int maxElements)
{
	int i;

	displayAccountDetailHeader();

	for (i = 0; i < maxElements; i++)
	{

		if (accountData[i].accountNumber != 0)
		{
			displayAccountDetailRecord(&accountData[i]);
		}


	}

	putchar('\n');

}


//Validation of password and User login name
int validatePasswordAndUserLogin(const struct Account* accountData, int maxElements)
{
	int remainingLimit = REMAINING_LIMIT;
	int indexNo = 0, accountNo = 0, checkPassword = 0, checkLogin = 0;
	int   keepLoop = 1;
	char inputLogin[500] = "0";
	char inputPassword[500] = "0";

	do
	{

		printf("Enter the account#: ");
		accountNo = getPositiveInteger();

		indexNo = findAccountIndexByAcctNum(accountNo, accountData, maxElements, DONOT_PROMPT);

		printf("User Login    : ");
		getCString(inputLogin, 1, 500);

		checkLogin = strcmp(inputLogin, accountData[indexNo].login.userLogin);

		printf("Password      : ");
		getCString(inputPassword, 1, 500);

		checkPassword = strcmp(inputPassword, accountData[indexNo].login.password);

		if (checkLogin == 0 && checkPassword == 0)
		{

			printf("\n");
			keepLoop = 0;

		}
		else
		{

			remainingLimit--;
			printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", remainingLimit);

		}

		if (remainingLimit == 0)
		{

			indexNo = -1;
			printf("ERROR:  Login failed!\n\n");
			pauseExecution();
			keepLoop = 0;

		}

	} while (keepLoop);

	return indexNo;
}


