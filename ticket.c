

#define _CRT_SECURE_NO_WARNINGS

  // SYSTEM LIBRARY
#include<stdio.h>

  //USER LIBRARY
#include "accountTicketingUI.h"



//This function's purpose is to search the array received in argument 2 for a match on a desired ticket number.
int findTicketIndexByTickNum(int ticketNum, const struct Ticket ticketData[], int maxElements, int prompt_ticket_num)
{
	int i = 0, indexFound = -1;

	if (prompt_ticket_num)
	{

		printf("Enter ticket number: ");
		ticketNum = getPositiveInteger();
		putchar('\n');

	}

	for (i = 0, indexFound = -1; indexFound < 0 && i < maxElements; i++)
	{

		if (ticketNum == ticketData[i].uniqueNum)
		{
			indexFound = i;
		}

	}

	return indexFound;
}

//Removes Tickets And Accounts Related To Tckets
int removeTickets(const struct AccountTicketingData* accountTicket, struct Account* accountInfo, int* count_removed_tickets)
{
	int i = 0;
	int result = 0;

	for (i = 0; i < accountTicket->TICKET_MAX_SIZE; i++)
	{

		if (accountTicket->tickets[i].customer_account_number == accountInfo->accountNumber)
		{

			if (accountTicket->tickets[i].ticketStatus == ACTIVE_TICKET_INDICATOR)
			{
				accountTicket->tickets[i].uniqueNum = 0;
				accountTicket->tickets[i].customer_account_number = 0;

			}
			else
			{
				*count_removed_tickets = accountTicket->tickets[i].countMessage;
				result = archiveRemovedClosedTickets(&accountTicket->tickets[i]);

				accountTicket->tickets[i].uniqueNum = 0;
				accountTicket->tickets[i].customer_account_number = 0;

			}

		}

	}

	return result;

}

//Create New Tickets For Customer
void createNewTicket(struct Ticket* newCustomerTicket, const struct Account* accountInfo, int maxElements)
{
	int indexTicket = 0, maxTicketNo = 0;
	int i = 0;
	int min = 1;

	indexTicket = findTicketIndexByTickNum(0, newCustomerTicket, maxElements, DONOT_PROMPT);

	if (indexTicket < 0)
	{

		printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
		pauseExecution();

	}
	else
	{

		for (i = 0; i < indexTicket; i++)
		{

			if (newCustomerTicket[i].uniqueNum > maxTicketNo)
			{
				maxTicketNo = newCustomerTicket[i].uniqueNum;
			}

		}

		newCustomerTicket[indexTicket].uniqueNum = maxTicketNo + 1;
		newCustomerTicket[indexTicket].customer_account_number = accountInfo->accountNumber;
		newCustomerTicket[indexTicket].countMessage = NEW_MESSAGE_COUNT;
		newCustomerTicket[indexTicket].ticketStatus = ACTIVE_TICKET_INDICATOR;
		newCustomerTicket[indexTicket].messageInfo->account_type_author = accountInfo->accountType;


		printf("New Ticket (Ticket#:%06d)\n", newCustomerTicket[indexTicket].uniqueNum);
		printf("----------------------------------------\n");
		printf("Enter the ticket SUBJECT (%d chars. maximum): ", SUBJECT_SIZE);
		getCString(newCustomerTicket[indexTicket].subjectLine, min, SUBJECT_SIZE);
		putchar('\n');
		printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MESSAGE_SIZE);

		getCString(newCustomerTicket[indexTicket].messageInfo[newCustomerTicket[indexTicket].countMessage - 1].messageDetail, min, MESSAGE_SIZE);

		for (i = 0; i < DISPLAY_NAME_LENGTH; i++)
		{

			newCustomerTicket[indexTicket].messageInfo[newCustomerTicket[indexTicket].countMessage - 1].displayName[i] = accountInfo->login.customerName[i];

		}

		putchar('\n');
		printf("*** New ticket created! ***\n\n");
		pauseExecution();

	}

}

//Validates Customer Ticket Number And Provides Index Of That Ticket Number
void modifyCustomerTicket(struct Ticket* newCustomerTicket, struct Account* accountInfo, int maxElements)
{

	int indexTicket = 0, ticketNum = 0;

	do
	{

		indexTicket = findTicketIndexByTickNum(ticketNum, newCustomerTicket, maxElements, PROMPT);


	} while (indexTicket == -1);



	if (newCustomerTicket[indexTicket].customer_account_number != accountInfo->accountNumber)
	{

		printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
		pauseExecution();

	}
	else
	{

		if (newCustomerTicket[indexTicket].ticketStatus == 1)
		{

			menuCustomerTicketModification(&newCustomerTicket[indexTicket], accountInfo);

		}
		else
		{

			printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
			pauseExecution();

		}

	}
}

