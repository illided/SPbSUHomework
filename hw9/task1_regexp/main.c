#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *createString(int stringLength)
{
    char *localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

char *getString()
{
    int maxSize = 5;
    int stringLength = 0;
    char *output = createString(maxSize);
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

int getState(int state, char input)
{
    switch (state)
    {
        case 1:
            if ((input == '+') || (input == '-'))
            {
                return 2;
            }
            if (isdigit(input))
            {
                return 3;
            }
        case 2:
            if (isdigit(input))
            {
                return  3;
            }
        case 3:
            if (input == '.')
            {
                return  4;
            }
            if (isdigit(input))
            {
                return 3;
            }
            if (input == 'E' || input == 'e')
            {
                return 6;
            }
        case 4:
            if (isdigit(input))
            {
                return  5;
            }
        case 5:
            if (isdigit(input))
            {
                return 5;
            }
            if (input == 'E' || input == 'e')
            {
                return 6;
            }
        case 6:
            if (input == '+' || input == '-')
            {
                return 7;
            }
            if (isdigit(input))
            {
                return 8;
            }
        case 7:
            if (isdigit(input))
            {
                return 8;
            }
        case 8:
            if (isdigit(input))
            {
                return 8;
            }
        default:
            return -1;
    }
}

int match(char* input)
{
    int state = 1;
    int currentCharPos = 0;
    while (input[currentCharPos] != '\0')
    {
        state = getState(state, input[currentCharPos]);
        if (state == -1)
        {
            return currentCharPos;
        }
        currentCharPos++;
    }
    if (state != 3 && state != 5 && state != 8)
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
