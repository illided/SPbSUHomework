#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleArrays.h"

const int numOfOperations = 4;
char operations[4] = {'+', '-', '*', '/'};
int priorities[4]  = { 1,   1,   2,   2};

int getPriority(char operation)
{
    for (int i = 0; i < numOfOperations; i++)
    {
        if (operation == operations[i])
        {
            return priorities[i];
        }
    }
    return 0;
}

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

char* convertRPN(char* input)
{
    int outputLength = 0;
    char *output = createString(2 * strlen(input));
    StackOfChar* specialCharsStack = createStackOfChar();
    for (int currentChar = 0; input[currentChar] != '\0'; currentChar++)
    {
        /* skipping all the spaces */
        if (input[currentChar] == ' ')
        {
            continue;
        }

        if (isdigit(input[currentChar]))
            /* if next token is a digit then
             * send it to the output*/
        {
            output[outputLength] = input[currentChar];
            /* if next token is not a digit then
             * add a space */
            if (!isdigit(input[currentChar + 1]))
            {
                outputLength++;
                output[outputLength] = ' ';
            }
            outputLength++;
        }
        else if (input[currentChar] == '(')
        {
            /* if token is the open bracket then
             * add it to the stack */
            appendChar('(', specialCharsStack);
        }
        else if (input[currentChar] == ')')
        {
            /* if this is the close bracket then
             * keep adding to the output every operation from the stack
             * until we get a open bracket (deleting open bracket) */
            while (peekChar(specialCharsStack) != '(')
            {
                if (stackOfCharIsEmpty(specialCharsStack))
                {
                    printf("Incorrect input (brackets are not balanced)\n");
                    return NULL;
                }
                output[outputLength] = popChar(specialCharsStack);
                output[outputLength + 1] = ' ';
                outputLength += 2;
            }
            popChar(specialCharsStack);
        }
        else if (isOperation(input[currentChar]))
        {
            /* if token is an operation then:
             * 1) if op have bigger priority than op on the top of the stack
             * add it to the stack
             * 2) else add top of the stack to output and repeat */
            int currentOperationPriority = getPriority(input[currentChar]);
            while ((peekChar(specialCharsStack) != '(') &&(currentOperationPriority <= getPriority(peekChar(specialCharsStack))))
            {
                output[outputLength] = popChar(specialCharsStack);
                output[outputLength + 1] = ' ';
                outputLength += 2;
            }
            appendChar(input[currentChar], specialCharsStack);
        }
        else
        {
            printf("Input is incorrect (non correct characters)");
            return NULL;
        }
    }
    /* add all left chars in the stack to the output */
    while (!stackOfCharIsEmpty(specialCharsStack))
    {
        output[outputLength] = popChar(specialCharsStack);
        output[outputLength + 1] = ' ';
        outputLength += 2;
    }
    output[outputLength] = '\0';
    free(specialCharsStack);
    return output;
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

int calculateFromRPNString(char* input)
{
    StackOfInt* numbers = createStackOfInt();
    int numberBuffer = 0;
    bool bufferIsEmpty = true;
    for (int charPos = 0; input[charPos] != '\0'; charPos++)
    {
        if (isdigit(input[charPos]))
        {
            numberBuffer = 10 * numberBuffer + (int) (input[charPos] - '0');
            bufferIsEmpty = false;
        }
        else if (isOperation(input[charPos]))
        {
            if (size(numbers) < 2)
            {
                printf("Incorrect input\n");
                return 0;
            }
            int secondNumber = popInt(numbers);
            int firstNumber = popInt(numbers);
            if ((secondNumber == 0) || (input[charPos] == '/'))
            {
                printf("Incorrect input (tried to divide by zero)\n");
                return 0;
            }
            appendInt(getOperationResult(input[charPos], firstNumber, secondNumber), numbers);

        }
        else if (input[charPos] == ' ')
        {
            if (!bufferIsEmpty)
            {
                appendInt(numberBuffer, numbers);
                numberBuffer = 0;
                bufferIsEmpty = true;
            }
        }
        else
        {
            printf("Incorrect input (strange char)\n");
            return 0;
        }
    }
    int result = popInt(numbers);
    free(numbers);
    return result;
}

int main() {
    printf("I am the calculator!\nEnter the string in the standart "
           "notation and you'll get the answer\n");
    char* input = getString();
    input = convertRPN(input);
    if (input == NULL)
    {
        return 0;
    }
    printf("Result = %d", calculateFromRPNString(input));
    return 0;
}