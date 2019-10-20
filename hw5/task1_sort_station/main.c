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

char* convertRPN(char* input)
{
    int outputLength = 0;
    char *output = createString(2 * strlen(input));
    Stack* specialCharsStack = createStack();
    for (int currentChar = 0; input[currentChar] != '\0'; currentChar++)
    {
        /* skipping all the spaces */
        if (input[currentChar] == ' ')
        {
            continue;
        }

        /* checking if the input is correct
         * (dont contain any other characters
         * than digits or operations)*/
        bool inputIsCorrect = false;
        for (int i = 0; i < numOfOperations; i++)
        {
            if (input[currentChar] == operations[i])
            {
                inputIsCorrect = true;
            }
        }
        inputIsCorrect = inputIsCorrect + isdigit(input[currentChar]) + (input[currentChar] == '(') +
                (input[currentChar] == ')');
        if (!inputIsCorrect)
        {
            printf("Input is incorrect (non correct characters)");
            return NULL;
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
            append('(', specialCharsStack);
        }
        else if (input[currentChar] == ')')
        {
            /* if this is the close bracket then
             * keep adding to the output every operation from the stack
             * until we get a open bracket (deleting open bracket) */
            while (peek(specialCharsStack) != '(')
            {
                if (isEmpty(specialCharsStack))
                {
                    printf("Incorrect input (brackets are not balanced)\n");
                    return NULL;
                }
                output[outputLength] = pop(specialCharsStack);
                output[outputLength + 1] = ' ';
                outputLength += 2;
            }
            pop(specialCharsStack);
        }
        else
        {
            /* if token is an operation then:
             * 1) if op have bigger priority than op on the top of the stack
             * add it to the stack
             * 2) else add top of the stack to output and repeat */
            int currentOperationPriority = getPriority(input[currentChar]);
            while ((peek(specialCharsStack) != '(') &&(currentOperationPriority <= getPriority(peek(specialCharsStack))))
            {
                output[outputLength] = pop(specialCharsStack);
                output[outputLength + 1] = ' ';
                outputLength += 2;
            }
            append(input[currentChar], specialCharsStack);
        }
    }
    /* add all left chars in the stack to the output */
    while (!isEmpty(specialCharsStack))
    {
        output[outputLength] = pop(specialCharsStack);
        output[outputLength + 1] = ' ';
        outputLength += 2;
    }
    output[outputLength] = '\0';
    return output;
}

int main()
{
   printf("Enter the string of numbers and operations:\n");
   char* input = getString();
   printf("String in reverse polish notation:\n%s", convertRPN(input));
   free(input);
   return 0;
}