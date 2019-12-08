#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

const bool showTheAnswer = false; // change to true if you want the answer to be shown at the start of the game
const int maxSize = 80; // maxSize > 11 because user can enter the bigger string

char* createString(int stringLength)
{
    char* localString = malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
        localString[i] = ' ';
    }
    return localString;
}

char* generateGuessedNumber(int numOfDigits)
{
    // Creating the answer with non repetitive digits and converting it to string.
    srand(time(NULL));
    int *guessedNumberAsArrayOfInt = malloc(sizeof(int) * numOfDigits);
    guessedNumberAsArrayOfInt[0] = 1 + rand() % 9;
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
    return guessedNumber;
}

int main() {
    printf("Choose the difficulty (number between 0 and 11: "
           "how many digits in the guessed number):\n");
    int numOfDigits = 0;
    scanf("%d", &numOfDigits);
    if ((numOfDigits <= 0) || (numOfDigits > 10))
    {
        printf("Incorrect input");
        return 0;
    }

    char *guessedNumber = generateGuessedNumber(numOfDigits);

    if (showTheAnswer)
    {
        printf("Hint: %s\n", guessedNumber);
    }

    int numOfTries = 0;
    int cows = 0;
    int bulls = 0;
    char *guess = createString(maxSize);
    printf("Rules:\n"
           "For each correct figure not in it's position, you get a cow\n"
           "For every correct figure in it's position, you get a bull\n"
           "Start your guessing!\n");
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

           /* Check for every digit in the guess
            * if on the same checked place the guessed number
            * and assumption have the same digit then add one bull. */

           char charToCheck = guess[guessCharPos];
           for (int guessNumberCharPos = 0; guessNumberCharPos < numOfDigits; guessNumberCharPos++)
           {
               if (charToCheck == guessedNumber[guessNumberCharPos])
               {
                   cows++;
               }
           }

           /* Otherwise, check each element
            * in the guessed number and if you find a match then add a cow. */
       }
       numOfTries++;
       printf("Bulls:%d Cows:%d Tries:%d\n", bulls, cows, numOfTries);
    }
    while (bulls != numOfDigits); // and do it till guess == guessed number
    printf("You win!!! (you guessed %d times)", numOfTries);

    free(guessedNumber);
    free(guess);
    return 0;
}