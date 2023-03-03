#include <stdio.h>

#define BOARD_SIZE 8

void print_board(int board[BOARD_SIZE][BOARD_SIZE])
{
    printf("  1 2 3 4 5 6 7 8\n");
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        printf("%d ", row + 1);
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            switch (board[row][col])
            {
            case 0:
                printf("- ");
                break;
            case 1:
                printf("x ");
                break;
            case 2:
                printf("o ");
                break;
            case 3:
                printf("X ");
                break;
            case 4:
                printf("O ");
                break;
            }
        }
        printf("%d\n", row + 1);
    }
    printf("  1 2 3 4 5 6 7 8\n");
}

int main()
{
    // initialize the board
    int board[BOARD_SIZE][BOARD_SIZE] = {
        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 0, 2, 0},
    };

    // play the game
    int player = 1;
    while (1)
    {
        // print the board
        printf("\n");
        print_board(board);

        // prompt user for input
        printf("\nPlayer %d's turn. Enter move (ex: '3a 4b'): ", player);
        char input[10];
        fgets(input, 10, stdin);

        // parse input
        int from_row = input[0] - '1';
        int from_col = input[1] - 'a';
        int to_row = input[3] - '1';
        int to_col = input[4] - 'a';

        // check if move is valid
        if (board[from_row][from_col] == player || board[from_row][from_col] == player + 2)
        {
            if (to_row >= 0 && to_row < BOARD_SIZE && to_col >= 0 && to_col < BOARD_SIZE)
            {
                if (board[to_row][to_col] == 0)
                {
                    if (player == 1)
                    {
                        if (to_row == from_row - 1 && (to_col == from_col - 1 || to_col == from_col + 1))
                        {
                            board[to_row][to_col] = player;
                            board[from_row][from_col] = 0;
                            player = 2;
                        }
                        else if (to_row == from_row - 2 && (to_col == from_col - 2 || to_col == from_col + 2))
                        {
                            int captured_row = (from_row + to_row) / 2;
                            int captured_col = (from_col + to_col) / 2;
                            if (board[captured_row][captured_col] == 2 || board[captured_row][captured_col] == 4)
                            {
                                board[to_row][to_col] = player;
                                board[from_row][from_col] = 0;
                                board[captured_row][captured_col] = 0;
                                player = 2;
                            }
                            else
                            {
                                printf("Invalid move. Try again.\n");
                            }
                        }
                        else
                        {
                            printf("Invalid move. Try again.\n");
                        }
                    }
                    else if (player == 2)
                    {
                        if (to_row == from_row + 1 && (to_col == from_col - 1 || to_col == from_col + 1))
                        {
                            board[to_row][to_col] = player;
                            board[from_row][from_col] = 0;
                            player = 1;
                        }
                        else if (to_row == from_row + 2 && (to_col == from_col - 2 || to_col == from_col + 2))
                        {
                            int captured_row = (from_row + to_row) / 2;
                            int captured_col = (from_col + to_col) / 2;
                            if (board[captured_row][captured_col] == 1 || board[captured_row][captured_col] == 3)
                            {
                                board[to_row][to_col] = player;
                                board[from_row][from_col] = 0;
                                board[captured_row][captured_col] = 0;
                                player = 1;
                            }
                            else
                            {
                                printf("Invalid move. Try again.\n");
                            }
                        }
                        else
                        {
                            printf("Invalid move. Try again.\n");
                        }
                    }
                }
                else
                {
                    printf("Invalid move. Try again.\n");
                }
            }
            else
            {
                printf("Invalid move. Try again.\n");
            }
        }
        else
        {
            printf("Invalid move. Try again.\n");
        }
    }
    printf("Player %d wins!\n", player == 1 ? 2 : 1);
    return 0;
}
