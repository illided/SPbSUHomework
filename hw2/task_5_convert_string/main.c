#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int maxSize = 1000;

void countNumOfChar(unsigned char input[], int charArray[])
{
    for (int i = 0; i < strlen(input); i++)
    {
        charArray[input[i]]++;
    }
}

bool isConvertable(unsigned char convertFrom[], unsigned char convertTo[])
{
    int charArray1[maxSize];
    int charArray2[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        charArray1[i] = 0;
        charArray2[i] = 0;
    }

    countNumOfChar(convertFrom, charArray1);
    countNumOfChar(convertTo, charArray2);

    for (int i = 0; i < maxSize; i++)
    {
        if (charArray1[i] != charArray2[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    unsigned char convertFrom[maxSize];
    unsigned char convertTo[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        convertFrom[i] = ' ';
        convertTo[i] = ' ';
    }

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

    return 0;
}