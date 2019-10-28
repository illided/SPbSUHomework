#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int maxBinaryNumLength = 32;

int raiseToThePower(int number, int power)
{
    if (power == 0)
    {
        return 1;
    }
    if (power % 2 == 0)
    {
        int squareRootOfTargetNumber = raiseToThePower(number, power / 2);
        return squareRootOfTargetNumber * squareRootOfTargetNumber;
    }
    return number * raiseToThePower(number, power - 1);
}

short int* getSumOfBinaries(short int* firstNumber, short int* secondNumber)
{
    short int buffer = 0;
    short int* result = malloc(sizeof(short int) * (maxBinaryNumLength));
    for (int i = 0; i < maxBinaryNumLength; i++)
    {
        result[i] = 0;
    }

    /* Algorithm beneath says:
     * for every digit (from last position to first)
     * sum 2 digit and a buffer (something that we usually "keep in mind")
     * then if we got 0 or 1 - ok
     * if we got a 2 than result = 0 and buffer = 1
     * if we got a 3 than result = 1 and buffer = 1 */

    for (int i = maxBinaryNumLength - 1; i >= 0; i--)
    {
        result[i] = firstNumber[i] + secondNumber[i] + buffer;
        buffer = result[i] / 2;
        result[i] = result[i] % 2;
    }

    return result;
}

short int* convertFromDecToBinary(int number)
{
    short int* numberInBinary = malloc(sizeof(short int) * (maxBinaryNumLength));
    for (int i = 0; i < maxBinaryNumLength; i++)
    {
        numberInBinary[i] = 0;
    }

    /* Checks if the number is negative
     * and if it is a negative than multiplying it
     * by 2 and keeping this in mind */

    bool numberIsNegative = (number < 0);
    if (numberIsNegative)
    {
        number *= -1;
    }

    int numLen = 0;
    while (number != 0)
    {
        numberInBinary[maxBinaryNumLength - 1 - numLen] = number % 2 + 0;
        numLen++;
        number = number / 2;
    }

    /* If previous check for negativity
     * was true than we need to transfer the number
     * to an "additional code"
     * (replace 0 by 1, 1 by 0 and add 1) */
    if (numberIsNegative)
    {
        for (int i = 0; i < maxBinaryNumLength; i++)
        {
            numberInBinary[i] = 1 - numberInBinary[i];
        }
        /* This horror was added to prevent memory leaks */
        short int* one = convertFromDecToBinary(1);
        short int* negativeNumberInBinary = getSumOfBinaries(numberInBinary, one);
        free(numberInBinary);
        free(one);
        return negativeNumberInBinary;
    }
    return numberInBinary;
}

int convertFromBinToDec(short int* numberInBinary)
{
    int numberInDec = 0;
    bool numberIsNegative = false;
    /* If the number is negative, then it needs
     * some preparation (you need to replace 0 with 1,
     * 1 with 0 and subtract one) */
    if (numberInBinary[0] == 1)
    {
        numberIsNegative = true;
        short int* minusOne = convertFromDecToBinary(-1);
        short int* pointerToBinaryNumber = numberInBinary;
        numberInBinary = getSumOfBinaries(numberInBinary, minusOne);
        free(pointerToBinaryNumber);
        free(minusOne);

        for (int i = 0; i < maxBinaryNumLength; i++)
        {
            numberInBinary[i] = 1 - numberInBinary[i];
        }
    }

    /* Converting a POSITIVE binary to decimal */
    for (int i = 0; i < maxBinaryNumLength; i++)
    {
        numberInDec += (int)numberInBinary[i] * raiseToThePower(2, maxBinaryNumLength - i - 1);
    }

    /* Multiplying it by -1 if it was negative */
    if (numberIsNegative)
    {
        numberInDec *= -1;
    }

    return numberInDec;
}

void printBinary(short int* binaryNumber)
{
    for (int i = 1; i <= maxBinaryNumLength; i++)
    {
        printf("%hi", binaryNumber[i - 1]);
        if (i % 8 == 0)
        {
            printf(" ");
        }
    }
}

int main() {
    printf("Enter two numbers:\n");
    int firstNumber = 0;
    int secondNumber = 0;
    scanf("%d %d", &firstNumber, &secondNumber);

    short int* firstNumberInBinary = convertFromDecToBinary(firstNumber);
    short int* secondNumberInBinary = convertFromDecToBinary(secondNumber);
    printf("First number in binary:  ");
    printBinary(firstNumberInBinary);
    printf("\n");
    printf("Second number in binary: ");
    printBinary(secondNumberInBinary);
    printf("\n");

    short int* sum = getSumOfBinaries(firstNumberInBinary, secondNumberInBinary);
    printf("Their sum (in binary):   ");
    printBinary(sum);

    printf("\nTheir sum (in dec): %d", convertFromBinToDec(sum));

    free(sum);
    free(firstNumberInBinary);
    free(secondNumberInBinary);
    return 0;
}