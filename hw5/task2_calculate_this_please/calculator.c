#include "stack.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isOperation(char input)
{
    const int numOfOperations = 4;
    char operations[] = {'+', '-', '*', '/'};
    for (int i = 0; i < numOfOperations; i++)
    {
        if (input == operations[i])
        {
            return true;
        }
    }
    return false;
}

double getOperationResult(char operation, double firstNumber, double secondNumber)
{
    switch (operation)
    {
        case '+':
        {
            return firstNumber + secondNumber;
        }
        case '-':
        {
            return firstNumber - secondNumber;
        }
        case '*':
        {
            return firstNumber * secondNumber;
        }
        case '/':
        {
            return firstNumber / secondNumber;
        }
    }
}

double getResultOfExpression(char* input)
{
    StackOfDouble* numbers = createStackOfDouble();
    double numberBuffer = 0;
    bool bufferIsEmpty = true;
    for (int charPos = 0; input[charPos] != '\0'; charPos++)
    {
        if (isdigit(input[charPos]))
        {
            numberBuffer = 10 * numberBuffer + (double) (input[charPos] - '0');
            bufferIsEmpty = false;
        }
        else if (isOperation(input[charPos]))
        {
            if (size(numbers) < 2)
            {
                printf("Incorrect input\n");
                deleteStackOfDouble(numbers);
                return 0;
            }
            double secondNumber = popDouble(numbers);
            double firstNumber = popDouble(numbers);
            if ((secondNumber == 0) && (input[charPos] == '/'))
            {
                printf("Incorrect input (tried to divide by zero)\n");
                deleteStackOfDouble(numbers);
                return 0;
            }
            appendDouble(getOperationResult(input[charPos], firstNumber, secondNumber), numbers);

        }
        else if (input[charPos] == ' ')
        {
            if (!bufferIsEmpty)
            {
                appendDouble(numberBuffer, numbers);
                numberBuffer = 0;
                bufferIsEmpty = true;
            }
        }
        else
        {
            printf("Incorrect input (strange char)\n");
            deleteStackOfDouble(numbers);
            return 0;
        }
    }
    if (!bufferIsEmpty)
    {
        appendDouble(numberBuffer, numbers);
    }
    double result = 0;
    int numbersSize = size(numbers);
    if (numbersSize == 1)
    {
        result = popDouble(numbers);
    }
    else if (numbersSize > 1)
    {
        printf("Incorrect input\n");
        deleteStackOfDouble(numbers);
        return 0;
    }
    deleteStackOfDouble(numbers);
    return result;
}