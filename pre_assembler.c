#include "pre_assembler.h"


int Macro_deployment(char *file_name)
{

	FILE* f0, * fem;
	int j,i;
	int length = 0; /*Define a variable into which we will enter the length of the line*/
	char line[MAX_LINE_LENGTH];/*Array definition for a single line from the input file*/
	char *lin;
	int lineNumber = 1; /*Current line number in the input file*/
	char fName[FILENAME_LEN];
	Mcro* mcros = NULL;/*Creating a pointer to the macro array built from an array of structs*/
	Variables0* global0;/*Creating a pointer to a struct*/
	global0 = (Variables0*)malloc(sizeof(Variables0));
	if (global0 == NULL)
		exit(1);
	global0->YesMcro = 0;
	global0->is_error0 = 0;/*Error flag 0 No error 1 Yes*/
	global0->numMcros = 0;
	global0->mcrosCapacity = 0;
	global0->sizeTabbel = 0;
	


	add_suffix(file_name, ".as", fName);
	f0 = fopen(fName, "r");
	if (f0 == NULL)
	{
		printf("No such file or directory\n");
		return error;
	}
	add_suffix(file_name, ".am", fName);
	fem = fopen(fName, "w");
	if (fem == NULL) 
	{
		printf("No such file or directory\n");
		return error;
	}

	/*Get a line from the input file into the "line" variable we defined until we reach the end of the file*/
	while (fgets(line, sizeof(line) + 2, f0) != NULL)
	{
		length = strlen(line); /*Inserting the line length into the "length" variable*/

		if (length > MAX_LINE_LENGTH) /*If the length of the line is greater than the maximum, we will return an error*/
		{
			printf("Error: Line %d is too long length: %d file: %s\n",lineNumber,length,file_name); /*הדפסת הודעת שגיאה*/
			global0->is_error0 = 1;/*Ignition increases errors*/
		}
		else
		{
			/*Sent to a function that will check whether the sentence is an empty sentence that contains only whitespace characters.*/
			if (White_space_check(line, lineNumber) == success)
			{
				lineNumber++;
				continue;
			}
			/*Sent to a function that will check if this line is a comment line.*/
			else if (Checking_comment_line(line) == success)
			{
				lineNumber++;
				continue;
			}
			lin = Unnecessary_profit(line);
			if (global0->YesMcro == 0 && Mcro_check(lin,lineNumber,global0,&mcros, file_name) == success)/*If the line is a valid macro definition*/
			{ 
				global0->YesMcro = 1; /*Lighting a flag we are in a macro*/
				lineNumber++; 
				continue; 
			}
			/*If we are inside a macro definition, we will perform the following actions or tests*/
			else if (global0->YesMcro == 1)
			{
				/*If the line is the end of a macro definition and it is valid, we will perform the following actions*/
				if (McroEnd_check(lin,lineNumber,global0,&mcros,file_name) == success) /*סיום מאקרו*/
				{
					global0->YesMcro = 0;
				}
				/*כל עוד אנחנו בתוך הגדרת מאקרו*/
				else/*If the line is a macro value, we do the following:*/
				{
					j = strlen(lin);
					if (global0->currentNumValues == global0->currentCapacity)/*If the current macro values ​​array is full*/
					{
						if (global0->mcrosCapacity == 0)/*If the macro capacity is 0, increase it to 20*/
						{
							global0->mcrosCapacity = INITIAL_CAPACITY;
							global0->val = (char*)malloc(sizeof(char) * global0->mcrosCapacity);
							if (global0->val == NULL)
							{
								printf("Not enough memory Exit the program and close the files!\n");
								fclose(f0);
								fclose(fem);
								exit(1);
							}
						}
						else/*If the array capacity is different from 0, multiply it by + 10*/
						{
							global0->mcrosCapacity = global0->mcrosCapacity + (j+3);
							global0->val = (char*)realloc(global0->val, sizeof(char) * global0->mcrosCapacity);
							if (global0->val == NULL)
							{
								printf("Not enough memory Exit the program and close the files!\n");
								fclose(f0);
								fclose(fem);
								exit(1);
							}
						}
					}
					strcat(global0->val, lin); 
					strcat(global0->val, "\n"); 
					global0->currentNumValues+=j;
				}
				lineNumber++; /* הגדלת מספר השורה*/
				continue; /* מעבר לשורה הבאה*/
			}
			else/*אם המילה שכתובה היא שם של מקרו במקומה נכתוב לקובץ את ערכי המקרו הזה*/
			{
				i = strlen(lin);
				if (i < 32)
				{
					if (mcro_name(lin, global0->sizeTabbelarr, &mcros) != error)
					{
						j = mcro_name(lin, global0->sizeTabbelarr,&mcros);/*מחזיר את מיקום השם כדי שנדע למצוא אותו והלדפיס את הערכים לקובץ*/
						
						fprintf(fem, "%s", mcros[j].mcvalues);
					}
				}
			}
			/*We will copy the line to the file*/
			fprintf(fem, "%s", lin);
		}
		lineNumber++; 
	}
	fclose(f0);
	fclose(fem);
	if (global0->is_error0 == 0)
	{
		printf("We finished the pre-assembler, let's start the first pass.\n");
		lineExtr(file_name, global0->sizeTabbelarr, &mcros);
		return success;
		/*אם אין שגיאות נעבור לשלב הבא*/
	}
free(global0);
free(mcros);
return error;
}
/*פונקציה להוספת סיומת לקובץ*/
void add_suffix(char* file_name,char* suffix,char* new_name)
{
	int len = strlen(file_name);
	int i;
	for (i = 0; i < len && file_name[i] != '.'; i++)
	{
		new_name[i] = file_name[i];
	}
	new_name[i] = '\0';  
	strcat(new_name, suffix); 
}

