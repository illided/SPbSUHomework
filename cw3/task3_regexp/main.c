#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum stateList
{
    initial,
    firstDigitInYear,
    secondDigitInYear,
    type,
    groupNumber,
    firstDigitInGroupNum,
    dash,
    firstM,
    secondM,
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
            if (isdigit(input))
            {
                return firstDigitInYear;
            }
            return somethingWrong;
        }
        case firstDigitInYear:
        {
            if (isdigit(input))
            {
                return secondDigitInYear;
            }
            return somethingWrong;
        }
        case secondDigitInYear:
        {
            if (input == 'B' || input == 'M' || input == 'S')
            {
                return type;
            }
            return somethingWrong;
        }
        case type:
        {
            if (input == '1')
            {
                return firstDigitInGroupNum;
            }
            if (input - '0' <= 9 && input - '0' >= 2)
            {
                return groupNumber;
            }
            return somethingWrong;
        }
        case firstDigitInGroupNum:
        {
            if (input == '0')
            {
                return groupNumber;
            }
            return somethingWrong;
        }
        case groupNumber:
        {
            if (input == '-')
            {
                return dash;
            }
        }
        case dash:
        {
            if (input == 'm')
            {
                return firstM;
            }
            return somethingWrong;
        }
        case firstM:
        {
            if (input == 'm')
            {
                return secondM;
            }
            return somethingWrong;
        }
        case secondM:
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
    if (state != secondM)
    {
        return strlen(input) - 1;
    }
    return -1;
}

int main()
{

    printf("Enter group number:\n");
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
        printf("Input is incorrect\n");
    }
    free(input);
    return 0;
}
