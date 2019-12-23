#include <stdio.h>
#include "basic_tree.h"
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
    Tree* tree = createTree();
    int input = -1;
    int activeElement = 0;
    printf("Hello! I am a tree program. Some things you can do via (<operation> enter <operand>):\n"
           "1 - add something to the tree\n"
           "2 - delete something\n"
           "3 - check if some value contains in the tree\n"
           "4 - print tree content in ascending order\n"
           "5 - print tree content in descending order\n"
           "6 - print in recurent order\n"
           "0 - exit\n");

    while (input != 0)
    {
        printf("Operation:\n");
        bool inputIsCorrect = false;
        input = getNumber(&inputIsCorrect);
        if (!inputIsCorrect)
        {
            printf("Invalid command\n");
            continue;
        }
        switch (input)
        {
            case 1:
            {
                printf("Value:\n");
                activeElement = getNumber(&inputIsCorrect);
                if (!inputIsCorrect)
                {
                    printf("Invalid value\n");
                    continue;
                }
                if (!isInTree(tree, activeElement))
                {
                    append(tree, activeElement);
                    printf("%d was added\n", activeElement);
                }
                else
                {
                    printf("Already have in the tree\n");
                }
                break;
            }
            case 2:
            {
                printf("Value:\n");
                activeElement = getNumber(&inputIsCorrect);
                if (!inputIsCorrect)
                {
                    printf("Invalid value\n");
                    continue;
                }
                if (isInTree(tree, activeElement))
                {
                    delete(tree, activeElement);
                    printf("%d was deleted\n", activeElement);
                }
                else
                {
                    printf("Dont have this value in the tree\n");
                }
                break;
            }
            case 3:
            {
                printf("Value:\n");
                activeElement = getNumber(&inputIsCorrect);
                if (!inputIsCorrect)
                {
                    printf("Invalid value\n");
                    continue;
                }
                if (!isInTree(tree, activeElement))
                {
                    printf("I don't have this value\n");
                }
                else
                {
                    printf("I have this value\n");
                }
                break;
            }
            case 4:
            {
                printInAscendingOrder(tree);
                printf("\n");
                break;
            }
            case 5:
            {
                printInDescendingOrder(tree);
                printf("\n");
                break;
            }
            case 6:
            {
                printInRecurentOrder(tree);
                printf("\n");
                break;
            }
            default:
            {
                printf("Invalid command\n");
                break;
            }
        }
    }
    burnTheTree(tree);
    return 0;
}