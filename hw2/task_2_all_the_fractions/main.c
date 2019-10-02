#include <stdio.h>

int greatestCommonFactor(int firstNumber, int secondNumber)
{
    while (firstNumber != secondNumber)
    {
        if (firstNumber > secondNumber)
        {
            firstNumber = firstNumber - secondNumber;
        }
        else
        {
            secondNumber = secondNumber - firstNumber;
        }
    }
    return firstNumber;
}

int main() {
    int maxDenominator = 0;

    printf("Enter the n:\n");
    scanf("%d", &maxDenominator);
    printf("All simple fractions with denominator less or equal to %d:\n", maxDenominator);

    for (int denominator = 2; denominator <= maxDenominator; denominator++)
    {
        for (int numerator = 1; numerator < denominator; numerator++)
        {
            if (greatestCommonFactor(numerator, denominator) == 1)
            {
                printf("%d/%d ", numerator, denominator);
            }
        }
        printf("\n");
    }
    return 0;
}