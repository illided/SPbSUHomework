#pragma once

struct List;
typedef struct List List;

List* createList();
void deleteList(List* list);
void append(List* list, int value, int index);
int pop(List* list, int index);
void sortList(List* list);
void printList(List* list);