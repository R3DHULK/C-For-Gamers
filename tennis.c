#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_GAMES 3
#define WINNING_SCORE 3

// Function to simulate a single point
int simulate_point() {
    // Generate a random number between 0 and 1
    int r = rand() % 2;
    return r;
}

int main() {
    // Set up random number generator
    srand(time(NULL));
    
    // Declare game variables
    int player1_score = 0;
    int player2_score = 0;
    int current_game = 1;
    int player1_serve = 1;
    
    // Main game loop
    while (current_game <= NUM_GAMES) {
        printf("Game %d\n", current_game);
        
        // Reset scores for new game
        player1_score = 0;
        player2_score = 0;
        
        // Serve alternates every game
        if (current_game % 2 == 0) {
            player1_serve = 0;
        }
        else {
            player1_serve = 1;
        }
        
        // Game loop
        int game_over = 0;
        while (!game_over) {
            // Determine which player is serving
            if (player1_serve) {
                printf("Player 1 is serving.\n");
            }
            else {
                printf("Player 2 is serving.\n");
            }
            
            // Simulate a point
            int point_winner = simulate_point();
            if (point_winner == 0) {
                player1_score++;
                printf("Point to Player 1.\n");
            }
            else {
                player2_score++;
                printf("Point to Player 2.\n");
            }
            
            // Check if game is over
            if (player1_score >= WINNING_SCORE || player2_score >= WINNING_SCORE) {
                game_over = 1;
            }
            
            // Switch serve every two points
            if ((player1_score + player2_score) % 2 == 0) {
                player1_serve = !player1_serve;
            }
        }
        
        // Print final scores
        printf("Game over! Final scores:\n");
        printf("Player 1: %d\n", player1_score);
        printf("Player 2: %d\n", player2_score);
        
        // Determine winner of the game
        if (player1_score > player2_score) {
            printf("Player 1 wins!\n");
        }
        else {
            printf("Player 2 wins!\n");
        }
        
        // Increment game counter
        current_game++;
    }
    
    printf("Thanks for playing!\n");
    
    return 0;
}
