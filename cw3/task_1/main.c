#include <stdio.h>
#include <stdlib.h>

int* readZeroTerminatedArrayOfInt(int* outputLength)
{
    int outputSize = 10;
    int* output = malloc(sizeof(int) * outputSize);
    int input = 0;
    scanf("%d", &input);
    while (input != 0)
    {
        if (*outputLength == outputSize)
        {
            outputSize *= 2;
            output = realloc(output, sizeof(int) * outputSize);
        }
        output[*outputLength] = input;
        scanf("%d", &input);
        (*outputLength)++;
    }
    return output;
}

void quickSort(int left, int right, int array[])
{
    int arrayLength = right - left + 1;
    int middle = array[arrayLength / 2 + left];
    int leftPointer = left;
    int rightPointer = right;

    if (right < left)
    {
        return;
    }

    do
    {
        while (array[leftPointer] < middle)
        {
            leftPointer++;
        }
        while (array[rightPointer] > middle)
        {
            rightPointer--;
        }
        if (leftPointer <= rightPointer)
        {
            int temp = array[leftPointer];
            array[leftPointer] = array[rightPointer];
            array[rightPointer] = temp;
            leftPointer++;
            rightPointer--;
        }
    } while (leftPointer <= rightPointer);

    quickSort(left, rightPointer, array);
    quickSort(leftPointer, right, array);
}

int main()
{
    int arrayLength = 0;
    int* array = readZeroTerminatedArrayOfInt(&arrayLength);
    quickSort(0, arrayLength - 1, array);
    int currentDigit = 0;
    int numOfReiteration = 1;
    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] != currentDigit)
        {
            if (currentDigit != 0)
            {
                printf("%d\n", numOfReiteration);
            }
            currentDigit = array[i];
            printf("%d: ", currentDigit);
            numOfReiteration = 1;
        }
        else
        {
            numOfReiteration++;
        }
    }
    printf("%d", numOfReiteration);
    free(array);
    return 0;
}
