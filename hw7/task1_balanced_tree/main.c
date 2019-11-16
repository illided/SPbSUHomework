#include <stdio.h>
#include "auto_balancing_tree.h"

int main() {
    Tree* tree = createTree();
    for (int i = 0; i < 12; i++)
    {
        append(i, tree);
        printInRecurentOrder(tree);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        delete(i, tree);
        printInRecurentOrder(tree);
        printf("\n");
    }
    burnTheTree(tree);
    return 0;
}