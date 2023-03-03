#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to check if two strings are equal
int string_equal(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

int main()
{
    // Set up random number generator
    srand(time(NULL));

    // Declare and initialize game variables
    int game_over = 0;
    int found_key = 0;
    int found_lock = 0;
    int current_room = 0;
    int num_rooms = 4;
    char input[100];

    // Declare and initialize room descriptions and item locations
    char *room_descriptions[] = {
        "You are in a dusty old attic. There are cobwebs in the corners and an old trunk in the center of the room.",
        "You are in a dimly lit bedroom. There is a bed in the corner and a dresser against the wall.",
        "You are in a cluttered study. There are books and papers strewn about the room and a large oak desk in the center.",
        "You are in a dark basement. There are shelves lining the walls and a musty smell in the air."};
    int room_items[][2] = {
        {1, 0},
        {0, 1},
        {1, 0},
        {0, 0}};

    // Main game loop
    while (!game_over)
    {
        // Print current room description
        printf("%s\n", room_descriptions[current_room]);

        // Check if there are any items in the room
        if (room_items[current_room][0] == 1)
        {
            printf("There is a key on the ground.\n");
        }
        if (room_items[current_room][1] == 1)
        {
            printf("There is a locked box on the dresser.\n");
        }

        // Get user input
        printf("What do you want to do? (type help for commands)");
        fgets(input, 100, stdin);
        strtok(input, "\n"); // Remove newline character

        // Check user input
        if (string_equal(input, "quit"))
        {
            game_over = 1;
        }
        else if (string_equal(input, "look"))
        {
            // Print current room description again
            printf("%s\n", room_descriptions[current_room]);
        }
        else if (string_equal(input, "take key"))
        {
            if (room_items[current_room][0] == 1)
            {
                printf("You take the key.\n");
                found_key = 1;
                room_items[current_room][0] = 0;
            }
            else
            {
                printf("There is no key in this room.\n");
            }
        }
        else if (string_equal(input, "unlock box"))
        {
            if (found_key && room_items[current_room][1] == 1)
            {
                printf("You unlock the box and find a mysterious note inside.\n");
                found_lock = 1;
                room_items[current_room][1] = 0;
            }
            else if (!found_key)
            {
                printf("You don't have a key.\n");
            }
            else
            {
                printf("There is no locked box in this room.\n");
            }
        }
        else if (string_equal(input, "read note"))
        {
            if (found_lock)
            {
                printf("The note reads:\n");
                printf("The treasure lies where the sun sets behind the mountain.\n");
            }
            else
            {
                printf("Invalid command.\n");
            }
        }
        else if (string_equal(input, "help"))
        {
            printf("Possible commands: quit, look, take key, unlock box, read note, help\n");
        }
        else
        {
            printf("Invalid command. Type 'help' for a list of possible commands.\n");
        }
        // Check if game is over
        if (found_lock)
        {
            printf("Congratulations! You found the treasure and won the game.\n");
            game_over = 1;
        }
        else if (string_equal(input, "quit"))
        {
            printf("Thanks for playing!\n");
            game_over = 1;
        }
        else
        {
            // Move to a new room
            int new_room = rand() % num_rooms;
            while (new_room == current_room)
            {
                new_room = rand() % num_rooms;
            }
            current_room = new_room;
        }
    }

    return 0;
}
