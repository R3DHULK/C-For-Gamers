#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Character stats
    int health = 100;
    int attack = 10;
    int defense = 5;
    int gold = 0;
    int experience = 0;

    // Monster stats
    int monster_health = 50;
    int monster_attack = 5;
    int monster_defense = 2;
    int monster_gold = 10;
    int monster_experience = 20;

    // Game loop
    while (health > 0)
    {
        // Print character stats
        printf("Health: %d\nAttack: %d\nDefense: %d\nGold: %d\nExperience: %d\n\n", health, attack, defense, gold, experience);

        // Choose action
        printf("Choose your action:\n1. Fight\n2. Flee\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            // Fight a monster
            printf("You encounter a monster!\n");

            // Loop until the monster or the player dies
            while (health > 0 && monster_health > 0)
            {
                // Print monster and player health
                printf("Monster Health: %d\n", monster_health);
                printf("Your Health: %d\n", health);

                // Player attacks monster
                int damage = attack - monster_defense;
                if (damage < 0)
                {
                    damage = 0;
                }
                monster_health -= damage;
                printf("You attack the monster for %d damage!\n", damage);

                // Monster attacks player
                damage = monster_attack - defense;
                if (damage < 0)
                {
                    damage = 0;
                }
                health -= damage;
                printf("The monster attacks you for %d damage!\n", damage);
            }

            // Check if player won or lost
            if (health > 0)
            {
                printf("You defeated the monster!\n");
                gold += monster_gold;
                experience += monster_experience;
            }
            else
            {
                printf("You were defeated by the monster...\n");
                break;
            }
        }
        else if (choice == 2)
        {
            // Flee from battle
            printf("You flee from the monster...\n");
        }
        else
        {
            // Invalid choice
            printf("Invalid choice.\n");
        }
    }

    // Game over
    printf("Game over!\n");
    printf("Final stats:\nHealth: %d\nAttack: %d\nDefense: %d\nGold: %d\nExperience: %d\n", health, attack, defense, gold, experience);

    return 0;
}
