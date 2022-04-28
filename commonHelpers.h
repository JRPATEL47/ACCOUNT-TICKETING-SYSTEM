#pragma once



#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int currentYear(void);

void clearStandardInputBuffer(void);

//guarantee an integer value is entered and returned.
int getInteger(void);

//guarantee a positive integer value is entered and returned.
int getPositiveInteger(void);

//guarantee a double value is entered and returned.
double getDouble(void);

//guarantee a positive double value is entered and returned.
double getPositiveDouble(void);

//guarantee an integer value is entered within the range (inclusive) and returned.
int getIntFromRange(int lowerBound, int upperBound);

//Guarantee a single character value is entered within the list of valid characters (as defined by the C string argument received) and returned.
char getCharOption(const char checkString[]);

//guarantees a C string value is entered containing the number of characters within the range specified by the 2nd and 3rd arguments (and return via the 1st argument pointer).
void getCString(char charPointer[], int minChar, int maxChar);

#endif