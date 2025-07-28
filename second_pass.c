#include "firstPass.h"
#include "second_pass.h"

int second_pass(char* file_name, int symbol_table_size, int table_code_size,int table_data_size, char *Symbol_array[], val** tabelData, val** tabelCode, int flag,int sizeArrMcro, Mcro** mcros)
{
	int i,a,b;
	int linenumber = 1;/*Variable that counts the lines of the file*/
	char *line=NULL, *templine=NULL, *word, *tempword=NULL,*ad=NULL,fName[100];
	FILE* f0, * fext, * fent=NULL, * fob;/*Program files*/
	Variables* global;/*Defining a pointer to the global array*/
	ent* entr;/*Defining a pointer to a struct*/
	ext* extr;/*Defining a pointer to a struct*/

	global = (Variables*)malloc(sizeof(Variables));
	if (global == NULL)
		exit(1);
	global->is_error2 = 0;
	global->yes_ent = 0;/*A flag that checks if there is nothing to print to the file is initialized to 0 which means there is nothing.*/
	global->yes_ext = 0;/*A flag that checks if there is nothing to print to the file is initialized to 0 which means there is nothing.*/

	i = table_code_size + table_data_size;
	entr = (ent*)malloc(sizeof(i));
	if (entr == NULL)
		exit(1);
	entr->addres = (char*)malloc(sizeof(char) * i);
	if (entr->addres == NULL)
		exit(1);
	entr->labbel = (char*)malloc(sizeof(char) * i);
	if (entr->labbel == NULL)
		exit(1);
	extr = (ext*)malloc(sizeof(i));
	if (entr == NULL)
		exit(1);
	extr->addres=(char*)malloc(sizeof(char) * i);
	if (extr->addres == NULL)
		exit(1);
	extr->labbel = (char*)malloc(sizeof(char) * i);
	if (extr->labbel == NULL)
		exit(1);

	f0 = fopen("file_name", "r");/*Opening the file I received in read mode*/
	if (f0 == NULL)
	{
		printf("No such file or directory\n");
		return error;
	}
	while (fgets(line, sizeof(line), f0) != NULL)/*A loop that receives line by line from the file*/
	{
		strcpy(templine , line);
		word = strtok(templine, " ");/*Outputs the first word up to a space.*/
		strcpy(tempword , word);/*A variable that contains the optional name for the label*/
		if (LabelValied(word,sizeArrMcro ,mcros) == 0)/*If the word is a label*/
			/*אם זה שווה 0 זה סמל שנמצא בטבלת הסמלים*/
		{
			word = strtok(NULL, " ");/*If we are inside a label, we will output the second word to check what it is.*/
			if ((strcmp(word, ".data") == 0) || (strcmp(word, ".string") == 0) || (strcmp(word, ".extern") == 0) )/*If this is a prompt, we'll skip it.*/
			{
				linenumber++;/*Let's move on to the next line.*/
				continue;/*Exiting the loop*/
			}
			/*Sent to a function that will check if the label is in the symbol table. If so, we will 
			return 0. If not, we will return 1. Then we will update the flag that there is an error and print an error message.*/
			else if (word_is_symbol(tempword, symbol_table_size, Symbol_array,global) == 1)
			{
				global->is_error2 = 1;/*Error flag lighting*/
				printf("Error, label %s not found linenumber %d \n",tempword, linenumber);/*We will issue an error message.*/
				linenumber++;/*Let's move on to the next line.*/
				continue;/*Exiting the loop*/
			}
			else if (strcmp(word, ".entry") == 0)/*If the label is entry, we will add the word "entry" to the symbol specification.*/
			{
				global->yes_ent = 1;
				add_entry_symbol(tempword, symbol_table_size, Symbol_array);
				strcat(entr->labbel, tempword);/*We will add the label to the Entry Labels structure.*/
				strcat(entr->labbel, "\n");
				ad = which_addres(tempword, symbol_table_size, Symbol_array);/*We will enter the address that will be returned from the function into the variable ad.*/
				strcat(entr->addres, ad);/*We will add her address to the direct entry.*/
				strcat(entr->addres, "\n");
				linenumber++;
				continue;
			}
		}
		linenumber++;
	}
	/*Sent to a function that will complete the encodings that the first pass did not complete.*/
	Adding_encoding_labbel(tabelCode, table_code_size, symbol_table_size, Symbol_array,entr,extr,global);
	Adding_encoding_labbel(tabelData, table_data_size, symbol_table_size, Symbol_array, entr, extr, global);
	/*If there is a label that is both an entry and an external, we will flag there is an error.*/
	if (Duplicate_check(&entr, &extr) == 1)
	{
		global->is_error2 = 1;
	}
	if (flag == error)
	{
		global->is_error2 = 1;
	}
	/*If the error flag is on, we will terminate the program.*/
	if (global->is_error2 == 0)
	{
		printf("Errors found in files\n");
		return error;
	}
	else/*Otherwise we will create the files*/
	{
		/*We will create the OB file. First, we will print how many code words and how many data words
		we had in the program, then we will print the addresses and encodings. Just before that, 
		we will convert the char variable to int and we are done creating the file.*/
		add_suffix(file_name, ".ob", fName);
		fob = fopen(fName, "w");
		if (fob == NULL)/*בודקת שהקובץ שיצרתי נפתח*/
		{
			printf("No such file or directory\n");
			return error;
		}
		fprintf(fob, "%d %d", table_code_size, table_data_size);
		/*Print code words*/
		for (i = 0; i < table_code_size; i++)
		{
			strcpy(line, (*tabelCode)[i].adress);
			strcpy(templine, (*tabelCode)[i].binaryMachineCode);
			word = strtok(line, "/n");
			tempword = strtok(templine, "/n");
			while (word != NULL && tempword != NULL)
			{
				a = atoi(word);/*נמיר לאינט*/
				b = atoi(tempword);/*נמיר לאינט*/
				fprintf(fob, "%07d %06x\n", a, b); /* פורמט עבור 7 ספרות עשרוני ו-6 ספרות אקסדצימלי*/
				word = strtok(NULL, "/n");
				tempword = strtok(NULL, "/n");
			}
		}
		/*Print data words*/
		for (i = 0; i < table_data_size; i++)
		{
			strcpy(line, (*tabelData)[i].adress);
			strcpy(templine, (*tabelData)[i].binaryMachineCode);
			word = strtok(line, "/n");
			tempword = strtok(templine, "\n");
			while (word != NULL && tempword != NULL)
			{
				
				a = atoi(word);/*נמיר לאינט*/
				b = atoi(tempword);/*נמיר לאינט*/
				fprintf(fob, "%07d %06x\n", a, b); /* פורמט עבור 7 ספרות עשרוני ו-6 ספרות אקסדצימלי*/
				word = strtok(NULL, "\n");
				tempword = strtok(NULL, "\n");
			}
		}
		fclose(fob);
		/*We will check if it says there is data to print to the EXT file by checking if the flag is on or off. If the flag is off, if the flag is on, we will print all the data we saved in the struct.*/
		if (global->yes_ext == 1)/*There are things to print.*/
		{
			add_suffix(file_name, ".ext", fName);
			fext = fopen(fName, "r");

			if (fext == NULL)
			{
				printf("No such file or directory\n");
				return error;
			}
			fprintf(fent, "%s %s\n", extr->labbel, extr->addres); /* כתיבת שני מספרים שלמים עם רווח ביניהם*/
			fclose(fext);
		}
		/*We will check if it says there is data to print to the ENT file by checking if the flag is on or off. If the flag is off, if the flag is on, we will print all the data we saved in the struct.*/
		if (global->yes_ent == 1)/*There are things to print.*/
		{
			add_suffix(file_name, ".ent", fName);
			fent = fopen(fName, "r");
			if (fent == NULL)
			{
				printf("No such file or directory\n");
				return error;
			}
			fprintf(fent, "%s %s\n", entr->labbel, entr->addres); /* כתיבת שני מספרים שלמים עם רווח ביניהם*/
			fclose(fent);
		}
		return success;
	}
	free(tabelCode);
	free(tabelData);
	free(entr);
	free(extr);
	free(global);
	return success;
}

