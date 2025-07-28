#include "mcro_check.h"
int Mcro_check(char *lineCheck, int lineNumber, Variables0* global0, Mcro** mcros, char* file_name)
{
	char Name[MAX_MCRO_NAME_LENGTH + 1]; /*Setting a string for the name of the macro*/
	int i = 0, j = 0, start,h;
	/*Checking whether there is a substring if the word macro*/
	if (strstr(lineCheck, "mcro"))
	{
		/*Skip spaces if there are any at the beginning of the string*/
		while (isspace(lineCheck[i]))
		{
			i++;
		}
		/*We will check whether the word macro starts with the current character*/
		if (strncmp(&lineCheck[i],"mcro",strlen("mcro")) != 0)
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d There are characters before the macro definition file_name %s.\n", lineNumber, file_name);
			return error;
		}
		/*If we are in the definition of a macro then we will skip the word macro to check the rest.*/
		i += strlen("mcro");
		if (!isspace(lineCheck[i]))/*We will check if there is a space between the word macro and the name of*/
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d - Missing space after 'mcro' file name: %s.\n", lineNumber, file_name);
			return error;
		}
		/*Let's skip the profit to get to the word*/
		while (isspace(lineCheck[i]))
		{
			i++;
		}
		/*We will check if the first letter of the name follows the rules*/
		if (!isalpha(lineCheck[i]) && lineCheck[i] != '_')
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d - Invalid macro name start file name: %s.\n", lineNumber, file_name);
			return error;
		}
		i++;
		start = i;/*We will initialize start to be a variable that is defined starting from the beginning of the word*/
		/*	We will check if the first letter of the name follows the rules*/
		while (lineCheck[i] != '\n')
		{
			if (isalnum(lineCheck[i]) || lineCheck[i] == '_')
			{
				j++;/*I was told how many letters the macro name has.*/
				if (j > MAX_MCRO_NAME_LENGTH)
				{
					global0->is_error0 = 1;/*Error flag lighting*/
					printf("Error: Line %d - Macro name too long file name: %s.\n", lineNumber, file_name);
					return error;
				}
				i++;
				continue;
			}
		}
		/*If J=0 there is no name and this is an error*/
		if (j == 0)
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d - Invalid macro name file name: %s.\n", lineNumber, file_name);
			return error;
		}
		/*We will put the name of the macro into an array and send it to a function that checks whether the name of the macro is a reserved name.*/
		strncpy(Name, &lineCheck[start], j);
		Name[j] = '\0';
		if (save_name(Name) == error)
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d - Macro name is a reserved word file name: %s.\n", lineNumber, file_name);
			return error;
		}
		h = global0->mcrosCapacity;
		/*We will check whether the name of the macro is already in the table.*/
		if (mcro_name(Name, h, mcros) == error)
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d - Macro name is in mcro arr file name: %s.\n", lineNumber, file_name);
			return error;
		}
		if (strcmp(Name, "mcro") == success)
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d - Macro name is not invalid file name: %s.\n", lineNumber, file_name);

			return error;
		}
		strcat(global0->name, Name);/*Copying the macro name to a temporary variable*/
	}
	else
	{
		return error;/*This is not a mcro definition line.*/
	}
	return success; /*The line is a valid mcro definition.*/
}
/*This function checks whether we are on the correct line of the mcro ending.*/
int McroEnd_check(char* lineCheck, int lineNumber, Variables0* global0,Mcro** mcros, char* file_name)
{
	int i = 0;
	/*Checking whether there is a substring if the words end macro*/
	if (strstr(lineCheck, "mcroend"))
	{
		/*Skip spaces if there are any at the beginning of the string*/
		while (isspace(lineCheck[i]))
		{
		i++;
		}
		/*If we reach a letter, we will check whether starting from this letter there is the word 
		"end of macro" if so, we will check whether nothing else is written after the word if there
		is no word before the end of macro and this is an error..*/
		if (strncmp(&lineCheck[i], "mcroend", 7) != success)
		{
			printf("Error: Line %d - Invalid mcroend line file_name %s.\n", lineNumber, file_name);
			return error;
		}
		else if (strncmp(&lineCheck[i], "mcroend", 7) == success)
		{
			i += 8;
			while (lineCheck[i] != '\n')
			{
				if (!isspace(lineCheck[i]))
				{
					global0->is_error0 = 1;/*Error flag lighting*/
					printf("Error: Line %d on mcro end line file_name %s\n", lineNumber, file_name);
					return error;
				}
				i++;
			}
		}
		else
		{
			global0->is_error0 = 1;/*Error flag lighting*/
			printf("Error: Line %d on mcro end line file_name %s\n",lineNumber, file_name);
			return error;
		}
		add_mcro(mcros, global0);/*We will add the macro to the macro array*/
		global0->YesMcro = 0;/*Turn off the macro flag*/
	}
	else
	{
		return error;
	}
	return success; /*Correct mcro end line*/
}

/*פונקצייה להוספת מקרו*/
void add_mcro(Mcro** mcros, Variables0* global0)
{
	int i;
	Mcro *temp_mcros = NULL;
	if (global0->sizeTabbel == 0)/* אם גודל הטבלה שאנחנו מניחים שצריך שווה 0 נגדיל ב 20*/
	{
		global0->sizeTabbel += INITIAL_CAPACITY;
		*mcros = (Mcro*)malloc(sizeof(Mcro) * global0->sizeTabbel);/*הקצאת זיכרון ראשוני לטבלת המקרואים*/
		if (mcros == NULL) 
		{
			printf("Memory allocation failed!\n"); 
			exit(1);
		}
	}
	else if (global0->sizeTabbel == global0->sizeTabbelarr)/*אם גודל הטבלה שחשבו שצריך שווה לגודל הטבלה שמילאנו נגדיל ב 10*/
	{
		global0->sizeTabbel += more;
		temp_mcros = (Mcro*)realloc(*mcros, sizeof(Mcro) * global0->sizeTabbel);/* נגדיל את המקום בזיכרון - שימוש ב-*mcros */
		if (temp_mcros == NULL)
		{
			printf("Memory allocation failed!\n");
			exit(1);
		}
		*mcros = temp_mcros; /* עדכון המצביע mcros שיצביע על הזיכרון החדש */
	}
	/*עכשיו יש מקום ונכניס את הערכים למערך*/
	i = global0->sizeTabbelarr;
	strcpy((*mcros)[i].mcname, global0->name);
	strcpy((*mcros)[i].mcvalues, global0->val);

	memset(global0->name, 0, sizeof(32));/*ניקוי הטקסט מהמשתנה שמכיל את שם המקרו בהכנה לשם הבא*/
	memset(global0->val, 0, sizeof(global0->currentCapacity));/*ניקוי הטקסט מהמשתנה שמכיל את ערכי המקרו בהכנה לערכי המקרו הבא*/
	global0->currentNumValues = 0;
	global0->currentCapacity = 0;
	global0->sizeTabbelarr++;
}


