#include "graph.h"
#include <stdlib.h>

struct Vertex
{
    int key;
    struct VertexList* neighbors;
    bool isChecked;
};

struct VertexListElement
{
    struct Vertex* vertex;
    struct VertexListElement* nextElement;
};

struct VertexList
{
    struct VertexListElement* head;
};

struct Graph
{
    struct VertexList* vertices;
};

typedef struct VertexList VertexList;
typedef struct VertexListElement VertexListElement;
typedef struct Vertex Vertex;

VertexListElement* createVertexListElement(Vertex* vertex)
{
    VertexListElement* newElement = malloc(sizeof(VertexListElement));
    newElement->vertex = vertex;
    newElement->nextElement = NULL;
    return newElement;
}

VertexList* createVertexList()
{
    VertexList* newVertexList = malloc(sizeof(VertexList));
    newVertexList->head = NULL;
    return newVertexList;
}

Vertex* createVertex(int key)
{
    Vertex* newVertex = malloc(sizeof(Vertex));
    newVertex->key = key;
    newVertex->neighbors = createVertexList();
    newVertex->isChecked = false;
    return newVertex;
}

Graph* createGraph()
{
    Graph* newGraph = malloc(sizeof(Graph));
    newGraph->vertices = createVertexList();
    return newGraph;
}

void deleteVertexList(VertexList* vertexList)
{
    if (vertexList == NULL)
    {
        return;
    }
    VertexListElement* pointer = vertexList->head;
    VertexListElement* deleted = NULL;
    while (pointer != NULL)
    {
        deleted = pointer;
        pointer = pointer->nextElement;
        free(deleted);
    }
    free(vertexList);
}

void deleteGraph(Graph* graph)
{
    if (graph == NULL)
    {
        return;
    }
    VertexListElement* pointer = graph->vertices->head;
    while (pointer != NULL)
    {
        deleteVertexList(pointer->vertex->neighbors);
        free(pointer->vertex);
        pointer = pointer->nextElement;
    }
    deleteVertexList(graph->vertices);
    free(graph);
}

void addToVertexList(VertexList* vertexList, Vertex* vertex)
{
    if (vertexList->head == NULL)
    {
        vertexList->head = createVertexListElement(vertex);
    }
    else
    {
        VertexListElement* pointer = vertexList->head;
        while (pointer->nextElement != NULL)
        {
            pointer = pointer->nextElement;
        }
        pointer->nextElement = createVertexListElement(vertex);
    }
}

void addToGraph(Graph* graph, int key)
{
    if (graph != NULL && !isInGraph(graph, key))
    {
        addToVertexList(graph->vertices, createVertex(key));
    }
}

Vertex* findVertex(Graph* graph, int key)
{
    if (graph == NULL)
    {
        return NULL;
    }
    VertexListElement* pointer = graph->vertices->head;
    while (pointer != NULL)
    {
        if (pointer->vertex->key == key)
        {
            return pointer->vertex;
        }
        pointer = pointer->nextElement;
    }
    return NULL;
}

bool isInGraph(Graph* graph, int key)
{
    return findVertex(graph, key) != NULL;
}

void setConnection(Graph* graph, int firstKey, int secondKey)
{
    if (graph == NULL)
    {
        return;
    }
    Vertex* firstVertex = findVertex(graph, firstKey);
    Vertex* secondVertex = findVertex(graph, secondKey);
    if (firstVertex != NULL && secondVertex != NULL)
    {
        addToVertexList(firstVertex->neighbors, secondVertex);
        addToVertexList(secondVertex->neighbors, firstVertex);
    }
}

bool depthFirstSearch(Vertex* firstVertex, Vertex* secondVertex)
{
    if (firstVertex == secondVertex)
    {
        return true;
    }
    firstVertex->isChecked = true;
    VertexListElement* pointer = firstVertex->neighbors->head;
    while (pointer != NULL)
    {
        if ((!pointer->vertex->isChecked) && depthFirstSearch(pointer->vertex, secondVertex))
        {
            return true;
        }
        pointer = pointer->nextElement;
    }
    return false;
}

bool areConnected(Graph* graph, int firstKey, int secondKey)
{
    if (graph == NULL)
    {
        return false;
    }
    Vertex* firstVertex = findVertex(graph, firstKey);
    Vertex* secondVertex = findVertex(graph, secondKey);
    bool connectionExist = false;
    if (firstVertex == NULL || secondVertex == NULL)
    {
        return false;
    }
    else
    {
         connectionExist = depthFirstSearch(firstVertex, secondVertex);
         VertexListElement* pointer = graph->vertices->head;
         while (pointer != NULL)
         {
             pointer->vertex->isChecked = false;
             pointer = pointer->nextElement;
         }
        return connectionExist;
    }
}