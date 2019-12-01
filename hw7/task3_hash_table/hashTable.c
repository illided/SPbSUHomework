#include "hashTable.h"
#include "stringByStudent.h"
#include <stdlib.h>
#include <stdio.h>

struct HashLine
{
    String *keyString;
    int content;
    int insertTries;
    bool isDeleted;
};

typedef struct HashLine HashLine;

HashLine *createHashLine(String *keyString, int content)
{
    /* This function creates hashline
     * and as you can see hashline can have NULL as a
     * content but can't have NULL as a key */

    if (keyString == NULL)
    {
        return NULL;
    }
    HashLine *hashLine = malloc(sizeof(HashLine));
    hashLine->keyString = cloneString(keyString);
    hashLine->content = content;
    hashLine->insertTries = 0;
    hashLine->isDeleted = false;
    return hashLine;
}

void deleteHashLine(HashLine *hashLine)
{
    if (hashLine != NULL)
    {
        deleteString(hashLine->keyString);
        free(hashLine);
    }
}

HashLine *copyHashLine(HashLine *hashLine)
{
    if (hashLine == NULL)
    {
        return NULL;
    }
    HashLine *newHashLine = createHashLine(hashLine->keyString, hashLine->content);
    return newHashLine;
}

bool isExist(HashLine *hashLine)
{
    return (hashLine != NULL) && (!hashLine->isDeleted);
}

struct HashTable
{
    HashLine **arrayOfLines;
    int size;
    int loaded;
    double maxLoadFactor;
};

HashTable *createHashTable(int startSize)
{
    if (startSize <= 0)
    {
        return NULL;
    }
    HashTable *hashTable = malloc(sizeof(HashTable));
    hashTable->size = startSize;
    hashTable->loaded = 0;
    hashTable->maxLoadFactor = 0.70;
    hashTable->arrayOfLines = malloc(sizeof(HashLine *) * startSize);
    for (int i = 0; i < startSize; i++)
    {
        hashTable->arrayOfLines[i] = NULL;
    }
    return hashTable;
}

void deleteHashTable(HashTable *hashTable)
{
    if (hashTable == NULL)
    {
        return;
    }
    for (int i = 0; i < hashTable->size; i++)
    {
        if (hashTable->arrayOfLines[i] != NULL)
        {
            deleteHashLine(hashTable->arrayOfLines[i]);
        }
    }
    free(hashTable->arrayOfLines);
    free(hashTable);
}

bool setMaxLoadFactor(double newMaxLoadFactor, HashTable *hashTable)
{
    if ((newMaxLoadFactor <= 0.90) && (hashTable != NULL))
    {
        hashTable->maxLoadFactor = newMaxLoadFactor;
        return true;
    }
    return false;
}

int getHash(String *keyString, int base)
{
    if ((keyString == NULL) || (base < 1))
    {
        return 0;
    }
    char *array = importStringToArray(keyString);
    int output = 0;
    for (int currentChar = 0; array[currentChar] != '\0'; currentChar++)
    {
        output = (output + (currentChar + 1) * array[currentChar]) % base;
    }
    free(array);
    return output;
}

HashLine *searchForLine(String *keyString, HashTable *hashTable)
{
    if ((hashTable == NULL) || (keyString == NULL))
    {
        return NULL;
    }
    int hash = getHash(keyString, hashTable->size);
    int tries = 0;
    while (hashTable->arrayOfLines[hash] != NULL)
    {
        if (!hashTable->arrayOfLines[hash]->isDeleted &&
            (areEqual(hashTable->arrayOfLines[hash]->keyString, keyString)))
        {
            return hashTable->arrayOfLines[hash];
        }
        tries++;
        hash = (hash + tries * tries) % (hashTable->size);
    }
    return NULL;
}

void pushHashLine(HashLine *hashLine, HashLine **arrayOfLines, int base)
{
    if ((hashLine == NULL) || (arrayOfLines == NULL))
    {
        return;
    }
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

void expand(HashTable *hashTable)
{
    if (hashTable == NULL)
    {
        return;
    }
    int newSize = hashTable->size * 2;
    HashLine **newArray = malloc(sizeof(HashLine *) * newSize);
    for (int i = 0; i < newSize; i++)
    {
        newArray[i] = NULL;
    }
    for (int i = 0; i < hashTable->size; i++)
    {
        if (isExist(hashTable->arrayOfLines[i]))
        {
            HashLine *newHashLine = copyHashLine(hashTable->arrayOfLines[i]);
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
    free(hashTable->arrayOfLines);
    hashTable->arrayOfLines = newArray;
    hashTable->size = newSize;
}

bool isInTable(String *keyString, HashTable *hashTable)
{
    return searchForLine(keyString, hashTable) != NULL;
}

void pushToHashTable(String *keyString, int content, HashTable *hashTable)
{
    /* creates a hashline and adds it to the table, then updates the
     * load factor and extends the table if necessary. Note that
     * the content string may be NULL and the key must exist */

    if ((keyString == NULL) || (hashTable == NULL) || (isInTable(keyString, hashTable)))
    {
        return;
    }
    HashLine *newHashLine = createHashLine(keyString, content);
    pushHashLine(newHashLine, hashTable->arrayOfLines, hashTable->size);
    hashTable->loaded++;
    double loadFactor = (double) (hashTable->loaded) / (double) (hashTable->size);
    if (loadFactor > hashTable->maxLoadFactor)
    {
        expand(hashTable);
    }
}

int getFromHashTable(String *keyString, HashTable *hashTable)
{
    if ((hashTable == NULL) || (keyString == NULL))
    {
        return 0;
    }
    HashLine *hashLine = searchForLine(keyString, hashTable);
    if (hashLine != NULL)
    {
        return hashLine->content;
    }
    return 0;
}

void deleteFromHashTable(String *keyString, HashTable *hashTable)
{
    if ((keyString == NULL) || (hashTable == NULL))
    {
        return;
    }
    HashLine *hashLine = searchForLine(keyString, hashTable);
    if (hashLine != NULL)
    {
        hashLine->isDeleted = true;
        hashTable->loaded--;
    }
}

void changeLineInHashTable(String *keyString, int newContent, HashTable *hashTable)
{
    if ((keyString == NULL) || (hashTable == NULL))
    {
        return;
    }
    HashLine *oldLine = searchForLine(keyString, hashTable);
    oldLine->content = newContent;
}

void printHashTableContentToFile(HashTable *hashTable, FILE *file)
{
    if (hashTable == NULL)
    {
        printf("Hashtable doesn't exist");
        return;
    }
    if (file == NULL)
    {
        return;
    }
    for (int i = 0; i < hashTable->size; i++)
    {
        if (isExist(hashTable->arrayOfLines[i]))
        {
            printStringToFile(hashTable->arrayOfLines[i]->keyString, file);
            fprintf(file, "\n%d\n", hashTable->arrayOfLines[i]->content);
        }
    }
}

void printHashTableInfo(HashTable *hashTable)
{
    if (hashTable == NULL)
    {
        printf("Hashtable doesn't exist");
        return;
    }
    HashLine *maxCollisionLine = NULL;
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
    printf("Load factor: %f\n", (double) (hashTable->loaded) / (double) (hashTable->size));
    printf("Average collision factor: %f\n", (double) (collisions) / (double) (hashTable->loaded));
    if (maxCollisionLine != NULL)
    {
        printf("Line with the biggest collision factor: ");
        printStringToFile(maxCollisionLine->keyString, stdout);
        printf(" %d", maxCollisionLine->content);
        printf(" (collision factor: %d)\n", maxCollision);
    }
}