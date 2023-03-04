#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SEQUENCE 100

// Function to generate a random number between 0 and 3
int randomInt() {
    return rand() % 4;
}

// Function to play the game
void playSimonSays(int sequence[], int length) {
    printf("Simon says:\n");
    for (int i = 0; i < length; i++) {
        switch (sequence[i]) {
            case 0:
                printf("Red\n");
                break;
            case 1:
                printf("Green\n");
                break;
            case 2:
                printf("Blue\n");
                break;
            case 3:
                printf("Yellow\n");
                break;
        }
        // Sleep for a short time to give the player a chance to remember the sequence
        for (int j = 0; j < 100000000; j++) {}
        system("clear"); // Clear the screen before showing the next color
    }

    printf("Your turn!\n");
    // Loop through the sequence again and ask the player to enter the colors
    for (int i = 0; i < length; i++) {
        int color;
        do {
            printf("Enter color %d (0=Red, 1=Green, 2=Blue, 3=Yellow): ", i+1);
            scanf("%d", &color);
        } while (color < 0 || color > 3);

        if (color != sequence[i]) {
            printf("Wrong! Game over.\n");
            return;
        }
    }

    printf("Congratulations, you win!\n");
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int sequence[MAX_SEQUENCE];
    int length = 0;

    // Generate the sequence
    while (1) {
        sequence[length] = randomInt();
        length++;
        playSimonSays(sequence, length);
    }

    return 0;
}
