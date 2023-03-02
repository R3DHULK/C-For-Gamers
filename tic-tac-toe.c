#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 3

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j != BOARD_SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i != BOARD_SIZE - 1)
            printf("---+---+---\n");
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char symbol)
{
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int win = 1;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != symbol)
            {
                win = 0;
                break;
            }
        }
        if (win)
            return 1;
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        int win = 1;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i][j] != symbol)
            {
                win = 0;
                break;
            }
        }
        if (win)
            return 1;
    }

    // Check diagonals
    int win = 1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][i] != symbol)
        {
            win = 0;
            break;
        }
    }
    if (win)
        return 1;

    win = 1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][BOARD_SIZE - 1 - i] != symbol)
        {
            win = 0;
            break;
        }
    }
    if (win)
        return 1;

    return 0;
}

int main()
{
    char board[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Player 1 uses 'X' and Player 2 uses 'O'.\n");
    printf("The board is numbered like this:\n");
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n");

    int player = 1;
    int moves = 0;
    while (1)
    {
        printf("Player %d's turn:\n", player);

        int row, col, pos;
        do
        {
            printf("Enter a position (1-9): ");
            scanf("%d", &pos);
            row = (pos - 1) / BOARD_SIZE;
            col = (pos - 1) % BOARD_SIZE;
        } while (pos < 1 || pos > BOARD_SIZE * BOARD_SIZE || board[row][col] != ' ');

        board[row][col] = (player == 1) ? 'X' : 'O';
        moves++;
        print_board(board);

        if (check_win(board, (player == 1) ? 'X' : 'O'))
        {
            printf("Player %d wins!\n", player);
            break;
        }

        if (moves == BOARD_SIZE * BOARD_SIZE)
        {
            printf("Tie game!\n");
            break;
        }

        player = (player == 1) ? 2 : 1;
    }

    return 0;
}
