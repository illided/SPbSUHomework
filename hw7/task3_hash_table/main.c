#include <stdio.h>
#include "hashTable.h"
#include "stringByStudent.h"

int main() {
    HashTable* hashTable = createHashTable(10);
    char ded[3] = {'a', '}', '\0'};
    String* test = getStringFromArray(ded);
    pushToHashTable(test, test, hashTable);
    for (int i = 1; i < 30; i++)
    {
        ded[0] = 'a' + i;
        ded[1] = 'z' - i;
        deleteString(test);
        test = getStringFromArray(ded);
        pushToHashTable(test, test, hashTable);
    }
    printHashTableContent(hashTable);
    printHashTableInfo(hashTable);
    deleteString(test);
    deleteHashTable(hashTable);
    return 0;
}