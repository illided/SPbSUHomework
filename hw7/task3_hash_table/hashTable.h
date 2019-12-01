#pragma once

#include"stringByStudent.h"

struct HashTable;
typedef struct HashTable HashTable;

HashTable* createHashTable(int startSize);
void deleteHashTable(HashTable* hashTable);
bool isInTable(String* keyString, HashTable* hashTable);
void pushToHashTable(String* keyString, int content, HashTable* hashTable);
int getFromHashTable(String* keyString, HashTable* hashTable);
void deleteFromHashTable(String* keyString, HashTable* hashTable);
void changeLineInHashTable(String* keyString, int newContent, HashTable* hashTable);
bool setMaxLoadFactor(double newMaxLoadFactor, HashTable* hashTable);
void printHashTableContentToFile(HashTable* hashTable, FILE* file);
void printHashTableInfo(HashTable* hashTable);
