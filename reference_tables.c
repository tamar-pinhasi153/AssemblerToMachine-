#include "reference_tables.h"


/*A function that checks if the name of something is in the macro table. If not, it will return 1. 
If so, it will return the location of the macro*/
int mcro_name(char *word, int size_mcro_table, Mcro** mcros)
{
	int i;
	if (mcros == NULL)
	{
		return success;
	}
	for (i = 0; i < size_mcro_table; i++)
	{
		if (strcmp(word,(*mcros)[i].mcname) == success)
		{
			return error;
		}
	}
	return i;
}

int save_name(char* Name)
{
	int i;
	char* opcodes_names[numOpcodes] = { "mov","cmp","add","sub","lea","clr","not","inc","dec","jmp",
		"bne","jsr","red","prn","rts","stop" };
	char* register_names[numRegister] = { "r0","r1","r2","r3","r4","r5","r6","r7","r8" };
	char* Directives_names[numDirectives] = { "data","string","entry","extern" };
	for (i = 0; i < numOpcodes; i++)
	{
		if (strcmp(Name, opcodes_names[i]) == success)
		{
			return error; 
		}
	}
	for (i = 0; i < numRegister; i++)
	{
		if (strcmp(Name, register_names[i]) == success)
		{
			return error; 
		}
	}
	for (i = 0; i < numDirectives; i++)
	{
		if (strcmp(Name, Directives_names[i]) == success) 
		{
			return error; 
		}
	}
	return success; 
}

int word_is_symbol(char *word, int size, char *arr[], Variables* global)
{
	int i;
	char *arrWord;
	char arrTemp[100];
	for (i = 0; i < size; i++)
	{
		strcpy(arrTemp, arr[i]);
		arrWord = strtok(arrTemp, " ");
		if (strcmp(arrWord, word) == 0)
		{
			return success;/*labbel in arr*/
		}
	}
	global->is_error2 = 1;
	printf("Error: %s is not in symbol tabbel",word);
	return error; 
}
/*Function for adding the entry label. It receives the name of the label to add, the label array, and its size.*/
void add_entry_symbol(char *word, int symbol_table_size, char *arr[])
{
	int i;
	char *arrWord, * new_arr, arrTemp[100];
	for (i = 0; i < symbol_table_size; i++)
	{
		strcpy(arrTemp, arr[i]);/*Puts the entire sentence at position i into a variable*/
		arrWord = strtok(arrTemp, " ");/*Inserts the first word, which is the label, into a variable*/
		if (strcmp(arrWord, word) == 0)/* Checks that the variable is equal to the label obtained from the second pass*/
		{
			new_arr = malloc(strlen(arr[i]) + strlen(", entry") + 1); /*Allocating memory for a variable that will be concatenated into the final string*/
			if (new_arr == NULL) 
			{
				printf("שגיאה בהקצאת זיכרון\n");
				exit(1);
			}
			strcpy(new_arr, arr[i]); /*Copying the original string*/
			strcat(new_arr, ", entry");/*We will enter the word entry.*/
			strcpy(arr[i], new_arr);/*We will copy the variable to the original string*/
			free(new_arr);
		}
	}
}
/*פונקצייה שמציגה איזה אפיון סמל אנחנו*/
char* which_kind_symbol(char *word,int symbol_table_size, char *arr[])
{
	char temparr[100], *word1, *word2, *word3;
	int i;
	for (i = 0; i < symbol_table_size; i++)
	{
		strcpy(temparr, arr[i]); /* העתקת המחרוזת המקורית כדי לא לשנות אותה*/
		word1 = strtok(temparr, " ");
		if (strcmp(word, word1) == 0)
		{
			word2 = strtok(NULL, " ");
			if(word2 != NULL)
			{
			    word3 = strtok(NULL, " ");
			    return word3;
			}
		}
	}
	return NULL;
}
/*A function that returns the address of the label*/
char* which_addres(char* word, int symbol_table_size, char* arr[])
{
	char temparr[100], * labbel, * addres;
	int i;
	for (i = 0; i < symbol_table_size; i++)
	{
		strcpy(temparr, arr[i]);
		labbel = strtok(temparr, " ");
		if (strcmp(word, labbel) == 0)
		{
			addres = strtok(NULL, " ");
			return addres;
		}
	}
	return NULL;
}

/*A helper function that will check if the characters are a binary address or a label that needs to
be encoded*/
int is_binary(char *address) 
{
	int i;
	for (i = 0; address[i] != '\0'; i++)
	{
		if (address[i] != '0' && address[i] != '1' && address[i] != '\n') 
		{
			return 1; 
		}
	}
	return 0; 
}

int decimal_to_binary(int number, char* binary, int bits)
{
	int i,max = (1U << (bits - 1)); 
	int min = -max; 
	int value; 

	/*Input validity check: If the number is out of range, returns an error message.*/
	if (number >= min && number <= max) 
	{
		/*If the number is positive, use it directly.*/
		if (number >= 0) 
		{
			value = number;
		}
		else 
		{
			/*If the number is negative, uses the "2's complement" method to represent it.*/
			value = (1U << bits) + number;
		}
		/*Convert the number to binary representation.*/
		for (i = bits - 1; i >= 0; i--)
		{
			binary[i] = (value & 1) ? '1' : '0'; /*Check if the current bit is 1 or 0*/
			value >>= 1; /*Shift the bits right by 1.*/
		}
		binary[bits] = '\0'; /*End the string with a '\0' character.*/
		return (int)binary;
	}
	else
	{
		/*If the number is out of range, returns an error message.*/
		printf(binary, "Error: Number %d out of range for %d bits", number, bits);
	}
return 0;
}

int Duplicate_check(ent** entr, ext** extr)
{
	char * a, * b, temp1[32], temp2[32];
	strcpy(temp1, (*entr)->labbel);
	strcpy(temp2, (*extr)->labbel);
	a = strtok(temp1, "\n");
	b = strtok(temp2, "\n");
	while (a != NULL && b != NULL)
	{
		if (strcmp(a, b) == 0)
		{
			return 1;
		}
		a = strtok(NULL, "\n");
		b = strtok(NULL, "\n");
	}
	return 0;
}



