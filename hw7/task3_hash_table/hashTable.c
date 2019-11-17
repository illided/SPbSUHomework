#include "hashTable.h"
#include "stringByStudent.h"
#include <stdlib.h>
#include <stdio.h>

struct HashLine
{
    String* keyString;
    String* contentString;
    int insertTries;
    bool isDeleted;
};
typedef struct HashLine HashLine;

HashLine* createHashLine(String* keyString, String* contentString)
{
    HashLine* hashLine = malloc(sizeof(HashLine));
    hashLine->keyString = cloneString(keyString);
    hashLine->contentString = cloneString(contentString);
    hashLine->insertTries = 0;
    hashLine->isDeleted = false;
}

void deleteHashLine(HashLine* hashLine)
{
    deleteString(hashLine->keyString);
    deleteString(hashLine->contentString);
    free(hashLine);
}

HashLine* copyHashLine(HashLine* hashLine)
{
    HashLine* newHashLine = createHashLine(hashLine->keyString, hashLine->contentString);
    return newHashLine;
}

bool isExist(HashLine* hashLine)
{
    return (hashLine != NULL) && (!hashLine->isDeleted);
}

struct HashTable
{
    HashLine** arrayOfLines;
    int size;
    int loaded;
    double maxLoadFactor;
};

HashTable* createHashTable(int startSize)
{
    if (startSize <= 0)
    {
        return NULL;
    }
    HashTable* hashTable = malloc(sizeof(HashTable));
    hashTable->size = startSize;
    hashTable->loaded = 0;
    hashTable->maxLoadFactor = 0.70;
    hashTable->arrayOfLines = malloc(sizeof(HashLine*) * startSize);
    for (int i = 0; i < startSize; i++)
    {
        hashTable->arrayOfLines[i] = NULL;
    }
    return hashTable;
}

void deleteHashTable(HashTable* hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
    {
        if (hashTable->arrayOfLines[i] != NULL)
        {
            deleteHashLine(hashTable->arrayOfLines[i]);
        }
    }
    free(hashTable);
}

int getHash(String* keyString, int base)
{
    char* array = importStringToArray(keyString);
    int output = 0;
    for (int currentChar = 0; array[currentChar] != '\0'; currentChar++)
    {
        output = (output + array[currentChar]) % base;
    }
    free(array);
    return output;
}

HashLine* searchForLine(String* keyString, HashTable* hashTable)
{
    int hash = getHash(keyString, hashTable->size);
    int tries = 0;
    while (isExist(hashTable->arrayOfLines[hash]))
    {
        if (areEqual(hashTable->arrayOfLines[hash]->keyString, keyString))
        {
            return hashTable->arrayOfLines[hash];
        }
        tries++;
        hash = (hash + tries * tries) % (hashTable->size);
    }
    return NULL;
}

void pushHashLine(HashLine* hashLine, HashLine** arrayOfLines, int base)
{
    int hash = getHash(hashLine->keyString, base);
    int tries = 0;
    while (isExist(arrayOfLines[hash]))
    {
        if (areEqual(arrayOfLines[hash]->keyString, hashLine->keyString))
        {
            return;
        }
        tries++;
        hash = (hash + tries * tries) % (base);
    }
    if (arrayOfLines[hash] != NULL)
    {
        deleteHashLine(arrayOfLines[hash]);
    }
    hashLine->insertTries = tries;
    arrayOfLines[hash] = hashLine;
}

void expand(HashTable* hashTable)
{
    int newSize = hashTable->size * 2;
    HashLine** newArray = malloc(sizeof(HashLine*) * newSize);
    for (int i = 0; i < newSize; i++)
    {
        newArray[i] = NULL;
    }
    for (int i = 0; i < hashTable->size; i++)
    {
        int tries = 0;
        if (isExist(hashTable->arrayOfLines[i]))
        {
            HashLine* newHashLine = copyHashLine(hashTable->arrayOfLines[i]);
            pushHashLine(newHashLine, newArray, newSize);
        }
    }
    for (int i = 0; i < hashTable->size; i++)
    {
        if (hashTable->arrayOfLines[i] != NULL)
        {
            deleteHashLine(hashTable->arrayOfLines[i]);
        }
    }
    hashTable->arrayOfLines = newArray;
    hashTable->size = newSize;
}

bool isInTable(String* keyString, HashTable* hashTable)
{
    return searchForLine(keyString, hashTable) != NULL;
}

void pushToHashTable(String* keyString, String* contentString, HashTable* hashTable)
{
    if (isInTable(keyString, hashTable))
    {
        return;
    }
    HashLine* newHashLine = createHashLine(keyString, contentString);
    pushHashLine(newHashLine, hashTable->arrayOfLines, hashTable->size);
    hashTable->loaded++;
    double loadFactor = (double)(hashTable->loaded) / (double)(hashTable->size);
    if (loadFactor > hashTable->maxLoadFactor)
    {
        expand(hashTable);
    }
}

void printHashTableContent(HashTable* hashTable)
{
    char* keyArray = NULL;
    char* contentArray = NULL;
    for (int i = 0; i < hashTable->size; i++)
    {
        if (isExist(hashTable->arrayOfLines[i]))
        {
            keyArray = importStringToArray(hashTable->arrayOfLines[i]->keyString);
            printf("%s ", keyArray);
            free(keyArray);
            contentArray = importStringToArray(hashTable->arrayOfLines[i]->contentString);
            printf("%s\n", contentArray);
            free(contentArray);
        }
    }
}

void printHashTableInfo(HashTable* hashTable)
{
    HashLine* maxCollisionLine = NULL;
    int maxCollision = 0;
    int collisions = 0;
    for (int i = 0; i < hashTable->size; i++)
    {
        if (isExist(hashTable->arrayOfLines[i]))
        {
            if (hashTable->arrayOfLines[i]->insertTries > maxCollision)
            {
                maxCollisionLine = hashTable->arrayOfLines[i];
                maxCollision = maxCollisionLine->insertTries;
            }
            collisions += hashTable->arrayOfLines[i]->insertTries;
        }
    }
    printf("Table size: %d\n", hashTable->size);
    printf("Lines available: %d\n", hashTable->size - hashTable->loaded);
    printf("Load factor: %f\n", (double)(hashTable->loaded) / (double)(hashTable->size));
    printf("Average collision factor: %f\n", (double)(collisions) / (double)(hashTable->loaded));
    if (maxCollisionLine != NULL)
    {
        char* tempKeyArray = importStringToArray(maxCollisionLine->keyString);
        char* tempContentArray = importStringToArray(maxCollisionLine->contentString);
        printf("Line with the biggest collision factor: %s %s (collision factor: %d)\n",
                tempKeyArray, tempContentArray, maxCollisionLine->insertTries);
        free(tempContentArray);
        free(tempKeyArray);
    }
}

