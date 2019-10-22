#ifndef STACK_H
#define STACK_H

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

struct StackOfInt;
struct StackOfIntElement;

typedef struct StackOfInt StackOfInt;
typedef struct StackOfIntElement StackOfIntElement;

StackOfInt* createStackOfInt();
void appendInt(int value, StackOfInt* stack);
int popInt(StackOfInt* stack);
int peekInt(StackOfInt* stack);
int size(StackOfInt* stack);
bool stackOfIntIsEmpty(StackOfInt* stack);

#endif
