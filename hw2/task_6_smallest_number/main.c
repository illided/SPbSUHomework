#include <stdio.h>
#include <math.h>

#define MAXSIZE 1000

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


int main()
{
    int numerals[MAXSIZE] = {0};
    int numLength = 0;
    int number = 0;

    printf("Enter the number:\n");
    scanf("%d", &number);

    while (number > 0)
    {
        numerals[numLength] = number % 10;
        number = number / 10;
        numLength++;
    }

    quickSort(0, numLength - 1, numerals);

    int result = 0;
    int i = 0;

    while (numLength > 0)
    {
        numLength--;
        result += numerals[numLength] * pow(10, i);
        i++;
    }

    printf("Answer:\n%d", result);
}