

#define _CRT_SECURE_NO_WARNINGS

  // SYSTEM LIBRARY

#include<stdio.h>
#include <time.h>

// USER LIBRARY

#include "commonHelpers.h"


int currentYear(void)
{
	time_t currentTime = time(NULL);

	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing 
	}

}

//guarantee an integer value is entered and returned.
int getInteger(void)
{
	int getInt = 0;
	char newLine = 0;

	do
	{
		scanf("%d%c", &getInt, &newLine);


		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}

	} while (newLine != '\n');

	return getInt;
}

//guarantee a positive integer value is entered and returned.
int getPositiveInteger(void)
{
	int repeatLoop = 1;
	int getPos = 0;

	do
	{
		getPos = getInteger();

		if (getPos <= 0)
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
		else
		{
			repeatLoop = 0;
		}

	} while (repeatLoop);

	return getPos;

}

//guarantee a double value is entered and returned.
double getDouble(void)
{
	double getDbl = 0.0;
	char newLine = 0;

	do
	{
		scanf("%lf%c", &getDbl, &newLine);

		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (newLine != '\n');

	return getDbl;
}

//guarantee a positive double value is entered and returned.
double getPositiveDouble(void)
{
	double get_dbl_pos = 0.0;
	int repeatLoop = 1;

	do
	{
		get_dbl_pos = getDouble();

		if (get_dbl_pos <= 0)
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}
		else
		{
			repeatLoop = 0;
		}

	} while (repeatLoop);

	return get_dbl_pos;
}

//guarantee an integer value is entered within the range (inclusive) and returned.
int getIntFromRange(int lowerBound, int upperBound)
{
	int get_int_range = 0;
	int repeatLoop = 1;
	do
	{
		get_int_range = getInteger();

		if (get_int_range < lowerBound || get_int_range > upperBound)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);
		}
		else
		{
			repeatLoop = 0;
		}

	} while (repeatLoop);

	return get_int_range;
}

//Guarantee a single character value is entered within the list of valid characters (as defined by the C string argument received) and returned.
char getCharOption(const char checkString[])
{
	char inputChar = 0;
	int i = 0;
	int repeatLoop = 1;
	int count = 0;
	char inputChar1 = 0;

	for (i = 0; checkString[i] != '\0'; i++)
	{
		count++;
	}

	do
	{
		scanf("%c%c", &inputChar, &inputChar1);


		if (inputChar1 == '\n')
		{

			for (i = 0; i < count && repeatLoop; i++)
			{

				if (inputChar == checkString[i])
				{
					repeatLoop = 0;
				}


			}

			if (repeatLoop)
			{
				printf("ERROR: Character must be one of [%s]: ", checkString);
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", checkString);
			clearStandardInputBuffer();
		}

	} while (repeatLoop);


	return inputChar;
}

//guarantees a C string value is entered containing the number of characters within the range specified by the 2nd and 3rd arguments (and return via the 1st argument pointer).
void getCString(char charPointer[], int minChar, int maxChar)
{
	int i = 0, j = 0;
	int count = 0;
	int repeatLoop = 1;
	char inputString[500];

	do
	{

		scanf("%500[^\n]", inputString);
		clearStandardInputBuffer();

		count = 0;
		for (i = 0; inputString[i] != '\0'; i++)
		{
			count++;
		}

		if (count < minChar && (minChar != maxChar))
		{

			printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
		}
		else if ((count <minChar || count>maxChar) && minChar == maxChar)
		{

			printf("ERROR: String length must be exactly %d chars: ", minChar);

		}
		else if (count > maxChar && (minChar != maxChar))
		{
			printf("ERROR: String length must be no more than %d chars: ", maxChar);
		}
		else
		{
			for (j = 0; j < count + 1; j++)
			{
				charPointer[j] = inputString[j];
			}
			repeatLoop = 0;
		}

	} while (repeatLoop);


}