#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BUTTONS 4
#define MAX_SEQUENCE 100

int simon_sequence[MAX_SEQUENCE];
int player_sequence[MAX_SEQUENCE];
int score;

void display_sequence(int sequence[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

void generate_sequence(int sequence[], int length)
{
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        sequence[i] = rand() % NUM_BUTTONS;
    }
}

void get_player_sequence(int sequence[], int length)
{
    for (int i = 0; i < length; i++)
    {
        scanf("%d", &sequence[i]);
    }
}

int compare_sequence(int seq1[], int seq2[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (seq1[i] != seq2[i])
        {
            return 0;
        }
    }
    return 1;
}

void play_game()
{
    int sequence_length = 1;
    int game_over = 0;
    generate_sequence(simon_sequence, sequence_length);
    while (!game_over)
    {
        printf("Simon's sequence:\n");
        display_sequence(simon_sequence, sequence_length);
        printf("Your turn:\n");
        get_player_sequence(player_sequence, sequence_length);
        if (compare_sequence(simon_sequence, player_sequence, sequence_length))
        {
            printf("Correct!\n");
            score++;
            sequence_length++;
            if (sequence_length > MAX_SEQUENCE)
            {
                printf("You win!\n");
                game_over = 1;
            }
            else
            {
                generate_sequence(simon_sequence, sequence_length);
            }
        }
        else
        {
            printf("Incorrect. Final score: %d\n", score);
            game_over = 1;
        }
    }
}

int main()
{
    printf("Welcome to Simon!\n");
    printf("Press any key to start.\n");
    getchar();
    play_game();
    return 0;
}
