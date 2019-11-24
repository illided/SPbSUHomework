#include "stringByStudent.h"
#include <stdlib.h>
#include <stdio.h>

struct String{
    char* content;
    int length;
};

String* createEmptyString()
{
    String* string = malloc(sizeof(String));
    string->content = malloc(sizeof(char));
    string->content[0] = ' ';
    string->length = 0;
    return string;
}

void deleteString(String* string)
{
    free(string->content);
    free(string);
}

int stringLength(String* string)
{
    return string->length;
}

bool isEmptyString(String* string)
{
    return stringLength(string) == 0;
}

String* getStringFromArray(char* array)
{
    String* string = createEmptyString();
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

char* importStringToArray(String* string)
{
    int outputArrayLength = stringLength(string) + 1;
    char* output = malloc(sizeof(char) * outputArrayLength);
    for (int i = 0; i < outputArrayLength; i++)
    {
        output[i] = ' ';
        output[i] = string->content[i];
    }
    output[outputArrayLength - 1] = '\0';
    return output;
}

void concatenateStrings(String* baseString, String* endSubString)
{
    /* adding the content of endSubString
     * to the end of baseString
     * (don't creates a third string) */

    int baseLength = stringLength(baseString);
    int endLength = stringLength(endSubString);
    baseString->content = realloc(baseString->content, sizeof(char) * (baseLength + endLength));
    baseString->length = baseLength + endLength;
    for (int i = 0; i < endLength; i++)
    {
        baseString->content[baseLength + i] = endSubString->content[i];
    }
}

void readToString(String* string)
{
    /* Rewrite the string with
     * data from standart input
     * (original data will be lost) */

    int stringLength = 0;
    int stringSpace = 5;
    char* stringContent = malloc(sizeof(char) * stringSpace);
    char input = ' ';

    scanf("%c", &input);
    while (input != '\n')
    {
        if (stringLength == stringSpace)
        {
            stringSpace += 5;
            stringContent = realloc(stringContent, sizeof(char) * stringSpace);
        }
        stringContent[stringLength] = input;
        stringLength++;
        scanf("%c", &input);
    }

    stringContent = realloc(stringContent, sizeof(char) * stringLength);
    free(string->content);
    string->content = stringContent;
    string->length = stringLength;
}

String* cloneString(String* string)
{
    // returns the string with the data of original string
    String* clonedString = createEmptyString();
    concatenateStrings(clonedString, string);
    return clonedString;
}

bool areEqual(String* firstString, String* secondString)
{
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

String* getSubString(String* string, int start, int end)
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

    char subStringContent[end - start + 2];
    for (int j = 0; j < end - start + 2; j++)
    {
        subStringContent[j] = ' ';
    }
    for (int i = 0; start + i <= end; i++)
    {
        subStringContent[i] = string->content[start + i];
    }

    subStringContent[end - start + 1] = '\0';
    return getStringFromArray(subStringContent);
}

void rewriteString(String* string, char* array)
{
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

