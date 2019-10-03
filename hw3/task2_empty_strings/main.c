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
    char* input = malloc(sizeof(char) * maxSize);
    for (int i = 0; i < maxSize; i++)
    {
        input[i] = ' ';
    }

    int numOfEmptyStrings = 0;
    do
    {
        fgets(input, sizeof(char) * maxSize, file);
        if (input == NULL)
        {
            break;
        }
        if (isEmpty(input))
        {
            numOfEmptyStrings++;
        }
    } while (!feof(file));
    printf("%d", numOfEmptyStrings);
    fclose(file);
    return 0;
}