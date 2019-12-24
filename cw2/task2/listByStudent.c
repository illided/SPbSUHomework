#include "listByStudent.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct ListElement
{
    int value;
    struct ListElement* nextElement;
};

typedef struct ListElement ListElement;

struct List
{
    int length;
    ListElement* head;
};

ListElement* createListElement(int value)
{
    ListElement* newElement = malloc(sizeof(ListElement));
    newElement->value = value;
    newElement->nextElement = NULL;
    return newElement;
}

List* createList()
{
    List* newList = malloc(sizeof(List));
    newList->length = 0;
    newList->head = NULL;
    return newList;
}

void append(List* list, int value, int index)
{
    if (list == NULL || index > list->length || index < 0)
    {
        return;
    }
    if (list->length == 0)
    {
        list->head = createListElement(value);
        list->length++;
        return;
    }
    ListElement* pointer = list->head;
    for (int i = 1; i < index; i++)
    {
        pointer = pointer->nextElement;
    }
    ListElement* newElement = createListElement(value);
    newElement->nextElement = pointer->nextElement;
    pointer->nextElement = newElement;
    list->length++;
}

void printList(List* list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("{}\n");
        return;
    }
    printf("{ ");
    ListElement* pointer = list->head;
    while (pointer != NULL)
    {
        printf("%d ", pointer->value);
        pointer = pointer->nextElement;
    }
    printf("}\n");
}

void deleteList(List* list)
{
    if (list == NULL)
    {
        return;
    }
    ListElement* pointer = list->head;
    ListElement* deleted = NULL;
    while (pointer != NULL)
    {
        deleted = pointer;
        pointer = pointer->nextElement;
        if (deleted != NULL)
        {
            free(deleted);
        }
    }
    free(list);
}

int pop(List* list, int index)
{
    if (list == NULL || index > list->length || index < 0 || list->length == 0)
    {
        return -1;
    }
    ListElement* pointer = list->head;
    ListElement* deletedElement = NULL;
    if (index == 0)
    {
        list->head = pointer->nextElement;
        free(pointer);
    }
    for (int i = 1; i < index; i++)
    {
        pointer = pointer->nextElement;
    }
    deletedElement = pointer->nextElement;
    int answer = deletedElement->value;
    pointer->nextElement = pointer->nextElement->nextElement;
    free(deletedElement);
    list->length--;
    return answer;
}

void findMaxAndReplace(ListElement* pointer, int value)
{
    ListElement* oldElement = pointer;
    int max = INT_MIN;
    ListElement* maxElement = NULL;
    while (pointer != NULL)
    {
        if (pointer->value > max)
        {
            max = pointer->value;
            maxElement = pointer;
        }
        pointer = pointer->nextElement;
    }
    if (maxElement != NULL)
    {
        maxElement->value = oldElement->value;
        oldElement->value = max;
    }
}

void sortList(List* list)
{
    if (list == NULL || list->length == 0)
    {
        return;
    }
    ListElement* pointer = list->head;
    ListElement* pointerToMax = NULL;
    for (int i = 0; i < list->length; i++)
    {
        findMaxAndReplace(pointer, pointer->value);
        pointer = pointer->nextElement;
    }
}