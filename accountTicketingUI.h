#pragma once


#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#define PROMPT 1
#define DONOT_PROMPT 0

#include"ticket.h"
#include"account.h"
#include"commonHelpers.h"
  // //STRUCTURES

struct AccountTicketingData
{
	struct Account* accounts;   // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets;     // array of tickets 
	const int TICKET_MAX_SIZE;  // maximum elements for ticket array 
};

//FUNCTIONS DECLARATIONS

//Displays a formatted table header with three (3) column
void displayAccountSummaryHeader(void);

//Displays a formatted table header with seven (7) column
void displayAccountDetailHeader(void);

//Displays a formatted record that aligns to the respective header as defined in function "displayAccountSummaryHeader" described earlier
void displayAccountSummaryRecord(const struct Account* accountData);

//Displays a formatted record that aligns to the respective header as defined in function "displayAccountDetailHeader" described earlier
void  displayAccountDetailRecord(struct Account* accountData);

//entry point to the application logic.
void  applicationStartup(struct AccountTicketingData* accountTicket);

//Displays a login menu:
int menuLogin(const struct Account accountData[], int maxElements);

//Display's the agent's main menu options until the user wishes to logout
void  menuAgent(struct AccountTicketingData* accountTicket, struct Account* accountInfo);

//Display's the customer's main menu options until the user wishes to logout
void  menuCustomer(struct Ticket* ticketData, struct Account* accountInfo, int maxElements);

//This function's purpose is to search the array received in argument 2 for a match on a desired account number.
int findAccountIndexByAcctNum(int accountNum, const struct Account accountData[], int maxElements, int prompt_account_num);

//This function displays a summary view of all the valid account records (where the account number is greater than zero (0)
void displayAllAccountSummaryRecords(struct Account accountData[], int maxElements);

//This function displays a detailed view of all the valid account records(where the account number is greater than zero(0)
void displayAllAccountDetailRecords(struct Account accountData[], int maxElements);

// Pause execution until user enters the enter key 
void pauseExecution(void);

//Displays Ticket's Header
void displayTicketHeader(void);

//Display's New Tickets
void displayNewTicketMessage(const struct AccountTicketingData* newTicket);

//Display's Active Tickets
void displayActiveTicketMessage(const struct AccountTicketingData* newTicket);

//Display's Customer Tickets
void displayCustomerTicketMessage(const  struct Ticket* displayTicket, const struct Account* accountInfo, int maxElements);

//Displays Customer Ticket's Header
void displayCustomerTicketHeader(void);

//Create New Tickets For Customer
void createNewTicket(struct Ticket* newCustomerTicket, const struct Account* accountInfo, int maxElements);

//Display Agent Messages That Are Closed
void displayAgentTicketMessage(const struct AccountTicketingData* newAgentTicket);

//Validates Customer Ticket Number And Provides Index Of That Ticket Number
void modifyCustomerTicket(struct Ticket* newCustomerTicket, struct Account* accountInfo, int maxElements);

//Removes Tickets And Accounts Related To Tckets
int removeTickets(const struct AccountTicketingData* accountTicket, struct Account* accountInfo, int* count_removed_tickets);

//Validates Agent Ticket Number And Provides Index Of That Ticket Number
void modifyAgentTicket(const struct AccountTicketingData* newAgentTicket, struct Account* accountInfo);

//Validation of password and User login name
int validatePasswordAndUserLogin(const struct Account* accountData, int maxElements);

//Provides Menu For Customer Ticket Modifications
void menuCustomerTicketModification(struct Ticket* ticketData, struct Account* accountInfo);

//Provides Agent For Customer Ticket Modifications
void menuAgentTicketModification(struct Ticket* ticketData, struct Account* accountInfo);


#endif