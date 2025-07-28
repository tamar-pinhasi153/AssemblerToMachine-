#include "coding.h"



/*coding instant adressing*/
char* codeIA(char* nextWord, int ic)
{
	int num;
	char* bin;
	char* word = (char*)malloc(25 * sizeof(char));
       if (word == NULL)
	 {
        
        return NULL; 
	}


	if (nextWord[1] == '-' || nextWord[1] == '+')/*if has a sighn before the number*/
		num = (nextWord[2]-'0');
	num = (nextWord[1]-'0');
	if (*nextWord == '-')/*If the number is negative*/
		bin = getBitsCom(num);
	bin = getBinaryLastNBits(num, 21);
	strncpy(word+3, bin, 21);/*the number*/
	/*ARE*/
	word[2] = '1';
	word[1] = '0';
	word[0] = '0';
	word[24] = '\0';
	free(bin);
	return word;
}
/*21 ביטים אחרונים של מספר בשיטת המשלים*/
char* getBitsCom(int num) 
{
	unsigned int mask = (1 << 21) - 1;  /* Mask for the last 21 bits (0x1FFFF)*/
	unsigned int last21Bits = num & mask; /* Extract the last 21 bits*/
        int i;
	/* Allocate memory for the binary string: 21 bits + '\0' for null termination*/
	char* binaryStr = (char*)malloc(22 * sizeof(char));
	if (binaryStr == NULL) 
        {
		return NULL; /* Return NULL if memory allocation fails*/
	}

	/* Convert the number to a binary string*/
	for ( i = 20; i >= 0; i--) 
	{
		binaryStr[i] = (last21Bits & 1) + '0'; /*Get the last bit and add '0'*/
		last21Bits >>= 1; /* Shift bits to the right*/
	}
	binaryStr[21] = '\0'; /* Add null terminator*/

   return binaryStr;
}
	/*num as char*/
char* numToChar(int num)
{
        int length;
	char* result = (char*)malloc(8 * sizeof(char)); /*dinamic memory*/
	if (result == NULL) 
	{
		return NULL; /*if failed in memory*/
	}
		length = my_snprintf(result, 8, "%d", num);

	if (length < 7)
	{
		int zerosToAdd = 7 - length;
		memmove(result + zerosToAdd, result, length + 1);
		memset(result, '0', zerosToAdd);
	}
   return result;
}
/*The operation accepts as a parameter a number in decimal base and any number - num and returns the last num (significant) characters in the binary representation of the number in decimal base received as a parameter.*/
 char* getBinaryLastNBits(unsigned int number, int num)
 {
      int i;
      char* binary;
      if (num < 1 || num > 32)/*checks if num valied*/
       {
              return NULL;
       }
       binary = (char*)malloc(num + 1);
       if (!binary)
       {
              return NULL; /* Treatment of failure*/
       }

         binary[num] = '\0'; /*end of string*/

       for (i = num - 1; i >= 0; i--)
       {
           binary[i] = (number & 1) + '0'; /*saves the last bit*/
           number >>= 1; /* move the number to the right*/
       }

return binary;
}
/*conect two string to gether*/
char* conect(char *str1,char *str2)
 {
    int len1 = strlen(str1);  /* אורך המחרוזת הראשונה */
    int len2 = strlen(str2);  /* אורך המחרוזת השנייה */
    char *result = (char *)malloc(len1 +1 + len2 + 1);  /* הקצאת זיכרון למחרוזת החדשה */

    if (!result)
    {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }

    strcpy(result, str1);             /* מעתיק את המחרוזת הראשונה */
    result[len1] = '\n';              /* שינוי: מוסיף ירידת שורה בסוף המחרוזת הראשונה */
    result[len1 + 1] = '\0';          /* שינוי: מסיים את המחרוזת הנוכחית לפני הוספה */

    strcat(result, str2);             /* מוסיף את המחרוזת השנייה */

    return result;       
}
/*convert to 7 digits in char*/
char* convert7(int num)
 {
    char *result = (char *)malloc(8); /* 7 תווים + '\0' לסיום */
    if (!result) 
     {
        printf("Error allocating memory.\n");
        return NULL;
    }

    /* %07d מוודא שיש בדיוק 7 ספרות עם אפסים מובילים */
    sprintf(result, "%07d", num);

    return result;
}
/*instead of sprintf*/
int my_snprintf(char* str, size_t size,const char* format,...) 
{
    int result;
    va_list args; /* Variable argument list */
    va_start(args, format); /* Initialize variable arguments */
    result = my_vsnprintf(str, size, format, args); /* Format string */
    va_end(args); /* Clean up variable arguments */
    return result;
}
/*instead of strdup*/
char* my_strdup(const char* s) 
{
    size_t len = strlen(s) + 1; /* Calculate length of string + null terminator */
    char* new_s = malloc(len); /* Allocate memory for new string */
    if (new_s == NULL) {
        return NULL; /* Return NULL if memory allocation fails */
    }
    memcpy(new_s, s, len); /* Copy string to new memory */
    return new_s; /* Return pointer to new string */
}

/*instead of vsnprintf*/
int my_vsnprintf(char *str, size_t size, const char *format, va_list args)
 {
    
    int len = 0; /* Length of the formatted string */
    int i = 0;   /* Index for the format string */
    int num;
    char* s;
    char c;
    while (format[i] != '\0' && len < size - 1) {
        if (format[i] == '%') {
            i++; /* Move to the format specifier */
            if (format[i] == 'd') {
                /* Integer format */
                num = va_arg(args, int);
                len += my_snprintf(str + len, size - len, "%d", num);
            } else if (format[i] == 's') {
                /* String format */
                s = va_arg(args, char *);
                len += my_snprintf(str + len, size - len, "%s", s);
            } else if (format[i] == 'c') {
                /* Character format */
                c = va_arg(args, int); 
                len += my_snprintf(str + len, size - len, "%c", c);
            } else if (format[i] == '%') {
                /* Escape sequence for % */
                str[len++] = '%';
            } else {
                /* Unsupported format, copy the character as is */
                str[len++] = format[i];
            }
        } else {
            /* Copy regular characters */
            str[len++] = format[i];
        }
        i++;
    }

    str[len] = '\0'; /* Null terminate the string */
    return len; /* Return the length of the formatted string */
}

