#ifndef AUTO_BALANCING_TREE_H
#define AUTO_BALANCING_TREE_H

#include <stdbool.h>

struct Tree;
struct Node;

typedef struct Tree Tree;
typedef struct Node Node;

Tree* createTree();
//return empty tree

bool isEmpty(Tree* tree);
/* return true if tree is empty
 * false - if not empty */

void append(int value, Tree* tree);
// add value to the tree

void delete(int value, Tree* tree);
// delete value from the tree

bool isInTree(int value, Tree* tree);
/* return true if value contains in the tree
 * false - if it's not */

void printInDescendingOrder(Tree* tree);
//print the tree values in descending order

void printInAscendingOrder(Tree* tree);
//print the tree values in ascending order

void printInRecurentOrder(Tree* tree);
/* print tree values in "intuitive form". Example:
 * (5 (2 null null) (10 null (12 null null))) */

void burnTheTree(Tree* tree);
//delete the tree
#endif
