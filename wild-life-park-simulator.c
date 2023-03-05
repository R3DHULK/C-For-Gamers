#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Animal struct
typedef struct
{
    char name[20];
    char species[20];
    int age;
    char isMale;
} Animal;

// Park struct
typedef struct
{
    Animal *animals;
    int numAnimals;
    int maxAnimals;
} Park;

// Function prototypes
void listAnimals(Park *park);
void addAnimal(Park *park);

// Main function
int main()
{
    // Create a new park
    Park park;
    park.numAnimals = 0;
    park.maxAnimals = 5;
    park.animals = (Animal *)malloc(park.maxAnimals * sizeof(Animal));

    // Main game loop
    while (1)
    {
        // Display options and prompt for choice
        printf("Choose an option:\n");
        printf("1. List animals\n");
        printf("2. Add animal\n");
        printf("3. Exit\n");
        int choice;
        scanf("%d", &choice);
        printf("\n");

        // Handle choice
        switch (choice)
        {
        case 1:
            listAnimals(&park);
            break;
        case 2:
            addAnimal(&park);
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice.\n\n");
            break;
        }
    }
}

// Function to list animals in the park
void listAnimals(Park *park)
{
    // Display the list of animals in the park
    printf("List of animals:\n");
    for (int i = 0; i < park->numAnimals; i++)
    {
        printf("%d. %s - %s (%d years old, %s)\n", i + 1, park->animals[i].name, park->animals[i].species, park->animals[i].age, (park->animals[i].isMale == 'y' ? "male" : "female"));
    }
    printf("\n");
}

// Function to add a new animal to the park
void addAnimal(Park *park)
{
    // Check if there's enough space to add a new animal
    if (park->numAnimals == park->maxAnimals)
    {
        printf("The park is full. Cannot add new animal.\n\n");
        return;
    }

    // Prompt for animal details
    Animal newAnimal;
    printf("Enter the name of the animal: ");
    scanf("%s", newAnimal.name);
    printf("Enter the species of the animal: ");
    scanf("%s", newAnimal.species);
    printf("Enter the age of the animal: ");
    scanf("%d", &newAnimal.age);
    printf("Is the animal male? (y/n): ");
    scanf(" %c", &newAnimal.isMale);

    // Add the new animal to the park
    park->animals[park->numAnimals] = newAnimal;
    park->numAnimals++;
    printf("New animal added!\n\n");
}
