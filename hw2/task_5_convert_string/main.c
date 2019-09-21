#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 1000

void countNumOfChar(char input[], int charArray[])
{
    for (int i = 0; i < strlen(input); i++)
    {
        charArray[input[i]]++;
    }
}

bool isConvertable(char convertFrom[], char convertTo[])
{
    int charArray1[MAXSIZE] = {0};
    int charArray2[MAXSIZE] = {0};

    countNumOfChar(convertFrom, charArray1);
    countNumOfChar(convertTo, charArray2);

    for (int i = 0; i < MAXSIZE; i++)
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
    char convertFrom[MAXSIZE] = {' '};
    char convertTo[MAXSIZE] = {' '};

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