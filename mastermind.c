#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CODE_LENGTH 4  // The length of the code
#define MAX_GUESSES 10 // The maximum number of guesses allowed

void generateCode(int *code)
{
    // Generate a random code
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        code[i] = rand() % 6 + 1; // Each code digit can be from 1 to 6
    }
}

int checkGuess(int *code, int *guess, int *blackPegs, int *whitePegs)
{
    // Check the guess and return the number of black and white pegs
    int usedCodeDigits[CODE_LENGTH] = {0};  // Keep track of which code digits have been matched
    int usedGuessDigits[CODE_LENGTH] = {0}; // Keep track of which guess digits have been matched
    *blackPegs = 0;
    *whitePegs = 0;
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (code[i] == guess[i])
        {
            (*blackPegs)++;
            usedCodeDigits[i] = 1;
            usedGuessDigits[i] = 1;
        }
    }
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (!usedGuessDigits[i])
        { // If the guess digit hasn't been matched
            for (int j = 0; j < CODE_LENGTH; j++)
            {
                if (!usedCodeDigits[j] && guess[i] == code[j])
                { // If the code digit hasn't been matched and matches the guess digit
                    (*whitePegs)++;
                    usedCodeDigits[j] = 1;
                    usedGuessDigits[i] = 1;
                    break;
                }
            }
        }
    }
    return (*blackPegs == CODE_LENGTH); // Return 1 if the guess is correct, 0 otherwise
}

int main()
{
    int code[CODE_LENGTH];
    generateCode(code);
    printf("Welcome to Mastermind!\n");
    printf("Guess the 4-digit code, where each digit is between 1 and 6.\n");
    printf("You have %d guesses.\n", MAX_GUESSES);
    for (int numGuesses = 1; numGuesses <= MAX_GUESSES; numGuesses++)
    {
        printf("Guess #%d: ", numGuesses);
        int guess[CODE_LENGTH];
        for (int i = 0; i < CODE_LENGTH; i++)
        {
            scanf("%d", &guess[i]);
        }
        int blackPegs, whitePegs;
        if (checkGuess(code, guess, &blackPegs, &whitePegs))
        {
            printf("Congratulations! You guessed the code in %d guesses.\n", numGuesses);
            return 0;
        }
        else
        {
            printf("Black pegs: %d, white pegs: %d.\n", blackPegs, whitePegs);
        }
    }
    printf("Sorry, you couldn't guess the code in %d guesses. The code was:", MAX_GUESSES);
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        printf(" %d", code[i]);
    }
    printf(".\n");
    return 0;
}
