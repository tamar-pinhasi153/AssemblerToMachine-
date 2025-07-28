#ifndef SECOND_PASS_H

#define SECOND_PASS_H

#include "coding.h"
#include "assembler.h"
#include "pre_assembler.h"
#include "mcro_check.h"
#include "propriety.h"
#include "reference_tables.h"
#include "firstPass.h"

/*In the second pass function, I defined a loop that reads line by line from the file into 
a variable called line. Then I put the line into another variable called templine so that I
can cut the first word that I put into the variable word. I put the word into another 
variable called tempword. Then I check if word is a symbol/label. If not, we move to the
next line. If so, I update word to the word that comes later and check if word is equal to 
the prompt word. If so, I move to the next line. If not, I check if it is an entry prompt. 
If so, we check if tempword is in the symbol table. If not, we throw an error and turn on a 
flag. If so, we send it to a helper function in the table file that will add the word entry 
to the label in the symbol specification. Then we process the label and its address in a
struct that is defined to contain only the labels that are entry, their name and address, 
and we move to the next line. Now, we move to the encodings. We send it to a function that 
will encode the labels that were not encoded. In the first pass, the function is void, 
it will update the data until the table ends, then we will check if there is an entry label 
and also an external label. If so, we will issue an error and turn on a flag. Otherwise,
we will continue and check if we found errors in the first or second pass. We will end the 
program without outputting the files. If no errors are detected up to this point, we will 
create the files. We will start by creating the OB file. First, we will print the size of 
the code table and the size of the data table to it, which means how many code words we have
and how many data words. Then we will print the addresses and encodings. Only before that,
we will convert the char variable to int and we have finished creating the file. 
Now we will move on to the next file. We will check if it says there is data to print to the
EXT file. If the flag is off, there is no data. If it is on, there is data. Then we will 
print the name of the label and the address that we saved in the struct and do the same for 
the ENT file. Now the second stage is over. If there were no errors, the files are ready,
and if there were errors, we will return the number 1.*/
int second_pass(char* file_name, int symbol_table_size, int table_code_size,int table_data_size, char *Symbol_array[], val** tabelData, val** tabelCode, int flag,int sizeArrMcro, Mcro** mcros);



int LabelValied(char* word ,int sizeArrMcro, Mcro** mcros);

#endif

