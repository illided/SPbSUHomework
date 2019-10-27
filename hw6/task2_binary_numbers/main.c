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

    if (numberIsNegative)
    {
        for (int i = 0; i < maxBinaryNumLength; i++)
        {
            numberInBinary[i] = 1 - numberInBinary[i];
        }
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

    for (int i = 0; i < maxBinaryNumLength; i++)
    {
        numberInDec += (int)numberInBinary[i] * raiseToThePower(2, maxBinaryNumLength - i - 1);
    }

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