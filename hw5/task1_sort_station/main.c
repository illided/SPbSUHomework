#include "calculator.h"
#include "simpleArrays.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    printf("Enter the string of numbers and operations:\n");
    char* input = getString();
    if (strlen(input) > 0)
    {
        char* output = convertToReversePolishNotation(input);
        printf("String in reverse polish notation:\n%s", output);
        free(output);
    }
    free(input);
    return 0;
}