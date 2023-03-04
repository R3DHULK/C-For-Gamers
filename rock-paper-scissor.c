#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

int main() {
    int playerScore = 0;
    int computerScore = 0;
    int rounds = 0;

    printf("Welcome to Rock-Paper-Scissors game!\n\n");

    while(1) {
        int playerMove;
        printf("Enter your move (1 = Rock, 2 = Paper, 3 = Scissors, 0 = Quit): ");
        scanf("%d", &playerMove);

        if (playerMove == 0) {
            break;
        }

        if (playerMove < 1 || playerMove > 3) {
            printf("Invalid move! Please try again.\n");
            continue;
        }

        int computerMove = rand() % 3 + 1;

        printf("You played: ");
        switch(playerMove) {
            case ROCK:
                printf("Rock\n");
                break;
            case PAPER:
                printf("Paper\n");
                break;
            case SCISSORS:
                printf("Scissors\n");
                break;
        }

        printf("Computer played: ");
        switch(computerMove) {
            case ROCK:
                printf("Rock\n");
                break;
            case PAPER:
                printf("Paper\n");
                break;
            case SCISSORS:
                printf("Scissors\n");
                break;
        }

        if (playerMove == computerMove) {
            printf("It's a tie!\n");
        } else if (playerMove == ROCK && computerMove == SCISSORS ||
                   playerMove == PAPER && computerMove == ROCK ||
                   playerMove == SCISSORS && computerMove == PAPER) {
            printf("You win this round!\n");
            playerScore++;
        } else {
            printf("Computer wins this round!\n");
            computerScore++;
        }

        rounds++;
        printf("Current score: You %d - %d Computer\n\n", playerScore, computerScore);
    }

    printf("\nFinal score: You %d - %d Computer\n", playerScore, computerScore);
    printf("Total rounds played: %d\n", rounds);

    return 0;
}
