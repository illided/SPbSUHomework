#include <stdio.h>

int main()
{
    int number = 0;

    printf("Enter the number:\n");
    scanf("%d", &number);

    int numerals[10] = {0};

    while (number > 0)
    {
        numerals[number % 10]++;
        number = number / 10;
    }

    int result = 0;

    if (numerals[0] != 0)
    {
        int firstDigit = 1;
        while (numerals[firstDigit] == 0)
        {
            firstDigit++;
        }
        numerals[firstDigit]--;
        result += firstDigit;
    }

    int digitNumber = 0;

    while (digitNumber != 9)
    {
        while ((numerals[digitNumber] == 0) && (digitNumber != 9))
        {
            digitNumber++;
        }

        while(numerals[digitNumber] != 0)
        {
            result = result * 10 + digitNumber;
            numerals[digitNumber]--;
        }
    }

    printf("Answer:\n%d", result);
    return 0;
}