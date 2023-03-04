#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_RESOURCES 100
#define MAX_BUILDINGS 10
#define MAX_BUILDING_NAME_LENGTH 20

// Structs
typedef struct
{
    int food;
    int water;
    int power;
} Resources;

typedef struct
{
    char name[MAX_BUILDING_NAME_LENGTH];
    int cost;
    Resources production;
} Building;

// Function prototypes
void display_resources(Resources resources);
void display_buildings(Building *buildings, int num_buildings);
int get_choice(int num_options);
void build_building(Building *building, Resources *resources);

// Main function
int main()
{
    // Declare and initialize resources
    Resources resources = {10, 10, 10};

    // Declare and initialize buildings
    Building buildings[MAX_BUILDINGS] = {
        {"Farm", 10, {2, 0, 0}},
        {"Well", 10, {0, 2, 0}},
        {"Power Plant", 20, {0, 0, 3}},
        {"House", 5, {0, 0, 0}}};
    int num_buildings = 4;

    // Main game loop
    while (1)
    {
        // Display resources
        printf("\nResources:\n");
        display_resources(resources);

        // Display available buildings
        printf("\nAvailable buildings:\n");
        display_buildings(buildings, num_buildings);

        // Get user input
        printf("\nWhat do you want to do? ");
        int choice = get_choice(num_buildings + 1);

        // Build a building
        if (choice == num_buildings)
        {
            // Get user input
            printf("\nWhich building do you want to build? ");
            int building_choice = get_choice(num_buildings);

            // Check if resources are sufficient
            if (resources.food >= buildings[building_choice].cost &&
                resources.water >= buildings[building_choice].cost &&
                resources.power >= buildings[building_choice].cost)
            {
                // Build the building and update resources
                build_building(&buildings[building_choice], &resources);
                printf("\n%s built!\n", buildings[building_choice].name);
            }
            else
            {
                printf("\nNot enough resources to build %s.\n", buildings[building_choice].name);
            }
        }
        // Exit game
        else if (choice == num_buildings + 1)
        {
            break;
        }
        // Display building info
        else
        {
            printf("\n%s:\n", buildings[choice].name);
            printf("Cost: %d\n", buildings[choice].cost);
            printf("Production:\n");
            display_resources(buildings[choice].production);
        }
    }

    return 0;
}

// Function to display the current resources
void display_resources(Resources resources)
{
    printf("Food: %d\n", resources.food);
    printf("Water: %d\n", resources.water);
    printf("Power: %d\n", resources.power);
}

// Function to display the available buildings
void display_buildings(Building *buildings, int num_buildings)
{
    for (int i = 0; i < num_buildings; i++)
    {
        printf("%d. %s\n", i + 1, buildings[i].name);
    }
    printf("%d. Build a new building\n", num_buildings + 1);
    printf("%d. Exit game\n", num_buildings + 2);
}

// Function to get user choice from a list of options
int get_choice(int num_options)
{
    int choice;
    scanf("%d", &choice);

    // Check if choice is valid
    while (choice < 1 || choice > num_options)
    {
        printf("Invalid choice. Please enter a number between 1 and %d: ", num_options);
        scanf("%d", &choice);
    }

    return choice - 1;
}

// Function to build a new building and update resources
void build_building(Building *building, Resources *resources)
{
    resources->food -= building->cost;
    resources->water -= building->cost;
    resources->power -= building->cost;

    resources->food += building->production.food;
    resources->water += building->production.water;
    resources->power += building->production.power;
}
