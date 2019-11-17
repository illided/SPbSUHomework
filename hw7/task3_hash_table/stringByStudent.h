#ifndef STRINGBYSTUDENT_H
#define STRINGBYSTUDENT_H

#include <stdbool.h>

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
void readToString(String* string);
String* getSubString(String* string, int start, int end);
bool isEmptyString(String* string);

#endif
