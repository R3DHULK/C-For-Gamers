#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 16

// Function declarations
void initialize_board(int board[], int board_size);
void print_board(int board[], int board_size);
void shuffle_board(int board[], int board_size);
int get_card_choice(int board[], int board_size, int choices[]);
int check_match(int board[], int card1, int card2);
void mark_cards(int board[], int card1, int card2);

// Main function
int main()
{
    int board[BOARD_SIZE];
    int choices[2];
    int matches = 0;
    int attempts = 0;

    // Seed random number generator
    srand(time(NULL));

    // Initialize the board
    initialize_board(board, BOARD_SIZE);

    // Shuffle the board
    shuffle_board(board, BOARD_SIZE);

    // Play the game
    while (matches < BOARD_SIZE / 2)
    {
        // Print the board
        print_board(board, BOARD_SIZE);

        // Get the player's card choices
        choices[0] = get_card_choice(board, BOARD_SIZE, choices);
        choices[1] = get_card_choice(board, BOARD_SIZE, choices);

        // Check if the cards match
        if (check_match(board, choices[0], choices[1]))
        {
            printf("Match!\n");
            mark_cards(board, choices[0], choices[1]);
            matches++;
        }
        else
        {
            printf("No match.\n");
        }

        // Increment the number of attempts
        attempts++;
    }

    // Game over
    printf("Congratulations! You won in %d attempts.\n", attempts);

    return 0;
}

// Function to initialize the board with pairs of numbers
void initialize_board(int board[], int board_size)
{
    int i;
    for (i = 0; i < board_size; i += 2)
    {
        board[i] = i / 2 + 1;
        board[i + 1] = i / 2 + 1;
    }
}

// Function to print the board
void print_board(int board[], int board_size)
{
    int i;
    printf(" ");
    for (i = 0; i < board_size; i++)
    {
        printf("----");
    }
    printf("\n");
    for (i = 0; i < board_size; i++)
    {
        printf("|");
        if (board[i] == 0)
        {
            printf("  ");
        }
        else
        {
            printf("%2d", board[i]);
        }
        printf(" ");
        if (i == board_size - 1)
        {
            printf("|\n");
        }
        else if ((i + 1) % 4 == 0)
        {
            printf("|\n ");
            int j;
            for (j = 0; j < 4; j++)
            {
                printf("----");
            }
            printf("\n");
        }
    }
    printf(" ");
    for (i = 0; i < board_size; i++)
    {
        printf("----");
    }
    printf("\n");
}

// Function to shuffle the board
void shuffle_board(int board[], int board_size)
{
    int i, j, temp;
    for (i = board_size - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = board[i];
        board[i] = board[j];
        board[j] = temp;
    }
}

// Function to get the player's card choice
int get_card_choice(int board[], int board_size, int choices[])
{
    int card;
    do
    {
        printf("Enter a card number (1-%d): ", board_size / 2);
        scanf("%d", &card);
        if (card < 1 || card > board_size / 2)
        {
            printf("Invalid card number. Please try again.\n");
        }
        else if (board[(card - 1) * 2] == 0 && board[(card - 1) * 2 + 1] == 0)
        {
            printf("Card already matched. Please choose another card.\n");
        }
        else if (choices[0] != -1 && choices[1] != -1 && card != choices[0] && card != choices[1])
        {
            printf("You can only choose two cards at a time. Please choose again.\n");
        }
        else
        {
            return card;
        }
    } while (1);
}
// Function to check if two cards match
int check_match(int board[], int card1, int card2)
{
    if (board[(card1 - 1) * 2] == board[(card2 - 1) * 2])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to mark cards as matched
void mark_cards(int board[], int card1, int card2)
{
    board[(card1 - 1) * 2] = 0;
    board[(card1 - 1) * 2 + 1] = 0;
    board[(card2 - 1) * 2] = 0;
    board[(card2 - 1) * 2 + 1] = 0;
}
