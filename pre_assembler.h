#ifndef PRE_ASSEMBLER_H

#define PRE_ASSEMBLER_H

#include "pre_assembler.h"
#include "mcro_check.h"
#include "firstPass.h"

#define MAX_MCRO_NAME_LENGTH 31
#define MAX_LINE_LENGTH 81
#define INITIAL_CAPACITY 82
#define more 10
#define error 1
#define success 0
#define FILENAME_LEN 100


/*This function reads line by line from the input file. Each line it reads checks if the line exceeds 81
characters. If so, it issues an error and turns on an error flag. If not, it checks if the line is a
comment line. If so, it does not copy to the output file. If not, it checks if it is a permission line.
If so, it does not copy to the output file. If not, it checks if it is a macro definition line. If so,
it turns on a macro flag. Then it copies all the values in the following lines up to the maroon end
flag. When it reaches the macro end flag, it copies the values to the macro table. If the line is not
one of the following distributions, it copies the line to the output file. If there were errors, it
stops here. If not, it goes to the next step.*/
int Macro_deployment(char* file_name);

/**
 * @brief Adds a suffix to a file name before the first period.
 *
 * Appends the `suffix` to the `file_name` before the first '.' into `new_name`.
 * If no '.' is found, appends to the end.
 *
 * @param file_name Original file name.
 * @param suffix Suffix to add.
 * @param new_name Buffer for the result (ensure sufficient size).
 */
void add_suffix(char* file_name, char* suffix, char* new_name);

/*
Function: Checking_comment_line
Purpose : Checks if a given line is a comment line(starts with ';').
Parameters :
    lineCheck : A character array representing the line to check.
    Returns :
    0 (success) if the line is a comment line,
    1 (error)otherwise(including NULL or empty line).
    * /
    */
    int Checking_comment_line(char lineCheck[]);


/**
 * @brief Checks if a given line contains only whitespace characters.
 *
 * This function determines whether a given line of text consists solely of whitespace characters,
 * such as spaces, tabs, or newline characters.
 *
 * @param line A character array representing the line to check.
 * @param lineNumber The line number in the input file.
 *
 * @return Returns 'success' (0) if the line contains only whitespace characters, or 'error' (non-zero) otherwise.
 * If the input line is NULL, it prints an error message and returns 'success'.
 *
 * @note This function uses the 'isspace' function from 'ctype.h' to identify whitespace characters.
 * @note 'success' and 'error' should be defined as constants in the calling code.
 */
int White_space_check(char line[], int lineNumber);


/**
 * @brief Checks if a given line contains only whitespace characters.
 *
 * This function determines whether a given line of text consists solely of whitespace characters,
 * such as spaces, tabs, or newline characters.
 *
 * @param line A character array representing the line to check.
 * @param lineNumber The line number in the input file.
 *
 * @return Returns 0 (success) if the line contains only whitespace characters, or a non-zero value (error) otherwise.
 * If the input line is NULL, it prints an error message and returns 0 (success).
 *
 * @note This function uses the 'isspace' function from 'ctype.h' to identify whitespace characters.
 * @note It is assumed that 'success' and 'error' are defined constants in the calling code.
 */
char* Unnecessary_profit(char* lineCheck);

void lineExtr( char* fileName,int sizeArrMcro, Mcro** mcros);
#endif
