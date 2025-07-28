#include <stdio.h>
#include "firstPass.h"

int IC = 100;
int DC = 0;
int i=0;

/*Row extractor*/
void lineExtr(char* fileName,int sizeArrMcro, Mcro** mcros)
{
    int i;   
    char* lebelsArray[100]={NULL};
    char bLabel[31];
    char line[MAX_LINE_LENGTH];
    Flags* myFlags;
    val* tabelCode = NULL;
    val* tabelData = NULL;
    FILE *f0;
    myFlags=(Flags*)malloc(sizeof(Flags));
	if (myFlags == NULL)
		exit(1);
    myFlags->flagIA = FALSE;
    myFlags->flagIAdes = FALSE;
    myFlags->flagRA = FALSE;
    myFlags->flagRAdes = FALSE;
    myFlags->flagLabelE = FALSE;
    myFlags->flagLabelBeg = FALSE;
    myFlags->flagLabelOri = FALSE;
    myFlags->flagLabelDes = FALSE;
    myFlags->flagRegOri = FALSE;
    myFlags->flagRegDes = FALSE;
    myFlags->flag = FALSE;
    myFlags->dataCounter = TRUE;
    myFlags->codeCounter = TRUE;

    tabelCode = (val*)malloc(sizeof(val));
	if (tabelCode == NULL)
		exit(1);
    tabelData = (val*)malloc(sizeof(val));
	if (tabelData == NULL)
	  	exit(1);
    tabelCode->enlargement = 0;
    tabelCode->numarr = 0;
    tabelData->enlargement = 0;
    tabelData->numarr = 0;

    f0 = fopen(fileName, "r");/*open the as file*/
    if (f0 == NULL)/*if the file doesnt exists- erorr*/
    { 
        printf("Error: Could not open file %s\n", fileName);
        return;
    }
    while (fgets(line, sizeof(line), f0) != NULL)/*read every line in the file*/
    {
        lineConvert(line,lebelsArray,bLabel,myFlags,&tabelCode,&tabelData,sizeArrMcro,mcros);
    }
    i = myFlags->flag;
    second_pass(fileName, i,myFlags->codeCounter ,myFlags->dataCounter, lebelsArray,  &tabelData, &tabelCode, i,sizeArrMcro,mcros);/*second pass*/
    fclose(f0);
    free(mcros);
    free(myFlags);
}

