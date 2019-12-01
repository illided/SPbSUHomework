#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hashTable.h"
#include "stringByStudent.h"

char* createArray(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

void readWordFromFileToArray(FILE* file, char* oldString, int* size)
{
    int length = 0;
    char input = ' ';
    input = fgetc(file);
    while ((input != ' ') && (input != EOF) && (input != '\n'))
    {
        if (*size == length)
        {
            *size *= 2;
            oldString = realloc(oldString, sizeof(int) * (*size));
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

int main()
{
    FILE* text = fopen("file.txt", "r");
    if (text == NULL)
    {
        printf("Something went wrong");
        return -1;
    }

    rewind(text);
    int initialSize = 1000;
    char* input = createArray(initialSize);
    int entries = 0;
    HashTable* hashTable = createHashTable(50);
    String* keyString = createEmptyString();

    while (!feof(text))
    {
        readWordFromFileToArray(text, input, &initialSize);
        if (input[0] != '\0')
        {
            formatArrayOfChar(input);
            rewriteString(keyString, input);
            if (!isInTable(keyString, hashTable))
            {
                pushToHashTable(keyString, 1, hashTable);
            }
            else
            {
                entries = getFromHashTable(keyString, hashTable);
                entries++;
                changeLineInHashTable(keyString, entries, hashTable);
            }
        }
    }
    printHashTableContentToFile(hashTable, stdout);
    printHashTableInfo(hashTable);

    fclose(text);
    deleteHashTable(hashTable);
    deleteString(keyString);
    free(input);
    return 0;
}