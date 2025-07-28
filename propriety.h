#ifndef PROPRIETY_H
#define PROPRIETY_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define DEFAULT -1 /*האם זה צריך להיות -1 ??*/


#include "firstPass.h"
#include "reference_tables.h"
#include "mcro_check.h"

/*
* gets: the line after the commend word
* returns: 0 if the word is a name of register and 1 if not
*/
int ifReg(char* str);

/*
*gets: the line after the commend word
* returens:0 if the operand uses the immediate adress and 1 if not
*/
int immediateAdress(char* str);

/*
* gets:a line
* returns: 0 if it has a label in the begining of the line and 1 if not
*/
 int labelCheck(char* str, int sizeArrMcro, Mcro** mcros);

/*
* gets:the line after the commend word of .data
* returns: 0 if the line is valied for .data and 0 if not
*/
int isDataValied(char* word);

/*
* gets: part of line
* returens: 0 if it is a valied label with '&' in the begining else returens 1
*/
int relativeAdress(char* str, int sizeArrMcro, Mcro** mcros);


/*
* gets: a word nnd deleate all the tabs from the beginning and end
*/
void spaceRemover(char* str);

/*
* gets: a word
* returens: 0 if it is a valied label and 1 if not
*/
 int LabelValied(char* word,int sizeArrMcro, Mcro** mcros);

/*
* gets: a word, arrey, and the length of arrey
* returens:0 if the word apears in the arrey and 1 if not
*/
int existlabel(char* word, char* arrey[], int length);

/*
*gets: a line
* returns: label name if exists else returns null
*/
char* labelFinder(char* word);

/*
* gets: a line
* returens 0 if has entry or extern in the line else returens false
*/
int check_entry_or_extern(const char* word);

/*int LabelValied(char* word ,int sizeArrMcro, Mcro** mcros);*/
#endif
