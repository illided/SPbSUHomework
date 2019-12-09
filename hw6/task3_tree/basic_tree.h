#ifndef BASIC_TREE_H
#define BASIC_TREE_H

#include <stdbool.h>

struct Tree;
struct Node;

typedef struct Tree Tree;
typedef struct Node Node;

//return empty tree
Tree* createTree();

/* return true if tree is empty
 * false - if not empty */
bool isEmpty(Tree* tree);

// add value to the tree
void append(int value, Tree* tree);

// delete value from the tree
void delete(int value, Tree* tree);

/* return true if value contains in the tree
 * false - if it's not */
bool isInTree(int value, Tree* tree);

//print the tree values in descending order
void printInDescendingOrder(Tree* tree);

//print the tree values in ascending order
void printInAscendingOrder(Tree* tree);

/* print tree values in "intuitive form". Example:
 * (5 (2 null null) (10 null (12 null null))) */
void printInRecurentOrder(Tree* tree);

//delete the tree
void burnTheTree(Tree* tree);

#endif