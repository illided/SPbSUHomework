#include <stdio.h>
#include <stdlib.h>
#include "simpleArrays.h"
#include "calculator.h"

int main()
{
    printf("Enter an expression in the standard notation\n");
    char* input = getString();
    bool inputIsCorrect = false;
    double answer = calculate(input, &inputIsCorrect);
    if (inputIsCorrect)
    {
        printf("Answer: %lf", answer);
    }
    free(input);
    return 0;
}