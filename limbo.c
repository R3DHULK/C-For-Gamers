#include <stdio.h>

int main() {
    printf("Welcome to Limbo!\n");
    printf("You wake up in a dark forest with no memory of how you got there.\n");
    printf("You can only see a faint light in the distance.\n\n");

    printf("What do you want to do?\n");
    printf("1. Move towards the light.\n");
    printf("2. Stay where you are.\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("You start moving towards the light.\n");
        printf("As you move closer, you realize that the light is coming from a lantern.\n");
        printf("You pick up the lantern and continue walking.\n\n");

        printf("What do you want to do?\n");
        printf("1. Keep moving forward.\n");
        printf("2. Turn back.\n");

        scanf("%d", &choice);

        if (choice == 1) {
            printf("You come across a chasm that you cannot cross.\n");
            printf("There is a lever on the other side.\n");
            printf("You need to find a way to cross the chasm and reach the lever.\n");
        } else {
            printf("You turn back and end up back where you started.\n");
            printf("You feel like you're going in circles.\n");
        }
    } else {
        printf("You decide to stay where you are.\n");
        printf("After a while, you start to feel hungry and thirsty.\n");
        printf("You realize that you need to find food and water if you want to survive.\n");
    }

    return 0;
}
