#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 7

#define EMPTY 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2

int board[ROWS][COLS];

void init_board()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = EMPTY;
        }
    }
}

void print_board()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("|");
            switch (board[i][j])
            {
            case EMPTY:
                printf(" ");
                break;
            case PLAYER_ONE:
                printf("X");
                break;
            case PLAYER_TWO:
                printf("O");
                break;
            }
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
}

bool check_win(int player)
{
    // Check horizontal
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS - 3; j++)
        {
            if (board[i][j] == player &&
                board[i][j + 1] == player &&
                board[i][j + 2] == player &&
                board[i][j + 3] == player)
            {
                return true;
            }
        }
    }

    // Check vertical
    for (int i = 0; i < ROWS - 3; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == player &&
                board[i + 1][j] == player &&
                board[i + 2][j] == player &&
                board[i + 3][j] == player)
            {
                return true;
            }
        }
    }

    // Check diagonal (down-right)
    for (int i = 0; i < ROWS - 3; i++)
    {
        for (int j = 0; j < COLS - 3; j++)
        {
            if (board[i][j] == player &&
                board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player &&
                board[i + 3][j + 3] == player)
            {
                return true;
            }
        }
    }

    // Check diagonal (down-left)
    for (int i = 0; i < ROWS - 3; i++)
    {
        for (int j = 3; j < COLS; j++)
        {
            if (board[i][j] == player &&
                board[i + 1][j - 1] == player &&
                board[i + 2][j - 2] == player &&
                board[i + 3][j - 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}

bool check_full()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

int get_move(int player)
{
    int col;
    do
    {
        printf("Player %d, choose a column (1-7): ", player);
        scanf("%d", &col);
        col--;
    } while (col < 0 || col >= COLS || board[0][col] != EMPTY);
    // Insert the player's piece into the selected column
    for (int i = ROWS - 1; i >= 0; i--)
    {
        if (board[i][col] == EMPTY)
        {
            board[i][col] = player;
            return i;
        }
    }
    return -1; // This should never happen if check_full() is called first
}

int main()
{
    int turn = PLAYER_ONE;
    int row, col;
    init_board();
    print_board();

    while (true)
    {
        col = get_move(turn);
        row = get_move(col);
        board[row][col] = turn;

        print_board();

        if (check_win(turn))
        {
            printf("Player %d wins!\n", turn);
            break;
        }
        else if (check_full())
        {
            printf("Game over! It's a tie.\n");
            break;
        }

        turn = (turn == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    }

    return 0;
}

