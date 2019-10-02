#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printSplitting(int *array, int number)
{
    int firstDigit = true;
    for (int currentlyPrinting = 1; currentlyPrinting <= number; currentlyPrinting++)
    {
        int numOfPrintedDigits = 0;
        while (numOfPrintedDigits != array[currentlyPrinting])
        {
            if (firstDigit)
            {
                printf("%d", currentlyPrinting);
                firstDigit = false;
            }
            else
            {
                printf(" + %d", currentlyPrinting);
            }
            numOfPrintedDigits++;
        }
    }
    printf(" = %d\n", number);
}

int main() {
    int number = 0;
    printf("Enter the number: \n");
    scanf("%d", &number);

    if (number <= 0)
    {
        printf("The number cannot be represented as the sum of the natural terms");
        return 0;
    }

    int *array = malloc((number + 1) * sizeof(int));
    for (int i = 0; i < number + 1; i++)
    {
        array[i] = 0;
    }

    printf("It's splittings:\n");

    while (array[number] != 1)
    {
        array[1]++;
        int j = 1;
        while ((array[j] >= number / j) && (array[1] != number))
        {
            array[j] = 0;
            j++;
        }

        if (j != 1)
        {
            array[j]++;
        }

        int currentSum = 0;
        for (int digit = 1; digit <= number; digit++)
        {
            currentSum += array[digit] * digit;
        }

        if (currentSum == number)
        {
            printSplitting(array, number);
        }
    }
    return 0;
}