#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grid_t_ {
	unsigned int grid[81];
	struct grid_t_ *next;
} grid_t;

typedef struct sub_t_ {
	int row;
	int col;
	int v[10];
} sub_t;

int load_grids(grid_t **result, const char *path)
{
	FILE *fh;
	char buffer[1024];
	grid_t *current = NULL, *next = NULL;
	int gridcount = 0, line = 0, pos = 0, i = 0;

	fh = fopen(path, "r");
	if (!fh) {
		return -1;
	}

	while (fgets(buffer, sizeof(buffer), fh) != NULL) {
		line++;

		if (strncmp(buffer, "Grid", 4) == 0) {
			next = current;
			current = (grid_t*)malloc(sizeof(grid_t));
			current->next = next;

			pos = 0;
			gridcount++;

			continue;
		}

		if (strlen(buffer) != 11) {
			fprintf(stderr, "invalid line of length %d\n", (unsigned int)strlen(buffer));
			continue;
		}

		for (i = 0; i < 9; i++, pos++) {
			if (pos >= 81) {
				fprintf(stderr, "invalid grid format at line %d\n", line);
				return -1;
			}
			current->grid[pos] = buffer[i] - '0';
		}
	}

	fclose(fh);

	*result = current;
	return gridcount;
}

void print_grid(grid_t *grid)
{
	int i, j, sum;
	for (i = 0; i < 9; i++) {
		sum = 0;
		for (j = 0; j < 9; j++) {
			printf("%d ", grid->grid[9*i+j]);
			sum += grid->grid[9*i+j];
		}
		printf("- %d\n", sum);
	}
}

int solve_grid(grid_t *grid, int level)
{
	grid_t g; // local copy
	int i, j, k, m; // counters
	sub_t currentsub;
	int solved = 0;
	int unsolved = 0; // number of unsolved slots
	int lastpass = 0, subs = 0;

	// copy the passed grid to avoid propagating incorrect
	// solutions upwards
	memcpy(&g, grid, sizeof(grid_t));

	// make all simple substitutions
	for (;;) {
		subs = 0;
		unsolved = 0;

		// iterate over all rows
		for (i = 0; i < 9; i++) {
			// iterate over all columns
			for (j = 0; j < 9; j++) {
				int box, sol, solcount;
				int v[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

				// skip slots that already have an assigned value
				if (g.grid[9*i+j] != 0) {
					continue;
				}

				// increment number of unsolved slots
				unsolved++;

				// eliminate all values occupied by other slots on this row
				for (k = 0; k < 9; k++) {
					v[g.grid[9*i+k]] = 0;
				}

				// eliminate values occupied by other slots in the same column
				for (k = 0; k < 9; k++) {
					v[g.grid[9*k+j]] = 0;
				}

				// finally, eliminate all slots occupied by values in the same 3x3 box
				box = 3*(i/3) + j/3;
				for (k = 3*(box/3); k < 3*(box/3)+3; k++) {
					for (m = 3*(box%3); m < 3*(box%3)+3; m++) {
						v[g.grid[9*k+m]] = 0;
					}
				}

				// count the number of possible values for this slot
				solcount = 0;
				sol = 0;
				for (k = 0; k < 10; k++) {
					if (v[k] != 0) {
						sol = v[k];
						solcount++;
					}
				}

				// if no possible values are found, there are no solutions
				if (solcount == 0) {
					return 0;
				}
				// if there is only one possible value, we substitute this value
				// into the grid
				else if (solcount == 1) {
					#ifdef DEBUG
						printf("unique substitution %d found at %d, %d\n", sol, i, j);
					#endif
					g.grid[i*9+j] = sol;
					subs++;
				}
				// otherwise just store a list of possible values until later
				// and try them until we find a solution.
				else {
					currentsub.row = i;
					currentsub.col = j;
					memcpy(&currentsub.v, v, sizeof(v));
				}
			}
		}

		// no possible substitutions remain, end loop
		if (subs == 0) {
			break;
		}
	}

	// permute solutions
	if (unsolved > 0) {
		for (i = 0; i < 10; i++) {
			if (currentsub.v[i] == 0) {
				continue;
			}

			g.grid[9*currentsub.row + currentsub.col] = currentsub.v[i];
			#ifdef DEBUG
				printf("%d: setting %d, %d to %d\n", level, currentsub.row, currentsub.col, currentsub.v[i]);
			#endif
			if (solve_grid(&g, level+1)) {
				solved = 1;
				break;
			}
		}
	} else {
		solved = 1;
	}


	if (!solved) {
		return 0;
	}

	// copy the final solution upwards the stack
	memcpy(grid, &g, sizeof(grid_t));

	return 1;
}

int main(int argc, char **argv)
{
	grid_t *grids, *current, *next;
	int gridcount;
	int i;

	if (argc != 2) {
		printf("usage: ./sudoku sudoku.txt\n");
		return 0;
	}

	gridcount = load_grids(&grids, argv[1]);
	if (gridcount == -1) {
		fprintf(stderr, "failed to open grid file.\n");
		return 1;
	}

	i = 0;
	for (current = grids; current != NULL; ) {
		printf("grid %d\n", i);
		print_grid(current);
		printf("\n");

		if (solve_grid(current, 0)) {
			print_grid(current);
		} else {
			printf("solution not found!\n");
		}

		printf("\n");

		next = current->next;
		free(current);
		current = next;
		i++;
	}

	return 0;
}
