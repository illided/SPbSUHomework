#include "auto_balancing_tree.h"
#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int value;
    int height;
    Node* rightChild;
    Node* leftChild;
    Node* parent;
};

struct Tree
{
    Node* root;
};

Tree* createTree()
{
    Tree* tree = malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

Node* createNode(int value, Node* parent)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->rightChild = NULL;
    newNode->leftChild = NULL;
    newNode->parent = parent;
    newNode->value = value;
    newNode->height = 0;
    return newNode;
}

bool isEmpty(Tree* tree)
{
    return (tree == NULL) || (tree->root == NULL);
}

bool isLeaf(Node* node)
{
    return (node->rightChild == NULL) && (node->leftChild == NULL);
}

int getHeight(Node* node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

void updateHeight(Node* node)
{
    int rightChildHeight = getHeight(node->rightChild);
    int leftChildHeight = getHeight(node->leftChild);
    if (leftChildHeight < rightChildHeight)
    {
        node->height = rightChildHeight + 1;
    }
    else
    {
        node->height = leftChildHeight + 1;
    }
}

int getBalanceFactor(Node* node)
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

void setChild(Node* child, Node* parent, Tree* tree)
{
    /* overwriting the data for child about
     * it's parent to a given node
     * and data for appropriate child in parent node
     * (does not overwrites the data of child's old parent)
     * (CANT HAVE A NULL FOR A CHILD ARGUMENT)
     * (works with the root) */

    if (child == NULL)
    {
        return;
    }
    if (parent != NULL)
    {
        if (child->value > parent->value)
        {
            parent->rightChild = child;
        }
        else if (child->value < parent->value)
        {
            parent->leftChild = child;
        }
    }
    else
    {
        tree->root = child;
    }
    child->parent = parent;
}

void replaceWithNull(Node* node, Tree* tree)
{
    /* set the data about this child in parent
     * node to NULL
     * (you have to use function instead of the setChild
     * function if you want to set NULL child to some node)
     * (works with the root) */

    if (node->parent != NULL)
    {
        if (node->parent->leftChild == node)
        {
            node->parent->leftChild = NULL;
        }
        else if (node->parent->rightChild == node)
        {
            node->parent->rightChild = NULL;
        }
    }
    else
    {
        tree->root = NULL;
    }
}

void rotateRight(Node* node, Tree* tree)
{
    Node* pivot = node->leftChild;
    Node* fatherNode = node->parent;
    Node* traitor = pivot->rightChild;

    setChild(node, pivot, tree);
    setChild(pivot, fatherNode, tree);
    if (traitor != NULL)
    {
        setChild(traitor, node, tree);
    }
    else
    {
        node->leftChild = NULL;
    }
}

void rotateLeft(Node* node, Tree* tree)
{
    Node* pivot = node->rightChild;
    Node* fatherNode = node->parent;
    Node* traitor = pivot->leftChild;

    setChild(node, pivot, tree);
    setChild(pivot, fatherNode, tree);
    if (traitor != NULL)
    {
        setChild(traitor, node, tree);
    }
    else
    {
        node->rightChild = NULL;
    }
}

void balance(Node* node, Tree* tree)
{
    if (node->leftChild != NULL)
    {
        updateHeight(node->leftChild);
    }
    if (node->rightChild != NULL)
    {
        updateHeight(node->rightChild);
    }

    if (getBalanceFactor(node) == 2)
    {
        if (getBalanceFactor(node->rightChild) < 0)
        {
            rotateRight(node->rightChild, tree);
        }
        rotateLeft(node, tree);
    }
    if (getBalanceFactor(node) == -2)
    {
        if (getBalanceFactor(node->leftChild) > 0)
        {
            rotateLeft(node->leftChild, tree);
        }
        rotateRight(node, tree);
    }
}

void appendNodeByPointer(int value, Node* node, Tree* tree)
{
    /* go down the tree from a starting node
     * (if value of current node is bigger
     * than added value, then go right
     * if it less, than go left)
     * and search a place for a leaf */

    if (value > node->value)
    {
        if (node->rightChild != NULL)
        {
            appendNodeByPointer(value, node->rightChild, tree);
        }
        else
        {
            node->rightChild = createNode(value, node);
        }
    }
    else if (value < node->value)
    {
        if (node->leftChild != NULL)
        {
            appendNodeByPointer(value, node->leftChild, tree);
        }
        else
        {
            node->leftChild = createNode(value, node);
        }
    }
    updateHeight(node);
    balance(node, tree);
}

void append(Tree* tree, int value)
{
    if (tree == NULL)
    {
        return;
    }
    if (isEmpty(tree))
    {
        tree->root = createNode(value, NULL);
    }
    else
    {
        appendNodeByPointer(value, tree->root, tree);
    }
}

Node* findMaxNode(Node* node)
{
    /* finds the node with the biggest
     * value in subTree and returns
     * pointer to this node */

    if (node->rightChild == NULL)
    {
        return node;
    }
    return findMaxNode(node->rightChild);
}

void deleteNodeByPointer(Node* node, Tree* tree)
{
    /* deleting a giving node and rearranging the nodes
     * (works properly with the root) */
    if (isLeaf(node))
    {
        replaceWithNull(node, tree);
        free(node);
    }
    else if ((node->leftChild != NULL) && (node->rightChild == NULL))
    {
        setChild(node->leftChild, node->parent, tree);
        free(node);
    }
    else if ((node->leftChild == NULL) && (node->rightChild != NULL))
    {
        setChild(node->rightChild, node->parent, tree);
        free(node);
    }
    else
    {
        Node* localMax = findMaxNode(node->leftChild);
        node->value = localMax->value;
        deleteNodeByPointer(localMax, tree);
    }
}

void findAndDelete(int value, Node* node, Tree* tree)
{
    if (value > node->value)
    {
        if (node->rightChild != NULL)
        {
            findAndDelete(value, node->rightChild, tree);
        }
    }
    else if (value < node->value)
    {
        if (node->leftChild != NULL)
        {
            findAndDelete(value, node->leftChild, tree);
        }
    }
    else if (value == node->value)
    {
        deleteNodeByPointer(node, tree);
        return;
    }
    updateHeight(node);
    balance(node, tree);
}

void delete(Tree* tree, int value)
{
    /* search for a node with a giving
     * value and deleting it */

    if (isEmpty(tree))
    {
        return;
    }
    findAndDelete(value, tree->root, tree);
}

Node* findNodeWithValue(int value, Node* node, Tree* tree)
{
    /* Search for a specific
     * value in the tree.
     * If it is found, then returns
     * a pointer to the node with this value */
    Node* output = NULL;
    if (value > node->value)
    {
        if (node->rightChild != NULL)
        {
            output = findNodeWithValue(value, node->rightChild, tree);
        }
    }
    else if (value < node->value)
    {
        if (node->leftChild != NULL)
        {
            output = findNodeWithValue(value, node->leftChild, tree);
        }
    }
    else
    {
        output = node;
    }
    return output;
}

bool isInTree(Tree* tree, int value)
{
    /* return true if value contains in the tree
     * false - if it's not */
    if (isEmpty(tree) || (tree == NULL))
    {
        return false;
    }
    if (findNodeWithValue(value, tree->root, tree) != NULL)
    {
        return true;
    }
    return false;
}

void printSubTreeInAscendingOrder(Node* node)
{
    if (node->leftChild != NULL)
    {
        printSubTreeInAscendingOrder(node->leftChild);
    }
    printf("%d ", node->value);
    if (node->rightChild != NULL)
    {
        printSubTreeInAscendingOrder(node->rightChild);
    }
}

void printInAscendingOrder(Tree* tree)
{
    if (isEmpty(tree))
    {
        printf("{}");
    }
    printf("{ ");
    printSubTreeInAscendingOrder(tree->root);
    printf("}");
}

void printSubTreeInDescendingOrder(Node* node)
{
    if (node->rightChild != NULL)
    {
        printSubTreeInDescendingOrder(node->rightChild);
    }
    printf("%d ", node->value);
    if (node->leftChild != NULL)
    {
        printSubTreeInDescendingOrder(node->leftChild);
    }
}

void printInDescendingOrder(Tree* tree)
{
    if (isEmpty(tree))
    {
        printf("{}");
        return;
    }
    printf("{ ");
    printSubTreeInDescendingOrder(tree->root);
    printf("}");
}


void printSubTreeInRecurentOrder(Node* node)
{
    printf("(%d ", node->value);
    if (node->leftChild != NULL)
    {
        printSubTreeInRecurentOrder(node->leftChild);
    }
    else
    {
        printf("null ");
    }

    if (node->rightChild != NULL)
    {
        printSubTreeInRecurentOrder(node->rightChild);
    }
    else
    {
        printf("null");
    }
    printf(") ");
}

void printInRecurentOrder(Tree* tree)
{
    /* calls a recurent function
     * print sub tree for a root */
    if (isEmpty(tree))
    {
        printf("()");
        return;
    }
    printSubTreeInRecurentOrder(tree->root);
}

void burnTheTree(Tree* tree)
{
    while (!isEmpty(tree))
    {
        deleteNodeByPointer(tree->root, tree);
    }
    if (tree != NULL)
    {
        free(tree);
    }
}