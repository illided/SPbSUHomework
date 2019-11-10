#include <stdio.h>
#include "basic_tree.h"

int main() {
    Tree* tree = createTree();
    printf("Hello! I am a happy tree!\nI can store a lot of things!\n");
    printf("(lets put 6, 2, 8, 4, 1, 10, 7)\n");
    append(6, tree);
    append(2, tree);
    append(8, tree);
    append(4, tree);
    append(1, tree);
    append(10, tree);
    append(7, tree);

    printf("In ascending ord: ");
    printInAscendingOrder(tree);
    printf("\n");
    printf("In descending order: ");
    printInDescendingOrder(tree);
    printf("\n");
    printf("In recurent order: ");
    printInRecurentOrder(tree);
    printf("\n");

    printf("I can delete things!\n(lets delete 2, 8 and 6)\n");
    delete(2, tree);
    delete(8, tree);
    delete(6, tree);
    printInRecurentOrder(tree);

    printf("\nI can check if there a something in the tree!\nAsk me about some number:\n");
    int number = 0;
    scanf("%d", &number);
    if (isInTree(number, tree))
    {
        printf("%d is in the tree\n", number);
    }
    else
    {
        printf("%d is not in the tree\n", number);
    }

    burnTheTree(tree);
    return 0;
}