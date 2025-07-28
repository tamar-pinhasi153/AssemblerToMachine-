#ifndef REFERENCE_TABLES_H

#define REFERENCE_TABLES_H

#define External_encoding "000000000000000000000001"

/*Since it is forbidden to use a global variable, I created a struct that I will pass from function to function 
and it will serve as a global variable.*/
typedef struct {
    int is_error2;/*A variable that defines whether there is an error on the second pass.*/
    int yes_ext;/*Flag that checks whether there is data to output to the file ent*/
    int yes_ent;/*Flag that checks whether there is data to output to the file ext*/
}Variables;

/*Defining a struct that will contain the name and address of extern labels*/
typedef struct {
    char *labbel;
    char *addres;
}ext;
/*Defining a struct that will contain the name and address of entry labels*/
typedef struct {
    char *labbel;
    char *addres;
}ent;

#include "second_pass.h"
#include "assembler.h"
#include "pre_assembler.h"
#include "mcro_check.h"
#include "firstPass.h"


/**
 * mcro_name - Checks if a word exists in the macro table.
 *
 * @word: The word to check (string).
 * @size_mcro_table: The size of the macro table.
 * @mcros: Pointer to the array of Mcro structures (the macro table).
 *
 * @return: 1 if the word exists in the table, 0 otherwise.
 */
int mcro_name(char* word, int size_mcro_table, Mcro** mcros);

/**
 * save_name - Checks if a given name is a reserved keyword (opcode, register, or directive).
 *
 * @Name: The name to check (string).
 * @global0: Pointer to the Variables0 structure containing error flags.
 *
 * @return: 1 if the name is a reserved keyword, 0 otherwise.
 * If a reserved keyword is found, it also sets the is_error0 flag in global0 to 1.
 */
int save_name(char* Name);

/**
 * word_is_symbol - Checks if a word exists as a symbol in a given array of strings.
 *
 * @word: The word to search for.
 * @size: The size of the array.
 * @arr: The array of strings to search within.
 * @global: Pointer to the Variables structure containing error flags.
 *
 * @return: 0 if the word is found as a symbol, 1 otherwise.
 * If the word is not found, it prints an error message and sets the is_error2 flag in global to 1.
 */
int word_is_symbol(char* word, int size, char* arr[],Variables* global);

/**
 * add_entry_symbol - Adds the "entry" attribute to symbol table entries matching a given word.
 *
 * @word: The word to match against symbol names.
 * @symbol_table_size: The size of the symbol table array.
 * @arr: The symbol table array (array of strings).
 *
 * This function iterates through the symbol table, compares the first word of each entry
 * with the given word, and appends ", entry" to the entry if they match.
 */
void add_entry_symbol(char* word, int symbol_table_size, char* arr[]);
/**
 * which_kind_symbol - Retrieves the third word from a matching symbol table entry.
 *
 * @word: The word to match against symbol names.
 * @symbol_table_size: The size of the symbol table array.
 * @arr: The symbol table array (array of strings).
 *
 * The third word is equal to this, which characterizes the symbol.
 * This function iterates through the symbol table, compares the first word of each entry
 * with the given word, and returns the third word if a match is found.
 *
 * @return: The third word from the matching entry, or NULL if no match is found.
 */
/**/
char* which_kind_symbol(char* word, int symbol_table_size, char* arr[]);

/**
 * which_addres - Retrieves the second word (address) from a matching symbol table entry.
 *
 * @word: The word to match against symbol names.
 * @symbol_table_size: The size of the symbol table array.
 * @arr: The symbol table array (array of strings).
 *
 * The second word is the label's address.
 * This function iterates through the symbol table, compares the first word of each entry
 * with the given word, and returns the second word (address) if a match is found.
 *
 * @return: The second word (address) from the matching entry, or NULL if no match is found.
 */
char* which_addres(char* word, int symbol_table_size, char* arr[]);

/**
 * is_binary - Checks if a given string represents a binary address.
 *
 * @address: The string to check.
 *
 * This function iterates through the input string and checks if all characters are either '0', '1', or '\n'.
 *
 * @return: 0 if the string is a valid binary address, 1 otherwise.
 */
int is_binary(char* address);

/**
 * decimal_to_binary - Converts a decimal number to its binary representation.
 *
 * @number: The decimal number to convert.
 * @binary: A character array to store the binary representation.
 * @bits: The number of bits to use for the binary representation.
 *
 * This function converts a given decimal number to its binary representation using the specified number of bits.
 * It handles both positive and negative numbers using two's complement representation.
 *
 * @return: 0 if the conversion is successful, 1 if the number is out of range.
 */
int decimal_to_binary(int number, char* binary, int bits);




/*This function checks if there is a label defined as both Country and External, in which case it
throws an error*/
int Duplicate_check(ent** entr, ext** extr);

#endif
