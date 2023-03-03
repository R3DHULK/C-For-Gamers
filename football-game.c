#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random number between min and max
int rand_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to simulate a football match
void play_match(int home_team_strength, int away_team_strength) {
    int home_score = 0, away_score = 0;

    printf("Kick-off! The match begins.\n");

    // Simulate the first half
    for (int i = 1; i <= 45; i++) {
        int home_chance = rand_range(1, 100);
        int away_chance = rand_range(1, 100);

        if (home_chance <= home_team_strength) {
            home_score++;
            printf("GOAL! Home team scores at %d minutes.\n", i);
        }

        if (away_chance <= away_team_strength) {
            away_score++;
            printf("GOAL! Away team scores at %d minutes.\n", i);
        }
    }

    printf("Half-time: Home %d - %d Away\n", home_score, away_score);

    // Simulate the second half
    for (int i = 46; i <= 90; i++) {
        int home_chance = rand_range(1, 100);
        int away_chance = rand_range(1, 100);

        if (home_chance <= home_team_strength) {
            home_score++;
            printf("GOAL! Home team scores at %d minutes.\n", i);
        }

        if (away_chance <= away_team_strength) {
            away_score++;
            printf("GOAL! Away team scores at %d minutes.\n", i);
        }
    }

    printf("Full-time: Home %d - %d Away\n", home_score, away_score);

    // Determine the winner or draw
    if (home_score > away_score) {
        printf("Home team wins!\n");
    } else if (away_score > home_score) {
        printf("Away team wins!\n");
    } else {
        printf("It's a draw!\n");
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int choice;
    int team_strength[2];

    printf("Welcome to the text-based football game!\n");
    printf("Select your team strength:\n");
    printf("1. Weak\n");
    printf("2. Medium\n");
    printf("3. Strong\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            team_strength[0] = 50;
            break;
        case 2:
            team_strength[0] = 70;
            break;
        case 3:
            team_strength[0] = 90;
            break;
        default:
            printf("Invalid choice. Exiting.\n");
            return 0;
    }

    // Generate a random strength for the opponent team
    team_strength[1] = rand_range(50, 90);

    printf("You will be playing against an opponent team with strength %d.\n", team_strength[1]);

    // Play the match
    play_match(team_strength[0], team_strength[1]);

    return 0;
}
