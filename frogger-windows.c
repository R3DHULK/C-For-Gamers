#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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
    system("cls");
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

int main()
{
    x = STARTING_X;
    y = STARTING_Y;

    while (!game_over)
    {
        draw_grid();

        if (_kbhit())
        {
            switch (_getch())
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

        Sleep(100);
    }

    printf("Game Over! Final score: %d\n", score);

    return 0;
}
