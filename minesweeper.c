#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10
#define NUM_MINES 10

int board[BOARD_HEIGHT][BOARD_WIDTH];
int revealed[BOARD_HEIGHT][BOARD_WIDTH];

void init_board()
{
    // Initialize the game board with random mine locations
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = 0;
            revealed[i][j] = 0;
        }
    }
    int num_mines_placed = 0;
    while (num_mines_placed < NUM_MINES)
    {
        int x = rand() % BOARD_WIDTH;
        int y = rand() % BOARD_HEIGHT;
        if (board[y][x] == 0)
        {
            board[y][x] = 9; // 9 represents a mine
            num_mines_placed++;
        }
    }
}

void display_board()
{
    // Display the game board using ASCII characters
    printf("  ");
    for (int j = 0; j < BOARD_WIDTH; j++)
    {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (revealed[i][j])
            {
                if (board[i][j] == 9)
                {
                    printf("* ");
                }
                else
                {
                    printf("%d ", board[i][j]);
                }
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int count_adjacent_mines(int x, int y)
{
    // Count the number of adjacent mines to a cell
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (i >= 0 && i < BOARD_HEIGHT && j >= 0 && j < BOARD_WIDTH && board[i][j] == 9)
            {
                count++;
            }
        }
    }
    return count;
}

void reveal_cell(int x, int y)
{
    // Recursively reveal cells and their neighbors
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT || revealed[y][x])
    {
        return;
    }
    revealed[y][x] = 1;
    if (board[y][x] == 0)
    {
        // Reveal neighbors recursively
        for (int i = y - 1; i <= y + 1; i++)
        {
            for (int j = x - 1; j <= x + 1; j++)
            {
                reveal_cell(j, i);
            }
        }
    }
}

int main()
{
    // Set up the game board and initialize the random number generator
    srand(time(NULL));
    init_board();

    // Set up the game loop
    int game_over = 0;
    int num_cells_revealed = 0;
    while (!game_over)
    {
        // Display the game board and prompt for input
        display_board();
        printf("Enter x and y coordinates to reveal (e.g. '3 4'): ");
        int x, y;
        scanf("%d %d", &x, &y);

        // Reveal the selected
        if (board[y][x] == 9)
        {
            // Game over if a mine is revealed
            game_over = 1;
        }
        else
        {
            // Otherwise, reveal the selected cell and update the number of cells revealed
            reveal_cell(x, y);
            num_cells_revealed++;
        }

        // Check for win condition
        if (num_cells_revealed == BOARD_WIDTH * BOARD_HEIGHT - NUM_MINES)
        {
            printf("You win!\n");
            game_over = 1;
        }
    }

    // Display the final game board
    display_board();

    return 0;
}
