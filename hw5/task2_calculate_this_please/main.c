#include <stdio.h>
#include <stdlib.h>
#include "simpleArrays.h"
#include "calculator.h"

int main()
{
    printf("Enter an expression in reverse polish notation\n");
    char* input = getString();
    printf("Answer:\n%lf", getResultOfExpression(input));
    free(input);
    return 0;
}