//Provides Menu For Customer Ticket Modifications
void menuCustomerTicketModification(struct Ticket* ticketData, struct Account* accountInfo)
{

	int modifyOption = 0;
	int min = 0, max = 3;
	int repeatLoop = 1;
	char closeTicket = 0;
	char leaveMessage = 0;
	int i = 0;

	do
	{

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticketData->uniqueNum);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticketData->ticketStatus == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticketData->subjectLine);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		modifyOption = getIntFromRange(min, max);
		putchar('\n');

		switch (modifyOption)
		{
		case 1:

			printf("Enter the revised ticket SUBJECT (%d chars. maximum): ", SUBJECT_SIZE);
			getCString(ticketData->subjectLine, min, SUBJECT_SIZE);
			putchar('\n');
			break;

		case 2:


			if (ticketData->countMessage >= NUMBER_OF_MESSAGES)
			{

				printf("ERROR: Message limit has been reached, call ITS Support!\n");

			}
			else
			{

				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MESSAGE_SIZE);
				ticketData->countMessage = ticketData->countMessage + 1;
				getCString(ticketData->messageInfo[ticketData->countMessage - 1].messageDetail, min, MESSAGE_SIZE);

				for (i = 0; i < DISPLAY_NAME_LENGTH; i++)
				{

					ticketData->messageInfo[ticketData->countMessage - 1].displayName[i] = accountInfo->login.customerName[i];

				}

			}

			putchar('\n');

			break;

		case 3:

			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			closeTicket = getCharOption("YN");

			if (closeTicket == 'Y')
			{

				ticketData->ticketStatus = 0;

			}
			else
			{

				ticketData->ticketStatus = 1;

			}

			putchar('\n');

			if (ticketData->countMessage < NUMBER_OF_MESSAGES)
			{

				printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
				leaveMessage = getCharOption("YN");
				putchar('\n');

				if (leaveMessage == 'Y')
				{

					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MESSAGE_SIZE);
					ticketData->countMessage = ticketData->countMessage + 1;
					getCString(ticketData->messageInfo[ticketData->countMessage - 1].messageDetail, min, MESSAGE_SIZE);

					for (i = 0; i < DISPLAY_NAME_LENGTH; i++)
					{

						ticketData->messageInfo[ticketData->countMessage - 1].displayName[i] = accountInfo->login.customerName[i];

					}
					putchar('\n');

				}
			}

			if (closeTicket == 'Y')
			{

				printf("*** Ticket closed! ***\n\n");
				pauseExecution();
				repeatLoop = 0;

			}

			break;

		case 0:

			pauseExecution();
			repeatLoop = 0;
			break;

		}

	} while (repeatLoop);
}

