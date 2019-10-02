#include <stdio.h>
#include <limits.h>

const int maxSize = 10000;

int main() {
    int array[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        array[i] = 0;
    }
    int arrayLength = 0;

    printf("Enter the length of the array:\n");
    scanf("%d", &arrayLength);
    printf("Enter the array:\n");
    for(int i = 0; i < arrayLength; i++)
    {
        scanf("%d", &array[i]);
    }

    int singleMaximum = INT_MIN;
    int multipleMaximum = INT_MIN;

    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] > singleMaximum)
        {
            singleMaximum = array[i];
        }
        else if (array[i] == singleMaximum)
        {
            multipleMaximum = singleMaximum;
        }
    }

    if (multipleMaximum != INT_MIN)
    {
        printf("Answer: %d", multipleMaximum);
    }
    else
    {
        printf("There is not a single maximum in the array that occurs more than once");
    }
    return 0;
}