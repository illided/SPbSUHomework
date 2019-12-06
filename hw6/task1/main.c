#include <stdio.h>

int main()
{
    printf("Enter the number:\n");
    double number = 0;
    scanf("%lf", &number);

    unsigned char* pointerToDouble = (unsigned char*) &number;
    int binaryNumber[64];
    int currentBinLength = 0;
    for(int i = 7; i  >= 0; i --)
    {
        unsigned char num = (unsigned) pointerToDouble[i];
        for (int j = sizeof(num) * 8 - 1; j >= 0; --j)
        {
            if (num & (1 << j))
            {
                binaryNumber[currentBinLength] = 1;
            }
            else
            {
                binaryNumber[currentBinLength] = 0;
            }
            currentBinLength++;
        }
    }

    int order = 0;
    for (int i = 1; i < 12; i++)
    {
        order = 2 * order + binaryNumber[i];
    }
    order -= 1023;

    long double mantis = 0;
    for (int i = 63; i >= 12; i--)
    {
        mantis = mantis / 2 + binaryNumber[i];
    }
    mantis = 1 + mantis / 2;

    printf("Result: ")
    if (mantis == 1 && order == -1023)
    {
        printf("0");
        return 0;
    }

    if (binaryNumber[0] == 0)
    {
        printf("+");
    }
    else
    {
        printf("-");
    }

    printf("%.15LF * 2^(%d)", mantis, order);
    return 0;
}