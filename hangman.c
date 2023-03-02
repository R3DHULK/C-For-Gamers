#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WRONG_GUESSES 6
#define WORDS_COUNT 5

const char* WORDS[WORDS_COUNT] = {
    "computer",
    "programming",
    "algorithm",
    "database",
    "software"
};

int main() {
    // Select a random word from the list
    const char* word = WORDS[rand() % WORDS_COUNT];
    int word_len = strlen(word);

    // Initialize the guessed word with underscores
    char guessed_word[word_len+1];
    memset(guessed_word, '_', word_len);
    guessed_word[word_len] = '\0';

    // Keep track of guessed letters and wrong guesses
    int wrong_guesses = 0;
    char guessed_letters[26] = {0};
    int guessed_letters_count = 0;

    printf("Welcome to Hangman!\n");
    printf("The word has %d letters. You have %d wrong guesses.\n", word_len, MAX_WRONG_GUESSES);

    // Loop until the player guesses the word or runs out of guesses
    while (wrong_guesses < MAX_WRONG_GUESSES && strcmp(guessed_word, word) != 0) {
        // Print the current state of the guessed word
        printf("Guess the word: %s\n", guessed_word);

        // Print the guessed letters
        printf("Guessed letters: ");
        for (int i = 0; i < guessed_letters_count; i++) {
            printf("%c ", guessed_letters[i]);
        }
        printf("\n");

        // Ask the player for a letter
        printf("Enter a letter: ");
        char letter;
        scanf(" %c", &letter);

        // Check if the letter has already been guessed
        if (isalpha(letter) && !strchr(guessed_letters, letter)) {
            guessed_letters[guessed_letters_count++] = letter;

            // Check if the letter is in the word
            int found = 0;
            for (int i = 0; i < word_len; i++) {
                if (word[i] == letter) {
                    guessed_word[i] = letter;
                    found = 1;
                }
            }

            if (!found) {
                printf("Sorry, '%c' is not in the word.\n", letter);
                wrong_guesses++;
            }
        } else {
            printf("Please enter a valid letter that has not been guessed before.\n");
        }
    }

    // Print the final result
    if (wrong_guesses == MAX_WRONG_GUESSES) {
        printf("Sorry, you ran out of guesses. The word was '%s'.\n", word);
    } else {
        printf("Congratulations, you guessed the word '%s'!\n", word);
    }

    return 0;
}
