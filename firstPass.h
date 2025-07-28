#ifndef FIRST_PASS_H

#define FIRST_PASS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdlib.h>

#define MAX_LINE_LENGTH 81
#define DEFEULT -1 

typedef struct {
    char adress[28];
    char binaryMachineCode[100];
    int enlargement; /*מה גודל המערך כרגע*/
    int numarr; /*סכימת כמה תאים יש לי במערך*/
}val;

typedef struct {
	char adress[25];
	char line[81];
	char binaryMachineCode[23];	
}value;


typedef enum {
    TRUE = 0,
    FALSE = 1
}bool;

typedef struct {
    int flagIA;/*instant adressing*/
    int flagIAdes;/*instant adressing destenation parameter*/
    int flagRA;/*relative adressing*/
    int flagRAdes;/*relative adressing destenation parameter*/
    int flagLabelE;/*extern or entery label*/
    int flagLabelBeg;/*beginning label*/
    int flagLabelOri;/*origin parameter label*/
    int flagLabelDes;/*destenation parameter label*/
    int flagRegOri;/*origin register*/
    int flagRegDes;/*destenetion register*/
    int flag;/*error flag*/
    int dataCounter;/*data struc line counter*/
    int codeCounter;/*code struc line counter*/
}Flags;

extern int i;
extern int IC;
extern int DC;



#include "coding.h"

#include "mcro_check.h"
#include "reference_tables.h"
#include "propriety.h"

/*
* gets:file
* returns: send to coding every line and then continue to second pass
*/
void lineExtr( char* fileName,int sizeArrMcro, Mcro** mcros);

/*
* gets: first word in the line
* returens: the number of the function, if the word is not function returns DEFAULT -1
*/
int funcFinder(char* func);


/*
* gets: a line, labels array and a label name
* The operation checks a row to see if it is valid and if so, it sends it for encoding and adds it to the table.
*/
void lineConvert(char* str, char** lebelsArray, char* bLabel, Flags* myFlags, val** tabelCode, val** tabelData, int sizeArrMcro, Mcro** mcros );




/*
*gets: a number present a place
*returens the number in 7 digites as char
*/
char* convert7(int num);


/*
* gets: a word the num of function and the struct of flages
* returens:0 if the parameter is valied and update the right flag else returens 1
*/
int originParam(char* str, int i, Flags *myFlags, int sizeArrMcro, Mcro** mcros);

/*
* gets: a word the num of function and the struct of flages
* returens:0 if the parameter is valied and update the right flag else returens 
*/
int destenationParam(char* str,int i,  Flags *myFlags, int sizeArrMcro, Mcro** mcros);


/*
* gets: num of function, word of parameter, struct of all flages
* returens: the code word 
*/
char* coding(int i,char *nextWord,int IC, Flags* myFlags);



/*
* gets: a line and counter 
* returens: insert all the parameter to the struct and returens how many are added
*/
int dataCoding(char* nextWord, int dc, Flags* myFlags, val** tabel);

/*
* gets: a line and counter
* returens: insert all the parameter to the struct and returens how many are added
*/
int stringCoding(char* nextWord, int dc, Flags* myFlags, val** tabel);


/*This function receives the label address and the label encoding and enters it into the table. 
The call to the function is made in several places because this function enters the encodings of the 
code table and also the data*/
void add_Coding(val** tabel, char* addressput, char* numput);


/*The encoding function for labels that were not encoded in the first pass, there are 3 types of 
labels, either it is a castan or with & or entry, so we will split the function into 3 if each will
handle a different case, if the label starts with & we will insert the word starting from position 1 
into a variable that we will send into the symbol table to verify that it exists if we do not return an
error if so we calculate the difference between the address of this label in the symbol table and the 
address that is one place before in the struct array, we will send this difference to a function that 
will convert the difference to a binary address we will add the addressing type to the three right 
places and move on, if the label is external we will encode it as address 0 and add the addressing 
method and then we will copy the label name into the struct that contains the names of the labels that 
are external and their addresses, if the label is not one of them then it is an entry label which means
we will encode the address of the label From the symbol table, if it is not in the table, we will 
return an error and turn on a flag. If it is, we will return the address that was sent to the phone, 
which we will convert to binary. We will add the addressing method to it and update the encoding array.
We will also add the label name and its address in the struct that contains the labels that are external
, their name and address. If the variable does not match any of the definitions, then it is probably 
not something that needs to be encoded. It is already an address that is represented in binary form and
we will copy it as it is and move on.*/
void Adding_encoding_labbel(val** tabel, int table_size, int symbol_table_size, char* arrsymbol[], ent* entr, ext* extr,Variables* global);

int second_pass(char* file_name, int symbol_table_size, int table_code_size,int table_data_size, char *Symbol_array[], val** tabelData, val** tabelCode, int flag,int sizeArrMcro, Mcro** mcros);

int ifReg(char* str);
int immediateAdress(char* str);
int relativeAdress(char* str, int sizeArrMcro, Mcro** mcros);
void spaceRemover(char* str);
char* codeIA(char* nextWord, int ic);
int labelCheck(char* word, int sizeArrMcro, Mcro** mcros);
int check_entry_or_extern(const char* word);
char* labelFinder(char* word);
int LabelValied(char* word ,int sizeArrMcro, Mcro** mcros);
int existlabel(char* word, char* arrey[], int length);
int isDataValied(char* word);
int immediateAdress(char* str);
char* getBinaryLastNBits(unsigned int number, int num);
char* conect(char *str1,char *str2);
char* convert7(int num);
int my_snprintf(char* str, size_t size, const char* format,...) ;
char* my_strdup(const char* s) ;
int my_vsnprintf(char *str, size_t size, const char *format, va_list args);
#endif
