#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "simpleArrays.h"
#include "stack.h"


const int numOfOperations = 4;
char operations[4] = {'+', '-', '*', '/'};

char* getString()
{
    /* gets a string from stdin with
     * random size */
    int maxSize = 5;
    int stringLength = 0;
    char* output = createString(maxSize);
    char input = ' ';

    scanf("%c", &input);
    while (input != '\n')
    {
        if (stringLength == maxSize)
        {
            maxSize += 5;
            output = realloc(output, sizeof(char) * maxSize);
        }
        output[stringLength] = input;
        stringLength++;
        scanf("%c", &input);
    }
    output[stringLength] = '\0';
    return output;
}

bool isOperation(char input)
{
    for (int i = 0; i < numOfOperations; i++)
    {
        if (input == operations[i])
        {
            return true;
        }
    }
    return false;
}

int getOperationResult(char operation, int firstNumber, int secondNumber)
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

int calculateFromRPNString(char* input) {
    StackOfInt* numbers = createStackOfInt();
    int numberBuffer = 0;

    for (int charPos = 0; input[charPos] != '\0'; charPos++)
    {
        if (isdigit(input[charPos]))
        {
            numberBuffer = 10 * numberBuffer + (int) (input[charPos] - '0');
        }
        else if (isOperation(input[charPos]))
        {
            if (size(numbers) < 2)
            {
                printf("Incorrect input (dont have enough numbers)");
                return 0;
            }
            int secondNumber = popInt(numbers);
            int firstNumber = popInt(numbers);
            appendInt(getOperationResult(input[charPos], firstNumber, secondNumber), numbers);

        }
        else if (input[charPos] == ' ')
        {
            if (numberBuffer != 0)
            {
                appendInt(numberBuffer, numbers);
                numberBuffer = 0;
            }
        }
        else
        {
            printf("Incorrect input (strange char)");
            return 0;
        }
    }
    int result = popInt(numbers);
    free (numbers);
    return result;
}

int main() {
    char* input = getString();
    printf("%d", calculateFromRPNString(input));
    free(input);
    return 0;
}