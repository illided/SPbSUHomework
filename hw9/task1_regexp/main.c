#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum stateList
{
    initial,
    numSign,
    firstDigits,
    dot,
    digitsAfterDot,
    exponent,
    exponentSign,
    exponentDigits,
    somethingWrong
};

char* createString(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

char* getString()
{
    int maxSize = 5;
    int stringLength = 0;
    char* output = createString(maxSize);
    char input = ' ';

    scanf("%c", &input);
    while (input != '\n')
    {
        output[stringLength] = input;
        stringLength++;
        scanf("%c", &input);
        if (stringLength == maxSize)
        {
            maxSize *= 2;
            output = realloc(output, sizeof(char) * maxSize);
        }
    }
    output[stringLength] = '\0';
    return output;
}

int getState(enum stateList state, char input)
{
    switch (state)
    {
        case initial:
        {
            if ((input == '+') || (input == '-'))
            {
                return numSign;
            }
            if (isdigit(input))
            {
                return firstDigits;
            }
            return somethingWrong;
        }
        case numSign:
        {
            if (isdigit(input))
            {
                return firstDigits;
            }
            return somethingWrong;
        }
        case firstDigits:
        {
            if (input == '.')
            {
                return dot;
            }
            if (isdigit(input))
            {
                return firstDigits;
            }
            if (input == 'E' || input == 'e')
            {
                return exponent;
            }
            return somethingWrong;
        }
        case dot:
        {
            if (isdigit(input))
            {
                return digitsAfterDot;
            }
            return somethingWrong;
        }
        case digitsAfterDot:
        {
            if (isdigit(input))
            {
                return digitsAfterDot;
            }
            if (input == 'E' || input == 'e')
            {
                return exponent;
            }
            return somethingWrong;
        }
        case exponent:
        {
            if (input == '+' || input == '-')
            {
                return exponentSign;
            }
            if (isdigit(input))
            {
                return exponentDigits;
            }
            return somethingWrong;
        }
        case exponentSign:
        case exponentDigits:
        {
            if (isdigit(input))
            {
                return exponentDigits;
            }
            return somethingWrong;
        }
        case somethingWrong:
        {
            return somethingWrong;
        }
    }
}

int match(char* input)
{
    enum stateList state = initial;
    int currentCharPos = 0;
    while (input[currentCharPos] != '\0')
    {
        state = getState(state, input[currentCharPos]);
        if (state == somethingWrong)
        {
            return currentCharPos;
        }
        currentCharPos++;
    }
    if (state != firstDigits && state != digitsAfterDot && state != exponentDigits)
    {
        return strlen(input) - 1;
    }
    return -1;
}

int main()
{
    printf("Enter floating point number:\n");
    char* input = getString();
    int mistakePosition = match(input);
    if (mistakePosition == -1)
    {
        printf("Input is correct");
    }
    else
    {
        for (int i = 0; i < mistakePosition; i++)
        {
            printf(" ");
        }
        printf("^\n");
        printf("Input is incorrect");
    }
    free(input);
    return 0;
}
