#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "simpleArrays.h"

const int maxSize = 1000;

void countNumOfChar(unsigned char input[], int charArray[])
{
    unsigned int inputLength = strlen(input);
    for (unsigned int i = 0; i < inputLength; i++)
    {
        charArray[input[i]]++;
    }
}

bool isConvertable(unsigned char convertFrom[], unsigned char convertTo[])
{
    int *charArray1 = createArrayOfInt(maxSize);
    int *charArray2 = createArrayOfInt(maxSize);

    countNumOfChar(convertFrom, charArray1);
    countNumOfChar(convertTo, charArray2);

    for (int i = 0; i < maxSize; i++)
    {
        if (charArray1[i] != charArray2[i])
        {
            return false;
        }
    }

    free(charArray1);
    free(charArray2);
    return true;
}

int main()
{
    unsigned char *convertFrom = createUnsignedString(maxSize);
    unsigned char *convertTo = createUnsignedString(maxSize);

    printf("Enter the first string:\n");
    scanf("%s", convertFrom);
    printf("Enter the second string:\n");
    scanf(" %s", convertTo);

    if ((strlen(convertFrom) == strlen(convertTo)) && (isConvertable(convertFrom, convertTo)))
    {
        printf("Can be converted");
    }
    else
    {
        printf("Can not be converted");
    }

    free(convertFrom);
    free(convertTo);
    return 0;
}