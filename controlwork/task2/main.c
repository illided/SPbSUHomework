#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *firstNumber, int *secondNumber)
{
    int temp = *secondNumber;
    *secondNumber = *firstNumber;
    *firstNumber = temp;
}

int* scanArray(int* globalArrayLength)
{
    int input = 0;
    int arraySize = 5;
    int* array = malloc(sizeof(int) * arraySize);
    int localArrayLength = 0;
    scanf("%d", &input);
    while (input != 0)
    {
        array[localArrayLength] = input;
        localArrayLength++;
        if (localArrayLength == arraySize)
        {
            arraySize += 5;
            array = realloc(array, sizeof(int) * arraySize);
        }
        scanf("%d", &input);
    }
    *globalArrayLength = localArrayLength;
    return array;
}

int *createRandomArray(int arrayLength)
{
    srand(time(NULL));
    int *array = malloc(sizeof(int) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        array[i] = 11 + rand() % 32;
    }
    return array;
}

int main() {
    printf("Should array be random ot to be scanned (r - random / s - scanned)?\n");
    char theWayOfOperating = ' ';
    scanf("%c", &theWayOfOperating);
    int arrayLength = 0;
    int* array = NULL;
    if (theWayOfOperating == 's')
    {
        printf("Enter the array:\n");
        array = scanArray(&arrayLength);
    }
    else if (theWayOfOperating == 'r')
    {
        printf("Enter the length of the random array:\n");
        scanf("%d", &arrayLength);
        array = createRandomArray(arrayLength);
    }
    else
    {
        printf("Incorrect input\n");
        return 0;
    }

    if (arrayLength >= 3)
    {

        for (int i = 0; i <= (arrayLength - 1) - ((arrayLength - 1) % 2) - 2 ; i += 2)
        {
            for (int j = i + 2; j <= (arrayLength - 1) - ((arrayLength - 1) % 2); j += 2)
            {
                if (array[i] > array[j])
                {
                    swap(&array[i], &array[j]);
                }
            }
        }
    }

    printf("Answer:\n");
    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d ", array[i]);
    }
    free(array);
}