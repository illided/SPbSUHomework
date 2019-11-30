#include <stdlib.h>
#include <stdio.h>

char *createString(int stringLength)
{
    char *localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

unsigned char *createUnsignedString(int stringLength)
{
    unsigned char *localString = malloc(sizeof(unsigned char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

int *createArrayOfInt(int arrayLength)
{
    int *arrayOfInt = malloc(sizeof(int) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        arrayOfInt[i] = 0;
    }
    return arrayOfInt;
}

void scanArrayOfInt(int begin, int end, int *arrayOfInt)
{
    for (int i = begin; i <= end; i++)
    {
        scanf("%d", &arrayOfInt[i]);
    }
}

void printArrayOfInt(int begin, int end, int *arrayOfInt)
{
    for (int i = begin; i <= end; i++)
    {
        printf("%d", arrayOfInt[i]);
    }
}