#ifndef MCRO_CHECK_H

#define MCRO_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct{
	char *mcname;/*שם*/
	char *mcvalues;/*ערכים*/
} Mcro;


typedef struct {
    int is_error0;
    int YesMcro;/*Flag indicating whether we are inside a macro definition 0 off 1 on*/
    int numMcros;/*I was told the number of macros that entered the array*/
    int mcrosCapacity;/*The size of the macro array is currently so I'll know if I run out of space to insert more.*/
    char name[32]; /*A variable that will contain the name of the mcro.*/
    int sizeTabbel;/*The size of the table we allocate*/
    int sizeTabbelarr; /*The size of the table we used*/
    char *val;/*We will enter the macro values into the variable until we reach the end of the macro definition line, then we will enter them into the variable*/
    char *currentMcroValues;
    int currentNumValues;
    int currentCapacity; 
}Variables0;
#include "assembler.h"
#include "pre_assembler.h"
#include "propriety.h"
#include "firstPass.h"

/*The mcro check function checks whether the mcro has been defined correctly, which means that the
word mcro is written correctly and that the name of the mcro is without errors. During the function,
I sent several helper functions to help me check, among other things, whether the name of the mcro is
a reserved name, whether there is a space between the word mcro and the name of the mcro*/
int Mcro_check(char *lineCheck, int lineNumber,Variables0* global0, Mcro** mcros, char* file_name);

/*This function accepts values to add to a macro array.*/
void add_mcro(Mcro** mcros,Variables0* global0);

/*This function checks whether we are on the line defining the end of the macro and also checks that
the line is valid. If the line is valid, we return 0. If the line is invalid or is not a macro end line,
we return 1.*/
int McroEnd_check(char* lineCheck, int lineNumber, Variables0* global0,Mcro** mcros, char* file_name);


#endif
