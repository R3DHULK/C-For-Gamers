#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 70
#define HEIGHT 20

int ball_x, ball_y, ball_dx, ball_dy;
int paddle_x;
int brick[WIDTH][HEIGHT];
int score, lives;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void init_game()
{
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    ball_dx = 1;
    ball_dy = -1;
    paddle_x = WIDTH / 2 - 3;
    score = 0;
    lives = 3;
    int i, j;
    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            brick[i][j] = 1;
        }
    }
}

void draw_borders()
{
    int i;
    for (i = 0; i < WIDTH + 2; i++)
    {
        gotoxy(i, 0);
        printf("*");
        gotoxy(i, HEIGHT + 1);
        printf("*");
    }
    for (i = 0; i < HEIGHT + 2; i++)
    {
        gotoxy(0, i);
        printf("*");
        gotoxy(WIDTH + 1, i);
        printf("*");
    }
}

void draw_ball()
{
    gotoxy(ball_x, ball_y);
    set_color(12);
    printf("O");
    set_color(7);
}

void draw_paddle()
{
    int i;
    for (i = 0; i < 6; i++)
    {
        gotoxy(paddle_x + i, HEIGHT);
        printf("=");
    }
}

void draw_bricks()
{
    int i, j;
    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            if (brick[i][j])
            {
                gotoxy(i + 1, j + 1);
                set_color(10);
                printf("#");
                set_color(7);
            }
        }
    }
}

void draw_stats()
{
    gotoxy(1, HEIGHT + 3);
    printf("Score: %d", score);
    gotoxy(WIDTH - 9, HEIGHT + 3);
    printf("Lives: %d", lives);
}

void move_ball()
{
    gotoxy(ball_x, ball_y);
    printf(" ");
    ball_x += ball_dx;
    ball_y += ball_dy;
    if (ball_x < 1 || ball_x > WIDTH)
    {
        ball_dx = -ball_dx;
    }
    if (ball_y < 1)
    {
        ball_dy = -ball_dy;
    }
    if (ball_y > HEIGHT)
    {
        lives--;
        if (lives == 0)
        {
            gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
            printf("Game Over");
            getch();
            exit(0);
        }
        else
        {
            init_game();
        }
    }
}

void move_paddle()
{
    if (kbhit())
    {
        char key = getch();
        if (key == 'a' && paddle_x > 1)
        {
            paddle_x--;
        }
        // Move the paddle to the right
        if (key == 'd' && paddle_x < WIDTH - PADDLE_WIDTH)
        {
            paddle_x += PADDLE_SPEED;
        }
        // Move the paddle to the left
        else if (key == 'a' && paddle_x > 0)
        {
            paddle_x -= PADDLE_SPEED;
        }

        // Check for collision with the paddle
        if (ball_y + BALL_SIZE == HEIGHT - PADDLE_OFFSET &&
            ball_x >= paddle_x && ball_x <= paddle_x + PADDLE_WIDTH)
        {
            ball_dy = -ball_dy;
            score++;
        }

        // Check for collision with the bricks
        for (int i = 0; i < NUM_BRICKS; i++)
        {
            if (bricks[i].visible)
            {
                if (ball_x + BALL_SIZE >= bricks[i].x &&
                    ball_x <= bricks[i].x + BRICK_WIDTH &&
                    ball_y + BALL_SIZE >= bricks[i].y &&
                    ball_y <= bricks[i].y + BRICK_HEIGHT)
                {
                    bricks[i].visible = false;
                    ball_dy = -ball_dy;
                    score++;
                    break;
                }
            }
        }

        // Draw the paddle
        for (int i = 0; i < PADDLE_WIDTH; i++)
        {
            display[paddle_x + i][HEIGHT - PADDLE_OFFSET] = PADDLE_CHAR;
        }

        // Draw the ball
        display[ball_x][ball_y] = BALL_CHAR;

        // Draw the bricks
        for (int i = 0; i < NUM_BRICKS; i++)
        {
            if (bricks[i].visible)
            {
                for (int j = 0; j < BRICK_WIDTH; j++)
                {
                    for (int k = 0; k < BRICK_HEIGHT; k++)
                    {
                        display[bricks[i].x + j][bricks[i].y + k] = BRICK_CHAR;
                    }
                }
            }
        }

        // Update the score display
        mvprintw(0, 0, "Score: %d", score);

        // Refresh the screen
        refresh();

        // Sleep for a short amount of time to control game speed
        usleep(10000);
    }

    // End curses mode
    endwin();

    return 0;
}
