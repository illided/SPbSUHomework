#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simpleArrays.h"

const int maxSize = 1000;

char* stretch(char* input, int requiredLength)
{
    char* output = createString(requiredLength + 1);
    output[requiredLength] = '\0';
    int inputLength = strlen(input);
    int needToAdd = requiredLength - inputLength;

    int numOfSpaces = 0;
    for (int i = 0; i < inputLength; i++)
    {
        if (input[i] == ' ') {
            numOfSpaces++;
        }
    }

    int extraSpaces = needToAdd % numOfSpaces;
    int baseSpaces = needToAdd / numOfSpaces;
    int outputLength = 0;

    for (int i = 0; i < inputLength; i++)
    {
        output[outputLength] = input[i];
        outputLength++;

        if (input [i] == ' ')
        {
            for (int j = 0; j < baseSpaces; j++)
            {
                outputLength++;
            }

            if (extraSpaces != 0)
            {
                outputLength++;
                extraSpaces--;
            }
        }
    }

    return output;
}

int main() {
    char* input = createString(maxSize);
    int requiredLength = 0;

    printf("Enter the string:\n");
    gets(input);
    printf("Enter the required length:\n");
    scanf("%d", &requiredLength);

    if (strlen(input) > requiredLength)
    {
        printf("Incorrect input!!\n");
        return 0;
    }

    char* stretchedLine = stretch(input, requiredLength);
    printf("Stretched line: \n%s", stretchedLine);
    free(stretchedLine);
    free(input);
    return 0;
}