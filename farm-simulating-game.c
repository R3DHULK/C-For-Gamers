#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
int randInt(int min, int max);
int sellCrop(int crop, int *money);
void plantCrop(int *crop);
void waterCrop(int crop);

int main()
{
    // Set up random number generator
    srand(time(NULL));

    // Initialize variables
    int crop = 0;    // Crop count
    int money = 100; // Starting money
    int days = 1;    // Number of days passed

    // Main game loop
    while (money > 0)
    {
        // Display current status
        printf("Day %d\n", days);
        printf("Crop count: %d\n", crop);
        printf("Money: $%d\n", money);

        // Prompt user for action
        printf("What do you want to do?\n");
        printf("1. Plant crops\n");
        printf("2. Water crops\n");
        printf("3. Harvest crops\n");
        printf("4. Quit game\n");

        int choice;
        scanf("%d", &choice);

        // Perform selected action
        switch (choice)
        {
        case 1:
            plantCrop(&crop);
            break;
        case 2:
            waterCrop(crop);
            break;
        case 3:
            money += sellCrop(crop, &money);
            break;
        case 4:
            printf("Thanks for playing!\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }

        // Randomly add new crop
        if (randInt(1, 10) == 1)
        {
            crop++;
            printf("A new crop has grown!\n");
        }

        // Increment day counter
        days++;
    }

    // Game over
    printf("You have run out of money. Game over!\n");
    return 0;
}

// Generates a random integer between min and max (inclusive)
int randInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Sells all crops and adds to money
int sellCrop(int crop, int *money)
{
    int value = crop * 10;
    *money += value;
    printf("You have sold %d crops for $%d.\n", crop, value);
    crop = 0; // Reset crop count
    return value;
}

// Plant new crop if no crop is planted
void plantCrop(int *crop)
{
    if (*crop == 0)
    {
        *crop = 1;
        printf("You have planted a new crop.\n");
    }
    else
    {
        printf("You already have a crop planted. Wait for it to grow.\n");
    }
}

// Water crop to speed up growth
void waterCrop(int crop)
{
    if (crop > 0)
    {
        printf("You watered your crop. It will grow faster now.\n");
    }
    else
    {
        printf("You don't have a crop planted. Plant a new crop first.\n");
    }
}