/*Returns the index in the array where the word exists.*/
int funcFinder(char* func)
{
    int i,sizeArry;
    char* allFunc[] = { "mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop" };/*all the functions*/
    spaceRemover(func);
    sizeArry = sizeof(allFunc) / sizeof(allFunc[0]);
    for (i = 0; i < sizeArry; i++)/*find the num of the func*/
    {
        if (strcmp(func, allFunc[i])==0)
            return i;
    }
    return DEFEULT;/*if it isnt a name of function*/
}
/*Checks line integrity and converts to code*/
void lineConvert(char* str, char** labelsArray, char* bLabel, Flags* myFlags, val** tabelCode, val** tableData, int sizeArrMcro, Mcro** mcros )
{
    int num,i=0;
    char* word = str;
    char* firstWord = strtok(word, " ");
    char* nextWord = strtok(NULL, "\n");
    char* origin = strtok(nextWord, ",");
    char* destenation = strtok(NULL, "\n");
    int funcNum = funcFinder(firstWord);
    char* wordCode;
    char* anotherWord;
    char* theirdWord ;
    char enter[50] = { 0 };
    char* code1,*code2;
    char* place;
    char* finalCode;
    char* labelName;
    switch (funcNum)
    {
    case 0:/*mov*/
    {

        if (origin == NULL || destenation == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (originParam(origin ,funcNum, myFlags,sizeArrMcro, mcros) == FALSE || destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE) /*validetion of the parameters*/

            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");

            }
            else/*coding*/
            {
                wordCode = coding(funcNum, nextWord, IC, myFlags);
                if (myFlags->flagIA == TRUE)/*if exist first adressing need another word*/
                {
                   anotherWord = codeIA(nextWord, IC);
		   IC++;
                }
            }
        }
    }
    break;
    case 1:/*cmp*/
    {
        if (origin == NULL || destenation == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {

            if (originParam( origin,funcNum, myFlags,sizeArrMcro, mcros) == FALSE || destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }

            else/*coding*/
            {
                wordCode = coding(funcNum, nextWord, IC, myFlags);
                if (myFlags->flagIA == TRUE)/*if exist first adressing need another word*/
                 {
                   anotherWord = codeIA(nextWord, IC);
		   IC++;
                }
                if (myFlags->flagIAdes == TRUE)/*if exist first adressing need another word*/
                 {
                   theirdWord = codeIA(nextWord, IC);
		   IC++;
                }
            }
        }

    }
    break;
    case 2:/*add*/
    {
        if (origin == NULL || destenation == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {

            if (originParam(origin,funcNum, myFlags,sizeArrMcro, mcros) == FALSE || destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }

            else/*coding*/
            {
                wordCode = coding(funcNum, nextWord, IC, myFlags);
                if (myFlags->flagIA == TRUE)/*if exist first adressing need another word*/
                  {
                   anotherWord = codeIA(nextWord, IC);
		   IC++;
                }
            }
        }
    }
    break;
    case 3:/*sub*/
    {
        if (origin == NULL || destenation == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {

            if (originParam(origin,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE || destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }

            else/*coding*/
            {
                wordCode = coding(funcNum, nextWord, IC, myFlags);
                if (myFlags->flagIA == TRUE)/*if exist first adressing need another word*/
                {
                   anotherWord = codeIA(nextWord, IC);
		   IC++;
                }
            }
        }
    }
    break;
    case 4:/*lea*/
    {
        if (origin == NULL || destenation == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {

            if (originParam(origin,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE || destenationParam(destenation,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }

            else/*coding*/
            {
                wordCode = coding(funcNum, nextWord, IC, myFlags);
            }
        }

    }
    break;
    case 5:/*clr*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }
    }
    break;
    case 6:/*not*/
    {

        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }
    }
    break;

    case 7:/*inc*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }
    }
    break;
    case 8:/*dec*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }

    }
    break;
    case 9:/*jmp*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }

    }
    break;
    case 10:/*bne*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum,  myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }

    }
    break;
    case 11:/*jsr*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            /*coding*/
            wordCode = coding(funcNum, nextWord, IC, myFlags);

        }
    }
    break;
    case 12:/*red*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);

        }
    }
    break;
    case 13:/*prn*/
    {
        if (origin == NULL)/*not enough parameters*/
        {
            myFlags->flag = TRUE;/*error flag*/
            printf("not enough parameters");
        }
        else
        {
            if (destenationParam(destenation,funcNum, myFlags,sizeArrMcro, mcros) == FALSE)/*validetion of the parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("parameter arnt valied");
            }
            else/*coding*/
            {
                wordCode = coding(funcNum, nextWord, IC, myFlags);
                if (myFlags->flagIAdes == TRUE)/*if exist first adressing need another word*/
                {
                   anotherWord = codeIA(nextWord, IC);
		   IC++;
                }
            }

        }
    }
    break;
    case 14:/*rts*/
    {
        if (strcmp(firstWord, "rts") != 0)/*not valied prameters*/
        {/*error flag*/
            myFlags->flag = TRUE;
            printf("not valied word");
        }
        else
            if (origin != NULL || destenation != NULL)/*not other parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("not valied input");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);
    }
    break;
    case 15:/*stop*/
    {
        if (strcmp(firstWord, "stop") != 0)/*not valied prameters*/
        {
            myFlags->flag = TRUE;
            printf("not valied word");
        }
        else
            if (origin != NULL || destenation != NULL)/*not other parameters*/
            {
                myFlags->flag = TRUE;/*error flag*/
                printf("not valied input");
            }
            else/*coding*/
                wordCode = coding(funcNum, nextWord, IC, myFlags);
    }
    break;
    case -1:/*not a function*/
    {
        if (labelCheck(firstWord,sizeArrMcro, mcros) == TRUE)/*the first word is a label*/
          {
            if (check_entry_or_extern(nextWord) == FALSE)/*if not entry or extern*/
            {
                /*save label name*/
                spaceRemover(firstWord);
                bLabel = (labelFinder(firstWord));
                myFlags->flagLabelBeg = TRUE;
                lineConvert(nextWord, labelsArray, bLabel, myFlags,tabelCode,tableData,sizeArrMcro, mcros );/*check the function for next word*/
            }
           }
            else 
              if (strcmp(firstWord, ".data") == TRUE)/*the word is .data*/
		{
                    if (isDataValied(nextWord) == FALSE)/*not valied line*/
                    {
                        myFlags->flag = TRUE;/*error flag*/
                        printf("not valied input");
                    }
                    else
                    {

                        num = dataCoding(nextWord, DC, myFlags, tableData);/*add to counter the number of added word to table*/
                        DC+=num;
			myFlags->dataCounter+=num;
			if (myFlags->flagLabelBeg == TRUE && ( labelsArray != NULL || existlabel(bLabel, labelsArray, i) == FALSE))/*if has valied label*/
                        {
                            /**enter = (char*)malloc(50 * sizeof(char));
                            if (enter == NULL)
                            {
                                perror("malloc failed");if erroe

                            }*/
                            memset(enter, 0, 50);
                            my_snprintf(enter, 50, "%s %d data", bLabel, DC);
                            labelsArray[i] = my_strdup(enter); /*dinamic mammory*/
                            if (i >= 100)
                            {
                                labelsArray = (char**)realloc(labelsArray, 1 * sizeof(char*));
                                if (labelsArray == NULL) 
                                {
                                    perror("realloc failed");
                                    exit(1);
                                }
                                if (labelsArray[i] == NULL)
                                {
                                    perror("strdup failed");
                                }
                                i++;
                                bLabel = NULL;
                            }
                        }
                     }
                    }
                        else
                            if (strcmp(firstWord, ".string") == TRUE)/*if the first word is .string*/
                            {
                                if (nextWord == NULL || nextWord == '\0')/*case of error*/
                                {
                                    myFlags->flag = TRUE;/*error flag*/
                                    printf("not valied input");
                                }
                                else
                                {
                                    num = stringCoding(nextWord, DC, myFlags, tableData);/*add to counter the number of added word to table*/
				    DC+=num;
				    myFlags->dataCounter+=num;
                                    if (myFlags->flagLabelBeg == TRUE && (*labelsArray != NULL || existlabel(bLabel, labelsArray, i) == FALSE))/*if has valied label*/
                                    {
                                        /**enter = (char*)malloc(50 * sizeof(char));
                                        if (enter == NULL)
                                        {
                                            perror("malloc failed");error

                                        }*/
                                        memset(enter, 0, 50);
                                        my_snprintf(enter, 50, "%s %d data", bLabel, DC);
                                        labelsArray[i] = my_strdup(enter); /*dinamic memmory*/
                                        if (i >= 100)
                                        {
                                            labelsArray = (char**)realloc(labelsArray, 1 * sizeof(char*));
                                            if (labelsArray == NULL)
                                            {
                                                perror("realloc failed");
                                                exit(1);
                                            }
                                            if (labelsArray[i] == NULL)
                                            {
                                                perror("strdup failed");
                                            }
                                            i++;
                                            bLabel = NULL;
                                        }

                                    }
                                }
                            }
                            else
                                if (strcmp(firstWord, ".entry") == TRUE)/*first word is antry*/
                                {
                                    if (LabelValied(nextWord,sizeArrMcro, mcros ) == FALSE)
                                    {
                                        myFlags->flag = TRUE;/*error flag*/
                                        printf("not valied input");
                                    }
                                }
                                else

                                    if (strcmp(firstWord, ".exteren") == TRUE)/*first word is extern*/
                                    {
                                        if (LabelValied(nextWord,sizeArrMcro, mcros) == TRUE)
                                        {
                                            myFlags->flag = TRUE;/*error flag*/
                                            printf("not valied input");
                                        }
                                        else
                                            if (LabelValied(origin,sizeArrMcro, mcros) == TRUE)
                                            {
                                                bLabel = (labelFinder(origin));
                                                /*enter = (char*)malloc(50 * sizeof(char));
                                                if (enter == NULL)
                                                {
                                                    perror("malloc failed");error

                                                }*/
                                                memset(enter, 0, 50);
                                                my_snprintf(enter, 50, "%s %d data", bLabel, DC);
                                                labelsArray[i] = my_strdup(enter); /*dinamic memmory*/
                                                if (labelsArray[i] == NULL)
                                                {
                                                    perror("strdup failed");
                                                }
                                                if (i >= 100)
                                                {
                                                    labelsArray = (char**)realloc(labelsArray, 1 * sizeof(char*));
                                                    if (labelsArray == NULL)
                                                    {
                                                        perror("realloc failed");
                                                        exit(1);
                                                    }
                                                    i++;
                                                    IC++;
                                                    bLabel = NULL;
                                                    myFlags->flagLabelBeg = FALSE;
                                                }
                                            }
                                            myFlags->flagLabelE = TRUE;
                                    }
                                    else/*not known word*/
                                    {
                                        myFlags->flag = TRUE;
                                        printf("not valied line");
                                    }
                        break;
                    }
    }
    if (myFlags->flagLabelBeg == FALSE && (labelsArray == NULL || existlabel(bLabel, labelsArray, i ) == FALSE) && myFlags->flagLabelE == FALSE)/*if has a label in the beginning*/
    {
        /*add label to table*/
       /*enter = (char*)malloc(50 * sizeof(char));
        if (enter == NULL)
        {
            perror("malloc failed");error

        }*/
        memset(enter, 0, 50);
        my_snprintf(enter, 50, "%s %d data", bLabel, DC);
        labelsArray[i] = my_strdup(enter); /*dinamic memmory*/
        if (i >= 100)
        {
            labelsArray = (char**)realloc(labelsArray, 1 * sizeof(char*));
            if (labelsArray == NULL) {
                perror("realloc failed");
                exit(1);
            }
            if (labelsArray[i] == NULL)
            {
                perror("strdup failed");
            }
            i++;
            IC++;
            bLabel = NULL;
            myFlags->flagLabelBeg = FALSE;
        }
    }
    if (myFlags->flagLabelBeg == TRUE && existlabel(bLabel, labelsArray, i) == FALSE && myFlags->flagLabelE == TRUE)/*if has a label in the beginning*/
    {
        /*add label to table*/
       /*enter = (char*)malloc(50 * sizeof(char));
        if (enter == NULL)
        {
            perror("malloc failed");error

        }*/
        memset(enter, 0, 50);
        my_snprintf(enter, 50, "%s %d data", bLabel, DC);
        labelsArray[i] = my_strdup(enter); /*dinamic memmory*/
        if (labelsArray[i] == NULL)
        {
            perror("strdup failed");
        }
        if (i >= 100)
        {
            labelsArray = (char**)realloc(labelsArray, 1 * sizeof(char*));
            if (labelsArray == NULL)
            {
                perror("realloc failed");
                exit(1);
            }
            i++;
            IC++;
            bLabel = NULL;
            myFlags->flagLabelBeg = FALSE;
        }
    }
   
    /*insert to struct*/
     if(wordCode!=NULL)
    {

    if(anotherWord!= NULL && theirdWord!=NULL)
    {
      code1=convert7(IC-3);
      code2=convert7(IC-2);
      finalCode=conect(code1, code2);
      free(code1);
      free(code2);
      code1=convert7(IC-1);
      finalCode=conect(finalCode, code1);
      free(code1);
      place=conect(wordCode, anotherWord);
      place=conect(place, theirdWord);
    }
   else
   if(anotherWord!=NULL)
   {
     code1=convert7(IC-2);
     code2=convert7(IC-1);
     finalCode= conect(code1, code2);
     free(code1);
     free(code2);
     place=conect(wordCode, anotherWord);
   }
   else
   {
    finalCode=convert7(IC);
    place=wordCode;
   }
   if(myFlags->flagLabelOri==TRUE)
   {
    labelName=labelFinder(origin);
    finalCode=conect(finalCode, labelName);
   }
   if(myFlags->flagLabelDes==TRUE)
   {
     labelName=labelFinder(destenation);
     finalCode=conect(finalCode, labelName);
   }
    finalCode=conect(finalCode, "\n");
    place=conect(place, "\n");
    add_Coding(tabelCode, place, finalCode);
    myFlags->codeCounter++;
    free(place);
    free(finalCode);
    }

    
    /*Reset*/
    myFlags->flagIA = FALSE;
    myFlags->flagIAdes = FALSE;
    myFlags->flagRA = FALSE;
    myFlags->flagRAdes = FALSE;
    myFlags->flagLabelE = FALSE;
    myFlags->flagLabelOri = FALSE;
    myFlags->flagLabelDes = FALSE;
    myFlags->flagRegOri = FALSE;
    myFlags->flagRegDes = FALSE;
    
}
                   

 /*check validety of origin parameters*/
 int originParam(char* str, int i, Flags *myFlags, int sizeArrMcro, Mcro** mcros)
 {
     char* word = str;
     spaceRemover(word);
     if (word[0] == '\0')/*the word is only tabes and spaces*/
         return FALSE;
     if (i != 4)
     {
         if (*word == '+' || *word == '-')
         {
             if (isdigit(word[1]) != 0)
                 return TRUE;
         }
         if (isdigit(word) != 0)/*if it is a number*/
             return TRUE;
         if (immediateAdress(word))/*if it is a '#'*/
         {
             myFlags->flagIA = TRUE;
             return TRUE;
             
         }
             
         if (LabelValied(word,sizeArrMcro, mcros))/*if it is a label*/
         {
             myFlags->flagLabelOri = TRUE;
             return TRUE;
             
         }
         if (ifReg(word) != DEFEULT)/*if it is a register*/
         {
             myFlags->flagRegOri = TRUE;
             return TRUE;
             
         }
         else
         {
             if (LabelValied(word,sizeArrMcro, mcros))/*if it is a label*/
             {
                 myFlags->flagLabelOri = TRUE;
                 return TRUE;

             }
         }
         return FALSE;
     }
return FALSE;
}

 /*check validety for destanation parametr*/
 int destenationParam(char* str,int i,  Flags *myFlags, int sizeArrMcro, Mcro** mcros)
 {
     char* word = str;
     spaceRemover(word);
     if (word[0] == '\0')/*the word is only tabes and spaces*/
         return FALSE;
     if (i == 1 || i == 13)
     {
         if (*word == '+' || *word == '-')
         {
             if (isdigit(word[1]) != 0)
                 return TRUE;
         }
         if (isdigit(*word) != 0)/*if it is a number*/
             return TRUE;
         if (immediateAdress(word))
         {
             myFlags->flagIAdes = TRUE;
             return TRUE;
             
         }
         
         if (LabelValied(word,sizeArrMcro, mcros))/*if it is a label*/
         {
             myFlags->flagLabelDes = TRUE;
             return TRUE;
             
         }
         if (ifReg(word) != DEFEULT)/*if it is a register*/
         {
             myFlags->flagRegDes = TRUE;
             return TRUE;
            
         }
     }
     else
     {

         if (i >= 9 && 1 <= 11)
         {
             if (*word == '+' || *word == '-')
             {
                 if (isdigit(word[1]) != 0)
                     return TRUE;
             }
             if (isdigit(*word) != 0)/*if it is a number*/
                 return TRUE;
             if (immediateAdress(word))
             {
                 myFlags->flagIAdes = TRUE;
                 return TRUE;

             }

             if (relativeAdress(word,sizeArrMcro, mcros))/*if it is a label*/
             {
                 myFlags->flagLabelDes = TRUE;
                 return TRUE;

             }
         }
         else
         {
             if (*word == '+' || *word == '-')
             {
                 if (isdigit(word[1]) != 0)
                     return TRUE;
             }
             if (isdigit(*word) != 0)/*if it is a number*/
                 return TRUE;
             if (immediateAdress(word))
             {
                 myFlags->flagIAdes = TRUE;
                 return TRUE;

             }
             if (relativeAdress(word,sizeArrMcro, mcros) != 0)
             {
                 myFlags->flagRAdes = TRUE;
                 return TRUE;
             }
         }
     }
     
     return FALSE;
 }
char* coding(int i,char *nextWord,int IC, Flags* myFlags)
{
	char *bin18,  *bin3, *bin16, *bin13, *bin8, *bin11, *bin0;
	char* wordCode = (char*)malloc(25 * sizeof(char));
        if (wordCode == NULL) 
	{
    
             return NULL;
  	}
 	i = strlen(wordCode);
	memset(wordCode, '\0',i);
	/*places 18-23 3-7*/
	if (i == 2 || i == 3)/*add, sub*/
	{
		bin18 = getBinaryLastNBits(2, 5);
		if (i == 2)
		   bin3 = getBinaryLastNBits(1, 5);
		if (i == 3)
		   bin3 = getBinaryLastNBits(2, 5);
		
	}
	if (i == 0)/*mov*/
	{
		bin18= getBinaryLastNBits(0, 5);
		bin3 = getBinaryLastNBits(0, 5);
	}
	if (i == 1)/*cmp*/
	{
		bin18 = getBinaryLastNBits(1, 5);
		bin3 = getBinaryLastNBits(0, 5);
	}
	if (i == 4)/*lea*/
	{
		bin18 = getBinaryLastNBits(4, 5);
		bin3 = getBinaryLastNBits(0, 5);
	}
	if (i>=5 && i<=8)/*clr, not, inc, dec*/
	{
		bin18 = getBinaryLastNBits(5, 5);
		if(i==5)
			bin3= getBinaryLastNBits(1, 5);
		else 
			if(i==6)
			 bin3 = getBinaryLastNBits(2, 5);
		else 
		    if (i == 7)
			 bin3 = getBinaryLastNBits(3, 5);
		else
		 bin3 = getBinaryLastNBits(4, 5);
	}
	if (i>=9 && i<=11)/*jmp, bne, jsr*/
	{
		bin18 = getBinaryLastNBits(9, 5);
		if (i == 9)
			bin3 = getBinaryLastNBits(1, 5);
		else 
			if (i == 10)
			 bin3 = getBinaryLastNBits(2, 5);
		else
		 bin3 = getBinaryLastNBits(3, 5);
	}
	if (i >= 12 && i <= 15)/*red, prn, rts, stop*/
	{
		bin18 = getBinaryLastNBits(i, 5);
		bin3 = getBinaryLastNBits(0, 5);
	}
	/*מקומות 13-17*/
	if (i >= 5 && i <= 13)/*gets only one operand*/
	{
     bin13= getBinaryLastNBits(0, 3);
	 bin16= getBinaryLastNBits(0, 2);
	 if (i >= 9 && i <= 11)/*jmp bne jsr*/
	 {
		 if(myFlags->flagLabelDes==TRUE)/*adressing 1*/
			 bin11 = getBinaryLastNBits(1, 2);
		 else
			 if(myFlags->flagIAdes==TRUE)/*adressing 1*/
				 bin11 = getBinaryLastNBits(1, 2);
			 else/*no adressing*/
				 bin11 = getBinaryLastNBits(0, 2);
		 bin8 = getBinaryLastNBits(0, 3);
	 }
	 else
	 {
		 if (myFlags->flagLabelDes == TRUE)/*adressing 1*/
		 {
			 bin11 = getBinaryLastNBits(1, 2);
			 bin8 = getBinaryLastNBits(0, 3);
		 }
		 else
			 if (myFlags->flagRegDes == TRUE)/*adressing 3*/
			 {
				 bin11 = getBinaryLastNBits(3, 2);
				 bin8 = getBinaryLastNBits(ifReg(nextWord), 3);

			 }
			 else/*no adressing*/
			 {
				 bin11 = getBinaryLastNBits(0, 2);
				 bin8 = getBinaryLastNBits(0, 3);
			 }
	 }
	  }
	if (i == 14 || i == 15)/*no parameter*/
	{
		bin8 = getBinaryLastNBits(0, 3);
		bin11= getBinaryLastNBits(0, 2);
		bin13= getBinaryLastNBits(0, 3);
		bin16= getBinaryLastNBits(0, 2);
	}
	if (i >= 0 && i <= 4)/*can get two parameters*/
	{
		if (i == 4)/*lea*/
		{
			if(myFlags->flagLabelOri ==TRUE)/*adressing 1*/
			{
				bin16 = getBinaryLastNBits(1, 2);
				bin13 = getBinaryLastNBits(0, 3);
				

			}
			else
			 if (myFlags->flagLabelDes == TRUE)/*adressing 1*/
			 {
                bin11 = getBinaryLastNBits(1, 2);
				bin8 = getBinaryLastNBits(0, 3);
			 }
			 else
			  if (myFlags->flagRegDes == TRUE/*adressing 3*/)
			  {
				bin11 = getBinaryLastNBits(3, 2);
				bin8 = getBinaryLastNBits(ifReg(nextWord), 3);
			  }
				
		}
		else
		{
			if (myFlags->flagLabelOri == TRUE)/*adressing 1 */
			{
				bin16 = getBinaryLastNBits(1, 2);
				bin13 = getBinaryLastNBits(0, 3);


			}
			else
			 if (myFlags->flagRegOri == TRUE)/*adressing 1 */
			 {
				bin16 = getBinaryLastNBits(3, 2);
				bin13 = getBinaryLastNBits(ifReg(nextWord), 3);
			 }
			 else
			  if (myFlags->flagIA == TRUE)/*adressing 0*/
			  {
				bin16 = getBinaryLastNBits(0, 2);
				bin13 = getBinaryLastNBits(0, 3);
			   }
			  else
			   if (myFlags->flagLabelDes == TRUE)/*adressing 1 */
			   {
				bin11 = getBinaryLastNBits(1, 2);
				bin8 = getBinaryLastNBits(0, 3);
			   }
			   else
			    if (myFlags->flagRegDes == TRUE)/*adressing 3*/
			    {
				 bin11 = getBinaryLastNBits(3, 2);
				 bin8 = getBinaryLastNBits(ifReg(nextWord), 3);
			    }
		}
		if(bin16==NULL)
			bin16 = getBinaryLastNBits(0, 2);
		if(bin13==NULL)
			bin13 = getBinaryLastNBits(0, 3);
		if(bin11==NULL)
			bin11 = getBinaryLastNBits(0, 2);
		if(bin8==NULL)
			bin8 = getBinaryLastNBits(0, 3);
	}
	/*ARE*/
	if (myFlags->flagIA == TRUE || myFlags->flagIAdes==TRUE)/*adressing 0*/
		bin0 = my_strdup("100");
	else
	if (myFlags->flagLabelOri == TRUE || myFlags->flagLabelDes == TRUE)/*adressing 1*/
	{
		if (myFlags->flagLabelE == TRUE)/*label .extern or .entry*/
			bin0 = my_strdup("001");
		else
			bin0 = my_strdup("010");
	}
	else
	if (myFlags->flagRA == TRUE || myFlags->flagRAdes==TRUE)/*adressing 2*/
			bin0 =my_strdup( "100");
	else
	if (myFlags->flagRegOri == TRUE || myFlags->flagRegDes==TRUE)/*adressing 3*/
			bin0 =my_strdup( "000");
	else
		bin0 = my_strdup("000");
	/*insert all the code part*/
	strncpy(wordCode+18, bin18, 5);
	strncpy(wordCode + 3, bin3, 5);
	strncpy(wordCode + 16, bin16, 2);
	strncpy(wordCode + 13, bin13, 3);
	strncpy(wordCode + 11, bin11, 2);
	strncpy(wordCode + 8, bin8, 3);
	strncpy(wordCode, bin0, 3);
	wordCode[24] = '\0';
	free(bin18);
	free(bin3);
	free(bin16);
	free(bin13);
	free(bin11);
	free(bin8);
        IC++;
	return wordCode;

}
/*coding all the numbers in .data and addit to the struct*/
int dataCoding(char *nextWord, int dc, Flags* myFlags, val* *tabelData)
{
	int num, i = 0, flagMin = FALSE;
	char* binNum;
        char* code;
	while (*nextWord != '\n' || *nextWord!= '\0')/*till the end of the line*/
	{
		if (*nextWord != '\t' && *nextWord != ' ' && *nextWord != ',')
		{
			
				if (isdigit(nextWord) != 0)/*if it is a number*/
				{
					num=0;
					while (nextWord != NULL && isdigit(*nextWord) != 0)/*fint all the digits of the number*/
					{
						num = (num * 10) + (*nextWord- '0');
						nextWord++;
					}
					if (flagMin == TRUE)/*if ta number is negetive*/
					  {
						num = -num;
						flagMin = FALSE;
					  }
					binNum= getBinaryLastNBits(num, 23);
                       /*insert to struct*/
                       {
                       code=convert7(dc+i);
                       add_Coding(tabelData, code, binNum);
                       free(code);
                       }

					i++;
				}
			else
			
				if (isdigit(nextWord)==0)/*if the char is '-' update the minus flag if it is ',' or tab ignore*/
				{
					if (*nextWord == '-')
						flagMin = TRUE;
					else
						if (*nextWord == '+')
							flagMin = FALSE;
				}
					
			
		}
		nextWord++;
   }
	
	return i;
}
/*gets the arry in .string ant add evrey char to the struct and count it*/
int stringCoding(char* nextWord, int dc, Flags* myFlags, val** tabelData)
{
	int i = 0,num;
	char* binNum;
        char* code;
	while (*nextWord != '\n' || *nextWord!= '\0')/*all the chares in the line*/
	{
		
		num = (int)*nextWord;
        binNum= getBinaryLastNBits(num, 23);
		/*insert to the struct*/;
       {
           code=convert7(dc+i);
           add_Coding(tabelData, code, binNum);
           free(code);
        }

        i++;
	}
	/*insert /0*/
	binNum= getBinaryLastNBits(0, 23);
	
	i++;
	return i;
}
void add_Coding(val** tabel, char* addressput, char* numput)
{
	int a;
	if ((*tabel)->enlargement == 0)
	{
		(*tabel)->enlargement = 50;
		*tabel = (val*)malloc(sizeof(val) * (*tabel)->enlargement);
		if (*tabel == NULL)
		{
			printf("Memory allocation failed!\n");
			exit(1);
		}
	}
	else if ((*tabel)->enlargement == (*tabel)->numarr)
	{
		(*tabel)->enlargement += 10;
		*tabel = (val*)realloc(*tabel, sizeof(val) * (*tabel)->enlargement);
		if (*tabel == NULL)
		{
			printf("Memory allocation failed!\n");
			exit(1);
		}
	}
		a = (*tabel)->numarr;
		strcpy((*tabel)[a].adress, addressput);
		strcpy((*tabel)[a].binaryMachineCode, numput);
}

/*The encoding function*/
void Adding_encoding_labbel(val** tabel, int table_size, int symbol_table_size, char* arrsymbol[], ent* entr, ext* extr,Variables* global)
{
	char* label_test;/*Label word*/
	char binary[22];
	char* label_name;/*The label word starting from second place like if there is & then after that it will start*/
	char* add=NULL;
	char addtemp[40], *address_label;
	char* address_jmp;
	char TempBinaryMachineCode[100];
	char temp_label_test[100], temp_label_jmp[100];
	int  convert, i, j, ARE = 100, AREent = 010, sum = 0, temp;
	for (i = 0; i < table_size; i++)
	{
		/*Puts everything in the cell into a variable*/
		strcpy(temp_label_test, (*tabel[i]).binaryMachineCode);
		strcpy(temp_label_jmp, (*tabel[i]).adress);
		/*Inserts the first encoding for label checking*/
		label_test = strtok(temp_label_test, "\n");
		while (label_test != NULL)
		{
			/*I defined a variable at the beginning of the loop so that every time they enter the loop,
			this variable will be incremented by 1, so I will know where the address I need to output
			is, and at the end of each encoding, the variable is initialized to 0.*/
			sum++;
			label_name = &label_test[1];
			/*If this is not a binary address and this word is in the symbol table*/
			if (is_binary(label_test) == 1 && label_test[0] == '&' && word_is_symbol(label_name, symbol_table_size, arrsymbol, global) == 0)
			{
				address_label = which_addres(label_name, symbol_table_size, arrsymbol);/*Label address*/
				address_jmp = strtok(temp_label_jmp, "\n");
				temp = (int)address_label - (int)address_jmp;/*Label less jump*/
				convert = decimal_to_binary(temp,binary, 21);/*Sending to phone that converts to binary*/
				convert += ARE;/*Adding the right three places*/
				strcat(TempBinaryMachineCode, (char*)convert);/*We will insert the new encoding in its place.*/
				strcat(TempBinaryMachineCode, "\n");
			}/*If the label is external*/
			else 
			if (is_binary(label_test) == 1 && word_is_symbol(label_name, symbol_table_size, arrsymbol, global) == 0 && strcmp(which_kind_symbol(label_name, symbol_table_size, arrsymbol), "extern") == 0) 

			{
				strcat(TempBinaryMachineCode, External_encoding);/*Replacing the string with the address*/
				strcat(TempBinaryMachineCode, "\n");
				/*We will add to the struct to print at the end to the file*/
				global->yes_ext = 1;/*We will turn on the flag that there are variables to output to the file.*/
				strcat(extr->labbel, label_name);/*Adding the name to the external struct*/
				strcat(extr->labbel, "\n");
				strcpy(addtemp, (*tabel[i]).adress);
				add = strtok(addtemp, "\n");
				j = sum;
				/*This loop runs until it reaches the address it needs to output, and it knows the
				location through the variable sum we defined.*/
				while (j > 0)
				{
					add = strtok(NULL, "\n");
					if (j == 1)
					{
						strcat(extr->addres, add);/*Adding the address to the struct*/
						strcat(extr->addres, "\n");
					}
					j--;
				}
				/*sum = 0;*/
			}/*If the label is Enter*/
			else if (is_binary(label_test) == 1 && word_is_symbol(label_name, symbol_table_size, arrsymbol, global) == 0)
			{
				address_label = which_addres(label_name, symbol_table_size, arrsymbol);/*Label address*/
				convert = decimal_to_binary(temp, binary, 21);/*Sending to phone that converts to binary*/
				convert += AREent;/*Adding the right three places*/
				strcat(TempBinaryMachineCode, (char*)convert);/*Replacing the string with the address*/
				strcat(TempBinaryMachineCode, "\n");
				global->yes_ent = 1;/*Turning on the flag has data to output to a file*/
				strcat(entr->labbel, label_name);/*Adding the name to the struct*/
				strcat(entr->labbel, "\n");
				add = strtok(addtemp, "\n");
				j = sum;
				/*This loop runs until it reaches the address it needs to output, and it knows the
				location through the variable sum we defined.*/
				while (j > 0)
				{
					add = strtok(NULL, "\n");
					if (j == 1)
					{
						strcat(extr->addres, add);/*Adding the address to the struct*/
						strcat(extr->addres, "\n");
					}
					j--;
				}
				/*sum = 0;*/
			}
			else
			{
				strcat(TempBinaryMachineCode, label_test);
				strcat(TempBinaryMachineCode, "\n");
				/*sum = 0;*/
			}
			label_test = strtok(NULL, "\n"); /*Getting the next encoding*/
		}
		/*Copies the new values into the encoding tabl*/
		strcpy(TempBinaryMachineCode,(*tabel[i]).binaryMachineCode);
		sum = 0;
	}
}
#include "second_pass.h" 

