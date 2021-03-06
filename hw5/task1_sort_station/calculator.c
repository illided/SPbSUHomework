#include "simpleArrays.h"
#include "stack.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getPriority(char operation)
{
    const int numOfOperations = 4;
    char operations[] = {'+', '-', '*', '/'};
    int priorities[] = {1, 1, 2, 2};

    for (int i = 0; i < numOfOperations; i++)
    {
        if (operation == operations[i])
        {
            return priorities[i];
        }
    }
    return 0;
}

bool isInputCorrect(char input)
{
    const int numOfOperations = 4;
    char operations[] = {'+', '-', '*', '/'};
    bool inputIsCorrect = false;
    for (int i = 0; i < numOfOperations; i++)
    {
        if (input == operations[i])
        {
            inputIsCorrect = true;
        }
    }
    return inputIsCorrect || isdigit(input) || (input == '(') || (input == ')');
}

bool tryToHandleCloseBracket(int* outputLength, Stack* specialCharsStack, char* output)
{
    /* if this is the close bracket then
    * keep adding to the output every operation from the stack
    * until we get a open bracket (deleting open bracket) */
    while (peek(specialCharsStack) != '(')
    {
        if (isEmpty(specialCharsStack))
        {
            printf("Input is incorrect!");
            deleteStack(specialCharsStack);
            free(output);
            return false;
        }
        output[*outputLength] = pop(specialCharsStack);
        output[*outputLength + 1] = ' ';
        *outputLength += 2;
    }
    pop(specialCharsStack);
    return true;
}

bool tryToHandleOperation(int* outputLength, Stack* specialCharsStack, char* output, char currentChar)
{
    /* if token is an operation then:
    * 1) if op have bigger priority than op on the top of the stack
    * add it to the stack
    * 2) else add top of the stack to output and repeat */
    int currentOperationPriority = getPriority(currentChar);
    while ((peek(specialCharsStack) != '(') &&
           (currentOperationPriority <= getPriority(peek(specialCharsStack))))
    {
        if (isEmpty(specialCharsStack))
        {
            printf("Input is incorrect!");
            deleteStack(specialCharsStack);
            free(output);
            return false;
        }
        output[*outputLength] = pop(specialCharsStack);
        output[*outputLength + 1] = ' ';
        *outputLength += 2;
    }
    append(currentChar, specialCharsStack);
    return true;
}

char* convertToReversePolishNotation(char* input)
{
    int outputLength = 0;
    int inputLength = strlen(input);
    char* output = createString(2 * inputLength + 1);
    Stack* specialCharsStack = createStack();
    for (int currentChar = 0; input[currentChar] != '\0'; currentChar++)
    {
        // skipping all the spaces
        if (input[currentChar] == ' ')
        {
            continue;
        }

        if (!isInputCorrect(input[currentChar]))
        {
            printf("Input is incorrect (non correct characters)");
            deleteStack(specialCharsStack);
            free(output);
            return NULL;
        }

        if (isdigit(input[currentChar]))
        {
            // if next token is a digit then send it to the output
            output[outputLength] = input[currentChar];

            // if next token is not a digit then add a space
            if (currentChar + 1 == inputLength || !isdigit(input[currentChar + 1]))
            {
                outputLength++;
                output[outputLength] = ' ';
            }
            outputLength++;
        }
        else if (input[currentChar] == '(')
        {
            // if token is the open bracket then add it to the stack
            append('(', specialCharsStack);
        }
        else if (input[currentChar] == ')')
        {
            if (!tryToHandleCloseBracket(&outputLength, specialCharsStack, output))
            {
                return NULL;
            }
        }
        else
        {
            if (!tryToHandleOperation(&outputLength, specialCharsStack, output, input[currentChar]))
            {
                return NULL;
            }
        }
    }
    // add all left chars in the stack to the output
    while (!isEmpty(specialCharsStack))
    {
        output[outputLength] = pop(specialCharsStack);
        output[outputLength + 1] = ' ';
        outputLength += 2;
    }
    output[outputLength] = '\0';
    deleteStack(specialCharsStack);
    return output;
}