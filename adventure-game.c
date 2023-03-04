#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 50

typedef struct Room {
    char name[MAX_INPUT_SIZE];
    char description[MAX_INPUT_SIZE];
    int north;
    int south;
    int east;
    int west;
} Room;

int main() {
    // Define the game map
    Room map[3];
    strcpy(map[0].name, "Room 1");
    strcpy(map[0].description, "You are in a small, dimly-lit room.");
    map[0].north = 1;
    map[0].south = -1;
    map[0].east = -1;
    map[0].west = -1;

    strcpy(map[1].name, "Room 2");
    strcpy(map[1].description, "You are in a large, spacious room.");
    map[1].north = -1;
    map[1].south = 0;
    map[1].east = -1;
    map[1].west = -1;

    strcpy(map[2].name, "Room 3");
    strcpy(map[2].description, "You are in a dark, creepy room.");
    map[2].north = -1;
    map[2].south = -1;
    map[2].east = 0;
    map[2].west = -1;

    // Set up the initial game state
    int current_room = 0;
    char input[MAX_INPUT_SIZE];

    printf("Welcome to the game! Type 'help' for a list of commands.\n");

    // Main game loop
    while (1) {
        // Print the current room description
        printf("\n%s\n", map[current_room].description);

        // Get user input
        printf("> ");
        fgets(input, MAX_INPUT_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character from input

        // Process user input
        if (strcmp(input, "help") == 0) {
            printf("Available commands: go [north|south|east|west], quit\n");
        } else if (strcmp(input, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strncmp(input, "go ", 3) == 0) {
            // Extract the direction from the input
            char *direction = input + 3;

            // Move the player in the specified direction
            if (strcmp(direction, "north") == 0 && map[current_room].north != -1) {
                current_room = map[current_room].north;
            } else if (strcmp(direction, "south") == 0 && map[current_room].south != -1) {
                current_room = map[current_room].south;
            } else if (strcmp(direction, "east") == 0 && map[current_room].east != -1) {
                current_room = map[current_room].east;
            } else if (strcmp(direction, "west") == 0 && map[current_room].west != -1) {
                current_room = map[current_room].west;
            } else {
                printf("You can't go that way.\n");
            }
        } else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }

    return 0;
}
