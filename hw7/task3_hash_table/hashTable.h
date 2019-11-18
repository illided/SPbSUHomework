#ifndef HASHTABLE_H
#define HASHTABLE_H

#include"stringByStudent.h"

struct HashTable;
typedef struct HashTable HashTable;

HashTable* createHashTable(int startSize);
void deleteHashTable(HashTable* hashTable);
bool isInTable(String* keyString, HashTable* hashTable);
void pushToHashTable(String* keyString, String* contentString, HashTable* hashTable);
String* getFromHashTable(String* keyString, HashTable* hashTable);
void deleteFromHashTable(String* keyString, HashTable* hashTable);
bool setMaxLoadFactor(double newMaxLoadFactor, HashTable* hashTable);
void printHashTableContent(HashTable* hashTable);
void printHashTableInfo(HashTable* hashTable);
String** dumpHashTable(HashTable* hashTable);


#endif
