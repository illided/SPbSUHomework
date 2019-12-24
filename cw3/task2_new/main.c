#include <stdio.h>
#include "priorityQueue.h"

int main()
{
    PriorityQueue* newQueue = createQueue();
    enqueue(newQueue,14, 9);
    enqueue(newQueue,45, 8);
    enqueue(newQueue,3, 7);
    enqueue(newQueue,6, 10);
    enqueue(newQueue,7, 13);
    enqueue(newQueue,12, 1);
    enqueue(newQueue,78, 5);
    printQueue(newQueue);
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", dequeue(newQueue));
    }
    deleteQueue(newQueue);
    return 0;
}
