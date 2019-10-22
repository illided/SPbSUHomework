#include "stack.h"
#include <stdlib.h>

struct StackOfCharElement
{
    char value;
    StackOfCharElement* next;
};

struct StackOfChar
{
    StackOfCharElement* head;
};

StackOfChar* createStackOfChar()
{
    StackOfChar* newStack = malloc(sizeof(StackOfChar));
    newStack->head = NULL;
}

void appendChar(char value, StackOfChar* stack)
{
    StackOfCharElement* newElement = malloc(sizeof(StackOfCharElement));
    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;
}

char popChar(StackOfChar* stack)
{
    if (stack->head == NULL)
    {
        return 0;
    }
    StackOfCharElement* deletedElement = stack->head;
    stack->head = deletedElement->next;
    char value = deletedElement->value;
    free(deletedElement);
    return value;
}

bool stackOfCharIsEmpty(StackOfChar* stack)
{
    return stack->head == NULL;
}

char peekChar(StackOfChar* stack)
{
    if (stackOfCharIsEmpty(stack))
    {
        return '\0';
    }
    return stack->head->value;
}

struct StackOfIntElement
{
    int value;
    StackOfIntElement* next;
};

struct StackOfInt
{
    StackOfIntElement* head;
    int size;
};

StackOfInt* createStackOfInt()
{
    StackOfInt* newStack = malloc(sizeof(StackOfInt));
    newStack->head = NULL;
    newStack->size = 0;
}

void appendInt(int value, StackOfInt* stack)
{
    StackOfIntElement* newElement = malloc(sizeof(StackOfIntElement));
    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;
    stack->size++;
}

int popInt(StackOfInt* stack)
{
    if (stack->head == NULL)
    {
        return 0;
    }
    StackOfIntElement* deletedElement = stack->head;
    stack->head = deletedElement->next;
    int value = deletedElement->value;
    free(deletedElement);
    stack->size--;
    return value;
}

bool stackOfIntIsEmpty(StackOfInt* stack)
{
    return stack->head == NULL;
}

int peekInt(StackOfInt* stack)
{
    if (stackOfIntIsEmpty(stack))
    {
        return '\0';
    }
    return stack->head->value;
}

int size(StackOfInt* stack)
{
    return stack->size;
}
