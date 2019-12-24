#include <stdlib.h>
#include "priorityQueue.h"
#include <stdio.h>

const int initialSize = 10;

struct queueElement
{
    int value;
    int priority;
};

typedef struct queueElement queueElement;

struct PriorityQueue
{
    int size;
    int length;
    queueElement** array;
};

PriorityQueue* createQueue()
{
    PriorityQueue* newQueue = malloc(sizeof(PriorityQueue));
    newQueue->size = initialSize;
    newQueue->length = 0;
    newQueue->array = malloc(sizeof(queueElement*) * newQueue->size);
    for (int i = 0; i < initialSize; i++)
    {
        newQueue->array[i] = NULL;
    }
    return newQueue;
}

queueElement* createQueueElement(int value, int priority)
{
    queueElement* newElement = malloc(sizeof(queueElement));
    newElement->value = value;
    newElement->priority = priority;
    return newElement;
}

void extendQueue(PriorityQueue* queue, int newSize)
{
    if (queue->size > newSize)
    {
        return;
    }
    queue->array = realloc(queue->array, sizeof(queueElement*) * newSize);
    for (int i = queue->size; i < newSize; i++)
    {
        queue->array[i] = NULL;
    }
}

void swap(queueElement* firstElement, queueElement* secondElement)
{
    queueElement temp = *firstElement;
    *firstElement = *secondElement;
    *secondElement = temp;
}

void siftUp(int index, PriorityQueue* queue)
{
    while ((index >= 0) && (queue->array[index]->priority > queue->array[(index - 1) / 2]->priority))
    {
        swap(queue->array[index], queue->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

bool isInQueue(PriorityQueue* queue, int value)
{
    if (queue == NULL)
    {
        return false;
    }
    for (int i = 0; i < queue->length; i++)
    {
        if (queue->array[i]->value == value)
        {
            return true;
        }
    }
    return false;
}

void enqueue(PriorityQueue* queue, int value, int priority)
{
    if (queue == NULL || isInQueue(queue, value))
    {
        return;
    }
    queue->array[queue->length] = createQueueElement(value, priority);
    siftUp(queue->length, queue);
    queue->length++;
    if (queue->length == queue->size)
    {
        queue->size *= 2;
        extendQueue(queue, queue->size);
    }
}

void siftDown(int index, PriorityQueue* queue)
{
    int maxIndex = index;
    int leftChild = 2 * index + 1;
    if ((leftChild < queue->length) && queue->array[leftChild]->priority > queue->array[maxIndex]->priority)
    {
        maxIndex = leftChild;
    }
    int rightChild = 2 * index + 2;
    if ((rightChild < queue->length) && queue->array[rightChild]->priority > queue->array[maxIndex]->priority)
    {
        maxIndex = rightChild;
    }
    if (index != maxIndex)
    {
        swap(queue->array[index], queue->array[maxIndex]);
        siftDown(maxIndex, queue);
    }
}

int dequeue(PriorityQueue* queue)
{
    if (queue == NULL || queue->length == 0)
    {
        return -1;
    }
    int result = queue->array[0]->value;
    free(queue->array[0]);
    queue->array[0] = queue->array[queue->length - 1];
    siftDown(0, queue);
    queue->length--;
    return result;
}

void printQueue(PriorityQueue* queue)
{
    if (queue == NULL || queue->length == 0)
    {
        printf("()\n");
        return;
    }
    for (int i = 0; i < queue->length; i++)
    {
        printf("(%d %d)\n", queue->array[i]->priority, queue->array[i]->value);
    }
}

void deleteQueue(PriorityQueue* queue)
{
    for (int i = 0; i < queue->length; i++)
    {
        if (queue->array[i] != NULL)
        {
            free(queue->array[i]);
        }
    }
    free(queue->array);
    free(queue);
}