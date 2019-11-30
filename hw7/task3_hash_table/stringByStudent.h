#ifndef STRINGBYSTUDENT_H
#define STRINGBYSTUDENT_H

#include <stdbool.h>
#include <stdio.h>

struct String;

typedef struct String String;

String* createEmptyString();
void deleteString(String* string);
int stringLength(String* string);
String* getStringFromArray(char* array);
char* importStringToArray(String* string);
void concatenateStrings(String* baseString, String* endSubString);
String* cloneString(String* string);
bool areEqual(String* firstString, String* secondString);
void readToStringFromFile(String* string, FILE* file);
String* getSubString(String* string, int start, int end);
bool isEmptyString(String* string);
void rewriteString(String* string, char* array);
void printStringToFile(String* string, FILE* file);
bool isReadableEmpty(String* string);

#endif