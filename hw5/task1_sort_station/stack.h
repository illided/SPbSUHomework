#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

struct Stack;
struct StackElement;

typedef struct Stack Stack;
typedef struct StackElement StackElement;

Stack* createStack();
void append(char value, Stack* stack);
char pop(Stack* stack);
char peek(Stack* stack);
bool isEmpty(Stack* stack);
void deleteStack(Stack* stack);

#endif