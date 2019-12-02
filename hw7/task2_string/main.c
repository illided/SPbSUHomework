#include <stdio.h>
#include <stdlib.h>
#include "stringByStudent.h"

int main()
{
    String* test = createEmptyString();
    printf("Enter string:\n");
    readToStringFromFile(test, stdin);
    printStringToFile(test, stdout);

    printf("\nString length = %d\n", stringLength(test));

    String* clone = cloneString(test);
    printf("Cloned string: ");
    printStringToFile(clone, stdout);
    deleteString(clone);

    String* subString = getSubString(test, 2, 7);
    printf("\nSome random substring:");
    printStringToFile(subString, stdout);
    deleteString(subString);

    char* array = importStringToArray(test);
    printf("\nCopied to array: %s\n", array);
    String* originalString = getStringFromArray(array);
    printf("And back to string: ");
    printStringToFile(originalString, stdout);
    free(array);
    deleteString(originalString);

    String* newString = createEmptyString();
    printf("\nSend me another string:\n");
    readToStringFromFile(newString, stdin);
    if (isEmptyString(newString))
    {
        printf("Its empty!\n");
    }
    else
    {
        printf("Its not empty\n");
    }
    if (areEqual(test, newString))
    {
        printf("They are equal!\n");
    }
    else
    {
        printf("They are not equal!\n");
    }

    char* newArray = importStringToArray(newString);
    rewriteString(test, newArray);
    printf("Ops i rewrote old string with new: ");
    printStringToFile(test, stdout);
    free(newArray);
    deleteString(newString);

    deleteString(test);
    return 0;
}