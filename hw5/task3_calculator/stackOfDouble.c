#include "stackOfDouble.h"
#include <stdlib.h>

struct StackOfDoubleElement
{
    double value;
    StackOfDoubleElement* next;
};

struct StackOfDouble
{
    StackOfDoubleElement* head;
    int size;
};

StackOfDouble* createStackOfDouble()
{
    StackOfDouble* newStack = malloc(sizeof(StackOfDouble));
    newStack->head = NULL;
    newStack->size = 0;
    return newStack;
}

void appendDouble(double value, StackOfDouble* stack)
{
    StackOfDoubleElement* newElement = malloc(sizeof(StackOfDoubleElement));
    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;
    stack->size++;
}

double popDouble(StackOfDouble* stack)
{
    if (stack->head == NULL)
    {
        return 0;
    }
    StackOfDoubleElement* deletedElement = stack->head;
    stack->head = deletedElement->next;
    double value = deletedElement->value;
    free(deletedElement);
    stack->size--;
    return value;
}

bool stackOfDoubleIsEmpty(StackOfDouble* stack)
{
    return stack->head == NULL;
}

double peekDouble(StackOfDouble* stack)
{
    if (stackOfDoubleIsEmpty(stack))
    {
        return '\0';
    }
    return stack->head->value;
}

int size(StackOfDouble* stack)
{
    return stack->size;
}

void recursiveDeleteOfDouble(StackOfDoubleElement* stackElement)
{
    if (stackElement->next != NULL)
    {
        recursiveDeleteOfDouble(stackElement->next);
    }
    free(stackElement);
}

void deleteStackOfDouble(StackOfDouble* stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->head != NULL)
    {
        recursiveDeleteOfDouble(stack->head);
    }
    free(stack);
}
