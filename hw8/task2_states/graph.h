#pragma once

#include <stdbool.h>

struct Graph;

typedef struct Graph Graph;

Graph* createGraph();
void deleteGraph(Graph* graph);
void addToGraph(Graph* graph, int key);
void setConnection(Graph* graph, int firstKey, int secondKey, int connectionCost);
bool isInGraph(Graph* graph, int key);
bool areConnected(Graph* graph, int firstKey, int secondKey);
Graph* cluster(Graph* graph, const int* keyArray, int keyArrayLength);
void printClustering(Graph* graph, int* keyArray, int keyArrayLength);