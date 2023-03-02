#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define ROWS 10
#define COLS 20
#define MOLES 5
#define MOLE_CHAR 'M'
#define HAMMER_CHAR 'H'

int main()
{
    // initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);

    // initialize random number generator
    srand(time(NULL));

    // initialize game state
    int score = 0;
    char board[ROWS][COLS];
    int mole_rows[MOLES], mole_cols[MOLES];
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
    for (i = 0; i < MOLES; i++)
    {
        mole_rows[i] = rand() % ROWS;
        mole_cols[i] = rand() % COLS;
        board[mole_rows[i]][mole_cols[i]] = MOLE_CHAR;
    }

    // main game loop
    while (1)
    {
        // clear screen and print board
        clear();
        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                mvaddch(i, j, board[i][j]);
            }
        }

        // print score
        mvprintw(ROWS + 1, 0, "Score: %d", score);

        // get user input
        int ch = getch();
        if (ch == KEY_LEFT)
        {
            board[ROWS - 1][0] = HAMMER_CHAR;
            refresh();
            napms(50);
            board[ROWS - 1][0] = ' ';
        }
        else if (ch == KEY_RIGHT)
        {
            board[ROWS - 1][COLS - 1] = HAMMER_CHAR;
            refresh();
            napms(50);
            board[ROWS - 1][COLS - 1] = ' ';
        }

        // move moles
        for (i = 0; i < MOLES; i++)
        {
            board[mole_rows[i]][mole_cols[i]] = ' ';
            mole_rows[i] = (mole_rows[i] + 1) % ROWS;
            mole_cols[i] = rand() % COLS;
            board[mole_rows[i]][mole_cols[i]] = MOLE_CHAR;
        }

        // check for hits
        for (i = 0; i < MOLES; i++)
        {
            if (board[ROWS - 1][mole_cols[i]] == HAMMER_CHAR)
            {
                score++;
                mole_rows[i] = rand() % ROWS;
                mole_cols[i] = rand() % COLS;
                board[mole_rows[i]][mole_cols[i]] = MOLE_CHAR;
            }
        }

        // check for game over
        if (score >= 10)
        {
            mvprintw(ROWS + 2, 0, "You win!");
            getch();
            break;
        }
        else if (score <= -5)
        {
            mvprintw(ROWS + 2, 0, "You lose!");
            getch();
            break;
        }

        // wait a bit
        refresh();
        napms(100);
    }

    // clean up ncurses
    endwin();

    // exit program
    return 0;
}

