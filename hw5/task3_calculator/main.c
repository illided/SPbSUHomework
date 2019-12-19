#include <stdio.h>
#include <stdlib.h>
#include "simpleArrays.h"
#include "calculator.h"

int main()
{
    printf("Enter an expression in the standard notation\n");
    char* input = getString();
    printf("Answer:\n%lf", calculate(input));
    free(input);
    return 0;
}