#include "stringByStudent.h"
#include <stdlib.h>
#include <stdio.h>

struct String
{
    char *content;
    int length;
};

String *createEmptyString()
{
    String *string = malloc(sizeof(String));
    string->content = malloc(sizeof(char));
    string->content[0] = '\0';
    string->length = 0;
    return string;
}

void deleteString(String *string)
{
    if (string != NULL)
    {
        free(string->content);
        free(string);
    }
}

int stringLength(String *string)
{
    if (string != NULL)
    {
        return string->length;
    }
    return 0;
}

bool isEmptyString(String *string)
{
    return stringLength(string) == 0;
}

String *getStringFromArray(char *array)
{
    if (array == NULL)
    {
        return NULL;
    }
    String *string = createEmptyString();
    int stringLength = 0;
    while (array[stringLength] != '\0')
    {
        stringLength++;
    }
    string->length = stringLength;
    string->content = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        string->content[i] = array[i];
    }
    return string;
}

char *importStringToArray(String *string)
{
    if (string == NULL)
    {
        return NULL;
    }
    int outputArrayLength = stringLength(string) + 1;
    char *output = malloc(sizeof(char) * outputArrayLength);
    for (int i = 0; i < outputArrayLength; i++)
    {
        output[i] = ' ';
        output[i] = string->content[i];
    }
    output[outputArrayLength - 1] = '\0';
    return output;
}

void concatenateStrings(String *baseString, String *endSubString)
{
    /* adding the content of endSubString
     * to the end of baseString
     * (don't creates a third string)
     * (if any string is NULL than nothing happens) */

    if ((endSubString == NULL) || (baseString == NULL))
    {
        return;
    }
    int baseLength = stringLength(baseString);
    int endLength = stringLength(endSubString);
    baseString->content = realloc(baseString->content, sizeof(char) * (baseLength + endLength));
    baseString->length = baseLength + endLength;
    for (int i = 0; i < endLength; i++)
    {
        baseString->content[baseLength + i] = endSubString->content[i];
    }
}

void readToStringFromFile(String *string, FILE *file)
{
    /* Rewrite the string with
     * data from file or standart input
     * (original data will be lost) */

    if ((string == NULL) || (file == NULL))
    {
        return;
    }
    int stringLength = 0;
    int stringSpace = 5;
    char *stringContent = malloc(sizeof(char) * stringSpace);
    char input = fgetc(file);

    while ((input != '\n') && (!feof(file)))
    {
        if (stringLength == stringSpace)
        {
            stringSpace *= 2;
            stringContent = realloc(stringContent, sizeof(char) * stringSpace);
        }
        stringContent[stringLength] = input;
        stringLength++;
        input = fgetc(file);
    }

    stringContent = realloc(stringContent, sizeof(char) * stringLength);
    free(string->content);
    string->content = stringContent;
    string->length = stringLength;
}

String *cloneString(String *string)
{
    // returns the string with the data of original string

    if (string == NULL)
    {
        return NULL;
    }
    String *clonedString = createEmptyString();
    concatenateStrings(clonedString, string);
    return clonedString;
}

bool areEqual(String *firstString, String *secondString)
{
    /* returns true, if both strings contains the same characters
     * at the same places
     * returns false if previous statement is wrong
     * OR any of input is NULL
     * (NULL is not a string therefore it is an incorrect input) */

    if ((firstString == NULL) || (secondString == NULL))
    {
        return false;
    }
    if (stringLength(firstString) == stringLength(secondString))
    {
        int length = stringLength(firstString);
        for (int i = 0; i < length; i++)
        {
            if (firstString->content[i] != secondString->content[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

String *getSubString(String *string, int start, int end)
{
    /* return the sub string of a given string
     * (if the start or end point is less or bigger then
     * an original string than it will be setted to its first
     * or last character) */

    if (start < 0)
    {
        start = 0;
    }
    if (end > stringLength(string) - 1)
    {
        end = stringLength(string) - 1;
    }
    if (start > end)
    {
        return createEmptyString();
    }

    int substringLength = end - start + 1;
    char subStringContent[substringLength];
    for (int i = 0; i < substringLength; i++)
    {
        subStringContent[i] = string->content[start + i];
    }
    subStringContent[substringLength - 1] = '\0';
    return getStringFromArray(subStringContent);
}

void rewriteString(String *string, char *array)
{
    /* changes the contents of the string to
     * the contents of the array (if instead of
     * the array, NULL is passed, the string will be cleared) */

    if (string == NULL)
    {
        return;
    }
    if (array == NULL)
    {
        string->content = malloc(sizeof(char));
        string->content[0] = '\0';
        string->length = 0;
        return;
    }
    free(string->content);
    int stringLength = 0;
    while (array[stringLength] != '\0')
    {
        stringLength++;
    }
    string->length = stringLength;
    string->content = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        string->content[i] = array[i];
    }
}

void printStringToFile(String *string, FILE *file)
{
    if ((string == NULL) || (file == NULL))
    {
        return;
    }
    int strLength = stringLength(string);
    for (int i = 0; i < strLength; i++)
    {
        fprintf(file, "%c", string->content[i]);
    }
}

bool isReadableEmpty(String *string)
{
    if (string == NULL)
    {
        return false;
    }
    int strLength = stringLength(string);
    for (int i = 0; i < strLength; i++)
    {
        if ((string->content[i] != ' ') && (string->content[i] != '\n') && (string->content[i] != '\t'))
        {
            return false;
        }
    }
    return true;
}