#ifndef ASSEMBLER_H

#define ASSEMBLER_H

#include "mcro_check.h"
#include "pre_assembler.h"
#include "propriety.h"
#include "coding.h"
#include "reference_tables.h"
#include "firstPass.h"
#include "second_pass.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#define numRegister 9
#define numOpcodes 16
#define numDirectives 4
#define numRegister 9
#define BINARY_LENGTH 21
#define Initial_allocation 50
#define error 1                /*Set status 1 as error*/
#define success 0             /*Set status 0 as success*/
#define MAX_LINE_LENGTH 81   /*Setting maximum length of line 81 as constant*/
int main(int argc, char* argv[]);

#endif
