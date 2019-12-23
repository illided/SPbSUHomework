#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct Vertex
{
    int key;
    struct VertexList* neighbors;
    bool isChecked;
};

struct VertexListElement
{
    int connectionCost;
    struct Vertex* vertex;
    struct VertexListElement* nextElement;
};

struct VertexList
{
    struct VertexListElement* head;
};

struct Graph
{
    int numOfVertices;
    struct VertexList* vertices;
};

typedef struct VertexList VertexList;
typedef struct VertexListElement VertexListElement;
typedef struct Vertex Vertex;

VertexListElement* createVertexListElement(Vertex* vertex, int connectionCost)
{
    VertexListElement* newElement = malloc(sizeof(VertexListElement));
    newElement->vertex = vertex;
    newElement->connectionCost = connectionCost;
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
    newGraph->numOfVertices = 0;
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

void addToVertexList(VertexList* vertexList, Vertex* vertex, int connectionCost)
{
    if (vertex == NULL)
    {
        return;
    }
    if (vertexList->head == NULL)
    {
        vertexList->head = createVertexListElement(vertex, connectionCost);
    }
    else
    {
        VertexListElement* pointer = vertexList->head;
        while (pointer->nextElement != NULL)
        {
            pointer = pointer->nextElement;
        }
        pointer->nextElement = createVertexListElement(vertex, connectionCost);
    }
}

void addToGraph(Graph* graph, int key)
{
    if (graph != NULL && !isInGraph(graph, key))
    {
        addToVertexList(graph->vertices, createVertex(key), 0);
        graph->numOfVertices++;
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

void setConnection(Graph* graph, int firstKey, int secondKey, int connectionCost)
{
    if (graph == NULL)
    {
        return;
    }
    Vertex* firstVertex = findVertex(graph, firstKey);
    Vertex* secondVertex = findVertex(graph, secondKey);
    if (firstVertex != NULL && secondVertex != NULL)
    {
        addToVertexList(firstVertex->neighbors, secondVertex, connectionCost);
        addToVertexList(secondVertex->neighbors, firstVertex, connectionCost);
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

void clearCheckFlag(Graph* graph)
{
    VertexListElement* pointer = graph->vertices->head;
    while (pointer != NULL)
    {
        pointer->vertex->isChecked = false;
        pointer = pointer->nextElement;
    }
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
        clearCheckFlag(graph);
        return connectionExist;
    }
}

Vertex* findNearestFreeVertex(VertexList* vertexList)
{
    VertexListElement* pointer = vertexList->head;
    VertexListElement* nearestVertexElement = NULL;
    while (pointer != NULL)
    {
        if (!pointer->vertex->isChecked &&
            (nearestVertexElement == NULL || nearestVertexElement->connectionCost > pointer->connectionCost))
        {
            nearestVertexElement = pointer;
        }
        pointer = pointer->nextElement;
    }
    if (nearestVertexElement != NULL)
    {
        nearestVertexElement->vertex->isChecked = true;
        return nearestVertexElement->vertex;
    }
    return NULL;
}

VertexListElement* concatenateVertexList(VertexListElement* lastElement, VertexList* listToConcatenate)
{
    VertexListElement* pointer = listToConcatenate->head;
    while (pointer != NULL)
    {
        lastElement->nextElement = createVertexListElement(pointer->vertex, pointer->connectionCost);
        lastElement = lastElement->nextElement;
        pointer = pointer->nextElement;
    }
    lastElement->nextElement = NULL;
    return lastElement;
}

Vertex** findManyVertices(Graph* graph, const int* keyArray, int keyArrayLength)
{
    Vertex** verticesArray = malloc(sizeof(Vertex*) * keyArrayLength);
    Vertex* newVertex = NULL;
    for (int i = 0; i < keyArrayLength; i++)
    {
        newVertex = findVertex(graph, keyArray[i]);
        if (newVertex == NULL)
        {
            fprintf(stderr, "Capital was not found. Answer may be wrong\n");
            free(verticesArray);
            return NULL;
        }
        verticesArray[i] = newVertex;
        newVertex->isChecked = true;
    }
    return verticesArray;
}

bool prepareClusterMatrix(Graph* graph, VertexList** clusterMatrix, const int* keyArray, int keyArrayLength,
                          VertexListElement** lastElements)
{
    Vertex** capitalsArray = findManyVertices(graph, keyArray, keyArrayLength);
    if (capitalsArray == NULL)
    {
        return false;
    }
    for (int i = 0; i < keyArrayLength; i++)
    {
        clusterMatrix[i] = createVertexList();
        addToVertexList(clusterMatrix[i], capitalsArray[i], 0);
        lastElements[i] = concatenateVertexList(clusterMatrix[i]->head, findVertex(graph, keyArray[i])->neighbors);
    }
    free(capitalsArray);
    return true;
}

void deleteClusterMatrix(VertexList** clusterMatrix, int keyArrayLength)
{
    for (int i = 0; i < keyArrayLength; i++)
    {
        deleteVertexList(clusterMatrix[i]);
    }
    free(clusterMatrix);
}

Graph* getClustering(Graph* graph, const int* keyArray, int keyArrayLength)
{
    if (graph == NULL || keyArray == NULL)
    {
        return NULL;
    }
    Graph* clusteredGraph = createGraph();
    VertexList** clusterMatrix = malloc(sizeof(VertexList*) * keyArrayLength);
    VertexListElement** lastElementsArray = malloc(sizeof(VertexListElement*) * keyArrayLength);
    if (!prepareClusterMatrix(graph, clusterMatrix, keyArray, keyArrayLength, lastElementsArray))
    {
        clearCheckFlag(graph);
        free(clusterMatrix);
        free(lastElementsArray);
        deleteGraph(clusteredGraph);
        return NULL;
    }
    for (int i = 0; i < keyArrayLength; i++)
    {
        addToGraph(clusteredGraph, keyArray[i]);
    }

    int vertexToConnect = graph->numOfVertices - clusteredGraph->numOfVertices;
    Vertex* nearestVertex = NULL;
    int currentCapital = 0;
    while (vertexToConnect != 0)
    {
        nearestVertex = findNearestFreeVertex(clusterMatrix[currentCapital]);
        if (nearestVertex != NULL)
        {
            lastElementsArray[currentCapital] = concatenateVertexList(lastElementsArray[currentCapital],
                                                                      nearestVertex->neighbors);
            addToGraph(clusteredGraph, nearestVertex->key);
            setConnection(clusteredGraph, nearestVertex->key, keyArray[currentCapital], 0);
            vertexToConnect--;
        }
        currentCapital = (currentCapital + 1) % keyArrayLength;
    }

    clearCheckFlag(graph);
    deleteClusterMatrix(clusterMatrix, keyArrayLength);
    free(lastElementsArray);
    return clusteredGraph;
}

void printClustering(Graph* graph, int* keyArray, int arrayLength)
{
    Vertex* capital = NULL;
    VertexListElement* pointer = NULL;
    for (int i = 0; i < arrayLength; i++)
    {
        capital = findVertex(graph, keyArray[i]);
        pointer = capital->neighbors->head;
        printf("Capital: %d\nHis cities:", keyArray[i]);
        while (pointer != NULL)
        {
            printf(" %d", pointer->vertex->key);
            pointer = pointer->nextElement;
        }
        printf("\n");
    }
}