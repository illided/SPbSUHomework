#include <stdio.h>
#include "hashTable.h"
#include "stringByStudent.h"
#include <string.h>
#include <stdlib.h>


char* createArrayOfChar(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

char* getArrayOfChar()
{
    // gets a string from stdin with random size
    int maxSize = 5;
    int stringLength = 0;
    char* output = createArrayOfChar(maxSize);
    char input = ' ';

    scanf("%c", &input);
    while (input != '\n')
    {
        output[stringLength] = input;
        stringLength++;
        scanf("%c", &input);
        if (stringLength == maxSize)
        {
            maxSize *= 2;
            output = realloc(output, sizeof(char) * maxSize);
        }
    }
    output[stringLength] = '\0';
    return output;
}

int getNumber(bool* inputIsCorrect)
{
    char* mistakeChecker = NULL;
    int input = 0;
    char* stringInput = getArrayOfChar();
    if (stringInput[0] == '\0')
    {
        *inputIsCorrect = false;
        free(stringInput);
        return -1;
    }
    input = strtol(stringInput, &mistakeChecker, 10);
    if (mistakeChecker != NULL && strlen(mistakeChecker) > 0)
    {
        *inputIsCorrect = false;
        free(stringInput);
        return -1;
    }
    free(stringInput);
    *inputIsCorrect = true;
    return input;
}

void addEntry(HashTable* numberByNameBook, HashTable* nameByNumberBook)
{
    String* nameString = createEmptyString();
    String* phoneString = createEmptyString();

    printf("Name:\n");
    readToStringFromFile(nameString, stdin);
    printf("Number:\n");
    readToStringFromFile(phoneString, stdin);
    if (!isInTable(phoneString, nameByNumberBook) && !isInTable(nameString, numberByNameBook))
    {
        pushToHashTable(nameString, phoneString, numberByNameBook);
        pushToHashTable(phoneString, nameString, nameByNumberBook);
        printf("Person was added to the book\n");
    }
    else
    {
        printf("Already have in the book\n");
    }
    deleteString(nameString);
    deleteString(phoneString);
}

void printSearchResult(String* nameString, String* phoneString)
{
    printf("Search result: ");
    printStringToFile(nameString, stdout);
    printf(" ");
    printStringToFile(phoneString, stdout);
    printf("\n");
}

FILE* openPhoneBook()
{
    FILE* phonebook = fopen("phonebook.txt", "r");  // opening the file or creating it
    if (phonebook == NULL)
    {
        printf("Phone book was not found \nCreating the phone book...\n");
        phonebook = fopen("phonebook.txt", "w");
        fclose(phonebook);
        phonebook = fopen("phonebook.txt", "r");
    }
    rewind(phonebook);
    return phonebook;
}

void prepareHashTables(HashTable* numberByNameBook, HashTable* nameByNumberBook, FILE* phoneBook)
{
    String* nameString = createEmptyString();
    String* phoneString = createEmptyString();

    while (!feof(phoneBook))  // loading tables from file
    {
        readToStringFromFile(nameString, phoneBook);
        readToStringFromFile(phoneString, phoneBook);
        if (!isReadableEmpty(nameString) && !isReadableEmpty(phoneString))
        {
            pushToHashTable(nameString, phoneString, numberByNameBook);
            pushToHashTable(phoneString, nameString, nameByNumberBook);
        }
    }
    fclose(phoneBook);
    deleteString(nameString);
    deleteString(phoneString);
}

void savePhoneBook(HashTable* numberByNameBook)
{
    FILE* phoneBook = fopen("phonebook.txt", "w");
    if (phoneBook == NULL)
    {
        printf("Cant open or create file\n");
        return;
    }
    printHashTableContentToFile(numberByNameBook, phoneBook);
    printf("Phone book was saved to the file!\n");
    fclose(phoneBook);
}

void searchByNumber(HashTable* nameByNumberBook)
{
    String* phoneString = createEmptyString();
    printf("Number:\n");
    readToStringFromFile(phoneString, stdin);
    String* nameString = getFromHashTable(phoneString, nameByNumberBook);
    if (nameString == NULL)
    {
        printf("I could not find a person with this number\n");
    }
    else
    {
        printSearchResult(nameString, phoneString);
    }
    deleteString(phoneString);
    deleteString(nameString);
}

void searchByName(HashTable* numberByNameBook)
{
    String* nameString = createEmptyString();
    printf("Name:\n");
    readToStringFromFile(nameString, stdin);
    String* phoneString = getFromHashTable(nameString, numberByNameBook);
    if (phoneString == NULL)
    {
        printf("I could not find a person with this name\n");
    }
    else
    {
        printSearchResult(nameString, phoneString);
    }
    deleteString(nameString);
    deleteString(phoneString);
}

int main()
{
    FILE* phoneBook = openPhoneBook();

    HashTable* numberByNameBook = createHashTable(20);
    HashTable* nameByNumberBook = createHashTable(20);
    prepareHashTables(numberByNameBook, nameByNumberBook, phoneBook);

    printf("Hello! I am an interactive phone book. To work\n"
           "with me you need to first enter the operation number,\n"
           "press ENTER, and then enter what you need (also via ENTER). You can:\n"
           "1: add entry (name, ENTER, phone number)\n"
           "2: search name by number\n"
           "3: search number by name\n"
           "4: save your phone book\n"
           "0: close phone book\n");
    int operation = -1;
    bool inputIsCorrect = false;
    String* nameString = createEmptyString();
    String* phoneString = createEmptyString();
    while (operation != 0)
    {
        printf("Operation:\n");
        operation = getNumber(&inputIsCorrect);
        if (!inputIsCorrect)
        {
            printf("Invalid command\n");
            continue;
        }
        switch (operation)
        {
            case 1:
            {
                addEntry(numberByNameBook, nameByNumberBook);
                break;
            }
            case 2:
            {
                searchByNumber(nameByNumberBook);
                break;
            }
            case 3:
            {
                searchByName(numberByNameBook);
                break;
            }
            case 4:
            {
                savePhoneBook(numberByNameBook);
                break;
            }
            case 0:
            {
                printf("Goodbye!\n");
                break;
            }
            default:
            {
                printf("Invalid command\n");
                break;
            }
        }
    }

    deleteString(nameString);
    deleteString(phoneString);
    deleteHashTable(nameByNumberBook);
    deleteHashTable(numberByNameBook);
    return 0;
}