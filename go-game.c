#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 19

typedef enum { EMPTY, BLACK, WHITE } player_t;

typedef struct {
    player_t board[BOARD_SIZE][BOARD_SIZE];
} game_t;

void init_game(game_t *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = EMPTY;
        }
    }
}

void print_board(game_t game) {
    printf("   ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (game.board[i][j]) {
                case BLACK:
                    printf(" B ");
                    break;
                case WHITE:
                    printf(" W ");
                    break;
                default:
                    printf(" . ");
                    break;
            }
        }
        printf("%2d\n", i);
    }
    printf("   ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
    }
    printf("\n");
}

bool is_valid_move(game_t game, int row, int col, player_t player) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    if (game.board[row][col] != EMPTY) {
        return false;
    }
    return true;
}

void make_move(game_t *game, int row, int col, player_t player) {
    game->board[row][col] = player;
}

int main() {
    game_t game;
    init_game(&game);

    player_t current_player = BLACK;

    while (true) {
        print_board(game);

        int row, col;
        printf("%s's turn (row col): ", current_player == BLACK ? "Black" : "White");
        scanf("%d %d", &row, &col);

        if (!is_valid_move(game, row, col, current_player)) {
            printf("Invalid move\n");
            continue;
        }

        make_move(&game, row, col, current_player);

        current_player = current_player == BLACK ? WHITE : BLACK;
    }

    return 0;
}
