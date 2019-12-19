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
void deleteStackOfChar(StackOfChar* stack);

struct StackOfDouble;
struct StackOfDoubleElement;

typedef struct StackOfDouble StackOfDouble;
typedef struct StackOfDoubleElement StackOfDoubleElement;

StackOfDouble* createStackOfDouble();
void appendDouble(double value, StackOfDouble* stack);
double popDouble(StackOfDouble* stack);
double peekDouble(StackOfDouble* stack);
int size(StackOfDouble* stack);
bool stackOfDoubleIsEmpty(StackOfDouble* stack);
void deleteStackOfDouble(StackOfDouble* stack);

#endif
