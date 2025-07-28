#include "propriety.h"

/* checks if the paramter is register for clr, not, inc, red, prn*/
int ifReg(char* str)
{
    int i,j = DEFAULT;
    char regName[2];
    char* firstWord = str;
    if (firstWord != NULL)
    {
        spaceRemover(firstWord);/*remove spaces and tabs*/
        if (firstWord == NULL)/*if it has only spaces and tabs*/
        {
            printf("not valied parameter");
        }
        else
        {
            for (i = 0; i <= 7; i++)/*checks if it is a name of register*/
            {
                sprintf(regName, "r%d", i);
                if (strcmp(firstWord, regName) == 0)
                {
                    j = i;
                }
            }
            if (*(firstWord + 1) != '\0')/*if there are more chares after the register*/
            {
                printf("not valied parameter");
            }
        }
    }
    return j;/*returens register number*/
}


/*the operand # */
int immediateAdress(char* str)
{
    char* word;
    int i=0;
    word = str;
    if (word == NULL)/*empty prameter- no parameter*/
        return FALSE;
    if (word[i] == '#')
        i++;
    else
        return FALSE;
    if (word[i] == '+' || word[i] == '-')
        i++;
    if (word[i] == '\0')/*only + or -*/
        return FALSE;
    spaceRemover(word);
    if (isdigit(word[i]) == 0)/*not a number*/
        return FALSE;
    while (word[i] != ',' && word[i] != ' ' && word[i] != '\t' && word[i] != '\0')/*every char is a number*/
    {
        if (isdigit(word[i]) == 0)
            return FALSE;
        i++;
    }
    return TRUE;
}
/*checks if a word is a label*/
 int labelCheck(char* str, int sizeArrMcro, Mcro** mcros)
 {
     char* word;
     int i;
     /*size_t len = strlen(word);*/
     word = str;
     spaceRemover(word);
     i=strlen(word);
     if (word[0] == '\0' || i == 0)/*no label- empty*/
        return FALSE;
     else
     {
	 if(word[i] == '\0')
	    {
		if(word[i-1] == ':')
		{
		     if(LabelValied(word,sizeArrMcro, mcros) == TRUE)
		     {
		          return TRUE;/*the last char is ':' and the word is valied label*/
		     }
		}
	    }
     }
   return FALSE;
 }
 /*check the reative adressing */
 int relativeAdress(char* str, int sizeArrMcro, Mcro** mcros)
 {
     char* word = str;
     spaceRemover(word);
     if (word == NULL)/*the word is only tabes and spaces*/
         return FALSE;
     if(word[0]=='&')/*if the first char is '&'*/
         if(LabelValied((&word[1]),sizeArrMcro, mcros) == TRUE)/*if the label is valied*/
            return TRUE;
     return FALSE;
 }
    
 /*check validety for .data*/
 int isDataValied(char* str)
 {
     char* word;
     int i=0;
     int flag;
     word = str;
     spaceRemover(word);
     if (word == NULL)/*the word is only tabes and spaces*/
         return FALSE;
    flag = FALSE;
    while (word[i] != '\0')/*check until the end of row*/
     {
             if (isdigit(word[i]) != 0)/*if the char is a digit*/
             {
                 while (word[i] != '\0' && isdigit(word[i]) != 0)/*find all the digits of number*/
                     i++;
                 flag = TRUE;
             }
             else
             {
                 if (word[i] == ',')
                 {
                     if (flag == FALSE)/*two ',' without number between*/
                         return FALSE;
                     else
                         flag = FALSE;
                 }
                 else
                     if (word[i] == '+' || word[i] == '-')/*if the current char is + or -*/
                     {
                         if (word == NULL)/*if there is no chares after that*/
                             return FALSE;
                         if (isdigit(word[1]) == 0)/*if it doesnt have number after that*/
                             return FALSE;
                     }
                     if (word[i] != ' ' && word[i] != '\t')/*other not valied char*/
                         return FALSE;
               i++;
             }
             
     }
    if (flag == FALSE)/*last char is ','*/
         return FALSE;
    return TRUE;
 }
 
 /*tabes remover*/
 void spaceRemover(char* str)
 {
     int start;
     size_t len;
     if (str == NULL) 
         return;
     len = strlen(str);
     while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))/*remove spaces and tabs in the end*/
     {
         str[len - 1] = '\0';
         len--;
     }
      start = 0;
     while (str[start] == ' ' || str[start] == '\t')/*remove spaces and tabs in beginning*/
     {
         start++;
     }

     
     if (start > 0)
     {
         size_t i = 0;
         while (str[start + i] != '\0')
         {
             str[i] = str[start + i];
             i++;
         }
         str[i] = '\0'; 
     }
 }
 /*labels validety*/
 int LabelValied(char* word,int sizeArrMcro, Mcro** mcros)
 {
     int i=0;
     spaceRemover(word);
     if (word[i] == '\0')/*the word is only tabes and spaces*/
         return FALSE;
     if (strlen(word) > 31)/*if the length is too long*/
     {
        printf("not valied length");
         return FALSE;
         
     }
     if(isupper(word[i]) == 0)/*if the first char isnt big letter*/
     {
         printf("not valied char");
         return FALSE;
         
     }
     i++;
     while (word[i] != '\0' && word[i] != ' ' && word[i] != '\t' && word[i] != ':')
     {
         if(isdigit(word[i]) == 0 && isalpha(word[i]) == 0)/*if its is not latter or number*/
         {
             printf("not valied char");
             return FALSE;
             
         }
         i++;
     }
     if(mcro_name(word,sizeArrMcro, mcros)==1)/*if it is a name of macro*/
     {
         printf("mcro name");
         return FALSE;
         
     }
    if(save_name(word)==1)/*if it is a save name*/
    {
        printf("saved name");
        return FALSE;
        
    }
    return TRUE;

 }
 /*checks if llabel already exists in the list*/
 int existlabel(char* word, char** arrey, int length)
 {
     int i;
     char* arrWord;
     char arrTemp[100];
     for (i = 0; i < length; i++)
     {
         strcpy(arrTemp, arrey[i]);
         arrWord = strtok(arrTemp, " ");/*the name of label*/
         if (strcmp(arrWord, word) == 0)/*if the label in the arrey*/
             return TRUE; 
     }
     return FALSE;
 }
/*copy the label*/
 char* labelFinder(char *str)
 {
     char* word; 
     int i = 0;
     word = str;
     while (word[i] != '\n' && word != NULL && word[i] != ' ' && word[i] !=':')/*copy until the end of label*/
     {
         i++;
     }
     word[i] = '\0';
     return word;
 } 
 /*checks if has .entry or .extern in the line*/
 int check_entry_or_extern(const char* word)
 {
     if (word == NULL) 
         return FALSE;
     if (strstr(word, ".entry") != NULL || strstr(word, ".extern") != NULL)/*checks if has entry or extern in the line*/
     {
         return TRUE;
     }

     return FALSE;
 }

