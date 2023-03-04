#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100
#define NUM_SNAKES 10
#define NUM_LADDERS 10

// Structure to represent a snake or ladder
typedef struct
{
    int start;
    int end;
} SnakeOrLadder;

// Initialize the snakes and ladders on the board
void initSnakesAndLadders(SnakeOrLadder snakes[], SnakeOrLadder ladders[])
{
    // Initialize snakes
    snakes[0].start = 14;
    snakes[0].end = 5;
    snakes[1].start = 22;
    snakes[1].end = 3;
    snakes[2].start = 37;
    snakes[2].end = 17;
    snakes[3].start = 54;
    snakes[3].end = 34;
    snakes[4].start = 66;
    snakes[4].end = 45;
    snakes[5].start = 74;
    snakes[5].end = 23;
    snakes[6].start = 85;
    snakes[6].end = 49;
    snakes[7].start = 92;
    snakes[7].end = 36;
    snakes[8].start = 97;
    snakes[8].end = 20;
    snakes[9].start = 99;
    snakes[9].end = 28;

    // Initialize ladders
    ladders[0].start = 4;
    ladders[0].end = 19;
    ladders[1].start = 7;
    ladders[1].end = 27;
    ladders[2].start = 12;
    ladders[2].end = 36;
    ladders[3].start = 24;
    ladders[3].end = 48;
    ladders[4].start = 33;
    ladders[4].end = 59;
    ladders[5].start = 44;
    ladders[5].end = 62;
    ladders[6].start = 63;
    ladders[6].end = 81;
    ladders[7].start = 69;
    ladders[7].end = 87;
    ladders[8].start = 75;
    ladders[8].end = 86;
    ladders[9].start = 92;
    ladders[9].end = 98;
}

// Get a random number between min and max, inclusive
int getRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Move the player based on the dice roll
int movePlayer(int playerPos, int diceRoll, SnakeOrLadder snakes[], SnakeOrLadder ladders[])
{
    int newPos = playerPos + diceRoll;

    // Check if player has landed on a snake or ladder
    for (int i = 0; i < NUM_SNAKES; i++)
    {
        if (snakes[i].start == newPos)
        {
            printf("Oh no! You landed on a snake and slid down to position %d.\n", snakes[i].end);
            return snakes[i].end;
        }
    }
    for (int i = 0; i < NUM_LADDERS; i++)
    {
        if (ladders[i].start == newPos)
        {
            printf("Congratulations! You landed on a ladder and climbed up to position %d", ladders[i].end);
            return ladders[i].end;
        }
    }
    // Player hasn't landed on a snake or ladder, so return the new position
    return newPos;
}

int main()
{
    // Initialize random number generator
    srand(time(NULL));
    // Initialize the board
    int board[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board[i] = i + 1;
    }

    // Initialize snakes and ladders
    SnakeOrLadder snakes[NUM_SNAKES];
    SnakeOrLadder ladders[NUM_LADDERS];
    initSnakesAndLadders(snakes, ladders);

    // Initialize player position and dice roll
    int playerPos = 1;
    int diceRoll;

    // Main game loop
    while (playerPos < BOARD_SIZE)
    {
        printf("\nYou are currently on position %d. Press enter to roll the dice.", playerPos);
        getchar(); // Wait for user to press enter

        // Roll the dice
        diceRoll = getRandomNumber(1, 6);
        printf("You rolled a %d.\n", diceRoll);

        // Move the player based on the dice roll
        playerPos = movePlayer(playerPos, diceRoll, snakes, ladders);

        // Print the new player position
        printf("Your new position is %d.\n", playerPos);
    }

    // Player has reached the end of the board and won the game
    printf("\nCongratulations! You have won the game!\n");

    return 0;
}
