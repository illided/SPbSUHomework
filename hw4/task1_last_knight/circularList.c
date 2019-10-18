#include "circularList.h"
#include <stdlib.h>

struct circularListElement
{
    int value;
    circularListElement* next;
};

struct circularList
{
    circularListElement* root;
    int size;
};

circularList* createCircularList()
{
    circularList* newList = malloc(sizeof(circularList));
    newList->size = 0;
    newList->root = NULL;
}

void append(int value, circularList* list)
{
    circularListElement* newElement = malloc(sizeof(circularListElement));
    newElement->value = value;
    if (list->size == 0)
    {
        list->root = newElement;
    }
    else
    {
        circularListElement* pointer = list->root;
        while (pointer->next != list->root)
        {
            pointer = pointer->next;
        }
        pointer->next = newElement;
    }
    list->size++;
    newElement->next = list->root;
}

void setRootToNext(circularList* list)
{
    list->root = list->root->next;
}

int getValueFromRoot(circularList* list)
{
    return list->root->value;
}

int size(circularList* list)
{
    return list->size;
}

void delete(circularList* list)
{
    if (list->size == 0)
    {
        return;
    }
    circularListElement* pointer = list->root;
    while (pointer->next != list->root)
    {
        pointer = pointer->next;
    }
    list->root = list->root->next;
    free(pointer->next);
    pointer->next = list->root;
    list->size--;
}

