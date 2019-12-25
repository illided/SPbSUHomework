#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* createString(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

char* getString(FILE* file)
{
    int maxSize = 5;
    int stringLength = 0;
    char* output = createString(maxSize);
    char input = ' ';

    fscanf(file,"%c", &input);
    while (input != '\n' && !feof(file))
    {
        output[stringLength] = input;
        stringLength++;
        fscanf(file,"%c", &input);
        if (stringLength == maxSize)
        {
            maxSize *= 2;
            output = realloc(output, sizeof(char) * maxSize);
        }
    }
    output[stringLength] = '\0';
    return output;
}

int stringComparison(const void *i, const void *j)
{
    return strcmp(*(char**)i, *(char**)j);
}

int main()
{
    FILE* oldFile = fopen("file.txt", "r");
    if (oldFile == NULL)
    {
        fprintf(stderr, "Cant open the file\n");
        return 1;
    }
    int stringArrayLength = 0;
    int stringArraySize = 10;
    char** stringArray = malloc(sizeof(char*) * stringArraySize);
    while (!feof(oldFile))
    {
        stringArray[stringArrayLength] = getString(oldFile);
        stringArrayLength++;
        if (stringArrayLength == stringArraySize)
        {
            stringArraySize *= 2;
            stringArray = realloc(stringArray, sizeof(char*) * stringArraySize);
        }
    }
    fclose(oldFile);
    qsort(stringArray, stringArrayLength, sizeof(char*), (int(*) (const void *, const void *)) stringComparison);
    FILE* newFile = fopen("newFile.txt", "w");
    if (newFile == NULL)
    {
        fprintf(stderr, "Cant create the file\n");
        return 2;
    }
    char* uniqueString = stringArray[0];
    for (int i = 1; i < stringArrayLength; i++)
    {
        if (strcasecmp(uniqueString, stringArray[i]) == 0)
        {
            continue;
        }
        uniqueString = stringArray[i];
        fprintf(newFile, "%s\n", stringArray[i]);
    }
    for (int i = 0; i < stringArrayLength; i++)
    {
        free(stringArray[i]);
    }
    fclose(newFile);
    free(stringArray);
    return 0;
}
