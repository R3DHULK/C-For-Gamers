#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_HEALTH 100
#define MAX_HUNGER 100
#define MAX_THIRST 100
#define MAX_DAYS 7

int health, hunger, thirst, day;

void printStatus()
{
    printf("DAY %d\n", day);
    printf("Health: %d / %d\n", health, MAX_HEALTH);
    printf("Hunger: %d / %d\n", hunger, MAX_HUNGER);
    printf("Thirst: %d / %d\n", thirst, MAX_THIRST);
}

void rest()
{
    printf("You take a rest and recover some health.\n");
    health += 20;
    if (health > MAX_HEALTH)
    {
        health = MAX_HEALTH;
    }
}

void hunt()
{
    printf("You go hunting for food and water.\n");
    hunger += 30;
    thirst += 30;
    if (hunger > MAX_HUNGER)
    {
        hunger = MAX_HUNGER;
    }
    if (thirst > MAX_THIRST)
    {
        thirst = MAX_THIRST;
    }
}

void scavenge()
{
    printf("You scavenge for useful items.\n");
    int chance = rand() % 100;
    if (chance < 20)
    {
        printf("You found a first-aid kit!\n");
        health += 30;
        if (health > MAX_HEALTH)
        {
            health = MAX_HEALTH;
        }
    }
    else if (chance < 50)
    {
        printf("You found some canned food.\n");
        hunger += 20;
        if (hunger > MAX_HUNGER)
        {
            hunger = MAX_HUNGER;
        }
    }
    else if (chance < 80)
    {
        printf("You found a bottle of water.\n");
        thirst += 20;
        if (thirst > MAX_THIRST)
        {
            thirst = MAX_THIRST;
        }
    }
    else
    {
        printf("You didn't find anything useful.\n");
    }
}

void nextDay()
{
    day++;
    hunger -= 20;
    thirst -= 30;
    if (hunger < 0)
    {
        hunger = 0;
        health -= 10;
    }
    if (thirst < 0)
    {
        thirst = 0;
        health -= 20;
    }
    if (health <= 0)
    {
        printf("You died of hunger and thirst on day %d.\n", day);
        exit(0);
    }
    if (day == MAX_DAYS)
    {
        printf("You survived for %d days and won the game!\n", day);
        exit(0);
    }
}

int main()
{
    srand(time(NULL));
    health = MAX_HEALTH;
    hunger = MAX_HUNGER;
    thirst = MAX_THIRST;
    day = 0;
    while (1)
    {
        printStatus();
        printf("Choose an action:\n");
        printf("1. Rest\n");
        printf("2. Hunt\n");
        printf("3. Scavenge\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            rest();
            break;
        case 2:
            hunt();
            break;
        case 3:
            scavenge();
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
        usleep(100000); // wait for a short time (100 ms)
        nextDay();
    }
    return 0;
}
