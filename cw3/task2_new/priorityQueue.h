#pragma once

#include <stdbool.h>

struct PriorityQueue;
typedef struct PriorityQueue PriorityQueue;

PriorityQueue* createQueue();
void printQueue(PriorityQueue* queue);
bool isInQueue(PriorityQueue* queue, int value);
void enqueue(PriorityQueue* queue, int value, int priority);
int dequeue(PriorityQueue* queue);
void deleteQueue();