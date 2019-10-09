#include <stdio.h>
#include <stdlib.h>

int *createArrayOfInt(int arrayLength)
{
    int *arrayOfInt = malloc(sizeof(int) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        arrayOfInt[i] = 0;
    }
    return arrayOfInt;
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

    quickSort(left, rightPointer , array);
    quickSort(leftPointer, right, array);
}

int main() {
    /* This solution is sorting the array
     * and then looking for two
     * equal numbers closest to the end.
     * if such numbers are not found, then there
     * are no numbers in the array that are repeated. */

    printf("Enter the length of the array:\n");  // scanning the array
    int arrayLength = 0;
    scanf("%d", &arrayLength);
    printf("Enter the array:\n");
    int *array = createArrayOfInt(arrayLength);
    for (int i = 0; i <arrayLength; i++)
    {
        scanf("%d", &array[i]);
    }

    quickSort(0, arrayLength - 1, array);  // sorting it

    int pointer = arrayLength - 1;
    for (; (pointer > 0) && (array[pointer] != array[pointer - 1]); pointer--);  // finding the biggest repetitive

    if (pointer == 0)
    {
        printf("there are no numbers in the array that are repeated");
        return 0;
    }

    printf("The biggest repetitive number:\n%d", array[pointer]);

    free(array);
    return 0;
}