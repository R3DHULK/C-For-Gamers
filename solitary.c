#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define FOUNDATION_SIZE 4
#define TABLEAU_SIZE 7

typedef enum
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
} Suit;

typedef struct
{
    Suit suit;
    int rank;
} Card;

int main()
{
    // initialize deck
    Card deck[DECK_SIZE];
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 1; j <= 13; j++)
        {
            deck[i * 13 + j - 1].suit = i;
            deck[i * 13 + j - 1].rank = j;
        }
    }

    // shuffle deck
    srand(time(NULL));
    for (i = 0; i < DECK_SIZE; i++)
    {
        int r = rand() % DECK_SIZE;
        Card temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }

    // initialize foundation and tableau
    Card foundation[FOUNDATION_SIZE][13] = {0};
    Card tableau[TABLEAU_SIZE][13] = {0};
    int foundation_counts[FOUNDATION_SIZE] = {0};
    int tableau_counts[TABLEAU_SIZE] = {0};
    for (i = 0; i < TABLEAU_SIZE; i++)
    {
        tableau[i][0] = deck[i];
        tableau_counts[i] = 1;
    }
    for (i = TABLEAU_SIZE; i < TABLEAU_SIZE + 4; i++)
    {
        foundation[i - TABLEAU_SIZE][0] = deck[i];
        foundation_counts[i - TABLEAU_SIZE] = 1;
    }

    // play game
    int game_won = 0;
    while (!game_won)
    {
        // print game state
        printf("\nFoundation:\n");
        for (i = 0; i < FOUNDATION_SIZE; i++)
        {
            printf("%d: ", i);
            for (j = 0; j < foundation_counts[i]; j++)
            {
                printf("%d", foundation[i][j].rank);
                switch (foundation[i][j].suit)
                {
                case Hearts:
                    printf("H ");
                    break;
                case Diamonds:
                    printf("D ");
                    break;
                case Clubs:
                    printf("C ");
                    break;
                case Spades:
                    printf("S ");
                    break;
                }
            }
            printf("\n");
        }

        printf("\nTableau:\n");
        for (i = 0; i < TABLEAU_SIZE; i++)
        {
            printf("%d: ", i);
            for (j = 0; j < tableau_counts[i]; j++)
            {
                if (j == tableau_counts[i] - 1)
                {
                    if (tableau[i][j].rank == 1)
                    {
                        printf("A");
                    }
                    else if (tableau[i][j].rank == 10)
                    {
                        printf("0");
                    }
                    else if (tableau[i][j].rank == 11)
                    {
                        printf("J");
                    }
                    else if (tableau[i][j].rank == 12)
                    {
                        printf("Q");
                    }
                    else if (tableau[i][j].rank == 13)
                    {
                        printf("K");
                    }
                    else
                    {
                        printf("%d", tableau[i][j].rank);
                    }
                    switch (tableau[i][j].suit)
                    {
                    case Hearts:
                        printf("H ");
                        break;
                    case Diamonds:
                        printf("D ");
                        break;
                    case Clubs:
                        printf("C ");
                        break;
                    case Spades:
                        printf("S ");
                        break;
                    default:
                        printf("  ");
                        break;
                    }

                    if (tableau[i][j].rank == 1)
                    {
                        printf("A");
                    }
                    else if (tableau[i][j].rank >= 2 && tableau[i][j].rank <= 10)
                    {
                        printf("%d", tableau[i][j].rank);
                    }
                    else if (tableau[i][j].rank == 11)
                    {
                        printf("J");
                    }
                    else if (tableau[i][j].rank == 12)
                    {
                        printf("Q");
                    }
                    else if (tableau[i][j].rank == 13)
                    {
                        printf("K");
                    }
                    else
                    {
                        printf(" ");
                    }
                    // get move from user
                    int move_from, move_to, move_count;
                    printf("\nEnter move (from to count): ");
                    scanf("%d %d %d", &move_from, &move_to, &move_count);
                    // validate move
                    if (move_from < 0 || move_from >= TABLEAU_SIZE ||
                        move_to < 0 || move_to >= TABLEAU_SIZE + FOUNDATION_SIZE ||
                        move_count <= 0 ||
                        (move_from >= TABLEAU_SIZE && move_to >= TABLEAU_SIZE) ||
                        (move_from < TABLEAU_SIZE && move_to < TABLEAU_SIZE &&
                         tableau_counts[move_to] > 0 &&
                         tableau[move_from][move_count - 1].rank >= tableau[move_to][tableau_counts[move_to] - 1].rank))
                    {
                        printf("Invalid move. Try again.\n");
                        continue;
                    }

                    // execute move
                    if (move_to >= TABLEAU_SIZE)
                    {
                        // move to foundation
                        if (tableau_counts[move_from] < move_count)
                        {
                            printf("Invalid move. Try again.\n");
                            continue;
                        }
                        int suit = tableau[move_from][move_count - 1].suit;
                        int rank = tableau[move_from][move_count - 1].rank;
                        if (foundation_counts[suit] == 0 && rank == 1 ||
                            foundation_counts[suit] > 0 && foundation[suit][foundation_counts[suit] - 1].rank == rank - 1)
                        {
                            foundation[suit][foundation_counts[suit]] = tableau[move_from][move_count - 1];
                            foundation_counts[suit]++;
                            tableau_counts[move_from] -= move_count;
                        }
                        else
                        {
                            printf("Invalid move. Try again.\n");
                            continue;
                        }
                    }
                    else
                    {
                        // move to tableau
                        if (tableau_counts[move_to] > 0 &&
                            tableau[move_to][tableau_counts[move_to] - 1].rank - tableau[move_from][move_count - 1].rank != 1)
                        {
                            printf("Invalid move. Try again.\n");
                            continue;
                        }
                        for (i = 0; i < move_count; i++)
                        {
                            tableau[move_to][tableau_counts[move_to]] = tableau[move_from][tableau_counts[move_from] - move_count + i];
                            tableau_counts[move_to]++;
                        }
                        tableau_counts[move_from] -= move_count;
                        if (tableau_counts[move_from] > 0 && !tableau[move_from][tableau_counts[move_from] - 1].rank)
                        {
                            tableau_counts[move_from]--;
                        }
                    }

                    // check for game win
                    game_won = 1;
                    for (i = 0; i < FOUNDATION_SIZE; i++)
                    {
                        if (foundation_counts[i] != 13)
                        {
                            game_won = 0;
                            break;
                        }
                    }
                }

                // print game won message
                printf("\nYou won the game!\n");

            } // <-- remove the extra double-quote here

        } // end of for loop for printing tableau
    }     // end of for loop for playing game

    return 0;
}
