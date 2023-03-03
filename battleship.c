#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define SHIP_SIZE 5
#define EMPTY_CELL '-'
#define SHIP_CELL 'S'
#define HIT_CELL 'X'
#define MISS_CELL 'O'

void init_board(char board[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = EMPTY_CELL;
        }
    }
}

void place_ship(char board[][BOARD_SIZE], int size)
{
    int row, col, direction;
    int valid_position = 0;

    while (!valid_position)
    {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
        direction = rand() % 2;

        if (direction == 0)
        {
            if (row + size <= BOARD_SIZE)
            {
                valid_position = 1;
                for (int i = row; i < row + size; i++)
                {
                    if (board[i][col] != EMPTY_CELL)
                    {
                        valid_position = 0;
                        break;
                    }
                }
                if (valid_position)
                {
                    for (int i = row; i < row + size; i++)
                    {
                        board[i][col] = SHIP_CELL;
                    }
                }
            }
        }
        else
        {
            if (col + size <= BOARD_SIZE)
            {
                valid_position = 1;
                for (int i = col; i < col + size; i++)
                {
                    if (board[row][i] != EMPTY_CELL)
                    {
                        valid_position = 0;
                        break;
                    }
                }
                if (valid_position)
                {
                    for (int i = col; i < col + size; i++)
                    {
                        board[row][i] = SHIP_CELL;
                    }
                }
            }
        }
    }
}

int is_valid_move(int row, int col)
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

int make_move(char board[][BOARD_SIZE], int row, int col)
{
    if (!is_valid_move(row, col))
    {
        return 0;
    }

    switch (board[row][col])
    {
    case EMPTY_CELL:
        board[row][col] = MISS_CELL;
        return 1;
    case SHIP_CELL:
        board[row][col] = HIT_CELL;
        return 2;
    default:
        return 0;
    }
}

int main()
{
    char board[BOARD_SIZE][BOARD_SIZE];
    int num_ships = 0, num_hits = 0, num_misses = 0;
    int row, col, result;

    srand(time(NULL));

    init_board(board);

    while (num_ships < SHIP_SIZE)
    {
        place_ship(board, SHIP_SIZE);
        num_ships++;
    }

    printf("Welcome to Battleship!\n");

    while (num_hits < SHIP_SIZE)
    {
        printf("Ships left: %d\n", SHIP_SIZE - num_hits);
        printf("Misses: %d\n", num_misses);
        printf("  ");
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            printf("%d ", i);
        }
        printf("\n");
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            printf("%d ", i);
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }

        printf("Enter row and column to hit (e.g. 1 2): ");
        scanf("%d %d", &row, &col);

        result = make_move(board, row, col);

        if (result == 0)
        {
            printf("Invalid move!\n");
        }
        else if (result == 1)
        {
            printf("Miss!\n");
            num_misses++;
        }
        else if (result == 2)
        {
            printf("Hit!\n");
            num_hits++;
        }
    }

    printf("Congratulations, you sank all the ships!\n");
    printf("Final score: %d misses\n", num_misses);

    return 0;
}
