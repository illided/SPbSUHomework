#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

const bool showTheAnswer = true; //change to true if you want the answer to be shown at the start of the game
const int maxSize = 80;

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

char* createString(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

int main() {
    printf("Choose the difficulty (how many digits in the guessed number less than 11):\n");
    int numOfDigits = 0;
    scanf("%d", &numOfDigits);
    if ((numOfDigits <= 0) || (numOfDigits > 10))
    {
        printf("Incorrect input");
        return 0;
    }

    // Creating the answer with non repetitive digits and converting it to string.
    srand(time(NULL));
    int *guessedNumberAsArrayOfInt = malloc(sizeof(int) * numOfDigits);
    guessedNumberAsArrayOfInt[0] = 1 + rand() % 10;
    // Setting the first digit to a non zero term
    for (int i = 1; i < numOfDigits; i++)
    {
        int digit = 0;
        // getting a non repetitive digit
        bool isRepetitive = false;
        do
        {
            isRepetitive = false;
            digit = rand() % 10;
            for (int j = 0; j < i; j++)
            {
                if (guessedNumberAsArrayOfInt[j] == digit)
                {
                    isRepetitive = true;
                    break;
                }
            }
        }
        while (isRepetitive);
        // and adding it to the array
        guessedNumberAsArrayOfInt[i] = digit;
    }

    // converting the array of int to the array of char
    char* guessedNumber = createString(maxSize);
    for (int i = 0; i < numOfDigits; i++)
    {
        sprintf(&guessedNumber[i], "%d", guessedNumberAsArrayOfInt[i]);
    }
    // Deleting the array of int because it doesn't do anything now
    free(guessedNumberAsArrayOfInt);
    guessedNumber[numOfDigits] = '\0';


    if (showTheAnswer)
    {
        printf("Hint: %s\n", guessedNumber);
    }

    int numOfTries = 0;
    int cows = 0;
    int bulls = 0;
    char *guess = createString(maxSize);
    do
    {
        cows = 0;
        bulls = 0;
        scanf("%s", guess);
        int guessLength = strlen(guess);
        for (int guessCharPos = 0; guessCharPos < guessLength; guessCharPos++)
        {
            if (guess[guessCharPos] == guessedNumber[guessCharPos])
            {
                bulls++;
                continue;
            }
            for (int guessNumberCharPos = 0; guessNumberCharPos < numOfDigits; guessNumberCharPos++)
            {
                char charToCheck = guess[guessCharPos];
                if (charToCheck == guessedNumber[guessNumberCharPos])
                {
                    cows++;
                }
            }
        }
        printf("Bulls:%d Cows:%d\n", bulls, cows);
        numOfTries++;

        /*  Algorithm above says:
        * Check for every digit in the guess:
        * if on the same checked place the guessed number
        * and assumption have the same digit then add one bull.
        * Otherwise, check each element
        * in the guessed number and if you find a match then add a cow. */
    }
    while (bulls != numOfDigits);  // and do it till guess == guessed number
    printf("You win!!! (you guessed %d times)", numOfTries);

    free(guessedNumber);
    free(guess);
    return 0;
}