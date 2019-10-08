#include "phonebook.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

bool isEqual(int numOfChars, char firstString[], char secondString[]) {
    printf("IS EQUAL WAS CALLED\n");
    for (int i = 0; i < numOfChars; i++)
    {
        if (firstString[i] != secondString[i])
        {
            printf("NOT EQUAL\n");
            return false;
        }
    }
    return true;
}

char* getName(char* number, PhoneBook* phonebook)
{
    Record* pointer = phonebook->head;
    while (pointer != NULL)
    {
        if ((strlen(number) == strlen(pointer->number)) && (isEqual(strlen(number), number, pointer->number)))
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
        if ((strlen(name) == strlen(pointer->name)) && isEqual(strlen(name), name, pointer->name))
        {
            return pointer->number;
        }
        pointer = pointer->next;
    }
    return NULL;
}

void destroyPhoneBook(PhoneBook* phonebook)
{
    Record* pointer = phonebook->head;
    Record* deletedElement = NULL;
    free(phonebook);
    while (pointer != NULL)
    {
        free(pointer->name);
        free(pointer->number);
        deletedElement = pointer;
        pointer = pointer->next;
        free(deletedElement);
    }
}