#pragma once

#include <stdbool.h>

struct StackOfChar;
struct StackOfCharElement;

typedef struct StackOfChar StackOfChar;
typedef struct StackOfCharElement StackOfCharElement;

StackOfChar* createStackOfChar();
void appendChar(char value, StackOfChar* stack);
char popChar(StackOfChar* stack);
char peekChar(StackOfChar* stack);
bool stackOfCharIsEmpty(StackOfChar* stack);
void deleteStackOfChar(StackOfChar* stack);
