#include <stdio.h>

int getFibonacciNumber(int number)
{
    // f0 = 0 f1 = 1
    int firstNumber = 0;
    int secondNumber = 1;
    int tempNumber = 0;
    for (int i = 0; i < number; i++)
    {
        tempNumber = firstNumber;
        firstNumber = secondNumber;
        secondNumber += tempNumber;
    }
    return firstNumber;
}

int main() {
    for (int i = 0; i < 15; i++)
    {
        printf("%d\n", getFibonacciNumber(i));
    }
    return 0;
}