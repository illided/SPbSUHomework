#include <stdio.h>
#include "priorityQueue.h"
#include <stdlib.h>
#include <string.h>

char* createString(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

char* getString()
{
    // gets a string from stdin with random size
    int maxSize = 5;
    int stringLength = 0;
    char* output = createString(maxSize);
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
    char* stringInput = getString();
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

int main()
{
    PriorityQueue* newQueue = createQueue();
    int operation = -1;
    int value = -1;
    int priority = -1;
    bool inputIsCorrect = false;
    printf("Commands:\n"
           "1 - add to queue\n"
           "2 - dequeue\n"
           "3 - print queue\n"
           "0 - exit\n");
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
                printf("Value:\n");
                value = getNumber(&inputIsCorrect);
                if (!inputIsCorrect)
                {
                    printf("Incorrect value\n");
                    continue;
                }
                printf("Priority:\n");
                priority = getNumber(&inputIsCorrect);
                if (!inputIsCorrect)
                {
                    printf("Incorrect priority\n");
                    continue;
                }
                enqueue(newQueue, value, priority);
                break;
            }
            case 2:
            {
                printf("Maximum priority value: %d\n", dequeue(newQueue));
                break;
            }
            case 3:
            {
                printQueue(newQueue);
                break;
            }
            case 0:
            {
                printf("Goodbye!\n");
                break;
            }
            default:
            {
                printf("Invalid command");
                break;
            }
        }
    }
    deleteQueue(newQueue);
    return 0;
}
