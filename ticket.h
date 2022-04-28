#pragma once

/*==================================================
  Assignment #2 Milestone #4
  ==================================================
  Name    : Jenish Rajnikant Patel
  ID      : 131733206
  Email   : jrpatel47@myseneca.ca
  Section : NCC */

#ifndef TICKET_H_
#define TICKET_H_


#define TICKETSFILE "tickets.txt"
#define TICKETSARCFILE "tickets_arc.txt"



#define DISPLAY_NAME_LENGTH 30
#define MESSAGE_SIZE 150
#define SUBJECT_SIZE 30
#define NUMBER_OF_MESSAGES 20
#define NEW_MESSAGE_COUNT 1
#define REMAINING_LIMIT 3
#define ACTIVE_TICKET_INDICATOR 1
#define CLOSED_TICKET_INDICATOR 0

  //STRUCTURES

struct Message
{
	char account_type_author;
	char displayName[DISPLAY_NAME_LENGTH + 1];
	char messageDetail[MESSAGE_SIZE + 1];
};

struct Ticket
{
	int uniqueNum;
	int customer_account_number;
	int ticketStatus;
	char subjectLine[SUBJECT_SIZE + 1];
	int countMessage;
	struct Message messageInfo[NUMBER_OF_MESSAGES];


};

//This function's purpose is to search the array received in argument 2 for a match on a desired ticket number.
int findTicketIndexByTickNum(int ticketNum, const struct Ticket ticketData[], int maxElements, int prompt_ticket_num);

// To save the current updated tickets in tickets.txt
int saveCurrentTickets(const struct Ticket ticketData[], int maxElements);

// To load tickets data from the tickets.txt file
int loadTickets(struct Ticket ticketData[], int maxElements);

// To archive closed removed tickets in tickets_arc.txt
int archiveRemovedClosedTickets(const struct Ticket* ticketData);

// To archive closed tickets in tickets_arc.txt
void archiveClosedTickets(const struct Ticket* ticketData);



#endif