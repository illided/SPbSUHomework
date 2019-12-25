#pragma once

#include <stdbool.h>

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
