#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Enter the length of the array:\n");
    int arrayLength = 0;
    scanf("%d", &arrayLength);

    int* array = malloc(sizeof(int) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        array[i] = 0;
    }

    printf("Enter the array:\n");
    for (int i = 0; i < arrayLength; i++)
    {
        scanf(" %d", &array[i]);
    }

    for (int i = arrayLength - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if ((array[j] == 0) && (array[j + 1] != 0))
            {
                array[j] = array[j + 1];
                array[j + 1] = 0;
            }
        }
    }

    printf("Answer:\n");
    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}