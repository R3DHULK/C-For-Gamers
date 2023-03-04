#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_HEALTH 20
#define MAX_AMMO 6
#define MAX_ENEMIES 3

int player_health = MAX_HEALTH;
int player_ammo = MAX_AMMO;
int num_enemies = MAX_ENEMIES;

int roll_die(int num_sides) {
    return rand() % num_sides + 1;
}

void shoot() {
    if (player_ammo <= 0) {
        printf("You're out of ammo!\n");
        return;
    }

    printf("You take aim and pull the trigger...\n");
    player_ammo--;

    int hit_chance = roll_die(4);
    if (hit_chance <= 2) {
        printf("You missed your shot!\n");
        return;
    }

    int damage = roll_die(6);
    printf("You hit an enemy for %d damage!\n", damage);
    num_enemies--;
}

void rest() {
    int rest_time = roll_die(6);
    printf("You take a breather and rest for %d hours.\n", rest_time);
    player_health += rest_time;

    if (player_health > MAX_HEALTH) {
        player_health = MAX_HEALTH;
    }
}

void check_status() {
    printf("You have %d health and %d ammo.\n", player_health, player_ammo);

    if (num_enemies == 0) {
        printf("You've defeated all the enemies! You win!\n");
        exit(0);
    }
}

int main() {
    srand(time(0));

    printf("Welcome to the Wild West!\n");

    while (player_health > 0 && num_enemies > 0) {
        printf("You have %d enemies left to defeat.\n", num_enemies);
        printf("What would you like to do? (shoot/rest/check): ");

        char input[10];
        scanf("%s", input);

        if (strcmp(input, "shoot") == 0) {
            shoot();
        } else if (strcmp(input, "rest") == 0) {
            rest();
        } else if (strcmp(input, "check") == 0) {
            check_status();
        } else {
            printf("Invalid input!\n");
        }
    }

    if (player_health <= 0) {
        printf("You've been defeated! Game over.\n");
    }

    return 0;
}

