#ifndef BASIC_TREE_H
#define BASIC_TREE_H

#include <stdbool.h>

struct Tree;
struct Node;

typedef struct Tree Tree;
typedef struct Node Node;

Tree* createTree();
bool isEmpty(Tree* tree);
void append(int value, Tree* tree);
void delete(int value, Tree* tree);
bool isInTree(int value, Tree* tree);
void printInDescendingOrder(Tree* tree);
void printInAscendingOrder(Tree* tree);
void printInRecurentOrder(Tree* tree);
void burnTheTree(Tree* tree);

#endif
