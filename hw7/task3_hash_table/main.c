#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hashTable.h"
#include "stringByStudent.h"

const int maxSize = 1000;

char* createArray(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

void readWordFromFileToArray(FILE* file, char* oldString, int size)
{
    int length = 0;
    char input = ' ';
    input = fgetc(file);
    while ((input != ' ') && (input != EOF) && (input != '\n'))
    {
        if (size == length)
        {
            return;
        }
        oldString[length] = input;
        length++;
        input = fgetc(file);
    }
    oldString[length] = '\0';
}

void formatArrayOfChar(char* input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if ((input[i] == ',') || (input[i] == '.') || (input[i] == '!') || (input[i] == '?'))
        {
            input[i] = '\0';
            return;
        }
        else
        {
            input[i] = tolower(input[i]);
        }
    }
}

void increment(String* string)
{
    char* array = importStringToArray(string);
    int numRepresentation = strtol(array, NULL, 10);
    numRepresentation++;
    sprintf(array, "%d", numRepresentation);
    rewriteString(string, array);
    free(array);
}

int main()
{
    FILE* text = fopen("file.txt", "r");
    if (text == NULL)
    {
        printf("Something went wrong");
        return -1;
    }

    rewind(text);
    char* input = createArray(maxSize);
    HashTable* hashTable = createHashTable(20);
    String* keyString = createEmptyString();
    String* contentString = createEmptyString();

    while (!feof(text))
    {
        readWordFromFileToArray(text, input, maxSize);
        if (input[0] != '\0')
        {
            formatArrayOfChar(input);
            rewriteString(keyString, input);
            if (!isInTable(keyString, hashTable))
            {
                rewriteString(contentString, "1");
                pushToHashTable(keyString, contentString, hashTable);
            }
            else
            {
                deleteString(contentString);
                contentString = getFromHashTable(keyString, hashTable);
                increment(contentString);
                changeLineInHashTable(keyString, contentString, hashTable);
            }
        }
    }
    printHashTableContent(hashTable);
    printHashTableInfo(hashTable);

    fclose(text);
    deleteHashTable(hashTable);
    deleteString(keyString);
    deleteString(contentString);
    free(input);
    return 0;
}