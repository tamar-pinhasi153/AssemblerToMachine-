#ifndef CODING_H

#define CODING_H


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#include "firstPass.h"
#include "propriety.h"
#include "reference_tables.h"



/*
* gets: a word and number of the current label
* returens: the number as a code binary
*/
char* codeIA(char* nextWord, int ic);


/*
* gets: a number
* returens:A dynamically allocated string containing the binary representation of the last 21 bits of num
*/
char* getBitsCom(int num);
/*
* gets: a number
* returens: the binary code of number in char
*/
char* numToChar(int num);



/*
* gets: number and num
* returens the last num bits of the number as binary code 
*/
char* getBinaryLastNBits(unsigned int number, int num);

/*
gets:two strings
*returens:the two strings connect
*/
char* conect(char *str1,char *str2);


/*
*gets: a number present a place
*returens the number in 7 digites as char
*/
char* convert7(int num);

/*instead of sprintf*/
int my_snprintf(char* str, size_t size, const char* format,...) ;

/*instead of strdup*/
char* my_strdup(const char* s) ;

/*instead of vsnprintf*/
int my_vsnprintf(char *str, size_t size, const char *format, va_list args);
#endif
