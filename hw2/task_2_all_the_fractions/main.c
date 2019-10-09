#include <stdio.h>
#include <stdlib.h>

struct Fraction  // i think its much elegant to use a structure instead of two arrays;
{
    int numerator;
    int denominator;
};

typedef struct Fraction Fraction;

void addFraction(int numerator, int denominator, Fraction* fraction)
{
    fraction->numerator = numerator;
    fraction->denominator = denominator;
}

void printFractions(Fraction* arrayOfFractions, int arrayLength, int step)
{
    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d/%d ", arrayOfFractions[i].numerator, arrayOfFractions[i].denominator);
        if (i % step == 0)  // going to the next line every (step) fraction to add some readability;
        {
            printf("\n");
        }
    }
}

int main()
{
    /* This solution uses a series of Faroese, in which each next fraction is
       obtained with the help of some manipulations over the previous two:

       if we already have two fractions a / b and c / d in the sequence,
       then the third fraction p / q is calculated as
       p = round ((n + b) / d) * c - a
       q = round ((n + b) / d) * d - b   */

    int maxDenominator = 0;
    printf("Enter the n (n - is a natural number):\n");
    scanf("%d", &maxDenominator);
    if (maxDenominator <= 0)
    {
        printf("incorrect input");
        return 0;
    }

    int arraySize = 5;
    Fraction* arrayOfFractions = malloc(sizeof(Fraction) * arraySize);  // creating the array of all fractions
    addFraction(0, 1, &arrayOfFractions[0]);
    addFraction(1, maxDenominator, &arrayOfFractions[1]);

    /* The first two fractions should be 0/1 and 1/n since they
    are obviously the smallest and the last will be 1/1. */

    if (maxDenominator == 1)  // in case n = 1 answer will be 0/1 and 1/1
    {
        printf("All the simple fractions with the denominator less than %d:\n", maxDenominator);
        printFractions(arrayOfFractions, 2, 5);
        return 0;
    }

    int arrayLength = 2;
    int numerator = 0;
    int denominator = 0;

    do  // start creating the sequence
    {
        if (arrayLength == arraySize)  // adding more space if needed
        {
            arraySize += 5;
            arrayOfFractions = realloc(arrayOfFractions, sizeof(Fraction) * arraySize);
        }
        numerator = (maxDenominator + arrayOfFractions[arrayLength - 2].denominator) /
                arrayOfFractions[arrayLength - 1].denominator * arrayOfFractions[arrayLength - 1].numerator -
                arrayOfFractions[arrayLength - 2].numerator;  // = p

        denominator = (maxDenominator + arrayOfFractions[arrayLength - 2].denominator) /
                arrayOfFractions[arrayLength - 1].denominator * arrayOfFractions[arrayLength - 1].denominator -
                arrayOfFractions[arrayLength - 2].denominator;  // = q

        addFraction(numerator, denominator, &arrayOfFractions[arrayLength]);  // adding p/q
        arrayLength++;
    }
    while (arrayOfFractions[arrayLength - 1].denominator != 1);

    /*Also there will be only two fractions with the denominator 1
     and there is no point to check the numerator of the last fraction*/

    printf("All the simple fractions with the denominator less than %d:\n", maxDenominator);
    printFractions(arrayOfFractions, arrayLength, 5);

    free(arrayOfFractions);
    return 0;
}