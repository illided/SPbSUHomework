#include <stdio.h>

int main()
{
    int number = 0;

    printf("Enter the number:\n");
    scanf("%d", &number);

    int numerals[10] = {0};

    while (number > 0)  // counting how many of every digit there are in a number
    {
        numerals[number % 10]++;
        number = number / 10;
    }

    int result = 0;

    /* if there are some zeros in the initial number then lets put at the
     * first position the smallest digit
     * and then all the zeros. */

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

    // Continue (or starting) building the number after that

    int digitNumber = 0;

    while (digitNumber != 9)
    {
        while ((numerals[digitNumber] == 0) && (digitNumber != 9))
        {
            digitNumber++;
        }

        /* Taking the smallest digits that we still have
         * and building the number. */

        while(numerals[digitNumber] != 0)
        {
            result = result * 10 + digitNumber;
            numerals[digitNumber]--;
        }
    }

    printf("Answer:\n%d", result);
    return 0;
}