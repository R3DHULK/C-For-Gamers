#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 2
#define NUM_CARDS 5
#define NUM_RANKS 13
#define NUM_SUITS 4

enum rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};
enum suit
{
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

struct card
{
    enum rank card_rank;
    enum suit card_suit;
};

typedef struct card Card;

void shuffle_deck(Card *deck);
void print_card(Card card);
void print_hand(Card hand[NUM_CARDS]);
int evaluate_hand(Card hand[NUM_CARDS]);

int main()
{
    Card deck[NUM_RANKS * NUM_SUITS];
    Card hands[NUM_PLAYERS][NUM_CARDS];
    int i, j, player1_score, player2_score;

    // Initialize deck
    for (i = 0; i < NUM_RANKS; i++)
    {
        for (j = 0; j < NUM_SUITS; j++)
        {
            deck[i * NUM_SUITS + j].card_rank = i;
            deck[i * NUM_SUITS + j].card_suit = j;
        }
    }

    // Shuffle deck
    shuffle_deck(deck);

    // Deal cards to players
    for (i = 0; i < NUM_PLAYERS; i++)
    {
        for (j = 0; j < NUM_CARDS; j++)
        {
            hands[i][j] = deck[i * NUM_CARDS + j];
        }
    }

    // Print hands
    printf("Player 1's hand:\n");
    print_hand(hands[0]);
    printf("\n");
    printf("Player 2's hand:\n");
    print_hand(hands[1]);
    printf("\n");

    // Evaluate hands
    player1_score = evaluate_hand(hands[0]);
    player2_score = evaluate_hand(hands[1]);

    // Print winner
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2_score > player1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie game!\n");
    }

    return 0;
}

void shuffle_deck(Card *deck)
{
    int i, j;
    Card temp;
    srand(time(NULL));
    for (i = 0; i < NUM_RANKS * NUM_SUITS; i++)
    {
        j = rand() % (NUM_RANKS * NUM_SUITS);
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void print_card(Card card)
{
    switch (card.card_rank)
    {
    case Ace:
        printf("A");
        break;
    case Two:
        printf("2");
        break;
    case Three:
        printf("3");
        break;
    case Four:
        printf("4");
        break;
    case Five:
        printf("5");
        break;
    case Six:
        printf("6");
        break;
    case Seven:
        printf("7");
        break;
    case Eight:
        printf("8");
        break;
    case Nine:
        printf("9");
        break;
    case Ten:
        printf("T");
        break;
    case Jack:
        printf("J");
        break;
    case Queen:
        printf("Q");
        break;
    case King:
        printf("K");
        break;
    }
    switch (card.card_suit)
    {
    case Clubs:
        printf("C");
        break;
    case Diamonds:
        printf("D");
        break;
    case Hearts:
        printf("H");
        break;
    case Spades:
        printf("S");
        break;
    }
}
void print_hand(Card hand[NUM_CARDS])
{
    int i;
    for (i = 0; i < NUM_CARDS; i++)
    {
        print_card(hand[i]);
        printf(" ");
    }
}

int evaluate_hand(Card hand[NUM_CARDS])
{
    int i, j, rank_count[NUM_RANKS] = {0}, suit_count[NUM_SUITS] = {0}, pair_count = 0, three_count = 0, four_count = 0, flush = 0, straight = 0, straight_flush = 0, royal_flush = 0;
    for (i = 0; i < NUM_CARDS; i++)
    {
        rank_count[hand[i].card_rank]++;
        suit_count[hand[i].card_suit]++;
    }
    for (i = 0; i < NUM_RANKS; i++)
    {
        if (rank_count[i] == 2)
        {
            pair_count++;
        }
        else if (rank_count[i] == 3)
        {
            three_count++;
        }
        else if (rank_count[i] == 4)
        {
            four_count++;
        }
    }
    for (i = 0; i < NUM_SUITS; i++)
    {
        if (suit_count[i] == NUM_CARDS)
        {
            flush = 1;
        }
    }
    for (i = 0; i < NUM_RANKS - NUM_CARDS + 1; i++)
    {
        straight = 1;
        for (j = i; j < i + NUM_CARDS; j++)
        {
            if (rank_count[j] != 1)
            {
                straight = 0;
            }
        }
        if (straight)
        {
            break;
        }
    }
    if (straight && flush)
    {
        straight_flush = 1;
    }
    if (straight_flush && rank_count[Ten] && rank_count[Jack] && rank_count[Queen] && rank_count[King] && rank_count[Ace])
    {
        royal_flush = 1;
    }
    if (royal_flush)
    {
        return 10;
    }
    else if (straight_flush)
    {
        return 9;
    }
    else if (four_count)
    {
        return 8;
    }
    else if (three_count && pair_count == 1)
    {
        return 7;
    }
    else if (flush)
    {
        return 6;
    }
    else if (straight)
    {
        return 5;
    }
    else if (three_count)
    {
        return 4;
    }
    else if (pair_count == 2)
    {
        return 3;
    }
    else if (pair_count == 1)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}
