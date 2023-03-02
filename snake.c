#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20
#define SNAKE_LENGTH 5

typedef struct
{
    int x;
    int y;
} Point;

typedef struct Node
{
    Point pos;
    struct Node *next;
} Node;

Node *snake;

void init_snake()
{
    // Initialize the snake with a few segments
    snake = malloc(sizeof(Node));
    snake->pos.x = BOARD_WIDTH / 2;
    snake->pos.y = BOARD_HEIGHT / 2;
    snake->next = NULL;
    for (int i = 1; i < SNAKE_LENGTH; i++)
    {
        Node *segment = malloc(sizeof(Node));
        segment->pos.x = snake->pos.x - i;
        segment->pos.y = snake->pos.y;
        segment->next = snake;
        snake = segment;
    }
}

void display_board(char board[BOARD_HEIGHT][BOARD_WIDTH])
{
    // Display the game board using ASCII characters
    system("cls"); // Clear the console
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}

void update_snake(Point dir, char board[BOARD_HEIGHT][BOARD_WIDTH])
{
    // Update the snake's position based on its current direction
    Node *head = snake;
    Point new_head = {head->pos.x + dir.x, head->pos.y + dir.y};
    Node *new_segment = malloc(sizeof(Node));
    new_segment->pos = new_head;
    new_segment->next = head;
    snake = new_segment;
    board[new_head.y][new_head.x] = 'o'; // Add new head to board
    if (board[new_head.y][new_head.x] == 'X')
    { // Check for collision with food
        // Increase snake length and place new food
        // TODO: Implement this
    }
    else
    {
        // Remove tail from board and free its memory
        Node *tail = head;
        while (tail->next->next != NULL)
        {
            tail = tail->next;
        }
        board[tail->next->pos.y][tail->next->pos.x] = ' ';
        free(tail->next);
        tail->next = NULL;
    }
}

int main()
{
    // Set up the game board and initialize the snake
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = ' ';
        }
    }
    init_snake();
    Point dir = {1, 0}; // Snake starts moving to the right

    // Set up the game loop
    int game_over = 0;
    while (!game_over)
    {
        // Update the game state
        update_snake(dir, board);
        display_board(board);

        // Handle user input
        if (_kbhit())
        { // Check if a key has been pressed
            char key = _getch();
            switch (key)
            {
            case 'w':
                dir = (Point){0, -1};
                break;
            case 'a':
                dir = (Point){-1, 0};
                break;
            case 's':
                dir = (Point){0, 1};
            case 'd':
                dir = (Point){1, 0};
                break;
            case 'q':
                game_over = 1;
                break;
            default:
                break;
            }
        }

        // Pause for a short time before updating the game again
        clock_t start_time = clock();
        while (clock() < start_time + 1000 / 10)
        {
        }

        // TODO: Check for game over conditions (e.g. collision with wall or self)
    }

    // Free memory used by snake
    while (snake != NULL)
    {
        Node *next = snake->next;
        free(snake);
        snake = next;
    }

    return 0;
}
