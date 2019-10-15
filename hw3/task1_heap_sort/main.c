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
    int arrayLength = 0;
    scanf("%d", &arrayLength);

    int *array = malloc(sizeof(int) * arrayLength);
    printf("Enter the array:\n");
    for (int i = 0; i < arrayLength; i++)
    {
        scanf("%d", &array[i]);
    }

    int *heap = malloc(sizeof(int) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        heap[i] = array[i];
        siftUp(i, heap);
    }

    for (int heapSize = arrayLength; heapSize > 0; heapSize--)
    {
        array[heapSize - 1] = extractMax(heapSize, heap);
    }

    printf("Sorted array:\n");
    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d ", array[i]);
    }

    free(heap);
    free(array);
    return 0;
}