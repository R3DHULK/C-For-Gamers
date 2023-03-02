#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define DECK_SIZE 52
#define MAX_HAND_SIZE 10

int deck[DECK_SIZE];
int num_cards_in_deck = 0;

int player_hand[MAX_HAND_SIZE];
int num_cards_in_player_hand = 0;

int dealer_hand[MAX_HAND_SIZE];
int num_cards_in_dealer_hand = 0;

void initialize_deck()
{
    // Initialize the deck with all cards in order
    for (int i = 0; i < DECK_SIZE; i++)
    {
        deck[i] = i;
    }
    num_cards_in_deck = DECK_SIZE;
}

void shuffle_deck()
{
    // Shuffle the deck using the Fisher-Yates shuffle algorithm
    for (int i = num_cards_in_deck - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

int get_card_value(int card)
{
    // Get the value of a card, with face cards worth 10 and aces worth 1 or 11
    int value = (card % 13) + 1;
    if (value > 10)
    {
        value = 10;
    }
    if (value == 1)
    {
        // Check if the ace should be worth 11
        int hand_value = 0;
        for (int i = 0; i < num_cards_in_player_hand; i++)
        {
            int card_value = get_card_value(player_hand[i]);
            hand_value += card_value;
        }
        if (hand_value + 11 <= 21)
        {
            value = 11;
        }
    }
    return value;
}

void deal_card(int hand[], int *num_cards_in_hand)
{
    // Deal a card from the deck and add it to the specified hand
    int card = deck[num_cards_in_deck - 1];
    hand[*num_cards_in_hand] = card;
    (*num_cards_in_hand)++;
    num_cards_in_deck--;
}

void print_hand(int hand[], int num_cards_in_hand)
{
    // Print the specified hand
    for (int i = 0; i < num_cards_in_hand; i++)
    {
        int card = hand[i];
        int rank = (card % 13) + 1;
        char suit;
        switch (card / 13)
        {
        case 0:
            suit = 'C';
            break;
        case 1:
            suit = 'D';
            break;
        case 2:
            suit = 'H';
            break;
        case 3:
            suit = 'S';
            break;
        }
        printf("%d%c ", rank, suit);
    }
    printf("\n");
}

int get_hand_value(int hand[], int num_cards_in_hand)
{
    // Get the value of the specified hand
    int value = 0;
    int num_aces = 0;
    for (int i = 0; i < num_cards_in_hand; i++)
    {
        int card_value = get_card_value(hand[i]);
        value += card_value;
        if (card_value == 1)
        {
            num_aces++;
        }
    }
    // Check if any aces should be worth 11
    for (int i = 0; i < num_aces; i++)
    {
        if (value + 10 <= 21)
        {
            value += 10;
        }
    }
    return value;
}

bool player_turn()
{
    char choice;
    while (true)
    {
        cout << "Do you want to hit or stand? (h/s) ";
        cin >> choice;
        if (choice == 'h')
        {
            draw_card(player_hand);
            print_hand(player_hand, "Player");
            if (hand_value(player_hand) > 21)
            {
                cout << "You busted! Dealer wins." << endl;
                return false;
            }
        }
        else if (choice == 's')
        {
            cout << "Player stands." << endl;
            return true;
        }
        else
        {
            cout << "Invalid input. Please enter 'h' or 's'." << endl;
        }
    }
}

void dealer_turn()
{
    cout << endl
         << "Dealer's turn." << endl;
    print_hand(dealer_hand, "Dealer");
    while (hand_value(dealer_hand) < 17)
    {
        draw_card(dealer_hand);
        print_hand(dealer_hand, "Dealer");
        if (hand_value(dealer_hand) > 21)
        {
            cout << "Dealer busted! Player wins." << endl;
            return;
        }
    }
    cout << "Dealer stands." << endl;
}

void play_game()
{
    bool player_wins = false;
    initialize_deck();
    shuffle_deck();
    deal_cards();
    print_hand(player_hand, "Player");
    print_dealer_hand();

    // Player's turn
    if (player_turn())
    {
        // Dealer's turn
        dealer_turn();

        // Determine winner
        int player_hand_value = hand_value(player_hand);
        int dealer_hand_value = hand_value(dealer_hand);
        if (player_hand_value > dealer_hand_value || dealer_hand_value > 21)
        {
            cout << "Player wins!" << endl;
            player_wins = true;
        }
        else if (player_hand_value == dealer_hand_value)
        {
            cout << "It's a tie!" << endl;
        }
        else
        {
            cout << "Dealer wins." << endl;
        }
    }

    // Calculate the score
    int score = 0;
    if (player_wins)
    {
        score += 10;
        if (hand_value(player_hand) == 21)
        {
            score += 5;
        }
    }
    else
    {
        score -= 10;
    }
    cout << "Score: " << score << endl;
}

int main()
{
    srand(time(NULL));
    char play_again;
    do
    {
        play_game();
        cout << "Do you want to play again? (y/n) ";
        cin >> play_again;
    } while (play_again == 'y');
    return 0;
}
