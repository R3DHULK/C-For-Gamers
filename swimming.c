#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the player's initial stats
int player_energy = 100;
int player_distance = 0;

// Define the pool's length and the energy cost per lap
int pool_length = 50;
int energy_cost_per_lap = 10;

// Define a function to simulate swimming one lap
void swim_lap() {
  // Check if the player has enough energy
  if (player_energy >= energy_cost_per_lap) {
    // Subtract the energy cost and add to the distance
    player_energy -= energy_cost_per_lap;
    player_distance += pool_length;
    printf("You swim a lap and add %d meters to your distance.\n", pool_length);
    printf("Your energy level is now %d.\n", player_energy);
  } else {
    printf("You don't have enough energy to swim a lap. Rest to recover energy.\n");
  }
}

// Define a function to simulate resting and recovering energy
void rest() {
  // Add random energy between 10 and 30
  int energy_gain = rand() % 21 + 10;
  player_energy += energy_gain;
  printf("You rest and recover %d energy.\n", energy_gain);
  printf("Your energy level is now %d.\n", player_energy);
}

// Define the main function for the game
int main() {
  // Seed the random number generator
  srand(time(NULL));
  
  printf("Welcome to the Swimming Pool Game!\n");
  
  // Start the game loop
  while (1) {
    printf("\nChoose your action:\n");
    printf("1. Swim a lap\n");
    printf("2. Rest and recover energy\n");
    printf("3. Quit the game\n");
    int choice;
    scanf("%d", &choice);
    
    // Perform the chosen action
    if (choice == 1) {
      swim_lap();
    } else if (choice == 2) {
      rest();
    } else if (choice == 3) {
      printf("Thanks for playing!\n");
      break;
    } else {
      printf("Invalid choice. Try again.\n");
    }
    
    // End the game if the player reaches the target distance
    if (player_distance >= 500) {
      printf("Congratulations, you reached the target distance!\n");
      break;
    }
  }
  
  return 0;
}
