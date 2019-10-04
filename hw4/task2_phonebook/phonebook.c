#include "phonebook.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Record
{
    char* name;
    char* number;
    Record* next;
};

struct PhoneBook
{
    Record* head;
};

PhoneBook* createPhoneBook()
{
    PhoneBook* phonebook = malloc(sizeof(PhoneBook));
    phonebook->head = NULL;
    return phonebook;
}

void phoneBookAppend(char* name, char* number, PhoneBook* phonebook)
{
    Record* record = malloc(sizeof(Record));
    record->name = name;
    record->number = number;
    record->next = phonebook->head;
    phonebook->head = record;
}

char* getName(char* number, PhoneBook* phonebook)
{
    Record* pointer = phonebook->head;
    while (pointer != NULL)
    {
        if (strcasecmp(number, pointer->number) == 0)
        {
            return pointer->name;
        }
        pointer = pointer->next;
    }
    return NULL;
}

char* getNumber(char* name, PhoneBook* phonebook)
{
    Record* pointer = phonebook->head;
    while (pointer != NULL)
    {
        if (strcasecmp(name, pointer->name) == 0)
        {
            return pointer->number;
        }
        pointer = pointer->next;
    }
    return NULL;
}