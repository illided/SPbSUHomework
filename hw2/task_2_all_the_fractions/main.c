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

int main()
{
    /* This solution uses a series of Faroese, in which each next fraction is
       obtained with the help of some manipulations over the previous two:

       if we already have two fractions a / b and c / d in the sequence,
       then the third fraction p / q is calculated as
       p = round ((n + b) / d) * c - a
       q = round ((n + b) / d) * d - b

       This series is very similar to Fibonacci's numbers.
       It means that we dont need to store all the fractions
       but only two of them at a time. */

    int maxDenominator = 0;
    printf("Enter the n (n - is a natural number):\n");
    scanf("%d", &maxDenominator);
    if (maxDenominator <= 0)
    {
        printf("incorrect input");
        return 0;
    }

    printf("All the simple fractions between 0 and 1 with the denominator less than %d:\n", maxDenominator);

    Fraction* arrayOfFractions = malloc(sizeof(Fraction) * 2);  // creating the array of two fractions
    addFraction(0, 1, &arrayOfFractions[0]);
    addFraction(1, maxDenominator, &arrayOfFractions[1]);
    printf("%d/%d\n", arrayOfFractions[0].numerator, arrayOfFractions[0].denominator);
    printf("%d/%d\n", arrayOfFractions[1].numerator, arrayOfFractions[1].denominator);

    /* The first two fractions should be 0/1 and 1/n since they
    are obviously the smallest and the last will be 1/1. */

    if (maxDenominator == 1)  // in case n = 1 answer will be 0/1 and 1/1
    {
        return 0;
    }

    int numerator = 0;
    int denominator = 0;

    do  // start creating the sequence
    {
        numerator = (maxDenominator + arrayOfFractions[0].denominator) /
                arrayOfFractions[1].denominator * arrayOfFractions[1].numerator -
                arrayOfFractions[0].numerator;  // = p

        denominator = (maxDenominator + arrayOfFractions[0].denominator) /
                arrayOfFractions[1].denominator * arrayOfFractions[1].denominator -
                arrayOfFractions[0].denominator;  // = q

        addFraction(arrayOfFractions[1].numerator, arrayOfFractions[1].denominator, &arrayOfFractions[0]);  // setting second fraction to first position
        addFraction(numerator, denominator, &arrayOfFractions[1]);  // adding p/q
        printf("%d/%d\n", arrayOfFractions[1].numerator, arrayOfFractions[1].denominator);  // printing
    }
    while (arrayOfFractions[1].denominator != 1);

    /*Also there will be only two fractions with the denominator 1
     and there is no point to check the numerator of the last fraction*/

    free(arrayOfFractions);
    return 0;
}