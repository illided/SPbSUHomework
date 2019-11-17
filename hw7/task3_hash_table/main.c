#include <stdio.h>
#include "hashTable.h"
#include "stringByStudent.h"

int main() {
    HashTable* hashTable = createHashTable(2);
    char ded[2] = {'a', '\0'};
    String* test = getStringFromArray(ded);
    pushToHashTable(test, test, hashTable);
    ded[0] = 'b';
    deleteString(test);
    test = getStringFromArray(ded);
    pushToHashTable(test, test, hashTable);
    ded[0] = 'c';
    deleteString(test);
    test = getStringFromArray(ded);
    pushToHashTable(test, test, hashTable);
    ded[0] = 's';
    deleteString(test);
    test = getStringFromArray(ded);
    pushToHashTable(test, test, hashTable);
    ded[0] = 'x';
    deleteString(test);
    test = getStringFromArray(ded);
    pushToHashTable(test, test, hashTable);
    deleteString(test);
    printHashTableInfo(hashTable);
    printHashTableContent(hashTable);
    deleteHashTable(hashTable);
    return 0;
}