#include "stackOfChar.h"
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
    return newStack;
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

void recursiveDeleteOfChar(StackOfCharElement* stackElement)
{
    if (stackElement->next != NULL)
    {
        recursiveDeleteOfChar(stackElement->next);
    }
    free(stackElement);
}

void deleteStackOfChar(StackOfChar* stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->head != NULL)
    {
        recursiveDeleteOfChar(stack->head);
    }
    free(stack);
}
