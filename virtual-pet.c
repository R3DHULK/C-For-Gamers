#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Pet
{
    char name[20];
    int hunger;
    int boredom;
};

void initPet(struct Pet *pet, char *name)
{
    strcpy(pet->name, name);
    pet->hunger = 0;
    pet->boredom = 0;
}

void play(struct Pet *pet)
{
    pet->boredom -= 5;
    if (pet->boredom < 0)
    {
        pet->boredom = 0;
    }
    pet->hunger += 1;
}

void feed(struct Pet *pet)
{
    pet->hunger -= 3;
    if (pet->hunger < 0)
    {
        pet->hunger = 0;
    }
}

void checkStatus(struct Pet *pet)
{
    if (pet->hunger >= 10)
    {
        printf("%s is hungry!\n", pet->name);
    }
    if (pet->boredom >= 10)
    {
        printf("%s is bored!\n", pet->name);
    }
    if (pet->hunger == 0 && pet->boredom == 0)
    {
        printf("%s is happy and healthy!\n", pet->name);
    }
}

int isAlive(struct Pet *pet)
{
    return pet->hunger < 10 && pet->boredom < 10;
}

int main()
{
    srand(time(NULL));
    struct Pet myPet;
    printf("Welcome to Virtual Pet Game!\n");
    printf("What would you like to name your pet? ");
    char name[20];
    scanf("%s", name);
    initPet(&myPet, name);
    while (isAlive(&myPet))
    {
        checkStatus(&myPet);
        printf("What would you like to do? (1 = Play, 2 = Feed, 3 = Quit) ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            play(&myPet);
            break;
        case 2:
            feed(&myPet);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
        int randomEvent = rand() % 3;
        if (randomEvent == 0)
        {
            feed(&myPet);
            printf("Your pet found some food to eat!\n");
        }
        else if (randomEvent == 1)
        {
            play(&myPet);
            printf("Your pet found a toy to play with!\n");
        }
        else
        {
            printf("Your pet is resting.\n");
        }
    }
    printf("Game over. %s has died.\n", myPet.name);
    return 0;
}
