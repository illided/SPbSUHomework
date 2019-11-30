#include "stack.h"
#include <stdlib.h>

struct StackElement
{
    char value;
    StackElement *next;
};

struct Stack
{
    StackElement *head;
};

Stack *createStack()
{
    Stack *newStack = malloc(sizeof(Stack));
    newStack->head = NULL;
    return newStack;
}

void append(char value, Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    StackElement *newElement = malloc(sizeof(StackElement));
    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;
}

char pop(Stack *stack)
{
    if ((stack == NULL) || (stack->head == NULL))
    {
        return 0;
    }
    StackElement *deletedElement = stack->head;
    stack->head = deletedElement->next;
    char value = deletedElement->value;
    free(deletedElement);
    return value;
}

bool isEmpty(Stack *stack)
{
    return stack->head == NULL;
}

char peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        return '\0';
    }
    return stack->head->value;
}

void recursiveDelete(StackElement *stackElement)
{
    if (stackElement->next != NULL)
    {
        recursiveDelete(stackElement->next);
    }
    free(stackElement);
}

void deleteStack(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->head != NULL)
    {
        recursiveDelete(stack->head);
    }
    free(stack);
}