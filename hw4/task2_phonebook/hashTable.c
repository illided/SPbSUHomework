#include "hashTable.h"
#include "stringByStudent.h"
#include <stdlib.h>
#include <stdio.h>

struct HashLine
{
    String *keyString;
    String *contentString;
    int insertTries;
    bool isDeleted;
};

typedef struct HashLine HashLine;

HashLine *createHashLine(String *keyString, String *contentString)
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
    hashLine->contentString = cloneString(contentString);
    hashLine->insertTries = 0;
    hashLine->isDeleted = false;
    return hashLine;
}

void deleteHashLine(HashLine *hashLine)
{
    if (hashLine != NULL)
    {
        deleteString(hashLine->keyString);
        deleteString(hashLine->contentString);
        free(hashLine);
    }
}

HashLine *copyHashLine(HashLine *hashLine)
{
    if (hashLine == NULL)
    {
        return NULL;
    }
    HashLine *newHashLine = createHashLine(hashLine->keyString, hashLine->contentString);
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
        int tries = 0;
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
    hashTable->arrayOfLines = newArray;
    hashTable->size = newSize;
}

bool isInTable(String *keyString, HashTable *hashTable)
{
    return searchForLine(keyString, hashTable) != NULL;
}

void pushToHashTable(String *keyString, String *contentString, HashTable *hashTable)
{
    /* creates a hashline and adds it to the table, then updates the
     * load factor and extends the table if necessary. Note that
     * the content string may be NULL and the key must exist */

    if ((keyString == NULL) || (hashTable == NULL) || (isInTable(keyString, hashTable)))
    {
        return;
    }
    HashLine *newHashLine = createHashLine(keyString, contentString);
    pushHashLine(newHashLine, hashTable->arrayOfLines, hashTable->size);
    hashTable->loaded++;
    double loadFactor = (double) (hashTable->loaded) / (double) (hashTable->size);
    if (loadFactor > hashTable->maxLoadFactor)
    {
        expand(hashTable);
    }
}

String *getFromHashTable(String *keyString, HashTable *hashTable)
{
    if ((hashTable == NULL) || (keyString == NULL))
    {
        return NULL;
    }
    HashLine *hashLine = searchForLine(keyString, hashTable);
    if (hashLine != NULL)
    {
        return cloneString(hashLine->contentString);
    }
    return NULL;
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

void changeLineInHashTable(String *keyString, String *newContentString, HashTable *hashTable)
{
    if ((keyString == NULL) || (hashTable == NULL))
    {
        return;
    }
    HashLine *oldLine = searchForLine(keyString, hashTable);
    deleteString(oldLine->contentString);
    oldLine->contentString = cloneString(newContentString);
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
            fprintf(file, "\n");
            printStringToFile(hashTable->arrayOfLines[i]->contentString, file);
            fprintf(file, "\n");
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
        printf("Line with the biggest collision factor:\n");
        printStringToFile(maxCollisionLine->keyString, stdout);
        printf(" ");
        printStringToFile(maxCollisionLine->contentString, stdout);
        printf(" (collision factor: %d)\n", maxCollision);
    }
}