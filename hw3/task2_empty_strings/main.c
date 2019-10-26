#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int maxSize = 10000;

bool isEmpty(char input[])
{
    for (int i = 0; i < strlen(input); i++)
    {
        if ((input[i] != '\t') && (input[i] != ' ') && (input[i] != '\n'))
        {
            return false;
        }
    }
    return true;
}

int main() {
    FILE* file = fopen("file.txt", "r");
    if (file == NULL)
    {
        printf("Something went wrong");
        return 0;
    }
    rewind(file);
    char* input = malloc(sizeof(char) * maxSize);
    for (int i = 0; i < maxSize; i++)
    {
        input[i] = ' ';
    }

    int numOfNonEmptyStrings = 0;
    do
    {
        fgets(input, sizeof(char) * maxSize, file);
        if (input == NULL)
        {
            break;
        }
        if (!isEmpty(input))
        {
            numOfNonEmptyStrings++;
        }
    }
    while (!feof(file));
    printf("%d", numOfNonEmptyStrings);
    fclose(file);
    free(input);
    return 0;
}