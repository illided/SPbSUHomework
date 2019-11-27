#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include "stringByStudent.h"

const int maxSize = 1000;

char *createArrayOfChar(int arrayLength)
{
    char *localString = malloc(sizeof(char) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

void addEntry(HashTable *numberByNameBook, HashTable *nameByNumberBook)
{
    String *nameString = createEmptyString();
    String *phoneString = createEmptyString();

    printf("Name:\n");
    fflush(stdin);
    readToStringFromFile(nameString, stdin);
    printf("Number:\n");
    fflush(stdin);
    readToStringFromFile(phoneString, stdin);
    if (!isInTable(phoneString, nameByNumberBook) && !isInTable(nameString, numberByNameBook))
    {
        pushToHashTable(nameString, phoneString, numberByNameBook);
        pushToHashTable(phoneString, nameString, nameByNumberBook);
        printf("Person was added to the book\n");
    } else
    {
        printf("Already have in the book\n");
    }
    deleteString(nameString);
    deleteString(phoneString);
}

void printSearchResult(String *nameString, String *phoneString)
{
    printf("Search result: ");
    printStringToFile(nameString, stdout);
    printf(" ");
    printStringToFile(phoneString, stdout);
    printf("\n");
}

int main()
{
    FILE *phonebook = fopen("phonebook.txt", "r");  // opening the file or creating it
    if (phonebook == NULL)
    {
        printf("Phone book was not found \nCreating the phone book...\n");
        phonebook = fopen("phonebook.txt", "w");
        fclose(phonebook);
        phonebook = fopen("phonebook.txt", "r");
    }
    rewind(phonebook);

    HashTable *numberByNameBook = createHashTable(20);
    HashTable *nameByNumberBook = createHashTable(20);
    String *nameString = createEmptyString();
    String *phoneString = createEmptyString();

    while (!feof(phonebook))  // loading tables from file
    {
        readToStringFromFile(nameString, phonebook);
        readToStringFromFile(phoneString, phonebook);
        if (!isReadableEmpty(nameString) && !isReadableEmpty(phoneString))
        {
            pushToHashTable(nameString, phoneString, numberByNameBook);
            pushToHashTable(phoneString, nameString, nameByNumberBook);
        }
    }
    fclose(phonebook);

    printf("Hello! I am an interactive phone book. To work\n"
           "with me you need to first enter the operation number,\n"
           "press ENTER, and then enter what you need (also via ENTER). You can:\n"
           "1: add entry (name, ENTER, phone number)\n"
           "2: search name by number\n"
           "3: search number by name\n"
           "4: save your phonebook\n"
           "0: close phonebook\n");
    int operation = -1;
    while (operation != 0)
    {
        printf("Operation:\n");
        scanf("%d", &operation);
        switch (operation)
        {
            case 1:
                addEntry(numberByNameBook, nameByNumberBook);
                break;
            case 2:
                printf("Number:\n");
                fflush(stdin);
                readToStringFromFile(phoneString, stdin);
                nameString = getFromHashTable(phoneString, nameByNumberBook);
                if (nameString == NULL)
                {
                    printf("I could not find a person with this number\n");
                } else
                {
                    printSearchResult(nameString, phoneString);
                }
                break;
            case 3:
                printf("Name:\n");
                fflush(stdin);
                readToStringFromFile(nameString, stdin);
                phoneString = getFromHashTable(nameString, numberByNameBook);
                if (phoneString == NULL)
                {
                    printf("I could not find a person with this name");
                } else
                {
                    printSearchResult(nameString, phoneString);
                }
                break;
            case 4:
                phonebook = fopen("phonebook.txt", "w");
                if (phonebook == NULL)
                {
                    printf("Cant open or create file\n");
                    break;
                }
                printHashTableContentToFile(numberByNameBook, phonebook);
                printf("Phonebook was saved to the file!\n");
                fclose(phonebook);
                break;
        }
    }

    deleteString(nameString);
    deleteString(phoneString);
    deleteHashTable(nameByNumberBook);
    deleteHashTable(numberByNameBook);
    return 0;
}