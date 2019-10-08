#include <stdio.h>
#include <string.h>
#include "phonebook.h"
#include <stdbool.h>

const int maxSize = 1000;

int main()
{
    FILE* phonebook = fopen("phonebook.txt", "r");  // opening the file or creating it
    if (phonebook == NULL)
    {
        printf("Phone book was not found \n Creating the phone book...");
        phonebook = fopen("phonebook.txt", "w");
        fclose(phonebook);
        phonebook = fopen("phonebook.txt", "r");
    }

    PhoneBook* localPhoneBook = createPhoneBook();  // creating phonebook and loading it from file
    char name[maxSize];
    char number[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        name[i] = ' ';
        number[i] = ' ';
    }
    while (!feof(phonebook))
    {
        fgets(name, maxSize, phonebook);
        fgets(number, maxSize, phonebook);
        if (number[strlen(number) - 1] == '\n')
        {
            number[strlen(number) - 1] = '\0';
        }
        if (name[strlen(name) - 1] == '\n')
        {
            name[strlen(name) - 1] = '\0';
        }
        phoneBookAppend(name, number, localPhoneBook);
    }

    printf("Ready to work.Commands:\nAdd:\n1 <person name> <number>\n"  // working with the phone book
           "Search by name:\n2 <person name>\nSearch by number:\n3 <person number>\n"
           "Save:\n4\nExit:\n0\n");
    int typeOfOperation = 0;
    do
    {
        scanf("%d", &typeOfOperation);
        if (typeOfOperation == 1)
        {
            scanf("%s %s", name, number);

        }
    }
    while (typeOfOperation != 0);
    destroyPhoneBook(localPhoneBook);  // free the local memory
    fclose(phonebook);
    return 0;
}