//Display Agent Messages That Are Closed
void displayAgentTicketMessage(const struct AccountTicketingData* newAgentTicket)
{

	int i = 0, j = 0;
	int keepRepeating = 1, keepLoop = 1, ticketNo;
	int count = 0;

	do
	{

		keepLoop = 1;
		displayTicketHeader();

		for (i = 0; i < newAgentTicket->TICKET_MAX_SIZE; i++)
		{

			if (newAgentTicket->tickets[i].ticketStatus == CLOSED_TICKET_INDICATOR && newAgentTicket->tickets[i].uniqueNum != 0)
			{

				printf("%06d %5d %-15s %-6s %-30s %5d\n", newAgentTicket->tickets[i].uniqueNum, newAgentTicket->tickets[i].customer_account_number, newAgentTicket->tickets[i].messageInfo->displayName, newAgentTicket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", newAgentTicket->tickets[i].subjectLine, newAgentTicket->tickets[i].countMessage);

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
			for (i = 0; i < newAgentTicket->TICKET_MAX_SIZE && keepLoop; i++)
			{

				if (newAgentTicket->tickets[i].uniqueNum == ticketNo && newAgentTicket->tickets[i].uniqueNum != 0)
				{

					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", newAgentTicket->tickets[i].uniqueNum, newAgentTicket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", newAgentTicket->tickets[i].subjectLine);
					printf("================================================================================\n");

					for (j = 0; j < newAgentTicket->tickets[i].countMessage; j++)
					{

						printf("%s (%s):\n", newAgentTicket->tickets[i].messageInfo[j].account_type_author == 'A' ? "AGENT" : "CUSTOMER", newAgentTicket->tickets[i].messageInfo[j].displayName);
						printf("   %s\n\n", newAgentTicket->tickets[i].messageInfo[j].messageDetail);

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

//Validates Agent Ticket Number And Provides Index Of That Ticket Number
void modifyAgentTicket(const struct AccountTicketingData* newAgentTicket, struct Account* accountInfo)
{

	int indexTicket = 0, ticketNum = 0;

	do
	{

		indexTicket = findTicketIndexByTickNum(ticketNum, newAgentTicket->tickets, newAgentTicket->TICKET_MAX_SIZE, PROMPT);


	} while (indexTicket == -1);

	menuAgentTicketModification(&newAgentTicket->tickets[indexTicket], accountInfo);

}

//Provides Agent For Customer Ticket Modifications
void menuAgentTicketModification(struct Ticket* ticketData, struct Account* accountInfo)
{

	int modifyOption = 0;
	int min = 0, max = 3;
	int repeatLoop = 1;
	char closeTicket = 0, reopenTicket = 0;
	char leaveMessage = 0;
	int i = 0;

	do
	{
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticketData->uniqueNum);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticketData->ticketStatus == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticketData->subjectLine);
		printf("Acct#   : %d\n", ticketData->customer_account_number);
		printf("%s: %s\n", ticketData->messageInfo->account_type_author == 'A' ? "Agent" : "Customer", ticketData->messageInfo->displayName);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		modifyOption = getIntFromRange(min, max);
		putchar('\n');

		switch (modifyOption)
		{
		case 1:

			if (ticketData->ticketStatus == 0)
			{

				printf("ERROR: Ticket is closed - new messages are not permitted.\n");

			}
			else
			{

				if (ticketData->countMessage >= NUMBER_OF_MESSAGES)
				{

					printf("ERROR: Message limit has been reached, call ITS Support!\n");

				}
				else
				{

					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MESSAGE_SIZE);
					ticketData->countMessage = ticketData->countMessage + 1;
					getCString(ticketData->messageInfo[ticketData->countMessage - 1].messageDetail, min, MESSAGE_SIZE);

					for (i = 0; i < DISPLAY_NAME_LENGTH; i++)
					{

						ticketData->messageInfo[ticketData->countMessage - 1].displayName[i] = accountInfo->login.customerName[i];

					}

					ticketData->messageInfo[ticketData->countMessage - 1].account_type_author = accountInfo->accountType;

				}

			}

			putchar('\n');
			break;

		case 2:

			if (ticketData->ticketStatus == 0)
			{

				printf("ERROR: Ticket is already closed!\n\n");

			}
			else
			{

				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				closeTicket = getCharOption("YN");

				if (closeTicket == 'Y')
				{

					ticketData->ticketStatus = 0;

				}
				else
				{

					ticketData->ticketStatus = 1;

				}

				putchar('\n');

				if (ticketData->countMessage < NUMBER_OF_MESSAGES)
				{

					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					leaveMessage = getCharOption("YN");
					putchar('\n');

					if (leaveMessage == 'Y')
					{

						printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MESSAGE_SIZE);
						ticketData->countMessage = ticketData->countMessage + 1;
						getCString(ticketData->messageInfo[ticketData->countMessage - 1].messageDetail, min, MESSAGE_SIZE);

						for (i = 0; i < DISPLAY_NAME_LENGTH; i++)
						{

							ticketData->messageInfo[ticketData->countMessage - 1].displayName[i] = accountInfo->login.customerName[i];

						}

						ticketData->messageInfo[ticketData->countMessage - 1].account_type_author = accountInfo->accountType;

						putchar('\n');

					}
				}

				if (closeTicket == 'Y')
				{

					printf("*** Ticket closed! ***\n\n");

				}
			}

			break;

		case 3:


			if (ticketData->ticketStatus == 0)
			{

				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				reopenTicket = getCharOption("YN");

				if (reopenTicket == 'Y')
				{

					ticketData->ticketStatus = 1;
					printf("\n*** Ticket re-opened! ***");
					printf("\n\n");

				}
				else
				{

					ticketData->ticketStatus = 0;
					printf("\n");

				}

			}
			else
			{

				printf("ERROR: Ticket is already active!\n\n");

			}

			break;

		case 0:

			repeatLoop = 0;
			break;

		}

	} while (repeatLoop);
}

// To load tickets data from the tickets.txt file
int loadTickets(struct Ticket ticketData[], int maxElements)
{
	int countTickets = 0;
	int fieldCount;
	int i = 0;

	FILE* fp = fopen(TICKETSFILE, "r");

	if (fp != NULL)
	{
		do
		{

			fieldCount = fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
				&ticketData[countTickets].uniqueNum,
				&ticketData[countTickets].customer_account_number,
				&ticketData[countTickets].ticketStatus,
				ticketData[countTickets].subjectLine,
				&ticketData[countTickets].countMessage);

			if (fieldCount == 5)
			{

				if (ticketData[countTickets].uniqueNum > 0)
				{

					for (i = 0, fieldCount = 3; fieldCount == 3 && i < ticketData[countTickets].countMessage; i++)
					{

						fieldCount = fscanf(fp, "%c|%30[^|]|%150[^|]|", &ticketData[countTickets].messageInfo[i].account_type_author,
							ticketData[countTickets].messageInfo[i].displayName,
							ticketData[countTickets].messageInfo[i].messageDetail);

					}

				}

				countTickets++;

			}

		} while (!feof(fp) && countTickets < maxElements);

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

	}

	return countTickets;
}

// To save the current updated tickets in tickets.txt
int saveCurrentTickets(const struct Ticket ticketData[], int maxElements)
{
	int i = 0, j = 0, countTickets = 0;

	FILE* fp = fopen(TICKETSFILE, "w");

	if (fp != NULL)
	{

		for (i = 0; i < maxElements; i++)
		{

			if (ticketData[i].uniqueNum > 0)
			{

				fprintf(fp, "%d|%d|%d|%s|%d|", ticketData[i].uniqueNum, ticketData[i].customer_account_number, ticketData[i].ticketStatus, ticketData[i].subjectLine, ticketData[i].countMessage);

				if (ticketData[i].uniqueNum > 0)
				{

					for (j = 0; j < ticketData[i].countMessage; j++)
					{

						fprintf(fp, "%c|%s|%s|", ticketData[i].messageInfo[j].account_type_author,
							ticketData[i].messageInfo[j].displayName,
							ticketData[i].messageInfo[j].messageDetail);

						if (j == ticketData[i].countMessage - 1)
						{

							fprintf(fp, "\n");

						}

					}

				}

				countTickets++;
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

	return countTickets;
}

// To archive closed removed tickets in tickets_arc.txt
int archiveRemovedClosedTickets(const struct Ticket* ticketData)
{
	int i = 0;
	int result = 0;

	FILE* fp = fopen(TICKETSARCFILE, "a");

	if (fp != NULL)
	{

		fprintf(fp, "%d|%d|%d|%s|%d|", ticketData->uniqueNum, ticketData->customer_account_number, ticketData->ticketStatus, ticketData->subjectLine, ticketData->countMessage);

		if (ticketData->uniqueNum > 0)
		{

			for (i = 0; i < ticketData->countMessage; i++)
			{

				result = fprintf(fp, "%c|%s|%s|", ticketData->messageInfo[i].account_type_author,
					ticketData->messageInfo[i].displayName,
					ticketData->messageInfo[i].messageDetail);

				if (i == ticketData->countMessage - 1)
				{

					fprintf(fp, "\n");

				}

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

	return result > 0 ? 1 : 0;

}

// To archive closed tickets in tickets_arc.txt
void archiveClosedTickets(const struct Ticket* ticketData)
{
	int i = 0;

	FILE* fp = fopen(TICKETSARCFILE, "a");

	if (fp != NULL)
	{

		fprintf(fp, "%d|%d|%d|%s|%d|", ticketData->uniqueNum, ticketData->customer_account_number, ticketData->ticketStatus, ticketData->subjectLine, ticketData->countMessage);

		if (ticketData->uniqueNum > 0)
		{

			for (i = 0; i < ticketData->countMessage; i++)
			{

				fprintf(fp, "%c|%s|%s|", ticketData->messageInfo[i].account_type_author,
					ticketData->messageInfo[i].displayName,
					ticketData->messageInfo[i].messageDetail);

				if (i == ticketData->countMessage - 1)
				{

					fprintf(fp, "\n");

				}

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


}