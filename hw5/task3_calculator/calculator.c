#include "stack.h"
#include "simpleArrays.h"
#include "string.h"
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
    return isOperation(input) || isdigit(input) || input == '(' || input == ')';
}

bool handleCloseBracketWhileConverting(int* outputLength, StackOfChar* specialCharsStack, char* output)
{
    /* if this is the close bracket then
    * keep adding to the output every operation from the stack
    * until we get a open bracket (deleting open bracket) */
    while (peekChar(specialCharsStack) != '(')
    {
        if (stackOfCharIsEmpty(specialCharsStack))
        {
            printf("Input is incorrect!");
            deleteStackOfChar(specialCharsStack);
            free(output);
            return false;
        }
        output[*outputLength] = popChar(specialCharsStack);
        output[*outputLength + 1] = ' ';
        *outputLength += 2;
    }
    popChar(specialCharsStack);
    return true;
}

bool handleOperationWhileConverting(int* outputLength, StackOfChar* specialCharsStack, char* output, char currentChar)
{
    /* if token is an operation then:
    * 1) if op have bigger priority than op on the top of the stack add it to the stack
    * 2) else add top of the stack to output and repeat */
    int currentOperationPriority = getPriority(currentChar);
    while ((peekChar(specialCharsStack) != '(') &&
           (currentOperationPriority <= getPriority(peekChar(specialCharsStack))))
    {
        if (stackOfCharIsEmpty(specialCharsStack))
        {
            printf("Input is incorrect!");
            deleteStackOfChar(specialCharsStack);
            free(output);
            return false;
        }
        output[*outputLength] = popChar(specialCharsStack);
        output[*outputLength + 1] = ' ';
        *outputLength += 2;
    }
    appendChar(currentChar, specialCharsStack);
    return true;
}

char* convertToReversePolishNotation(char* input)
{
    int outputLength = 0;
    int inputLength = strlen(input);
    char* output = createString(2 * inputLength + 1);
    StackOfChar* specialCharsStack = createStackOfChar();
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
            deleteStackOfChar(specialCharsStack);
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
            appendChar('(', specialCharsStack);
        }
        else if (input[currentChar] == ')')
        {
            if (!handleCloseBracketWhileConverting(&outputLength, specialCharsStack, output))
            {
                return NULL;
            }
        }
        else
        {
            if (!handleOperationWhileConverting(&outputLength, specialCharsStack, output, input[currentChar]))
            {
                return NULL;
            }
        }
    }
    // add all left chars in the stack to the output
    while (!stackOfCharIsEmpty(specialCharsStack))
    {
        output[outputLength] = popChar(specialCharsStack);
        output[outputLength + 1] = ' ';
        outputLength += 2;
    }
    output[outputLength] = '\0';
    deleteStackOfChar(specialCharsStack);
    return output;
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

void handleOperationWhileCalculating(char input, StackOfDouble* numbers, bool* inputIsCorrect)
{
    if (size(numbers) < 2)
    {
        printf("Incorrect input\n");
        deleteStackOfDouble(numbers);
        *inputIsCorrect = false;
    }
    double secondNumber = popDouble(numbers);
    double firstNumber = popDouble(numbers);
    if ((secondNumber == 0) && (input == '/'))
    {
        printf("Incorrect input (tried to divide by zero)\n");
        deleteStackOfDouble(numbers);
        *inputIsCorrect = false;
    }
    appendDouble(getOperationResult(input, firstNumber, secondNumber), numbers);
}

double handleAnswer(bool bufferIsEmpty, double numberBuffer, StackOfDouble* numbers, bool* inputIsCorrect)
{
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
        *inputIsCorrect = false;
    }
    deleteStackOfDouble(numbers);
    *inputIsCorrect = true;
    return result;
}

double getResultOfExpression(const char* input, bool* inputIsCorrect)
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
            handleOperationWhileCalculating(input[charPos], numbers, inputIsCorrect);
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
            *inputIsCorrect = false;
            return 0;
        }
    }
    return handleAnswer(bufferIsEmpty, numberBuffer, numbers, inputIsCorrect);
}

double calculate(char* input, bool* inputIsCorrect)
{
    double result = 0;
    char* inputInReversePolishNotation = convertToReversePolishNotation(input);
    if (inputInReversePolishNotation != NULL)
    {
        result = getResultOfExpression(inputInReversePolishNotation, inputIsCorrect);
    }
    free(inputInReversePolishNotation);
    return result;
}