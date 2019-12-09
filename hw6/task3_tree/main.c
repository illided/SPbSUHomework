#include <stdio.h>
#include "basic_tree.h"

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
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                printf("Value:\n");
                scanf("%d", &activeElement);
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
            case 2:
                printf("Value:\n");
                scanf("%d", &activeElement);
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
            case 3:
                printf("Value:\n");
                scanf("%d", &activeElement);
                if (!isInTree(tree, activeElement))
                {
                    printf("I don't have this value\n");
                }
                else
                {
                    printf("I have this value\n");
                }
                break;
            case 4:
                printInAscendingOrder(tree);
                printf("\n");
                break;
            case 5:
                printInDescendingOrder(tree);
                printf("\n");
                break;
            case 6:
                printInRecurentOrder(tree);
                printf("\n");
                break;
        }
    }

    burnTheTree(tree);
    return 0;
}