#include <stdio.h>
#include <stdlib.h>

void swap(int* firstNumber, int* secondNumber)
{
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

void siftUp(int index, int* heap)
{
    while ((index >= 0) && (heap[index] > heap[(index - 1) / 2]))
    {
        swap(&heap[index], &heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void siftDown(int index, int heapSize, int* heap)
{
    int maxIndex = index;
    int leftChild = 2 * index + 1;
    if ((leftChild < heapSize) && heap[leftChild] > heap[maxIndex])
    {
        maxIndex = leftChild;
    }
    int rightChild = 2 * index + 2;
    if((rightChild < heapSize) && heap[rightChild] > heap[maxIndex])
    {
        maxIndex = rightChild;
    }
    if (index != maxIndex)
    {
        swap(&heap[index], &heap[maxIndex]);
        siftDown(maxIndex, heapSize, heap);
    }
}

int extractMax(int heapSize, int* heap)
{
    int result = heap[0];
    heap[0] = heap[heapSize - 1];
    siftDown(0, heapSize - 1, heap);
    return result;
}

int main() {
    printf("Enter the length of the array:\n");
    int heapSize = 0;
    scanf("%d", &heapSize);

    int *heap = malloc(sizeof(int) * heapSize);
    printf("Enter the array:\n");
    for (int i = 0; i < heapSize; i++)
    {
        scanf("%d", &heap[i]);
    }

    for (int i = heapSize - 1; i > 0; i--)
    {
        siftUp(i, heap);
    }

   printf("Sorted array:\n");
   for (int i = heapSize - 1; i >= 0; i--)
   {
       printf("%d ", heap[i]);
   }
   free(heap);
   return 0;
}