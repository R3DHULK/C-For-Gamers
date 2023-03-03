#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 30
#define HEIGHT 10
#define STARTING_X 2
#define STARTING_Y HEIGHT - 1

int x, y;
int game_over = 0;
int score = 0;

char grid[HEIGHT][WIDTH] = {
    "##############################",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "##############################"};

void draw_grid()
{
    system("clear");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("%s\n", grid[i]);
    }
    printf("Score: %d\n", score);
}

void move_frogger(int dx, int dy)
{
    int new_x = x + dx;
    int new_y = y + dy;

    if (new_x < 0 || new_x >= WIDTH)
    {
        return;
    }

    if (new_y < 0 || new_y >= HEIGHT)
    {
        return;
    }

    if (grid[new_y][new_x] == '#')
    {
        return;
    }

    if (new_y < y)
    {
        score += 10;
    }

    x = new_x;
    y = new_y;
}

void spawn_cars()
{
    for (int i = 1; i < HEIGHT - 1; i++)
    {
        if (rand() % 2 == 0)
        {
            grid[i][0] = '#';
        }
        else
        {
            grid[i][WIDTH - 1] = '#';
        }
    }
}

void move_cars()
{
    for (int i = 1; i < HEIGHT - 1; i++)
    {
        if (grid[i][0] == '#')
        {
            grid[i][0] = ' ';
            grid[i][WIDTH - 1] = '#';
        }
        else
        {
            grid[i][WIDTH - 1] = ' ';
            grid[i][0] = '#';
        }
    }
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main()
{
    x = STARTING_X;
    y = STARTING_Y;

    srand(time(NULL));

    while (!game_over)
    {
        draw_grid();

        if (kbhit())
        {
            char input = getchar();
            switch (input)
            {
            case 'w':
                move_frogger(0, -1);
                break;
            case 's':
                move_frogger(0, 1);
                break;
            case 'a':
                move_frogger(-1, 0);
                break;
            case 'd':
                move_frogger(1, 0);
                break;
            case 'q':
                game_over = 1;
                break;
            }
        }

        spawn_cars();
        move_cars();

        if (grid[y][x] == '#')
        {
            game_over = 1;
        }

        usleep(100);
    }

    printf("Game Over! Final score: %d\n", score);

    return 0;
}

