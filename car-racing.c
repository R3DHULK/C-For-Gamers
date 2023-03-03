#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRACK_LENGTH 20

void print_track(int player_position, int opponent_position);
int get_move();

int main() {
    srand(time(NULL));
    int player_position = 0;
    int opponent_position = 0;
    printf("Welcome to the Text-based Car Racing Game!\n");
    printf("Your car: [P]\nOpponent car: [O]\n");
    while (1) {
        print_track(player_position, opponent_position);
        int move = get_move();
        player_position += move;
        opponent_position += rand() % 3 + 1; // opponent moves randomly
        if (player_position >= TRACK_LENGTH) {
            printf("You win!\n");
            break;
        }
        else if (opponent_position >= TRACK_LENGTH) {
            printf("You lose!\n");
            break;
        }
    }
    return 0;
}

void print_track(int player_position, int opponent_position) {
    printf("\n");
    for (int i = 0; i < TRACK_LENGTH; i++) {
        if (i == player_position) {
            printf("[P]");
        }
        else if (i == opponent_position) {
            printf("[O]");
        }
        else {
            printf("[ ]");
        }
    }
    printf("\n");
}

int get_move() {
    int move;
    while (1) {
        printf("Enter a move (1-3): ");
        scanf("%d", &move);
        if (move >= 1 && move <= 3) {
            break;
        }
        printf("Invalid move. Please enter a move between 1 and 3.\n");
    }
    return move;
}
