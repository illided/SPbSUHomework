#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SHOW_THE_ANSWER false //change to true if you want the answer to be shown at the start of the game

int main() {
    printf("Choose the difficulty (how many digits in the guessed number):\n");
    int numOfDigits = 0;
    scanf("%d", &numOfDigits);

    srand(time(NULL));
    int *guessedNumber = malloc(numOfDigits * sizeof(int));
    for (int i = 0; i < numOfDigits; i++)
    {
        guessedNumber[i] = 1 + rand() % 9;
    }

    if (SHOW_THE_ANSWER)
    {
        printf("Answer: ");
        for (int m = 0; m < numOfDigits; m++)
        {
            printf("%d", guessedNumber[m]);
        }
        printf("\n");
    }

    int numOfTries = 0;
    int cows = 0;
    int bulls = 0;
    int guessUnsplitted = 0;
    printf("Start your guesses:\n");
    do
    {
        numOfTries++;
        cows = 0;
        bulls = 0;
        scanf("%d", &guessUnsplitted);
        int spaceForGuess = numOfDigits;
        int *guess = malloc(spaceForGuess * sizeof(int));
        int guessLength = 0;
        while (guessUnsplitted != 0)
        {
            if (guessLength == spaceForGuess)
            {
                spaceForGuess += 10;
                guess = realloc(guess, spaceForGuess * sizeof(int));
            }

            guess[guessLength] = guessUnsplitted % 10;
            guessUnsplitted = guessUnsplitted / 10;
            guessLength++;
        }

        for (int k = 0; k < guessLength / 2; k++)
        {
            int temp = guess[k];
            guess[k] = guess[guessLength - k - 1];
            guess[guessLength - k - 1] = temp;
        }

        for (int digitPosition = 0; digitPosition < guessLength; digitPosition++)
        {
            if (guessedNumber[digitPosition] == guess[digitPosition])
            {
                bulls++;
            }
            else
            {
                for (int dgtPosInGuessedNumber = 0; dgtPosInGuessedNumber < numOfDigits; dgtPosInGuessedNumber++)
                {
                    if ((guessedNumber[dgtPosInGuessedNumber] == guess[digitPosition]) &&
                            (guessedNumber[dgtPosInGuessedNumber] != guess[dgtPosInGuessedNumber]))
                    {
                        cows++;
                    }
                }
            }

        }
        printf("%d cows and %d bulls\n", cows, bulls);
        free(guess);
    } while (bulls != numOfDigits);
    printf("You win!!! (you guessed %d times)", numOfTries);
    return 0;
}