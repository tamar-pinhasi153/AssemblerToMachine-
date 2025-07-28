#include "assembler.h"

int main(int argc, char* argv[])
{
int i;
    for (i = 1; i < argc; i++)
    { 

        if (Macro_deployment(argv[i]) == 1)
        {
            continue; 
        }
    }
return success;
}
