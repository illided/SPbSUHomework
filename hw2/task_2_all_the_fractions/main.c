#include <stdio.h>

int greatestCommonFactor(int a, int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    return a;
}

int main() {
    int maxDenominator = 0;

    printf("Enter the n:\n");
    scanf("%d", &maxDenominator);

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