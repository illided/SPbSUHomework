#pragma once

#include <stdbool.h>

struct Graph;

typedef struct Graph Graph;

Graph* createGraph();
void deleteGraph(Graph* graph);
void addToGraph(Graph* graph, int key);
void setConnection(Graph* graph, int firstKey, int secondKey);
bool isInGraph(Graph* graph, int key);
bool areConnected(Graph* graph, int firstKey, int secondKey);