/*Function to check comment lines*/
int Checking_comment_line(char lineCheck[])
{
	if (lineCheck == NULL || lineCheck[0] == '\0')/*Check for NULL and empty string*/
	{
		return error;
	}
	/*Checks if the first character is ;*/
		if (lineCheck[0] == ';')
		{
			/*Returns the first character successfully; this is indeed a comment line and is not copied to the new file.*/
			return success;
		}
	/*Returns error The first character is not ; this is not a comment line*/
	return error;
}

/*פונקצייה שבודקת אם השורה מכילה רק תווים לבנים*/
int White_space_check(char line[], int lineNumber)
{
	int i = 0;
	if (line == NULL)
	{
		printf("the line is NULL line Number: %d \n", lineNumber);
		return success;
	}

	while (line[i] != '\0')
	{
		if (!isspace(line[i]))
		{
			return error; /*יש תו לא לבן אז השורה לא ריקה*/
		}
		i++;
	}
	return success; /* כל התווים לבנים*/
}
/*פונקצייה להסרת רווחים מיותרים*/
char* Unnecessary_profit(char* lineCheck) 
{
	int i, j = 0;
	int spaceFound = 0;
	char* new_str;
	int len;
	if (lineCheck == NULL)
	{
		return NULL;
	}

	
	len = strlen(lineCheck);
	new_str = (char*)malloc(len + 1); /* הקצאת זיכרון חדש*/

	if (new_str == NULL) 
	{
		return NULL; /* החזרת NULL במקרה של שגיאה בהקצאת זיכרון*/
	}

	for (i = 0; lineCheck[i] != '\0'; i++)
	{
		if (isspace(lineCheck[i]))
		{
			if (!spaceFound && j > 0)
			{
				new_str[j++] = ' ';
				spaceFound = 1;
			}
		}
		else {
			new_str[j++] = lineCheck[i];
			spaceFound = 0;
		}
	}

	if (j > 0 && isspace(new_str[j - 1]))
	{
		j--;
	}

	new_str[j] = '\0';
	return new_str;
}

